set(BEER_TEST_SRC main.cpp)


enable_testing()

add_executable(
  beergui_test
  ${BEER_TEST_SRC}
)

target_link_libraries(
  beergui_test
  GTest::gtest_main
  displaylib
)

gtest_discover_tests(beergui_test)
