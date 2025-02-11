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
    pwm_set_wrap(slice_num, 25000);              // define o período (ajuste conforme necessário)
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(22), 1500); // duty cycle padrão para servo
    pwm_set_enabled(slice_num, true);

    // Configurar GPIO 12 como saída digital para o LED RGB
    gpio_init(12);
    gpio_set_dir(12, GPIO_OUT);

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
