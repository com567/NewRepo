cmake_minimum_required(VERSION 3.16)
project(HdyStudentManager LANGUAGES CXX)

include(qt.cmake)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR})


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Sql
        Widgets
)
qt_standard_project_setup()

set(PROJECT_SOURCES
    main.cpp
    Resource.qrc
    HdyStudentManager.rc
    MainWindow.ui
    MainWindow.h
    MainWindow.cpp
    ContextHolder.h
    ContextHolder.cpp

    Module/Login/LoginPage.ui
    Module/Login/LoginPage.h
    Module/Login/LoginPage.cpp

    Module/FunctionMenu/MenuMgrPage.h
    Module/FunctionMenu/MenuMgrPage.cpp
    Module/FunctionMenu/MenuMgrPage.ui

    Module/Home/Home.h
    Module/Home/Home.cpp
    Module/Home/Home.ui
    Module/Home/HomePage.ui
    Module/Home/HomePage.h
    Module/Home/HomePage.cpp
    Module/Home/Personallnfo/PersonallnfoPage.ui
    Module/Home/Personallnfo/PersonallnfoPage.h
    Module/Home/Personallnfo/PersonallnfoPage.cpp
    
    Common/Delegate/NavTreeDelegate.h
    Common/Delegate/NavTreeDelegate.cpp

    Common/Notify/NotifyTipBox.h
    Common/Notify/NotifyTipBox.cpp
    Common/Notify/NotifyTipManager.h
    Common/Notify/NotifyTipManager.cpp

    Common/Widgets/ClickLabel.h
    Common/Widgets/ClickLabel.cpp
    Common/Widgets/AvatarChoose/AvatarChoose.h
    Common/Widgets/AvatarChoose/AvatarChoose.cpp
    Common/Widgets/AvatarChoose/AvatarChoose.ui
    Common/Widgets/AvatarChoose/AvatarChooseBox.h
    Common/Widgets/AvatarChoose/AvatarChooseBox.cpp
    Common/Widgets/NavigationMenu/Navigation.cpp
    Common/Widgets/NavigationMenu/Navigation.h
    Common/Widgets/MsgBox.h
    Common/Widgets/MsgBox.cpp
    Common/Widgets/MsgBox.ui
    Common/Widgets/ComboBox.h
    Common/Widgets/ComboBox.cpp
    Common/Widgets/HoverButton.h
    Common/Widgets/HoverButton.cpp

    Common/Utils/StringUtils.h
    Common/Utils/StringUtils.cpp
    Common/Utils/CaptchaMaker.h
    Common/Utils/CaptchaMaker.cpp
    Common/Utils/Coating.h
    Common/Utils/Coating.cpp
    Common/Utils/Utils.h
    Common/Utils/Utils.cpp

    Common/Config/Config.h
    Common/Config/Config.cpp

    Dao/MenuDao.h
    Dao/MenuDao.cpp
    Dao/UserDao.h
    Dao/UserDao.cpp
    Dao/DatabaseMap.h
    Dao/DatabaseMap.cpp

    Service/UserService.h
    Service/UserService.cpp
    Service/MenuService.h
    Service/MenuService.cpp
    
)

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        WIN32_EXECUTABLE FALSE
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Sql
        Qt::Widgets
)

