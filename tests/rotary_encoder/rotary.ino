#include <common.h>

void setup() {
    setupPins();
}

void loop() {
    static uint8_t pas_CLK = 0;
    static uint8_t pas_DT = 0;
    static uint8_t count = 0;
    uint8_t CLK = digitalRead(pinCLK);
    uint8_t DT = digitalRead(pinDT);

    if (CLK != pas_CLK && CLK == 0) {
        if (pas_DT | DT == HIGH) {
            if (count == 0) count = 9;
            else count--;

            debug("Counter clockwise");
            debug(count);
        } else {
            count++;
            count %= 10;

            debug("Clockwise");
            debug(count);
        }
    }
}