#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "src/BeerGUI.h"
#include "src/renderer-adafruit.h"

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();


Renderer<Adafruit_GFX> renderer(&display);
WindowManager manager(renderer, OLED_WIDTH, OLED_HEIGHT);
Window window(OLED_WIDTH, OLED_HEIGHT);
SliderComponent slider({{10, 10}, {110, 20}}, 255/2);


void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  };

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();

  window.addComponent(&slider);
  manager.add(0, window);
}


void loop() {
  manager.update();
}
