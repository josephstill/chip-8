CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Chip-8 CXX)

ADD_SUBDIRECTORY(disassembler)
ADD_SUBDIRECTORY(emulator)

FIND_PACKAGE(Qt4 REQUIRED)

INCLUDE(${QT_USE_FILE})

SET(CMAKE_AUTOUIC TRUE)

SET(SRC_FILES
    ${SRC_FILES}
    Disassembler.cpp
    MainWindow.cpp
    DisassemblyWindow.cpp
    HexDumpWindow.cpp
    Emulator.cpp
    main.cpp
    ProcessorInspectionWindow.cpp
    EmulatorWindow.cpp)

SET(HEADER_FILES
    ${HEADER_FILES}
    Disassembler.h)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
    
SET(QT_UI_FILES
    ${QT_UI_FILES}
    ProcessorInspectionWindow.ui)
QT4_WRAP_UI(UISrcs ${QT_UI_FILES})
    
SET(QT_WRAP_HEADERS
    ${QT_WRAP_HEADERS}
    MainWindow.h
    DisassemblyWindow.h
    HexDumpWindow.h
    Emulator.h
    ProcessorInspectionWindow.h
    EmulatorWindow.h)
QT4_WRAP_CPP(MOCSrcs ${QT_WRAP_HEADERS})

ADD_DEFINITIONS(-std=c++11)
ADD_EXECUTABLE(chip-8 ${SRC_FILES} ${HEADER_FILES} ${MOCSrcs} ${UISrcs})
TARGET_LINK_LIBRARIES(chip-8 ${QT_LIBRARIES})
