cmake_minimum_required(VERSION 3.21)

project(password-generator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_MODULE_PATH "C:\\Qt\\6.1.3\\mingw81_64\\lib\\cmake\\")

find_package(Qt6 REQUIRED Widgets)

set(SOURCE_FILES password-generator
        password-generator/src/focusablelineedit.cpp
        password-generator/src/main.cpp
        password-generator/src/mainwindow.cpp
        password-generator/src/mainwindow.ui
        password-generator/src/password-generator.pro
        password-generator/src/password-generator_en_US.ts
        password-generator/src/resources.qrc
        )

set(HEADER_FILES password-generator
        password-generator/src/mainwindow.h
        password-generator/src/focusablelineedit.h
        password-generator/src/ui_mainwindow.h
        )

add_executable(password-generator ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(password-generator
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
        PRIVATE ${Qt6Widgets_INCLUDE_DIRS}
        )

target_compile_features(password-generator PRIVATE cxx_std_17)

target_link_libraries(password-generator PUBLIC QT6::Widgets)