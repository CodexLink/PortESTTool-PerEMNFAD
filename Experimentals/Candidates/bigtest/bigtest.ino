#include <SPI.h>
#include <Adafruit_GFX.h>
#include "TFT_ILI9163C.h"

// Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

/*
Teensy3.x and Arduino's
You are using 4 wire SPI here, so:
 MOSI:  11//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
 MISO:  12//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
 SCK:   13//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
 the rest of pin below:
 */
#define SDA_MOSI
#define __CS D6
#define __DC D8
/*
Arduino MEGA

MISO-pin 50
MOSI-pin 51
SCK-  Pin 52
SS-    pin 53

Teensy 3.x can use: 2,6,9,10,15,20,21,22,23
Arduino's 8 bit: any
DUE: check arduino site
If you do not use reset, tie it to +3V3
*/

TFT_ILI9163C display = TFT_ILI9163C(__CS, __DC);

float p = 3.1415926;

void setup(void)
{
  Serial.begin(9600);
  display.begin();

  uint16_t time = millis();
  time = millis() - time;

  //  lcdTestPattern();
  //  delay(1000);

  display.clearScreen();
  Serial.println(F("Showing Setup...."));
  digitalWrite(8, HIGH);
  delay(1000);
  digitalWrite(8, LOW);
  display.clearScreen();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(YELLOW);
  display.print("---------------------");
  display.setCursor(display.width() / 6, 15);
  display.setTextSize(2);
  display.setTextColor(YELLOW);
  display.print("GeM-ESSAC");

  display.setTextSize(1);
  display.setTextColor(CYAN);

  display.setCursor(display.width() / 12, 40);
  display.print("Internet of Things");
  display.setCursor(display.width() / 9, 50);
  display.print("Multi - Essential");
  display.setCursor(display.width() / 12, 60);
  display.print("Sensing Components");
  display.setTextColor(RED);
  display.println(" ");
  display.setCursor(display.width() / 7, 75);
  display.print("Version Unknown");
  display.setCursor(display.width() / 4, 90);
  display.setTextColor(YELLOW);
  display.print("Created by");
  display.setCursor(display.width() / 24, 100);
  display.print("Janrey | 'CodexLink'");
  display.setTextColor(YELLOW);
  display.setTextSize(1);
  display.setCursor(0, display.height());
  display.println(" ");
  display.println(" ");
  display.print("---------------------");
  Serial.println(F("Show Setup Done."));
  display.clearScreen();
  Serial.println(F("Display Clear Screen"));
  testfillcircles(10, BLUE);
  Serial.println(F("Test Fill Circles 10, BLUE"));
  testdrawcircles(10, WHITE);
  Serial.println(F("Test Draw Circles 10, WHITE"));
  delay(1000);

  testroundrects();
  Serial.println(F("Test Round Rects"));
  delay(500);

  testtriangles();
  Serial.println(F("Test Triangles"));
  delay(500);

  display.clearScreen();
  display.setCursor(0, 0);
  display.print("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa");
  delay(1000);

  tftPrintTest();
  delay(2000);

  //a single pixel
  display.drawPixel(display.width() / 2, display.height() / 2, GREEN);
  delay(500);

  // line draw test
  testlines(YELLOW);
  Serial.println(F("Test Lines Yellow"));
  delay(500);

  // optimized lines
  testfastlines(RED, BLUE);
  Serial.println(F("Test Fast Lines Red and Blue"));
  delay(500);

  testdrawrects(GREEN);
  Serial.println(F("Test Draw Rects GREEN"));
  delay(1000);

  testfillrects(BLUE, YELLOW);
  Serial.println(F("Test Fill Rects BLUE, YELLOW"));
  delay(1000);

  randomRect(0);
  Serial.println(F("Random Rect 0"));
  delay(100);
  randomCircles(0);
  Serial.println(F("Random Circles 0"));
  delay(100);
  randomLines();
  Serial.println(F("Random Lines 0"));
  delay(100);
  randomPoints();
  Serial.println(F("Random Points 0"));
  delay(500);
}

