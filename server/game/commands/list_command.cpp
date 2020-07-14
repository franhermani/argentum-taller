#include "list_command.h"
#include "../world.h"
#include "../game_exception.h"
#include "../list_exception.h"

ListCommand::ListCommand(Player& player, const uint16_t npc_pos_x,
        const uint16_t npc_pos_y) :
player(player), NPCPosX(npc_pos_x), NPCPosY(npc_pos_y) {}

ListCommand::~ListCommand() = default;

void ListCommand::execute(World& world) {
    if (player.isDead())
        throw GameException(player.getId(), "Eres un fantasma. No puedes "
                                       "interactuar con NPCs");

    if (player.isWaitingToRevive())
        throw GameException(player.getId(),
                "No puedes ejecutar ningun comando hasta que termines de "
                "revivir. Quedan aprox. %d segundos",
                player.secondsToRevive());

    NPC* npc = world.getNPCByPos(position_t(NPCPosX, NPCPosY));
    throw ListException(player.getId(), npc->listItems(player));
}
