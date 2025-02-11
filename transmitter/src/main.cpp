#include <Arduino.h>
#include <CRC8.h>

#define TX D7

void setup() {
    Serial.begin(115200);
    pinMode(TX, OUTPUT);
}

CRC8 crc8(0x07, 0x84, 0x00, true, true);
// uint8_t group = 0x13;
// uint8_t crc = 0;

uint8_t a = 0;
uint8_t b = 22;
// bool on = false;

void loop() {
    Serial.println("Packet: " + String(a, HEX) + " " + String(b, HEX));
    // uint8_t data_orig[] = {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
    // 0,
    //                        1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1,
    //                        1};
    // Serial.println("Group" + String(group) + " CRC" + String(crc));
    // uint8_t data[] = {0xff, 0x31, 0x02, 0xBF, group, crc};
    // {0x5F, 0x23, 0x97, 0xFF, 0x13, 0xD6},
    uint8_t data[6] = {0x5F, a, b, 0xFF, 0x13, 0x68};
    // if (on) {
    //     data[1] = 0x23;
    // }

    uint8_t new_data[48] = {0};

    crc8.restart();
    for (int i = 0; i < 5; i++) {
        crc8.add(data[i]);
    }
    uint8_t crc = crc8.calc();
    data[5] = crc;

    // Create new data from data (reverse order)
    for (int i = 0; i < 6; i++) {
        for (int j = 7; j >= 0; j--) {
            new_data[i * 8 + 7 - j] = (data[i] >> j) & 1;
        }
    }

    // // Check original data with new data
    // bool is_same = true;
    // for (int i = 0; i < 48; i++) {
    //     if (data_orig[i] != new_data[i]) {
    //         is_same = false;
    //         break;
    //     }
    // }
    // Serial.println(is_same ? "Same" : "Different");

    for (int i = 0; i < 2; i++) {
        digitalWrite(TX, LOW);
        delayMicroseconds(550);
        digitalWrite(TX, HIGH);
        delayMicroseconds(550);
        for (int i = 0; i < 48; i++) {
            digitalWrite(TX, LOW);
            delayMicroseconds(220);
            digitalWrite(TX, HIGH);
            delayMicroseconds(new_data[i] ? 380 : 220);
        }
    }
    // if (crc == 0xFF) {
    //     group++;
    // }
    // crc++;
    // crc++;
    if (a == 255) {
        b++;
    };
    a++;

    // if (a > 40) {
    //     a = 20;
    // }
    // on = !on;
    // digitalWrite(TX, LOW);
    // delayMicroseconds(100000);
}
