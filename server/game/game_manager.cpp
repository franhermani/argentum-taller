#include <string>
#include <thread>
#include <chrono>
#include "game_manager.h"
#include "game_exception.h"
#include "list_exception.h"
#include "entities/npcs/priest.h"
#include "entities/npcs/merchant.h"
#include "entities/npcs/banker.h"
#include "../../common/defines/commands.h"
#include "../../common/defines/creatures.h"

GameManager::GameManager(File& config_file) :
worldFile(jsonParser.getConfigParams(config_file)["world_path"]),
params(jsonParser.getConfigParams(config_file),
        jsonParser.getWorldParams(worldFile)),
itemFactory(params.getConfigParams()["items"]),
equations(params.getConfigParams()),
world(params, itemFactory, messagesQueuePerPlayer),
worldMonitor(world),
msPerSend(params.getConfigParams()["ms_per_send"]) {
    keepRunning = true;
    isRunning = true;

    spawnNPCs();
    spawnCreatures();
}

void GameManager::run() {
    using clock = std::chrono::system_clock;
    using ms = std::chrono::milliseconds;

    int ms_per_update = params.getConfigParams()["ms_per_update"];

    while (keepRunning) {
        auto start = clock::now();
        while (! commandQueue.isEmpty()) {
            try {
                Command* command = commandQueue.pop();
                try {
                    command->execute(world);
                } catch (GameException& e) {
                    std::string message(e.what());
                    messagesQueuePerPlayer[e.getPlayerId()].push(message);
                } catch (ListException& e) {
                    listsQueuePerPlayer[e.getPlayerId()].push(e.getList());
                }
                delete command;
            } catch(ClosedQueueException&) {
                break;
            }
        }
        worldMonitor.update(ms_per_update);
        auto end = clock::now();
        auto elapsed = std::chrono::duration_cast<ms>(end - start).count();
        auto time_to_sleep = ms_per_update - elapsed;
        if (time_to_sleep > 0) std::this_thread::sleep_for(ms(time_to_sleep));
    }
    isRunning = false;
}

void GameManager::stop() {
    commandQueue.close();

    for (auto& kv : messagesQueuePerPlayer)
        messagesQueuePerPlayer[kv.first].close();

    for (auto& kv : listsQueuePerPlayer)
        listsQueuePerPlayer[kv.first].close();

    keepRunning = false;
}

bool GameManager::isDead() {
    return (! isRunning);
}

const int GameManager::addIdByUsername(const std::string &username) {
    return idManager.addPlayerByUsername(username);
}

void GameManager::addPlayerToWorld(Player* player) {
    worldMonitor.addPlayer(player);
}

void GameManager::removePlayerFromWorld(const int id) {
    worldMonitor.removePlayer(id);
}

void GameManager::removeUsername(const std::string& username) {
    idManager.removeUsername(username);
}

void GameManager::spawnNPCs() {
    json js = params.getConfigParams()["npcs"];

    int num_priests = js["priest"]["quantity"],
        num_merchants = js["merchant"]["quantity"],
        num_bankers = js["banker"]["quantity"];

    int orientation;

    position_t new_pos{};
    int i;
    for (i = 0; i < num_priests; i ++) {
        new_pos = world.loadNPCPosition();
        orientation = math.randomInt(LEFT, DOWN);
        world.addNPC(new Priest(itemFactory, new_pos, orientation));
    }
    for (i = 0; i < num_merchants; i ++) {
        new_pos = world.loadNPCPosition();
        orientation = math.randomInt(LEFT, DOWN);
        world.addNPC(new Merchant(itemFactory, new_pos, orientation,
                js["merchant"]["max_items"]));
    }
    for (i = 0; i < num_bankers; i ++) {
        new_pos = world.loadNPCPosition();
        orientation = math.randomInt(LEFT, DOWN);
        world.addNPC(new Banker(bank, new_pos, orientation));
    }
}

void GameManager::spawnCreatures() {
    json js = params.getConfigParams()["creatures"];
    json js_level = js["level"];
    int min_level = js_level["min"], max_level = js_level["max"],
        interval = js_level["interval"], level;

    int num_goblins = js["goblin"]["quantity"],
        num_skeletons = js["skeleton"]["quantity"],
        num_zombies = js["zombie"]["quantity"],
        num_spiders = js["spider"]["quantity"];

    int i;
    for (i = 0; i < num_goblins; i ++) {
        level = (i * interval) % max_level;
        if (level < min_level) level = min_level;
        world.addCreature(new Creature(world, equations,
                idManager.addCreatureById(), GOBLIN, level,
                js["goblin"]["move_velocity"],
                js["goblin"]["attack_velocity"],
                js["goblin"]["respawn_velocity"]));
    }
    for (i = 0; i < num_skeletons; i ++) {
        level = (i * interval) % max_level;
        if (level < min_level) level = min_level;
        world.addCreature(new Creature(world, equations,
                idManager.addCreatureById(), SKELETON, level,
                js["skeleton"]["move_velocity"],
                js["skeleton"]["attack_velocity"],
                js["skeleton"]["respawn_velocity"]));
    }
    for (i = 0; i < num_zombies; i ++) {
        level = (i * interval) % max_level;
        if (level < min_level) level = min_level;
        world.addCreature(new Creature(world, equations,
                idManager.addCreatureById(), ZOMBIE, level,
                js["zombie"]["move_velocity"],
                js["zombie"]["attack_velocity"],
                js["zombie"]["respawn_velocity"]));
    }
    for (i = 0; i < num_spiders; i ++) {
        level = (i * interval) % max_level;
        if (level < min_level) level = min_level;
        world.addCreature(new Creature(world, equations,
                idManager.addCreatureById(), SPIDER, level,
                js["spider"]["move_velocity"],
                js["spider"]["attack_velocity"],
                js["spider"]["respawn_velocity"]));
    }
}
