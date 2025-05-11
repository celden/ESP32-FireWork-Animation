#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define PARTICLE_COUNT 12

struct Particle {
  float x, y;
  float vx, vy;
};

Particle particles[PARTICLE_COUNT];

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  randomSeed(analogRead(0));
}

void loop() {
  int startX = random(20, SCREEN_WIDTH - 20);
  int startY = SCREEN_HEIGHT - 1;

  // Yukarı çıkış efekti
  for (int i = startY; i > 20; i -= 2) {
    display.clearDisplay();
    display.drawPixel(startX, i, SSD1306_WHITE);
    display.display();
    delay(20);
  }

  // Parçacıkları başlat
  for (int i = 0; i < PARTICLE_COUNT; i++) {
    float angle = random(0, 360) * 3.14 / 180;
    float speed = random(1, 3);
    particles[i].x = startX;
    particles[i].y = 20;
    particles[i].vx = cos(angle) * speed;
    particles[i].vy = sin(angle) * speed;
  }

  // Parçacıkların hareket animasyonu
  for (int frame = 0; frame < 10; frame++) {
    display.clearDisplay();
    for (int i = 0; i < PARTICLE_COUNT; i++) {
      particles[i].x += particles[i].vx;
      particles[i].y += particles[i].vy;
      display.drawPixel((int)particles[i].x, (int)particles[i].y, SSD1306_WHITE);
    }
    display.display();
    delay(80);
  }

  delay(500);
}
