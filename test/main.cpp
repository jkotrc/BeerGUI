#include <gtest/gtest.h>

#include "renderer-fake.h"
#include <window.h>
#include <component.h>
#include <slider.h>

// Demonstrate some basic assertions.
TEST(BeerTest, BasicCreation) {
  FRenderer ren;
  WindowManager manager(ren, 100, 50);
  Window* win = manager.add();
  EXPECT_EQ(win->getWidth(), 100);
  EXPECT_EQ(win->getHeight(), 50);
  win->addComponent({{0,0}, new SliderComponent({20,5}, 0)});
  manager.onEvent(InputEvent::SELECT);
  manager.onEvent(InputEvent::PLUS);
  manager.update();
}


// TEST(BeerTest, ComponentCreation) {
//   FRenderer ren;
//   WindowManager manager(ren, 100, 50);
//   Window* win = manager.add();
//   win->addComponent({{0,0}, new SliderComponent({20,5}, 0)});
//   win->addComponent({{0,0}, new SliderComponent({20,5}, 0)});
//   manager.onEvent(InputEvent::SELECT);
//   manager.onEvent(InputEvent::PLUS);
//   manager.update();
// }
