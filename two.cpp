#include <stdint.h>
#include <iostream>
#include <stdbool.h>

////////// DHT
#define DHT22 0
class DHT {
uint8_t tmp36_pin;
public:
    DHT(uint8_t tmp36_pin1, uint8_t) {
        tmp36_pin = tmp36_pin1;
    }

    float readTemperature(bool fahrenheit) {
        return ((((((analogRead(tmp36_pin1) * 5.0) / 1024.0) - .5) * 100) * 9.0)/ 5.0) + 32.0;
    }
};

int main() {
    DHT dht = DHT(1, DHT22);
    std::cout << dht.readTemperature(true) << std::endl;

}

//   lcd.print(((((((analogRead(A0) * 5.0) / 1024.0) - .5) * 100) * 9.0)/ 5.0) + 32.0);