void loop()
{
  testlines(random(0x0010, 0xFFFF));
  Serial.println(F("TestLines at Random of 0x0010 to 0xFFFF"));
  randomLines();
  Serial.println(F("Random Lines"));
  //randomCircles(1);
  Serial.println(F("... Skipped"));
  randomCircles(0);
  Serial.println(F("Random Circles 0"));
  randomRect(1);
  Serial.println(F("Random Rects 1 #1"));
  randomRect(1);
  Serial.println(F("Random Rects 1 #3"));
  randomRect(1);
  Serial.println(F("Random Rects 1 #4"));
  randomRect(1);
  Serial.println(F("Random Rects 1 #5"));
  randomRect(1);
  Serial.println(F("Random Rects 1 #6"));
  randomRect(0);
  Serial.println(F("Random Rects 1 #7"));
  randomRect(0);
  Serial.println(F("Random Rects 1 #8"));
  randomRect(0);
  Serial.println(F("Random Rects 1 #9"));
  randomRect(0);
  Serial.println(F("Random Rects 1 #10"));
  randomRect(0);
  Serial.println(F("Random Rects 1 #11"));
  randomRect(0);
  Serial.println(F("Random Rects 1 #12"));
  randomPoints();
  Serial.println(F("Random Points Null"));
  Serial.println(F("Big Test Done."));
}

void testlines(uint16_t color)
{
  display.clearScreen();
  for (int16_t x = 0; x < display.width() - 1; x += 6)
  {
    display.drawLine(0, 0, x, display.height() - 1, color);
  }
  for (int16_t y = 0; y < display.height() - 1; y += 6)
  {
    display.drawLine(0, 0, display.width() - 1, y, color);
  }
  display.clearScreen();
  for (int16_t x = 0; x < display.width() - 1; x += 6)
  {
    display.drawLine(display.width() - 1, 0, x, display.height() - 1, color);
  }
  for (int16_t y = 0; y < display.height() - 1; y += 6)
  {
    display.drawLine(display.width() - 1, 0, 0, y, color);
  }

  display.clearScreen();
  for (int16_t x = 0; x < display.width() - 1; x += 6)
  {
    display.drawLine(0, display.height() - 1, x, 0, color);
  }
  for (int16_t y = 0; y < display.height() - 1; y += 6)
  {
    display.drawLine(0, display.height() - 1, display.width() - 1, y, color);
  }
  display.clearScreen();
  for (int16_t x = 0; x < display.width() - 1; x += 6)
  {
    display.drawLine(display.width() - 1, display.height() - 1, x, 0, color);
  }
  for (int16_t y = 0; y < display.height() - 1; y += 6)
  {
    display.drawLine(display.width() - 1, display.height() - 1, 0, y, color);
  }
  delay(500);
}

void testdrawtext(char *text, uint16_t color)
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  for (uint8_t i = 0; i < 168; i++)
  {
    if (i == '\n')
      continue;
    display.write(i);
    if ((i > 0) && (i % 21 == 0))
      display.println();
  }
}

void testfastlines(uint16_t color1, uint16_t color2)
{
  display.clearScreen();
  for (int16_t y = 0; y < display.height() - 1; y += 5)
  {
    display.drawFastHLine(0, y, display.width() - 1, color1);
  }
  for (int16_t x = 0; x < display.width() - 1; x += 5)
  {
    display.drawFastVLine(x, 0, display.height() - 1, color2);
  }
}

