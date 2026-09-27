#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

#include "functions.h"


/**
 * Toggle LED, but skip every 11th time
 */
void toggle_led(int *count, bool *on){
        
    // Unless count is divisible by 11 toggle LED
    if ((int)(*count)++ % 11) *on = !(*on);


}

/**
 * Switch capitalization of a letter, return non letters
 */
char switch_capitalization(const char c){
        // Swap character's case if it is a letter
        if (c <= 'z' && c >= 'a') return (c - 32);
        else if (c >= 'A' && c <= 'Z') return (c + 32);
        
        // Output character
        else return c;
}