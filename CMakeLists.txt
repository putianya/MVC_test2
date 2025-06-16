cmake_minimum_required(VERSION 3.16)

project(StudentManagerSystem VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Charts)

set(PROJECT_SOURCES
        main.cpp
        model/databasemanager.h model/databasemanager.cpp
        model/studentmodel.h model/studentmodel.cpp
        model/schedulemodel.h model/schedulemodel.cpp
        model/financialmodel.h model/financialmodel.cpp
        controller/studentcontroller.h controller/studentcontroller.cpp
        controller/schedulecontroller.h controller/schedulecontroller.cpp
        controller/financialcontroller.h controller/financialcontroller.cpp
        view/mainwindow.h view/mainwindow.cpp view/mainwindow.ui
        view/studentinfowidget.h view/studentinfowidget.cpp view/studentinfowidget.ui
        view/schedulewidget.h view/schedulewidget.cpp view/schedulewidget.ui
        view/financialwidget.h view/financialwidget.cpp view/financialwidget.ui
        view/honorwallwidget.h view/honorwallwidget.cpp view/honorwallwidget.ui
        view/logindialog.h view/logindialog.cpp view/logindialog.ui
        view/systemsettingswidget.h view/systemsettingswidget.cpp view/systemsettingswidget.ui
        view/settings.h view/settings.cpp
        utils/tabledelegates.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(StudentManagerSystem
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        res.qrc
    )
else()
    if(ANDROID)
        add_library(StudentManagerSystem SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(StudentManagerSystem
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(StudentManagerSystem PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Sql Qt6::Charts)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.StudentManagerSystem)
endif()
set_target_properties(StudentManagerSystem PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS StudentManagerSystem
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(StudentManagerSystem)
endif()

include_directories(
     ${PROJECT_SOURCE_DIR}
)
