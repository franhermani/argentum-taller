#include "meditate_command.h"

MeditateCommand::MeditateCommand(Player& player) : player(player) {}

MeditateCommand::~MeditateCommand() = default;

void MeditateCommand::execute(World& world) {
    player.meditate();
}
