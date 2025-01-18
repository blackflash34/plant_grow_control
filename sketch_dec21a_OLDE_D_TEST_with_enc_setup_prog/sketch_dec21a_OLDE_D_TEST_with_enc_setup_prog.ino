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


int start_time_h = 0; //hour
int light_day_long = 0; //hour
int click_counter = 0;
int poliv_interval = 0; //hour
int poliv_duration = 0; //seconds
bool yn_checker = false;

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
  eb.setTimeout(100);

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
  start_setup();
  if (eb.left()) {
    Serial.println("LEFT");
  }
  if (eb.right()) {
    Serial.println("RIGHT");
  }

}

void intro() {
  display.clearDisplay();

  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(30,0);             // Start at top-left corner
  display.println(F("System"));
  display.setCursor(40,16); 
  display.println(F("start"));

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
void reaction_int(const char* word, int num) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(word);
  display.setCursor(0, 16);
  display.println(num);
  display.display();
}

void screensaver() {

  display.clearDisplay();
  display.setTextSize(1);
  for(int16_t i = 0; i< 128; i++) {
    display.setCursor(i, 0);
    display.println(F("."));
    display.display();
    delay(1000);
    display.clearDisplay();
  }

}

void start_setup() {
  if (eb.click()) {
    click_counter +=1;
  }
  
  if (click_counter == 0) {
    reaction_int("Start time:", start_time_h);
    if (eb.right()) {
      start_time_h += 1;
    }
    if (eb.left()) {
      start_time_h -= 1;
    }
    if (start_time_h < 0) {
      start_time_h = 23;
    }
    if (start_time_h > 23) {
      start_time_h = 0;
    }
  }
  if (click_counter == 1) {
    Serial.print("Start_cycle_time: ");
    Serial.println(start_time_h);
    reaction_int("Light cycle:", light_day_long);
    if (eb.right()) {
      light_day_long += 1;
    }
    if (eb.left()) {
      light_day_long -= 1;
    }
    if (light_day_long < 0) {
      light_day_long = 23;
    }
    if (light_day_long> 23) {
      light_day_long = 0;
    }
  }
  if (click_counter == 2) {
    reaction_int("Waterin interval:", poliv_interval);
    if (eb.right()) {
      poliv_interval += 1;
    }
    if (eb.left()) {
      poliv_interval -= 1;
    }
    if (light_day_long < 0) {
      light_day_long = 0;
    }
  }
  if (click_counter == 3) {
    reaction_int("Waterin duration:", poliv_duration);
    if (eb.right()) {
      poliv_duration += 1;
    }
    if (eb.left()) {
      poliv_duration -= 1;
    }
    if (poliv_duration < 0) {
      poliv_duration = 0;
    }
  }

  if (click_counter == 4) {
    display.clearDisplay();
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(30,0);             // Start at top-left corner
    display.println(F("Setup complete?"));

    if (eb.left()) yn_checker = true;
    if (eb.right()) yn_checker = false;
    if (yn_checker == false) {
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      display.setCursor(20,16);             // Start at top-left corner
      display.println(F("Yes"));
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(70,16);             // Start at top-left corner
      display.println(F("No"));
    }
    else{
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(20,16);             // Start at top-left corner
      display.println(F("Yes"));
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      display.setCursor(70,16);             // Start at top-left corner
      display.println(F("No"));
    }
    display.display();
  }

}
