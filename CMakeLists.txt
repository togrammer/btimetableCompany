cmake_minimum_required(VERSION 3.5)

project(bttt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(OpenSSL REQUIRED)

add_library(pqxx STATIC IMPORTED)
set_target_properties(pqxx PROPERTIES IMPORTED_LOCATION ../btt/pqxx.lib)
set(PQXX_LIB pqxx)
set(PQ_LIB PostgreSQL::PostgreSQL)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        choosewindow.cpp
        choosewindow.h
        choosewindow.ui
        registration.h registration.cpp registration.ui
        CompanyAPI.h
        Entities.h
        authorization.h authorization.cpp authorization.ui
        chooseaction.h chooseaction.cpp chooseaction.ui
        addeventaction.cpp addeventaction.h addeventaction.ui
        addspecialist.h addspecialist.cpp addspecialist.ui
        deletespecialist.h deletespecialist.cpp deletespecialist.ui
        deleteorder.h deleteorder.cpp deleteorder.ui
        listorders.h listorders.cpp listorders.ui
)

add_library(btt STATIC IMPORTED)
set_target_properties(btt PROPERTIES IMPORTED_LOCATION ../btt/btt.lib)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(bttt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(bttt SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(bttt
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(bttt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(bttt PRIVATE btt ${PQXX_LIB} ${PQ_LIB} OpenSSL::SSL OpenSSL::Crypto ws2_32.lib)

set_target_properties(bttt PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(bttt)
endif()