void testdrawrects(uint16_t color)
{
  display.clearScreen();
  for (int16_t x = 0; x < display.height() - 1; x += 6)
  {
    display.drawRect((display.width() - 1) / 2 - x / 2, (display.height() - 1) / 2 - x / 2, x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2)
{
  display.clearScreen();
  for (int16_t x = display.height() - 1; x > 6; x -= 6)
  {
    display.fillRect((display.width() - 1) / 2 - x / 2, (display.height() - 1) / 2 - x / 2, x, x, color1);
    display.drawRect((display.width() - 1) / 2 - x / 2, (display.height() - 1) / 2 - x / 2, x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color)
{
  for (uint8_t x = radius; x < display.width() - 1; x += radius * 2)
  {
    for (uint8_t y = radius; y < display.height() - 1; y += radius * 2)
    {
      display.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color)
{
  for (int16_t x = 0; x < (display.width() - 1) + radius; x += radius * 2)
  {
    for (int16_t y = 0; y < (display.height()) - 1 + radius; y += radius * 2)
    {
      display.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles()
{
  display.clearScreen();
  int color = 0xF800;
  int t;
  int w = display.width() / 2;
  int x = display.height();
  int y = 0;
  int z = display.width();
  for (t = 0; t <= 15; t += 1)
  {
    display.drawTriangle(w, y, y, x, z, x, color);
    x -= 4;
    y += 4;
    z -= 4;
    color += 100;
  }
}

void testroundrects()
{
  display.clearScreen();
  int color = 100;
  int i;
  int t;
  for (t = 0; t <= 4; t += 1)
  {
    int x = 0;
    int y = 0;
    int w = display.width();
    int h = display.height();
    for (i = 0; i <= 24; i += 1)
    {
      display.drawRoundRect(x, y, w, h, 5, color);
      x += 2;
      y += 3;
      w -= 4;
      h -= 6;
      color += 1100;
    }
    color += 100;
  }
}

void tftPrintTest()
{
  display.clearScreen();
  display.setCursor(0, 5);
  display.setTextColor(RED);
  display.setTextSize(1);
  display.println("Hello World!");
  display.setTextColor(YELLOW, GREEN);
  display.setTextSize(2);
  display.print("Hello WoRLD");
  display.setTextColor(BLUE);
  display.setTextSize(3);
  display.print(12.57);
  delay(1500);
  display.setCursor(0, 5);
  display.clearScreen();
  display.setTextColor(WHITE);
  display.setTextSize(0);
  display.println("Hello World!");
  display.setTextSize(1);
  display.setTextColor(GREEN);
  display.print(p, 5);
  display.println(" Want pi?");
  display.print(8675309, HEX);
  display.print(" Print HEX");
  display.setTextColor(WHITE);
  display.println("Sketch has been");
  display.println("running for: ");
  display.setTextColor(MAGENTA);
  display.print(millis() / 1000);
  display.setTextColor(WHITE);
  display.print(" sec.");
}

void randomRect(bool fill)
{
  display.clearScreen();
  uint8_t k, c;
  for (k = 0; k < 16; k++)
  {
    for (c = 0; c < 32; c++)
    {
      uint8_t cx, cy, x, y, w, h;
      yield();
      //  center
      cx = random(0, display.width());
      cy = random(0, display.height());
      //  size
      w = random(0, 30 + 6);
      h = random(0, 20 + 4);
      //  upper-left
      x = cx - w / 2;
      y = cy - h / 2;
      if (x < 0)
        x = 0;
      if (y < 0)
        y = 0;
      //  adjust size
      if (x + w > display.width())
        w = display.width() - x;
      if (y + h > display.height())
        h = display.height() - y;
      if (fill)
      {
        display.fillRect(x, y, w, h, random(0x0010, 0xFFFF));
      }
      else
      {
        display.drawRect(x, y, w, h, random(0x0010, 0xFFFF));
      }
    }
    display.clearScreen();
  }
}

void randomCircles(bool fill)
{
  display.clearScreen();
  uint8_t k, c;
  for (k = 0; k < display.height(); k++)
  {
    for (c = 0; c < display.height() / 2; c++)
    {
      //  coordinates
      uint8_t x = random(0, 120 + 3), y = random(0, 90 + 2), r = random(0, 40 + 1);
      if (x - r < 0)
        r = x;
      if (x + r > (display.width() - 1))
        r = (display.width() - 1) - x;
      if (y - r < 0)
        r = y;
      if (y + r > (display.height() - 1))
        r = (display.height() - 1) - y;
      if (fill)
      {
        display.fillCircle(x, y, r, random(0x0010, 0xFFFF));
      }
      else
      {
        display.drawCircle(x, y, r, random(0x0010, 0xFFFF));
      }
    }
    if (!fill)
      display.clearScreen();
  }
}

void randomLines()
{
  display.clearScreen();
  uint8_t k, c;
  for (k = 0; k < display.height(); k++)
  {
    for (c = 0; c < display.height() / 2; c++)
    {
      uint8_t x1 = random(0, display.width()), y1 = random(0, display.height()), x2 = random(0, display.width()), y2 = random(0, display.height());
      display.drawLine(x1, y1, x2, y2, random(0x0010, 0xFFFF));
    }
    display.clearScreen();
  }
}

void randomPoints()
{
  display.clearScreen();
  int k, c;
  for (k = 0; k < 128; k++)
  {
    for (c = 0; c < 1000; c++)
    {
      uint8_t x = random(0, display.width()), y = random(0, display.height());
      display.drawPixel(x, y, random(0x0010, 0xFFFF));
    }
    display.clearScreen();
  }
}