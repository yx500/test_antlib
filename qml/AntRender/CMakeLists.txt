get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

file(GLOB SINGLETON_QML RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *Backend.qml
    )

file(GLOB QML_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *.qml
    *.js
    *.mjs
    )

qt_add_library(${TARGET_NAME} STATIC)
set_source_files_properties(
        ${SINGLETON_QML}
    PROPERTIES
        QT_QML_SINGLETON_TYPE true
    )

qt_add_qml_module(${TARGET_NAME}
        URI ${TARGET_NAME}
        VERSION 1.0
        QML_FILES ${QML_SOURCES}
)


message("*** qt_add_qml_module: " ${TARGET_NAME})
