
# Test Scenario Setup

Use UNITY test library and connect device over USB.

Use flash_test to build and flash test.

# Test Exercise

## Blinking Task Test

Tests the blinking logic by calling blink_task()

This toggles the LED when !(count % 11) so we want to ensure that this behavior is correct

- Mocks the cyw43_arch_gpio_put() funciton
- Mocks hard_assert()
- Mocks cyw43_arch_init()
- Mocks vTaskDelay()
- Test the divide by 11 functionality
- Does not test timing
## Main Task Test

Tests the main task logic by calling main_task()

The main logic switches the capilization of a char when it it a valid english letter.

- Mocks xTaskCreate()
- Mocks getchar()
- Mocks putchar
- Tests character input and output

# Expected Behavior

Device outputs over USB:

Blinking Task Test Passed

Main Task Test Passed