cmake_minimum_required(VERSION 3.16)

project(ParadoxaDirecta
    VERSION 0.1.0
    DESCRIPTION "An alternative to the Paradox Launcher of Cities: Skylines."
    HOMEPAGE_URL https://github.com/neila-a/ParadoxaDirecta
    LANGUAGES CXX
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_VERSION_MAJOR 6)

set(CMAKE_PREFIX_PATH /media/neila/MobileDisk/programs/ubin/Qt/6.8.0/gcc_64/lib/cmake/)
find_package(Qt6 REQUIRED COMPONENTS Widgets LinguistTools)

add_subdirectory(qt-material-widgets/)

set(TS_FILES ParadoxaDirecta_zh_CN.ts)

set(PROJECT_SOURCES
    ${TS_FILES}
)

add_library(setting SHARED)
target_link_libraries(setting PRIVATE Qt6::Core)
target_sources(setting PRIVATE
    src/main/consts.h
    src/main/settings.h src/main/settings.cpp
)

add_library(translatedapplication SHARED)
target_link_libraries(translatedapplication PUBLIC Qt6::Core Qt6::Widgets)
target_sources(translatedapplication PRIVATE
    src/main/translatedapplication.h src/main/translatedapplication.cpp
)

qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

qt_add_executable(bootstrapper-v2
    MANUAL_FINALIZATION
    src/launcher/main.cpp
    src/launcher/citiesprocess.h src/launcher/citiesprocess.cpp
    ${PROJECT_SOURCES}
)
target_link_libraries(bootstrapper-v2 PRIVATE setting translatedapplication)
set_target_properties(bootstrapper-v2 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

qt_add_executable(settings
    MANUAL_FINALIZATION

    src/settings/main.cpp

    src/settings/settingswindow.h
    src/settings/settingswindow.cpp
    src/settings/settingswindow_slots.cpp

    src/settings/settingswindow.ui
    src/settings/settings.qrc

    src/uninstaller/uninstallerprocess.h
    src/uninstaller/uninstallerprocess.cpp

    ${PROJECT_SOURCES}
)
target_link_libraries(settings PRIVATE setting translatedapplication)
set_target_properties(settings PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

qt_add_executable(uninstaller
    MANUAL_FINALIZATION
    src/uninstaller/main.cpp
    ${PROJECT_SOURCES}

)
target_link_libraries(uninstaller PRIVATE setting translatedapplication)
set_target_properties(uninstaller PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Packaging support
install(TARGETS bootstrapper-v2 setting settings translatedapplication uninstaller DESTINATION .)

# Pack
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_CONTANT "neilaspace@outlook.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Neila")
set(CPACK_DEBIAN_PACKAGE_SECTION "games")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
include(CPack)
