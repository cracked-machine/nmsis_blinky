#include <nuclei_sdk_soc.h>
#include <nuclei_sdk_hal.h>

int main()
{
    gd_led_init(LED1);

    while(1)
    {
        gd_led_on(LEDG);
        delay_1ms(2000);
        gd_led_off(LEDG);
        delay_1ms(2000);

    }
    return 0;
}