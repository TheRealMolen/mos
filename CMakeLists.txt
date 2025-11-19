cmake_minimum_required(VERSION 3.30.0 FATAL_ERROR)

project(mos CXX C)

# Set application to GUI type for Win32 and MacOS
if(WIN32)
  set(GUI_TYPE WIN32)
endif(WIN32)
if(APPLE)
  set(GUI_TYPE MACOSX_BUNDLE)
endif(APPLE)

set(TARGET_DIR
  ${CMAKE_BINARY_DIR}/target
)

set(EXE_NAME ${PROJECT_NAME})

set(SOURCE_DIR src)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TARGET_DIR})

# YouCompleteMe completion setup - based on https://github.com/danebulat/vim-cmake-boilerplate
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#
add_subdirectory(src)

