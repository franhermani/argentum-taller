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
    // TODO arreglar private y public

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

    //Renderizador de pisos
    void renderTerrain(std::vector<std::vector<Terrain>>& matrix);

    //Renderizador de players
    void renderPlayers(std::vector<player_t> &players);

    //renderizador de npcs
    void renderNpcs(std::vector<npc_t>& npcs);

    void renderCreatures(std::vector<creature_t>& creatures);

    void renderItems(std::vector<item_t>& items);


    //Inicializador de SDL
    int init();

    void setTilesSize(int width, int height);

    std::map<int, float> getRenderablePlayerInfo();

    int getInventoryItemByPosition(int x, int y);
    int getListItemByPosition(int x, int y);

    int isClickingListItems(int x, int y);
    int isClickingListGold(int x, int y);
    int isClickingInventoryItems(int x, int y);
    int isClickingInventoryGold(int x, int y);
    };

#endif //ARGENTUM_GAME_RENDER_H
