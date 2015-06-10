set(SRC_FILES
    ${SRC_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/RomParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DisassemblyEngine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AssemblyUtils.cpp
    PARENT_SCOPE)

set(HEADER_FILES
    ${HEADER_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/RomParser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/DisassemblyEngine.h
    ${CMAKE_CURRENT_SOURCE_DIR}/AssemblyUtils.h
    PARENT_SCOPE)

