cmake_minimum_required (VERSION 2.6)
project (PUISSANCE4)

include_directories (${PUISSANCE4_SOURCE_DIR}/include)
add_executable (consolepuissance_4  src/Controler.cpp )
add_executable (puissance_4  src/interface_console.cpp )