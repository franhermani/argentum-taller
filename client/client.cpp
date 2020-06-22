#include <SDL2/SDL.h>
#include <iostream>
#include <exception>
#include <unistd.h>
#include "client.h"
#include "sdl/window.h"
#include "sdl/texture.h"
#include "vector"
#include "map"


Client::Client(const char *host, const char *port, const std::string& username,
        const uint8_t race_type, const uint8_t class_type) {
    gameHandler = new GameHandler(host, port, username, race_type, class_type);
}

Client::~Client() {
    delete gameHandler;
}

void Client::connectToServer() {
    gameHandler->run();
}

void Client::disconnectFromServer() {
    gameHandler->stop();
}

