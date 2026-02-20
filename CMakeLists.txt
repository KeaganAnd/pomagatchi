cmake_minimum_required(VERSION 3.15)
project(pomagatchi C OBJC)

set(CMAKE_C_STANDARD 99)

# Base source files
set(SRC
    src/main.c
)

# Add platform-specific files
if(APPLE)
    list(APPEND SRC src/platform_apple.m)
elseif(UNIX)
    list(APPEND SRC src/platform_linux.c)
elseif(WIN32)
    list(APPEND SRC src/platform_windows.c)
endif()

# Add executable with all sources
add_executable(pomagatchi ${SRC})

# Include directories
target_include_directories(pomagatchi PRIVATE external)

# Raylib static library
add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES
    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/external/libraylib.a
)

# Link raylib
target_link_libraries(pomagatchi PRIVATE raylib)

# Platform-specific libraries
if(APPLE)
    target_link_libraries(pomagatchi PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
        "-framework OpenGL"
    )
elseif(UNIX)
    target_link_libraries(pomagatchi PRIVATE GL m pthread dl rt X11)
elseif(WIN32)
    target_link_libraries(pomagatchi PRIVATE opengl32 gdi32 winmm)
endif()
