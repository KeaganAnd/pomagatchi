cmake_minimum_required(VERSION 3.15)
project(pomagatchi C)

set(CMAKE_C_STANDARD 99)

add_executable(pomagatchi src/main.c)

target_include_directories(pomagatchi PRIVATE external)

add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES
    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/external/libraylib.a
)

target_link_libraries(pomagatchi PRIVATE raylib)

if(APPLE)
    target_link_libraries(pomagatchi PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
        "-framework OpenGL"
    )
elseif(UNIX)
    target_link_libraries(desktop-critter PRIVATE GL m pthread dl rt X11)
elseif(WIN32)
    target_link_libraries(desktop-critter PRIVATE opengl32 gdi32 winmm)
endif()
