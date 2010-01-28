cmake_minimum_required (VERSION 2.6)
project (PUISSANCE4)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_MODULE_PATH}")
find_package(CppTest)

include_directories(${CPPTEST_INCLUDE_DIR})
include_directories (${PUISSANCE4_SOURCE_DIR}/include)

add_executable (unit_tests  test/test.cxx )
target_link_libraries(unit_tests ${CPPTEST_LIBRARY})



add_executable (consolepuissance_4  src/Controler.cpp )
add_executable (puissance_4  src/interface_console.cpp )

enable_testing()
ADD_TEST(unit_tests ${EXECUTABLE_OUTPUT_PATH}/unit_tests)
