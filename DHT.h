#include <stdint.h>


#define DHT22 0
#define DHT11 0
class DHT {
uint8_t tmp36_pin;
public:
    DHT(uint8_t tmp36_pin1, uint8_t) {
        tmp36_pin = tmp36_pin1;
    }

    int readTemperature() {
        return readTemperature(true);
    }
    
    int readTemperature(bool fahrenheit) {
        return ((((((analogRead(tmp36_pin) * 5.0) / 1024.0) - .5) * 100) * 9.0)/ 5.0) + 32.0;
    }
};