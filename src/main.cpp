#include <Arduino.h>
#include <Preferences.h>
#include <SPI.h>

#include <DisplaySelection.h>

#include "Test3Page.cpp"

Preferences storage;

void initStorage() {
    if (!storage.begin("storage", false)) {
        Serial.println("Failed to open storage");
    }
}


void setup() {
    Serial.begin(115200);
    Serial.println("setup");
    display.init(115200);

    // 处理 微雪 ESP32 e-page 驱动板 spi 设置的问题
    // ********************************************************* //
    SPI.end(); // release standard SPI pins, e.g. SCK(18), MISO(19), MOSI(23), SS(5)
    // SPI: void begin(int8_t sck=-1, int8_t miso=-1, int8_t mosi=-1, int8_t ss=-1);
    SPI.begin(13, 12, 14, 15);
    // map and init SPI pins SCK(13), MISO(12), MOSI(14), SS(15)
    // *** end of special handling for Waveshare ESP32 Driver board *** //

    initStorage();

    Serial.println("Test3Page init");

    Test3Page page(display);
    page.display();
    // drawScreen();
}

int16_t screen = 0;
int16_t delayScreen = 0;

void loop() {
    // delay(1000);

    // delayScreen++;
    // if (delayScreen > 10)
    // {
    //     delayScreen = 0;
    //     screen++;

    //     if (screen > 1)
    //     {
    //         screen = 0;
    //     }

    //     drawScreen();
    // }
}


