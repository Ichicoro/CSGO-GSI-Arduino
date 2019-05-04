#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "ssd1307_128x64_i2c.h"
#include <GameState.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET         -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
GameState gs;

int magAmmo = 15;
int maxAmmo = 0;
unsigned long last250msLoop = 0;
// int magSize = 150;

const unsigned char PROGMEM heart[] = {
    B01101100,
    B11111110,
    B11111110,
    B11111110,
    B01111100,
    B00111000,
    B00010000
};

const unsigned char PROGMEM down_arrow[] = {
    B11111000,
    B01110000,
    B00100000
};

int serial_val = -1;
int health = 53;

void setup() {
    Serial.begin(115200);
    gs = GameState();

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
	    Serial.println(F("SSD1306 allocation failed"));
	    for(;;); // Don't proceed, loop forever
    }
    display.clearDisplay();
    display.setRotation(2);

    // display.setTextColor(WHITE);
    // display.drawRoundRect(0,0,128,64,5,WHITE);
    // drawOwO();
    // display.display();
    // delay(1500);
}

void loop() {
    // if (Serial.available() > 0) {
    //     String serial = Serial.readString();
    //     // Serial.print("oof " + serial);
    //     if (isNumber(serial)) {
    //         int num = serial.toInt();
    //         health = constrain(num, 0, 100);
    //     }
    // }

    String serial = Serial.readStringUntil('\n');
    if (serial.length() != 0) {
        // String serial;
        // while (Serial.peek() != '\n') {
        //     serial += Serial.read();
        // }
        // Serial.println("Uh: " + serial);
        // Serial.flush();
        int serial_status = gs.update(serial);
        if (serial_status == 0) {
            // Serial.print("Ok!");
        } else {
            // Serial.print("Oof! Reason -> " + String(serial_status));
        }
    }
    
    display.clearDisplay();

    if (true) {
        drawHealthBar(WHITE);
        drawArmorBar(WHITE);
        drawAmmo(WHITE);
        drawGunName(WHITE);
        drawMoney(WHITE);
    }

    display.setCursor(100, 32);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.print(millis() % 100);

    display.display();
}

void drawOwO() {
    display.setTextSize(3);
    display.setCursor(37,12);
    display.print("OwO");

    display.setTextSize(1);
    display.setCursor(30,42);
    display.print("whats this?");
}

void drawUI() {
    display.drawRoundRect(0,0,128,64,7,WHITE);
    display.fillRoundRect(0,0,128,16,7,WHITE);
    display.fillRect(0,10,128,6,WHITE);
}

// void drawHealthBar() { return drawHealthBar(BLACK); }
void drawHealthBar(int16_t color) {
    int health = gs.health;
    display.setTextColor(color);
    display.setTextSize(1);
    
    display.setCursor(0, 0);
    display.print("H");

    int xPadding = 0;
    int maxWidth = 128-xPadding*2-31;
    drawABar(9, 0, maxWidth, 7, health, color);

    display.setCursor(128-xPadding*2-30+12, 0);
    display.print((health >= 100 ? "MAX" : String(health) + "%"));
}

void drawArmorBar(int16_t color) {
    int armor = gs.armor;
    display.setTextColor(color);
    display.setTextSize(1);
    
    display.setCursor(0, 57);
    display.print("A");

    int xPadding = 0;
    int maxWidth = 128-xPadding*2-31;
    display.setCursor(0,0);
    drawCheckeredBar(9, 57, maxWidth, 7, gs.armor, color);

    display.setCursor(128-xPadding*2-30+12, 57);
    display.print((armor >= 100 ? "MAX" : String(gs.armor) + "%"));
}

void drawAmmo(int16_t color) {
    int magAmmo = gs.clip_ammo;
    int magLen = getTextSize(String(magAmmo),3);
    display.setTextColor(color);

    // Draw ammo in the mag
    display.setTextSize(4);
    display.setCursor(5,9+5);
    display.print(magAmmo);

    // Draw backup ammo
    display.setTextSize(2);
    display.setCursor(5+magLen+15,9+5+21-1*7);
    display.print(gs.reserve_ammo);
}

void drawGunName(int16_t color) {
    int magSize = gs.clip_ammo;
    String weaponName = "GESU'";
    int magLen = getTextSize(String(magSize),3);
    int weaponNameLen = getTextSize(weaponName, 1);
    int inv_color = color==WHITE ? BLACK : WHITE;
    display.setTextColor(inv_color);
    display.setTextSize(1);
    int16_t pos = 5+magLen+17;

    // Draw white square
    display.fillRect(pos, 9+5, 2+weaponNameLen, 11, color); // la lunghezza era 30, o 21

    // Draw heart
    // display.drawBitmap(pos+2, 9+5+2, heart, 8, 7, inv_color);

    // Draw ammo in the mag
    display.setCursor(pos+2,9+5+2); // x+9
    display.print(weaponName);
}

void drawMoney(int16_t color) {
    display.setTextColor(color);
    display.setTextSize(1);
    display.setCursor(5, 9+5+3+28);
    display.print("MONEY $4100");
}

void drawBar(int16_t x, int16_t y, int16_t w, int16_t h, int16_t value, int16_t color) {
    display.drawRect(x, y, w, h, color);
    display.fillRect(x+2, y+2, map(constrain(value, 0, 100), 0, 100, 0, w-4), h-4, color);
}

void drawABar(int16_t x, int16_t y, int16_t w, int16_t h, int16_t value, int16_t color) {
    display.drawRect(x, y, w, h, color);
    display.fillRect(x, y, map(constrain(value, 0, 100), 0, 100, 0, w), h, color);
}

void drawCheckeredBar(int16_t x, int16_t y, int16_t w, int16_t h, int16_t value, int16_t color) {
    drawCheckeredRect(x, y, w, h, color);
    fillCheckeredRect(x, y, map(constrain(value, 0, 100), 0, 100, 0, w), h, color);
}

void drawCheckeredRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t color) {
    int inv_color = color==WHITE ? BLACK : WHITE;
    for (int i=x; i<x+w; i++) {
        for (int j=y; j<y+h; j++) {
            if ((j == y || j == y+h-1) || (i == x || i == x+w-1)) {
                if ((i%2==1 && j%2==1) || (i%2==0 && j%2==0)) {
                    display.drawPixel(i, j, color);
                } else {
                    display.drawPixel(i, j, inv_color);
                }
            }
        }
    }
}

void fillCheckeredRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t color) {
    int inv_color = color==WHITE ? BLACK : WHITE;
    for (int i=x; i<x+w; i++) {
        for (int j=y; j<y+h; j++) {
            if ((i%2==1 && j%2==1) || (i%2==0 && j%2==0)) {
                display.drawPixel(i, j, color);
            } else {
                display.drawPixel(i, j, inv_color);
            }
        }
    }
}

int16_t getTextSize(String s, int size) {
    return s.length() * (size*6) + size; 
}
