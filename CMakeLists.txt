cmake_minimum_required(VERSION 2.8)

project(Argentum)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS -pthread)

# CLIENT SOURCE FILES
file(GLOB_RECURSE CLIENT_FILES "client/*.cpp" "client/*.h" "common/*.cpp" "common/*.h")

# SERVER SOURCE FILES
file(GLOB_RECURSE SERVER_FILES "server/*.cpp" "server/*.h" "common/*.cpp" "common/*.h")

# SDL LIBRARY
file(GLOB SDL_FILES "client/sdl/*.cpp")
add_library(sdl-lib ${SDL_FILES})

# COMPILATION
add_compile_options(-Wall -Werror -pedantic -pedantic-errors)

# EXECUTABLE
add_executable(client client/main.cpp ${CLIENT_FILES})
add_executable(server server/main.cpp ${SERVER_FILES})

# LINK LIBRARIES
target_link_libraries(client sdl-lib SDL2 SDL2_image SDL2_ttf SDL2_mixer)
