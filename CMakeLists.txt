cmake_minimum_required(VERSION 3.5)

project(Schedule VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PICO_ENABLE_CXX_EXCEPTIONS 1)

configure_file(${CMAKE_SOURCE_DIR}/src/config.yml ${CMAKE_BINARY_DIR}/config.yml COPYONLY) # copy default config
configure_file(${CMAKE_SOURCE_DIR}/src/teachers.yml ${CMAKE_BINARY_DIR}/teachers.yml COPYONLY) # copy teachers.yml (experimental, should delete later)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES src/Schedule_ru_RU.ts)
set(INCLUDES
    ${CMAKE_SOURCE_DIR}/include/yaml-cpp/
    ${CMAKE_SOURCE_DIR}/include
    )

add_compile_definitions(YAML_CPP_STATIC_DEFINE)

link_directories(${CMAKE_SOURCE_DIR}/src/lib)
include_directories(${INCLUDES})

find_library(YCPP yaml-cpp ${CMAKE_SOURCE_DIR}/src/yaml-cpp.lib)

file(GLOB PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/*.*)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Schedule
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR}/src ${TS_FILES})
else()
    add_executable(Schedule
        ${PROJECT_SOURCES}
    )
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR}/src ${TS_FILES})
endif()

if (ANDROID)
    message(FATAL_ERROR "This is not an android application.\nYou can't compile it as an android app.")
endif()

target_link_libraries(Schedule PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Schedule PUBLIC ${CMAKE_SOURCE_DIR}/src/yaml-cpp.lib)

set_target_properties(Schedule PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER dev.blek.cuteschedule
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Schedule)
endif()
