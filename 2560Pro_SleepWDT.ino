#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>

unsigned int k;

ISR(WDT_vect) {
    k++;   
    wdt_reset();
}

void setup() {
//    if (MCUSR & _BV(WDRF)) {
//        MCUSR &= ~_BV(WDRF);
//        WDTCSR |= (_BV(WDCE) | _BV(WDE));
//        WDTCSR = 0x00;
//    }
    
    // config WDT
    cli();
    WDTCSR |= (_BV(WDCE) | _BV(WDE));
    WDTCSR = (_BV(WDIE) | _BV(WDP3) | _BV(WDP0)); // Enable WDT interrupt and set timeout         
    sei();
    Serial.begin(9600);
    Serial.println("Setup is running.");
    Serial.print("WDTCSR = ");
    Serial.println(WDTCSR);
    Serial.flush();
    // напоминалка для выставления времени задержки перед срабатыванием:
    //  16 мс:  0
    //  500 мс: _BV(WDP2) | _BV(WDP0)
    //  1 сек:  _BV(WDP2) | _BV(WDP1)
    //  2 сек:  _BV(WDP2) | _BV(WDP1) | _BV(WDP0)
    //  4 сек:  _BV(WDP3)
    //  8 сек:  _BV(WDP3) | _BV(WDP0)
    k = 0;
}

void loop() {
    if (k == 75) {
        cli();
        power_all_enable();
        Serial.println("Program is active.");
        Serial.print("k = ");
        Serial.println(k);
        Serial.print("WDTCSR = ");
        Serial.println(WDTCSR);
        Serial.flush();
        // main working cicle
        // WDT is active now
        // if main working cicle are demand more than 1s be remeber to include k = 0 and wdt_reset()(optional)
        k = 0;
    }
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    power_adc_disable();
    sei();
    sleep_cpu();
    sleep_disable();
}
