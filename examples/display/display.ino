#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BfButton.h>

#define BEER_ARDUINO
#include <BeerGUI.h> //Use angle brackets <BeerGUI.h> in arduino

using namespace beer;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

const int btnPin = 3; // GPIO #3 - Push button on encoder
const int DT = 4;    // GPIO #4 - DT on encoder (Output B)
const int CLK = 5;   // GPIO #5 - CLK on encoder (Output A)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
BfButton btn(BfButton::STANDALONE_DIGITAL, btnPin, true, LOW);
int btnState, btnPrevState;

enum Windows {
    W_MAINMENU = 0,
    W_SETTINGS,
    W_NWINDOWS
};

Renderer<Adafruit_GFX> ren(&display);
Window* windows[1];
WindowManager manager(ren, SCREEN_WIDTH, SCREEN_HEIGHT);

void pressHandler(BfButton *btn, BfButton::press_pattern_t pattern) {
    Serial.println("Enter handler");

  switch (pattern) {
    case BfButton::SINGLE_PRESS:
        Serial.println("Select");
        break;
    case BfButton::DOUBLE_PRESS:
        Serial.println("Long press");
        break;
    case BfButton::LONG_PRESS:
        Serial.println("Double press");
        break;
    }
}

SliderComponent cmp({50, 5}, 30);
void setup() {
    Serial.begin(9600);

// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

    display.display();
    delay(1000);
    display.clearDisplay();

    Serial.println("Let's go");

    windows[W_MAINMENU] = manager.createWindow();

    Window* win = manager.getWindow(W_MAINMENU);
    Serial.println((long)win);

    if(windows[W_MAINMENU]->addComponent({{30,10}, new SliderComponent({50, 5}, 30)})) {
        Serial.println("Component added");
    } else {
        Serial.println("Failed to add component");
    }

    pinMode(CLK, INPUT_PULLUP);
    pinMode(DT, INPUT_PULLUP);
    btnPrevState = digitalRead(CLK);

    btn.onPress(pressHandler)
        .onDoublePress(pressHandler)
        .onPressFor(pressHandler, 1000);
    Serial.println("setup complete");
}

void updateAll() {
    manager.update();
    display.display();
}

void loop() {
    btn.read();
    int btnState = digitalRead(CLK);
    int dt = digitalRead(DT);

    if (btnState != btnPrevState && btnState == 1) {
        if (dt != btnState) {
            Serial.println("+");
        } else {
            Serial.println("-");
        }

    }
    if (btnState != btnPrevState) {
        Serial.println("Change of state:");
    Serial.println(btnState);
    Serial.println(btnPrevState);
    Serial.println(dt);
    Serial.println("------");
    }
    btnPrevState = btnState;

    updateAll();
    delay(1);
}
