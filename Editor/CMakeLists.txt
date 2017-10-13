cmake_minimum_required(VERSION 3.8)

project(Editor)

# Gather c++ files
file(GLOB_RECURSE SRC_FILES 
	src/*.cpp
	src/*.h
)

add_executable(Editor ${SRC_FILES})

ADD_DEPENDENCIES(Editor DungeonCrawler)
ADD_DEPENDENCIES(Editor NativeUI)

include_directories ("../DungeonCrawler/src")
include_directories ("../NativeUI/src")
include_directories ("../include")

target_link_libraries(Editor DungeonCrawler)
target_link_libraries(Editor NativeUI)

if(MSVC)
    set_property(TARGET Editor APPEND PROPERTY LINK_FLAGS /DEBUG)
endif()

IF(WIN32)
    add_definitions("/Zi")
    #--------------------------------------------------------------------------
    # Since /Zi implies /OPT:NOREF, explicitly enable /OPT:REF on all
    # release builds (this ensures all unused symbols are stripped)
    #--------------------------------------------------------------------------
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /OPT:REF")
    set(CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL "${CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL} /OPT:REF")
    set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} /OPT:REF")
ENDIF()

#Set working directory to the directory where "Resources" folder is located
set_target_properties(Editor PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${ROOT_DIR}")
