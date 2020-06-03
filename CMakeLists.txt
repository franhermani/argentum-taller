cmake_minimum_required(VERSION 2.8)

project(Argentum)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS -pthread)

set(CLIENT_FILES
        common/socket.cpp
        common/socket.h
        common/socket_accept_error.h
        common/socket_error.cpp
        common/socket_error.h
        common/thread.cpp
        common/thread.h)

set(SERVER_FILES
        common/socket.cpp
        common/socket.h
        common/socket_accept_error.h
        common/socket_error.cpp
        common/socket_error.h
        common/thread.cpp
        common/thread.h)

add_compile_options(-Wall -Werror -pedantic -pedantic-errors)
add_executable(client client/main.cpp ${CLIENT_FILES})
add_executable(server server/main.cpp ${SERVER_FILES})
