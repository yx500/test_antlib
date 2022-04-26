cmake_minimum_required(VERSION 3.20)

get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(antrender VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_PREFIX_PATH "~/Qt/6.2.2/gcc_64")

set(CMAKE_AUTOMOC ON)
find_package(Qt6 COMPONENTS Core Qml Quick QuickControls2 REQUIRED)


file(GLOB_RECURSE SOURCES
    AntRender/*.cpp
    AntRender/*.h
)

set( PROJECT_SOURCES
    ${SOURCES}
    main.cpp
)

qt_add_executable( render ${PROJECT_SOURCES} )

target_include_directories(render PRIVATE "./AntRender" )
target_compile_definitions(render PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG> )
target_link_libraries(render PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Qml
)

add_subdirectory(AntRender)

target_compile_definitions( render PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG> )
target_link_libraries( render PRIVATE
    AntRenderplugin
)



