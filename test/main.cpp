#include <gtest/gtest.h>

#include "renderer-fake.h"
#include <window.h>
#include <component.h>
#include <slider.h>
#include <button.h>

using namespace beer;

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

TEST(BeerTest, ListOperations) {
  FRenderer ren;
  WindowManager manager(ren, 100, 50);
  List<WindowedComponent> components;

  auto onClick = [](){};
  components.push_back({{30,10}, new SliderComponent({50, 5}, 30)});
  components.push_back({{20,30}, new ButtonComponent({10, 10}, onClick)});
  components.push_back({{10,10}, new SliderComponent({50, 5}, 60)});
  components.push_back({{0,20}, new SliderComponent({50, 5}, 255/2)});
  components.push_back({{80,30}, new ButtonComponent({10, 10}, onClick)});
  EXPECT_EQ(components[0].position,Point(30,10));
  EXPECT_EQ(components[1].position,Point(20,30));
  EXPECT_EQ(components[4].position,Point(80,30));
}

TEST(BeerTest, ListOperations2) {
  List<WindowedComponent> components;

  components.push_back({{30,10}, new SliderComponent({50, 5}, 30)});
  components.push_back({{30,20}, new SliderComponent({50, 5}, 60)});
  components.push_back({{30,30}, new SliderComponent({50, 5}, 255/2)});
  components.push_back({{30,40}, new SliderComponent({50, 5}, 255/2)});
  components.push_back({{30,50}, new SliderComponent({50, 5}, 255/2)});
  EXPECT_EQ(components[0].position,Point(30,10));
  EXPECT_EQ(components[1].position,Point(30,20));
  EXPECT_EQ(components[2].position,Point(30,30));
  EXPECT_EQ(components[3].position,Point(30,40));
  EXPECT_EQ(components[4].position,Point(30,50));
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
