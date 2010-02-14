cmake_minimum_required (VERSION 2.6)
project (PUISSANCE4)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_MODULE_PATH}")

include_directories (${PUISSANCE4_SOURCE_DIR}/include)
add_executable (consolepuissance_4  src/controler.cpp )

enable_testing()
find_package(CppTest)
include_directories(${CPPTEST_INCLUDE_DIR})
add_executable (unit_tests  test/unit_test.cpp)
target_link_libraries(unit_tests ${CPPTEST_LIBRARY})
ADD_TEST(unit_tests ${EXECUTABLE_OUTPUT_PATH}/unit_tests)


Find_Package ( SDL REQUIRED )

link_libraries (
   ${SDL_LIBRARY}
   SDLmain # Sadly not included in SDL_LIBRARY variable
)


ADD_EXECUTABLE(ihm_puissance4  src/main.cpp)
target_link_libraries(ihm_puissance4 ${SDL_LIBRARY})
