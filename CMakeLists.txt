cmake_minimum_required(VERSION 3.29)
project(sandbox)

option(SANDBOX_VENDORED "Use vendored libraries" OFF)

# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")

if(SANDBOX_VENDORED)
    add_subdirectory(vendored/sdl EXCLUDE_FROM_ALL)
else()
    find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
    find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
endif()

file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.c)

add_executable(sandbox ${HEADER_FILES} ${SOURCE_FILES})

if(TARGET SDL2::SDL2main)
    target_link_libraries(sandbox PRIVATE SDL2::SDL2main)
endif()

target_include_directories(sandbox PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(sandbox PRIVATE SDL2::SDL2)