#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"      // nova inclusão para PWM
#include "hardware/gpio.h"     // nova inclusão para configuração de GPIO

int main()
{
    stdio_init_all();

    // Configurar GPIO 22 para saída PWM (servo motor)
    gpio_set_function(22, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(22);
    pwm_set_clkdiv(slice_num, 100.0f);           // ajuste para 50Hz com wrap de 25000
    pwm_set_wrap(slice_num, 25000);              // define o período (20ms)
    // Ajustar ciclo ativo para 2.400µs (aproximadamente 3 ticks) para posicionar o servo em 180°
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(22), 3);
    pwm_set_enabled(slice_num, true);
    sleep_ms(5000); // aguardar 5 segundos com a posição

    // Configurar GPIO 12 como saída digital para o LED RGB
    gpio_init(12);
    gpio_set_dir(12, GPIO_OUT);

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
