#include <stdio.h>
#include <stdbool.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <pico/cyw43_arch.h>
#include <unity.h>
#include "unity_config.h"


#include "functions.h"

void setUp(void) {}

void tearDown(void) {}

void test_switch_capitalization(){
    // Lowercase -> uppercase
    TEST_ASSERT_EQUAL_CHAR_MESSAGE('A', switch_capitalization('a'), "capitalization failed");
    TEST_ASSERT_EQUAL_CHAR_MESSAGE('B', switch_capitalization('b'), "capitalization failed");
    TEST_ASSERT_EQUAL_CHAR_MESSAGE('Y', switch_capitalization('y'), "capitalization failed");
    TEST_ASSERT_EQUAL_CHAR_MESSAGE('Z', switch_capitalization('z'), "capitalization failed");

    // Uppercase -> lowercase
    TEST_ASSERT_EQUAL_CHAR_MESSAGE('a', switch_capitalization('A'), "un-capitalization failed");
    TEST_ASSERT_EQUAL_CHAR_MESSAGE('b', switch_capitalization('B'), "un-capitalization failed");
    TEST_ASSERT_EQUAL_CHAR_MESSAGE('y', switch_capitalization('Y'), "un-capitalization failed");
    TEST_ASSERT_EQUAL_CHAR_MESSAGE('z', switch_capitalization('Z'), "un-capitalization failed");

    // Non-letters unchanged
    TEST_ASSERT_EQUAL_CHAR_MESSAGE('!', switch_capitalization('!'), "special character failed");
    TEST_ASSERT_EQUAL_CHAR_MESSAGE('@', switch_capitalization('@'), "special character failed");
    TEST_ASSERT_EQUAL_CHAR_MESSAGE('1', switch_capitalization('1'), "special character failed");
}

void test_toggle_led(){
    int count = 0;
    bool on = 0;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    for (int i = 0; i < 200; i += 1) {
        int curr_count = count;
        bool prev_on = on;
        toggle_led(&count, &on);
        int gpio = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN);
        TEST_ASSERT_EQUAL_MESSAGE(gpio, on, "GPIO should be set to the state of 'on' variable.");
        TEST_ASSERT_EQUAL_MESSAGE(count, curr_count +1, "Always increment the count");
        if (curr_count % 11) {
            TEST_ASSERT_NOT_EQUAL_MESSAGE(prev_on, on, "Should toggle when count is not a multiple of 11.");
        } else {
            TEST_ASSERT_EQUAL_MESSAGE(prev_on, on, "Should not toggle otherwise.");
        }
    }
}


int main (void)
{
    stdio_init_all();
    hard_assert(cyw43_arch_init() == PICO_OK);  // Required before using the LED (CYW43) GPIO
    while (1) {
        sleep_ms(5000); // Give time for TTY to attach.
        printf("Start tests\n");
        UNITY_BEGIN();

        RUN_TEST(test_toggle_led);
        RUN_TEST(test_switch_capitalization);

        sleep_ms(5000);
        UNITY_END();
    }
}
