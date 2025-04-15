cmake_minimum_required(VERSION 3.19)
project(kursovaya LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(kursovaya
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    autorization.cpp
    autorization.h
    autorization.ui
    main_lection.h
    main_lection.cpp
    main_lection.ui
    dialog_window_exit.h dialog_window_exit.cpp dialog_window_exit.ui
    zadania1.h zadania1.cpp zadania1.ui
    zadania2.h zadania2.cpp zadania2.ui
    zadania3.h zadania3.cpp zadania3.ui
    zadania4.h zadania4.cpp zadania4.ui
    test1.h test1.cpp test1.ui
    test2.h test2.cpp test2.ui
    test3.h test3.cpp test3.ui


)

target_link_libraries(kursovaya
    PRIVATE
    Qt::Core
    Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS kursovaya
    BUNDLE DESTINATION .
    RUNTIME DESTINATION CMAKE_INSTALL_BINDIR
    LIBRARY DESTINATION CMAKE_INSTALL_LIBDIR
)

qt_generate_deploy_app_script(
    TARGET kursovaya
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
