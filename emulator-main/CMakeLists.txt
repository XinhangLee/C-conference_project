cmake_minimum_required(VERSION 3.5)
project(Emulator)

set(C_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRCS)

add_executable(${PROJECT_NAME} ${SRCS})

add_compile_options(-O2 -Wall -fdiagnostics-color=always)

add_custom_target(copy-img ALL
                  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/img ${CMAKE_BINARY_DIR}/img)
