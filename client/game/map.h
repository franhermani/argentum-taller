
#ifndef ARGENTUM_MAP_H
#define ARGENTUM_MAP_H
#include "../../common/defines/world_structs.h"
#include "map_structs.h"
#include <map>
#include <vector>
#include <atomic>

class Map {
    world_t world;
    npcs_t npcs;
    list_t list;
    player_t mainPlayer;
    //el 108
    std::vector<int> mapDimensions;
    std::atomic<bool> interactingWithNpc;
    int username_id;
    //el 9
    int playerVisionWidth;
    int playerVisionHeight;

    //Dada la posicion de un jugador, devuelve la posicion donde
    // arrancaria en X su submatriz dentro de la matriz principal
    int getPlayerXStart(player_t& player);

    //Dada la posicion de un jugador, devuelve la posicion donde
    // arrancaria en Y su submatriz dentro de la matriz principal
    int getPlayerYStart(player_t& player);

    //Dada la posicion de un jugador, devuelve la posicion donde
    // terminaria en X su submatriz dentro de la matriz principal
    int getPlayerXEnd(player_t& player);

    //Dada la posicion de un jugador, devuelve la posicion donde
    // terminaria en Y su submatriz dentro de la matriz principal
    int getPlayerYEnd(player_t& player);

    int betweenPlayerBorders(int pos_x, int pos_y);


    //busca en la lista actual de jugadores y devuelve el principal
    player_t findMainPlayer();


    uint16_t getNewBordersXPosition(uint16_t pos_x, player_t& main_player);
    uint16_t getNewBordersYPosition(uint16_t pos_y, player_t& main_player);


    // devuelve los npcs/players/criatura/item
    // dentro del rango de vision del jguador principal
    // con posiciones actualizadas a la submatriz
    std::vector<player_t> findRenderablePlayers();
    std::vector<npc_t> findRenderableNpcs();
    std::vector<creature_t> findRenderableCreatures();
    std::vector<item_t> findRenderableItems();
    std::vector<gold_t> findRenderableGolds();
    std::vector<attack_t> findRenderableAttacks();

public:
    // constructor
    Map();
    // destructor
    ~Map();

    // Constructor y asignacion por copia deshabilitados
    Map(const Map&) = delete;
    Map& operator=(const Map&) = delete;

    //inicializa matriz
    void initialize(int username_id, std::vector<int>&
            blocks_around, npcs_t& npcs, std::vector<int>& map_dimensions);

    //actualiza el vector de jugadores recibido del server
    void updateWorld(world_t receivedWorld, list_t list);

    // devuelve npc/posicion al que se mira
    std::vector<int> getPositionLookingAt();
    std::vector<int> getPriestLookingAt();
    std::vector<int> getNpcLookingAt();

    //devuelve item/posicion donde se esta prado
    std::vector<int> getPositionStandingAt();
    std::vector<int> getItemStandingAt();
    std::vector<int> getGoldStandingAt();

    // getters de campo de vision del jugador
    int getPlayerVisionWidth();
    int getPlayerVisionHeight();
    std::vector<int> getDimensions();

    //devuelve infomacion del estado actual del mundo
    client_world_t getCurrentWorld();

    std::map<int, float> getPercentages();


    //npc interaction related functions
    void interact();
    void uninteract();
    int isInteracting();
    };




#endif //ARGENTUM_MAP_H
