project(mos CXX C)

set(main_SRCS
  main.cpp
  framebufApp.cpp framebuf.cpp
)

add_executable(${EXE_NAME} ${GUI_TYPE} ${main_SRCS})

find_package(SDL2 REQUIRED)

target_include_directories(${EXE_NAME} PUBLIC
    ${SOURCE_DIR}
    ${SDL2_INCLUDE_DIR}
)
target_link_libraries(${EXE_NAME}
    ${SDL2_LIBRARY}
)

set_property(TARGET ${EXE_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${EXE_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)


# YouCompleteMe completion setup - based on https://github.com/danebulat/vim-cmake-boilerplate
# add compiler warning flags just when building this project
# via the BUILD_INTERFACE generator expression
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

set(gcc_flags "-Wall;-Wextra;-Wshadow;-Wshadow;-Wformat=2")
set(msvc_flags "-W3")

target_compile_options(${EXE_NAME} PRIVATE
   "$<${gcc_like_cxx}:$<BUILD_INTERFACE:${gcc_flags}>>"
   "$<${msvc_cxx}: $<BUILD_INTERFACE:${msvc_flags}>>")


