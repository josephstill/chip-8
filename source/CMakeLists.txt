cmake_minimum_required (VERSION 2.6)
project (Chip-8 CXX)

add_subdirectory(disassembler)

set(SRC_FILES
    ${SRC_FILES}
    Disassembler.cpp
    main.cpp)

set(HEADER_FILES
    ${HEADER_FILES}
    Disassembler.h)

# Make sure C++ 11
add_definitions(-std=c++11)

add_executable(chip-8 ${SRC_FILES} ${HEADER_FILES})
