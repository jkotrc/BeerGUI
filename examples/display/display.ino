
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BEER_ARDUINO
#include <BeerGUI.h> //Use angle brackets <BeerGUI.h> in arduino

using namespace beer;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

enum Windows {
    W_MAINMENU = 0,
    W_SETTINGS,
    W_NWINDOWS
};

Renderer<Adafruit_GFX> ren(&display);
Window* windows[W_NWINDOWS];
WindowManager manager(ren, SCREEN_WIDTH, SCREEN_HEIGHT);

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

    Serial.println("Let's go");

    windows[W_MAINMENU] = manager.add();
    windows[W_SETTINGS] = manager.add();

    ButtonComponent::ButtonFunc onClick1 = []() { //define button action
        Serial.println("Going to settings");
         manager.makeActive(W_SETTINGS); //switch between windows
    };
    /* ButtonComponent::ButtonFunc onClick2 = []() { */
    /*     Serial.println("Going to main menu"); */
    /*      manager.makeActive(W_MAINMENU); */
    /* }; */
    windows[W_MAINMENU]->addComponent({{30,10}, new SliderComponent({50, 5}, 30)});
    windows[W_MAINMENU]->addComponent({{30,30}, new ButtonComponent({10, 10}, onClick1)});

    windows[W_SETTINGS]->addComponent({{30,10}, new SliderComponent({50, 5}, 60)});

    /* windows[W_SETTINGS]->addComponent({{30,20}, new SliderComponent({50, 5}, 255/2)}); */
    /* windows[W_SETTINGS]->addComponent({{80,30}, new ButtonComponent({10, 10}, onClick2)}); */

    /* manager.update(); */
    /* display.display(); */
    /* Create two sliders and push them around. Use whatever method of reacting to user */
    /* input, then call manager.onEvent. Changes won't be visible until manager.update() is called */
    /* test_program(); */
    /* manager.onEvent(InputEvent::PLUS); */
    /* updateAll(); */
    /* test_program(); */

    manager.onEvent(InputEvent::SELECT); //enter slider component with select
    updateAll();
    /* manager.onEvent(InputEvent::PLUS); //enter slider component with select */
    /* updateAll(); */
    Serial.println("setup complete");
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
    display.display();
}

void loop() {
    delay(500);
    updateAll(); //infinitely cycle between components in window
}
