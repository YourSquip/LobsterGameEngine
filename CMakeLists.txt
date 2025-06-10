cmake_minimum_required(VERSION 3.16)

project(LobsterGameEngine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#find_package(OpenGL REQUIRED)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)
#find_package(Qt6 REQUIRED COMPONENTS OpenGL)
#find_package(Qt5Multimedia REQUIRED)
#find_package(Qt6Multimedia REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(LobsterGameEngine
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        resources.qrc
        gameobject.h gameobject.cpp
        component.h component.cpp
        level.h level.cpp
        game.h game.cpp
        editor.h editor.cpp
        editorwidget.h editorwidget.cpp
        gameobjectstreewidget.h gameobjectstreewidget.cpp
        gameobjectinfowidget.h gameobjectinfowidget.cpp
        componentinfowidget.h componentinfowidget.cpp
        viewport.h viewport.cpp
        levelgraphicsscene.h levelgraphicsscene.cpp
        maptile.h maptile.cpp
        map.h map.cpp
        gameobjectpixmapitem.h gameobjectpixmapitem.cpp
        grid.h grid.cpp
        editortoolswidget.h editortoolswidget.cpp
        maptileslist.h maptileslist.cpp
        maptilegraphics.h maptilegraphics.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET LobsterGameEngine APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(LobsterGameEngine SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(LobsterGameEngine
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(LobsterGameEngine PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(LobsterGameEngine PRIVATE Qt${QT_VERSION_MAJOR}::Multimedia)
#target_link_libraries(LobsterGameEngine PRIVATE Qt${QT_VERSION_MAJOR}::OpenGL)
#target_link_libraries(LobsterGameEngine PRIVATE Qt${QT_VERSION_MAJOR}::Multimedia)
#target_link_libraries(LobsterGameEngine PRIVATE Qt6::Multimedia)
#target_link_libraries(LobsterGameEngine )
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.LobsterGameEngine)
endif()
set_target_properties(LobsterGameEngine PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS LobsterGameEngine
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(LobsterGameEngine)
endif()
