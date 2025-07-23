/*  Basic non-blocking LED blink example for CH32V003
  	This example uses the SysTick timer to toggle an LED every 500 ms.
 	It demonstrates how to use the SysTick CNT register to measure time intervals.
*/

#include "funconfig.h"    // defines CH32V003 and optionally SYSTICK_USE_HCLK
#include "ch32v003fun.h"
#include <stdint.h>

#define LED_PIN   PC4
#define BLINK_MS  500


static inline uint32_t millis(void) {
    // Wrap the raw SysTick CNT register in a function named “millis”
    return SysTick->CNT;
}

int main(void) {
    // 1) Core & GPIO setup
    SystemInit();              // bring HCLK up to 48 MHz
    funGpioInitAll();          // enable GPIO clocks
    funPinMode(LED_PIN, GPIO_CFGLR_OUT_2Mhz_PP);	// set LED pin at 2MHz push-pull output

    // Capture the start-of-loop tick
    uint32_t last = millis();
    // Convert ticks to milliseconds
    const uint32_t interval = Ticks_from_Ms(BLINK_MS);

    // Main loop
    while (1) {
        if ((millis() - last) >= interval) {
            last += interval;	// schedule next toggle time
            funDigitalWrite(LED_PIN, !funDigitalRead(LED_PIN)); // toggle the LED state
        }
    }
}
