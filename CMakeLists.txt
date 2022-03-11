cmake_minimum_required(VERSION 3.5)

project(CuteSchedule VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)
find_library(YCPP yaml-cpp ${CMAKE_SOURCE_DIR}/src/yaml-cpp.lib)

configure_file(${CMAKE_SOURCE_DIR}/src/config.yml ${CMAKE_BINARY_DIR}/config.yml COPYONLY) # copy default config

set(TS_FILES CuteSchedule_ru_RU.ts)

set(INCLUDES
    ${CMAKE_SOURCE_DIR}/include/yaml-cpp/
    ${CMAKE_SOURCE_DIR}/include
    )

include_directories(${INCLUDES})

add_compile_definitions(YAML_CPP_STATIC_DEFINE)
link_directories(${CMAKE_SOURCE_DIR}/src/lib)

file(GLOB PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/*.*)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CuteSchedule
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CuteSchedule APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(CuteSchedule SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CuteSchedule
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(CuteSchedule PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(CuteSchedule PUBLIC ${CMAKE_SOURCE_DIR}/src/yaml-cpp.lib)

set_target_properties(CuteSchedule PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CuteSchedule)
endif()
