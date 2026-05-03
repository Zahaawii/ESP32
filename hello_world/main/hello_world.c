#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"
#include <unistd.h>

#define LED_GPIO 4
#define LED_COUNT 64


/*
(0,0) = top-left
(7,0) = top-right
(0,7) = bottom-left
(7,7) = bottom-right
*/


// Helper function to get the index position of the board
int get_index(int x, int y)
{
    if (y % 2 == 0)
    {
        return y * 8 + (7 - x);
    }
    else
    {
        return y * 8 + x;
    }
}

// Helper function to set the data easier, variable strip is just strip, x for the x axes, y for the y axes, r = red, g = green, b = blue
void set_xy(led_strip_handle_t strip, int x, int y, int r, int g, int b)
{
    led_strip_set_pixel(strip, get_index(x, y), r, g, b);
}

void app_main(void)
{
    led_strip_handle_t strip;

    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_GPIO,
        .max_leds = LED_COUNT,
    };

    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000, // 10 MHz
    };

    led_strip_new_rmt_device(&strip_config, &rmt_config, &strip);

    // Turn everything off first
    led_strip_clear(strip);

    // Turn LED 0 RED (low brightness)
    for (int i = 0; i < 64; i++)
    {
        // Clear the strip
        led_strip_clear(strip);
        // turn ONE on
        led_strip_set_pixel(strip, i, 16, 0, 0); 
        printf("Flashing light number: %i\n", i);
         // send data
        led_strip_refresh(strip);     
         // wait 
        vTaskDelay(pdMS_TO_TICKS(200));
    }

    printf("Testing (0,0)\n");
    // Clear the strip
    led_strip_clear(strip);
    // Turn one light on 
    led_strip_set_pixel(strip, get_index(0, 0), 16, 0, 0);
    // Send the light data to the board
    led_strip_refresh(strip);
    vTaskDelay(pdMS_TO_TICKS(1000));
    

    printf("Testing (7,0)\n");
    led_strip_clear(strip);
    led_strip_set_pixel(strip, get_index(7, 0), 16, 0, 0);
    led_strip_refresh(strip);
    vTaskDelay(pdMS_TO_TICKS(1000));

    printf("Testing (0,7)\n");
    led_strip_clear(strip);
    led_strip_set_pixel(strip, get_index(0, 7), 16, 0, 0);
    led_strip_refresh(strip);
    vTaskDelay(pdMS_TO_TICKS(1000));

    printf("Testing (7,7)\n");
    led_strip_clear(strip);
    led_strip_set_pixel(strip, get_index(7, 7), 16, 0, 0);
    led_strip_refresh(strip);
    vTaskDelay(pdMS_TO_TICKS(1000));
    

    
    // Helper function to set the data easier, variable strip is just strip, x for the x axes, y for the y axes, r = red, g = green, b = blue
    led_strip_clear(strip);
    printf("x = 0, y = 0\n");
    set_xy(strip, 0, 0, 16, 0, 0);
    led_strip_refresh(strip);
    set_xy(strip, 1, 0, 16, 0, 0);
    printf("x = 1, y = 0\n");
    led_strip_refresh(strip);
    set_xy(strip, 2, 0, 16, 0, 0);
    printf("x = 2, y = 0\n");
    led_strip_refresh(strip);

    // Typing HI on the board
    led_strip_clear(strip);
    set_xy(strip, 1, 3, 16, 0, 0);
    set_xy(strip, 1, 4, 16, 0, 0);
    set_xy(strip, 1, 5, 16, 0, 0);
    set_xy(strip, 2, 4, 16, 0, 0);
    set_xy(strip, 3, 3, 16, 0, 0);
    set_xy(strip, 3, 4, 16, 0, 0);
    set_xy(strip, 3, 5, 16, 0, 0);
    set_xy(strip, 5, 3, 16, 0, 0);
    set_xy(strip, 5, 4, 16, 0, 0);
    set_xy(strip, 5, 5, 16, 0, 0);
    led_strip_refresh(strip);
  

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

