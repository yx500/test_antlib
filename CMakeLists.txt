cmake_minimum_required(VERSION 3.20)
project(test_antlib VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    graphicsscene.cpp
    graphicsscene.h
    graphicsview.cpp
    graphicsview.h
)

add_executable(test_antlib  ${PROJECT_SOURCES} )
target_link_libraries(test_antlib PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    antlib
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
        find_package(Qt6 REQUIRED COMPONENTS Core5Compat)
        target_link_libraries(test_antlib PUBLIC Qt6::Core5Compat)

        find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)
        qt_add_executable(pie  piemain.cpp )
        target_link_libraries(pie PUBLIC
            Qt::Core
            Qt::Gui
            Qt::Qml
            Qt::Quick
            antlib
        )
        qt_add_qml_module(pie
            URI Pie
            VERSION 1.0
            QML_FILES pieapp.qml
            SOURCES pie.cpp pie.h antrender.cpp antrender.h
            NO_RESOURCE_TARGET_PATH
        )

endif()
