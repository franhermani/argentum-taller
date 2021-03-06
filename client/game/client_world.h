
#ifndef ARGENTUM_CLIENT_WORLD_H
#define ARGENTUM_CLIENT_WORLD_H
#include "../../common/defines/world_structs.h"
#include "map_structs.h"
#include <map>
#include <vector>
#include <atomic>

class ClientWorld {
    world_t world;
    npcs_t npcs;
    list_t list;
    player_t mainPlayer;
    std::vector<int> mapDimensions;
    std::atomic<bool> interactingWithNpc;
    int username_id;
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
    ClientWorld();
    // destructor
    ~ClientWorld();

    // Constructor y asignacion por copia deshabilitados
    ClientWorld(const ClientWorld&) = delete;
    ClientWorld& operator=(const ClientWorld&) = delete;

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

    // Funcion template que busca en vision
    template<typename T>
    std::vector<T> findVisible(std::vector<T> vec);
};




#endif //ARGENTUM_CLIENT_WORLD_H
