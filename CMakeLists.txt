cmake_minimum_required(VERSION 2.8)

project(Argentum)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS -pthread)

file(GLOB CLIENT_FILES "client/*.cpp" "client/*.h" "common/*.cpp" "common/*.h")
file(GLOB SERVER_FILES "server/*.cpp" "server/*.h" "common/*.cpp" "common/*.h")

add_compile_options(-Wall -Werror -pedantic -pedantic-errors)
add_executable(client client/main.cpp ${CLIENT_FILES})
add_executable(server server/main.cpp ${SERVER_FILES})
