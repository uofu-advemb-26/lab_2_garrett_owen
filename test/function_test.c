#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"


#include "functions.h"

void setUp(void) {}

void tearDown(void) {}

void test_switch_capitalization(){
    char c = 'a';

    char ret;

    ret = switch_capitalization(c);

    TEST_ASSERT_TRUE_MESSAGE(ret = 'A', "capitalization failed");

    c = 'A';
    ret = switch_capitalization(c);
    TEST_ASSERT_TRUE_MESSAGE(ret = 'a', "un-capitalization failed");

    c = '1';
    ret = switch_capitalization(c);
    TEST_ASSERT_TRUE_MESSAGE(ret = '1', "special character failed");


}

void test_toggle_led(){

    int count = 1;
    bool on = false;
    bool prev_on = false;
    
    for(int i = 1; i < 9; i++){
        prev_on = on;
        toggle_led(&count, &on);
        TEST_ASSERT_TRUE_MESSAGE(count == (i + 1) , "Counting failed.");
        TEST_ASSERT_TRUE_MESSAGE(prev_on != on, "Toggling failed");
    }


}


int main (void)
{
    stdio_init_all();
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
