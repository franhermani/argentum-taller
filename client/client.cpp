#include <SDL2/SDL.h>
#include <iostream>
#include <exception>
#include <unistd.h>
#include "client.h"
#include "sdl/window.h"
#include "sdl/texture.h"
#include "vector"
#include "map"


Client::Client(const char *host, const char *port, const char *username) {
    gameHandler = new GameHandler(host, port, username);
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

