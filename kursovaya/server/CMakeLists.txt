cmake_minimum_required(VERSION 3.19)
project(server_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем автоматический MOC/UIT/RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Sql Network)
find_package(PostgreSQL REQUIRED)

# Источники и заголовки
set(SOURCES
    main.cpp
    server.cpp
    handler.cpp
    database.cpp
)

set(HEADERS
    server.h
    handler.h
    database.h
)

add_executable(server_app ${SOURCES} ${HEADERS})

target_link_libraries(server_app
    PRIVATE Qt6::Core Qt6::Sql Qt6::Network
    PostgreSQL::PostgreSQL
)
