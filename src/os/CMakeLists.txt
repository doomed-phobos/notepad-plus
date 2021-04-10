add_library(os-lib STATIC
win/system.cpp
win/native_dialogs.cpp
win/keys.cpp)

target_include_directories(os-lib PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_compile_definitions(os-lib PRIVATE -DUNICODE)

add_executable(os-test main.cpp)
target_link_libraries(os-test os-lib)