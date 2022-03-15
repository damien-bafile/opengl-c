cmake_minimum_required(VERSION 3.18)
project(openglC)

set(CMAKE_C_STANDARD 99)

list(APPEND COMPILE_FILES
    src/main.c
)

option(BUILD_LIB_FREEGLUT "Build with FreeGLUT." ON)

if(BUILD_LIB_FREEGLUT)
    OPTION(FREEGLUT_BUILD_STATIC_LIBS "Build FreeGLUT static library." OFF)
    OPTION(FREEGLUT_BUILD_SHARED_LIBS "Build FreeGLUT shared library." ON)
    option(FREEGLUT_BUILD_DEMOS "Build FreeGLUT demos." OFF)
    
    add_subdirectory(lib/freeglut)
    if (UNIX OR MINGW)
        target_compile_options(freeglut_static PRIVATE "-Wno-all")      # Remove annoying font unused values (in CMakeList line 305)
        target_compile_options(freeglut_static PRIVATE "-Wno-pedantic") # Remove annoying ISO C does not allow extra ';' outside of a function [-Wpedantic] (in CMakeList line 308)
    endif ()
    list(APPEND INCLUDE_DIRS $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/lib/freeglut/include>)
    list(APPEND INCLUDE_LIBS freeglut_static)
    add_compile_definitions(BUILD_LIB_FREEGLUT)
endif()

# OpenGL
set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)

if(WIN32)
    set(BUILD_OPTIONS WIN32)
elseif(UNIX OR APPLE)
    set(BUILD_OPTIONS MACOSX_BUNDLE)
endif()

add_executable(${PROJECT_NAME} ${BUILD_OPTIONS} ${COMPILE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${INCLUDE_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})

if (UNIX OR MINGW)
    target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -pedantic)
elseif (MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC /W3)
endif ()