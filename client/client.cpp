#include "client.h"

Client::Client(const char *host, const char *port) :
socket(host, port, false), keepPlaying(true) {}

void Client::play() {
    // TODO: ...
}
