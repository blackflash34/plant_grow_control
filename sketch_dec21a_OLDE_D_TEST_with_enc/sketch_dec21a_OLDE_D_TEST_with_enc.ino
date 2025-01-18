#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Arduino.h>
#include <EncButton.h>
EncButton eb(14, 2, 0);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };

void setup() {
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever

  eb.setBtnLevel(LOW);
  eb.setClickTimeout(500);
  eb.setDebTimeout(50);
  eb.setHoldTimeout(600);
  eb.setStepTimeout(200);
  eb.setTimeout(1000);

  eb.setEncReverse(0);
  eb.setEncType(EB_STEP4_LOW);
  eb.setFastTimeout(30);
  // сбросить счётчик энкодера
  eb.counter = 0;
  
  
  }

  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();

  display.drawPixel(10, 10, SSD1306_WHITE);
  display.display();
  delay(2000);

  intro();      // Draw many lines
  //screensaver();
  // Invert and restore display, pausing in-between
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);

}

void loop() {
  eb.tick();
  if (eb.left()) {
    reaction("left");
    Serial.println("left");
  }
  if (eb.right()) {
    reaction("right");
    Serial.println("right");
  }
  if (eb.leftH()) Serial.println("leftH");
  if (eb.rightH()) Serial.println("rightH");
  // кнопка
  if (eb.press()) Serial.println("press");
  if (eb.click()) Serial.println("click");
  if (eb.hold()) Serial.println("hold");
}

void intro() {
  display.clearDisplay();

  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("System start"));

  display.display();
  delay(2000);
}

void reaction(const char* word) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(word);
  display.display();
}

void screensaver() {
  
  display.clearDisplay();
  display.setTextSize(1);
  for(int16_t i = 0; i< 128; i++) {
    display.setCursor(i, 0);
    display.println(F("."));
    display.display();
    delay(2000);
    display.clearDisplay();
  }

}