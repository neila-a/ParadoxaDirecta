cmake_minimum_required(VERSION 3.16)

project(ParadoxaDirecta VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_VERSION_MAJOR 6)

set(CMAKE_PREFIX_PATH /media/neila/MobileDisk/programs/ubin/Qt/6.4.1/gcc_64/lib/cmake/)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt6 REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES ParadoxaDirecta_zh_CN.ts)

set(PROJECT_SOURCES
    src/main/settings.h src/main/settings.cpp
    ${TS_FILES}
)

qt_add_executable(bootstrapper-v2
    MANUAL_FINALIZATION

    src/main.cpp
    src/settings/settingswindow.h src/settings/settingswindow.cpp src/settings/settingswindow_slots.cpp src/settings/settingswindow.ui
    src/settings/settings.qrc

    ${PROJECT_SOURCES}

    src/launcher/citiesprocess.h src/launcher/citiesprocess.cpp
    src/main/translatedapplication.h src/main/translatedapplication.cpp
    src/main/consts.h
    src/uninstaller/uninstallerprocess.h src/uninstaller/uninstallerprocess.cpp
)
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ParadoxaDirecta APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_link_libraries(bootstrapper-v2 PRIVATE Qt6::Core Qt6::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(bootstrapper-v2 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
