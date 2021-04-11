cmake_minimum_required(VERSION 3.2)
#TODO: Crear un notepad, con más herramientas
# Sistema inspirado en LAF de dacap (estoy intentado comprender como se hace una UI)

set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MTd /Zi /Ob0 /Od /RTC1")

project(notepad+ CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

add_subdirectory(src)