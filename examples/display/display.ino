#define BEER_ARDUINO

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <BeerGUI.h> //Use angle brackets <BeerGUI.h> in arduino

using namespace beer;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Renderer<Adafruit_GFX> ren(&display);
WindowManager manager(ren, SCREEN_WIDTH, SCREEN_HEIGHT);
Window window(SCREEN_WIDTH, SCREEN_HEIGHT);

SliderComponent slider({{5, 5}, {60, 8}}, (uint8_t)255/2);
SliderComponent slider2({{5, 10}, {60, 13}}, (uint8_t)255/2);

void setup() {
    Serial.begin(9600);
    
// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    display.display();
    delay(2000); // Pause for 2 seconds

    display.clearDisplay();
  
    window.addComponent(&slider);
    window.addComponent(&slider2);
    manager.add(0, window);

    /*
     * Create two sliders and push them around. Use whatever method of reacting to user
     * input, then call manager.onEvent. Changes won't be visible until manager.update() is called
     */
    test_program();
    manager.onEvent(InputEvent::PLUS);
    updateAll();
    test_program();
}

void test_program() {
    delay(1000);
    manager.onEvent(InputEvent::SELECT); //enter slider component with select
    delay(250);
    for (int i = 0; i < 10; i++) {
        updateAll();
        delay(100);
        manager.onEvent(InputEvent::PLUS); //slider active. increase slider value
    }
    manager.onEvent(InputEvent::SELECT); //deactivate slider
}

void updateAll() {
    delay(50);
    manager.update();
    ren.drawPixel({127, 63}, {1,1,1});
    ren.drawText({70,30}, "yo", {1,1,1});
    display.display();
}

void loop() {
    updateAll(); //infinitely cycle between components in window
    manager.onEvent(InputEvent::PLUS);
    delay(500);
}
