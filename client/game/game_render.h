#ifndef GAME_RENDER_H
#define GAME_RENDER_H

#include <string>
#include <vector>
#include <map>
#include <SDL2/SDL_image.h>
#include "../sdl/window.h"
#include "../../common/thread.h"
#include "../../common/defines/terrains.h"
#include "../../common/defines/npcs.h"
#include "../../common/defines/world_structs.h"
#include "map_monitor.h"
#include "game_Surfaces_manager.h"


class GameRender : public Thread {
    const int screenWidth;
    const int screenHeight;
    MapMonitor& mapMonitor;
    int blocksWidth;
    int blocksHeight;
    SDLWindow window;
    GameSurfacesManager surfacesManager;
    //conservamos mundo renderizado en el momento
    // para poder trabajar estructuras interactivas con usuario
    client_world_t current_world;


public:
    //Constructor
    GameRender(const int screenWidth, const int screenHeight,
               MapMonitor &mapMonitor);

    //Destructor
    ~GameRender();

    void run() override;

    // Setea la variable booleana 'keepRunning' en false
    void stop() override;

    // Devuelve true si el thread no esta corriendo o
    // false en caso contrario
    bool isDead() override;

    //Renderizadores
    void renderTerrain(std::vector<std::vector<Terrain>>& matrix);
    void renderPlayers(std::vector<player_t> &players);
    void renderNpcs(std::vector<npc_t>& npcs);
    void renderCreatures(std::vector<creature_t>& creatures);
    void renderPlayerInfo(std::map<int,float>& percentages);
    void renderItems(std::vector<item_t>& items);
    void renderGolds(std::vector<gold_t> &golds);
    void renderEquipped(player_t& player);
    void renderInventory(std::vector<uint8_t>& inventory);
    void renderInventoryGolds(uint16_t quantity);
    void renderGameFrame();


    //Inicializador de SDL
    int init();
    //setea cantidad de bloques recibida por server
    void setTilesSize(int width, int height);

    //Consultas por posicion de click a cosas renderizadas
    int getInventoryItemByPosition(int x, int y);
    int getListItemByPosition(int x, int y);

    // Consultas de clicks dentro de areas renderizadas
    int isClickingListItems(int x, int y);
    int isClickingListGold(int x, int y);
    int isClickingInventoryItems(int x, int y);
    int isClickingInventoryGold(int x, int y);
    };

#endif //ARGENTUM_GAME_RENDER_H
