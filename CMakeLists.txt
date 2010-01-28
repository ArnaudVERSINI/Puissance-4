cmake_minimum_required (VERSION 2.6)
project (PUISSANCE4)

SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_MODULE_PATH}")
FIND_PACKAGE(CppTest)

INCLUDE_DIRECTORIES(${LIBXML2_INCLUDE_DIR} ${CPPTEST_INCLUDE_DIR})
add_executable (unit_tests  test/test.cxx )
TARGET_LINK_LIBRARIES(unit_tests ${CPPTEST_LIBRARY})


include_directories (${PUISSANCE4_SOURCE_DIR}/include)
add_executable (consolepuissance_4  src/Controler.cpp )
add_executable (puissance_4  src/interface_console.cpp )
