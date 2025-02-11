#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"

// -------------------- MACROS --------------------
#define PINO_SERVO        22
#define PINO_LED          12

#define PWM_FREQUENCY     50                  // 50 Hz => período de 20 ms
#define SYSTEM_CLOCK      125000000UL         // 125 MHz
#define PWM_CLKDIV        64.0f               // Divisor de clock do PWM

// Cálculo do wrap (número máximo de ticks)
#define PWM_WRAP          ((uint16_t)(SYSTEM_CLOCK / (PWM_FREQUENCY * PWM_CLKDIV)))

// Posições do servo: porcentagens de duty (baseadas em 20ms)
// 0°: 2.5%  | 90°: 7.35% | 180°: 12%
#define POSICAO_0_GRAUS   ((uint16_t)(PWM_WRAP * 2.5f / 100))
#define POSICAO_90_GRAUS  ((uint16_t)(PWM_WRAP * 7.35f / 100))
#define POSICAO_180_GRAUS ((uint16_t)(PWM_WRAP * 12.0f / 100))

// Incremento de 5 µs convertido para ticks (tick_time = PWM_CLKDIV/SYSTEM_CLOCK * 1e6)
#define STEP_US           5.0f
#define TICK_US           (PWM_CLKDIV/(float)SYSTEM_CLOCK*1e6f)
#define STEP_TICKS        ((uint16_t)(STEP_US / TICK_US))
#define STEP_DELAY_MS     10  // tempo entre pequenos incrementos (ms)

// -------------------- FUNÇÕES --------------------
void configurar_pwm(uint pino, uint16_t nivel_inicial) {
    gpio_set_function(pino, GPIO_FUNC_PWM);
    uint fatia = pwm_gpio_to_slice_num(pino);
    uint canal = pwm_gpio_to_channel(pino);
    pwm_set_clkdiv(fatia, PWM_CLKDIV);
    pwm_set_wrap(fatia, PWM_WRAP);
    pwm_set_chan_level(fatia, canal, nivel_inicial);
    pwm_set_enabled(fatia, true);
}

void ajustar_posicao_servo(uint pino, uint16_t pulso) {
    uint fatia = pwm_gpio_to_slice_num(pino);
    uint canal = pwm_gpio_to_channel(pino);
    pwm_set_chan_level(fatia, canal, pulso);
}

void ajustar_brilho_led(uint pino, uint16_t brilho) {
    uint fatia = pwm_gpio_to_slice_num(pino);
    uint canal = pwm_gpio_to_channel(pino);
    pwm_set_chan_level(fatia, canal, brilho);
}

// -------------------- MAIN --------------------
int main() {
    stdio_init_all();
    sleep_ms(2000); // Aguarda inicialização dos módulos

    // Print de início do sistema
    printf("🔵 Sistema Iniciado: Controle de Servomotor por PWM\n");

    // Configurar PWM para o servo e LED
    configurar_pwm(PINO_SERVO, POSICAO_90_GRAUS); // inicia em 90°
    configurar_pwm(PINO_LED, 0);                  // LED inicia com brilho 0

    // Etapa 1: Servo para 180° (2400 µs) e LED no máximo
    ajustar_posicao_servo(PINO_SERVO, POSICAO_180_GRAUS);
    ajustar_brilho_led(PINO_LED, PWM_WRAP); // brilho máximo
    printf("🔴 [180°] Servo Posicionado | PWM: %d | LED: LIGADO 🔴\n", POSICAO_180_GRAUS);
    sleep_ms(5000);

    // Etapa 2: Servo para 90° (1470 µs) e LED intermediário
    ajustar_posicao_servo(PINO_SERVO, POSICAO_90_GRAUS);
    ajustar_brilho_led(PINO_LED, PWM_WRAP / 2);
    printf("🟡 [90°] Servo Posicionado | PWM: %d | LED: 50%%\n", POSICAO_90_GRAUS);
    sleep_ms(5000);

    // Etapa 3: Servo para 0° (500 µs) e LED baixo
    ajustar_posicao_servo(PINO_SERVO, POSICAO_0_GRAUS);
    ajustar_brilho_led(PINO_LED, PWM_WRAP / 4);
    printf("🟢 [0°] Servo Posicionado | PWM: %d | LED: 25%%\n", POSICAO_0_GRAUS);
    sleep_ms(5000);

    // Aviso de início da transição suave
    printf("⚙️ Iniciando transição suave entre 0° e 180°\n");

    // Etapa 4: Transição suave entre 0° e 180°
    // Subida: de 0° para 180°
    for (uint16_t pulso = POSICAO_0_GRAUS; pulso <= POSICAO_180_GRAUS; pulso += STEP_TICKS) {
        ajustar_posicao_servo(PINO_SERVO, pulso);
        uint16_t brilho = (uint16_t)(((float)(pulso - POSICAO_0_GRAUS) * PWM_WRAP) / (POSICAO_180_GRAUS - POSICAO_0_GRAUS));
        ajustar_brilho_led(PINO_LED, brilho);
        // Print interativo durante a subida
        printf("↗ Subindo: PWM = %d | Brilho = %d\n", pulso, brilho);
        sleep_ms(STEP_DELAY_MS);
    }
    // Descenso: de 180° para 0°
    for (uint16_t pulso = POSICAO_180_GRAUS; pulso >= POSICAO_0_GRAUS; pulso -= STEP_TICKS) {
        ajustar_posicao_servo(PINO_SERVO, pulso);
        uint16_t brilho = (uint16_t)(((float)(POSICAO_180_GRAUS - pulso) * PWM_WRAP) / (POSICAO_180_GRAUS - POSICAO_0_GRAUS));
        ajustar_brilho_led(PINO_LED, brilho);
        // Print interativo durante a descida
        printf("↘ Descendo: PWM = %d | Brilho = %d\n", pulso, brilho);
        sleep_ms(STEP_DELAY_MS);
    }
    
    // Transição suave periódica
    while (true) {
        for (uint16_t pulso = POSICAO_0_GRAUS; pulso <= POSICAO_180_GRAUS; pulso += STEP_TICKS) {
            ajustar_posicao_servo(PINO_SERVO, pulso);
            uint16_t brilho = (uint16_t)(((float)(pulso - POSICAO_0_GRAUS) * PWM_WRAP) / (POSICAO_180_GRAUS - POSICAO_0_GRAUS));
            ajustar_brilho_led(PINO_LED, brilho);
            printf("↗ Transição: PWM = %d | Brilho = %d\n", pulso, brilho);
            sleep_ms(STEP_DELAY_MS);
        }
        for (uint16_t pulso = POSICAO_180_GRAUS; pulso >= POSICAO_0_GRAUS; pulso -= STEP_TICKS) {
            ajustar_posicao_servo(PINO_SERVO, pulso);
            uint16_t brilho = (uint16_t)(((float)(POSICAO_180_GRAUS - pulso) * PWM_WRAP) / (POSICAO_180_GRAUS - POSICAO_0_GRAUS));
            ajustar_brilho_led(PINO_LED, brilho);
            printf("↘ Transição: PWM = %d | Brilho = %d\n", pulso, brilho);
            sleep_ms(STEP_DELAY_MS);
        }
    }
}
