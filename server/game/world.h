#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <vector>
#include <set>
#include <map>
#include <string>
#include "../utilities/math_calculator.h"
#include "params.h"
#include "entities/items/item_factory.h"
#include "../../common/protected_queue.h"
#include "../../common/defines/terrains.h"
#include "entities/living_beings/player.h"
#include "entities/living_beings/creature.h"
#include "entities/npcs/npc.h"
#include "entities/gold.h"
#include "entities/attack.h"

class World {
    Math math;
    GameParams& params;
    ItemFactory& itemFactory;
    std::map<int, ProtectedQueue<std::string>>& messagesQueuePerPlayer;

    std::vector<position_t> safeZonesPositions;
    std::vector<position_t> impenetrablePositions;
    std::vector<position_t> cemeteryPositions;

    // TODO: borrar esto
    std::vector<std::vector<Terrain>> matrix;
    std::set<Terrain> entitiesImpenetrableTerrains;
    std::set<Terrain> attacksImpenetrableTerrains;
    std::set<Terrain> safeZonesTerrains;

    std::vector<Player*> players;
    std::vector<Creature*> creatures;
    std::vector<NPC*> npcs;
    std::vector<Item*> items;
    std::vector<Gold*> golds;
    std::vector<Attack*> attacks;
    int worldWidth, worldHeight;
    int playerWidth, playerHeight;

    // Llena el vector de posiciones de zonas seguras
    void loadSafeZonesPositions();

    // Llena el vector de posiciones del cementerio de criaturas
    void loadCemeteryPositions();

    // Llena el vector de posiciones de terrenos impenetrables
    void loadImpenetrablePositions();

    // TODO: borrar esto
    // Llena el vector de terrenos impenetrables por un player o criatura
    void loadEntitiesImpenetrableTerrains();
    // Llena el vector de terrenos impenetrables por un ataque
    void loadAttacksImpenetrableTerrains();
    // Llena el vector de terrenos considerados zona segura
    void loadSafeZonesTerrains();
    // Llena la matriz (mapa) segun el json generado por Tiled
    void loadMatrix();

    // Determina si una posicion (x,y) esta dentro de los limites de 'player'
    const bool inPlayerBoundaries(Player& player, position_t new_pos);

    // Determina si hay un terreno impenetrable por una entidad
    // en la posicion (x,y)
    const bool entityImpenetrableTerrainInPosition(position_t new_pos);

    // Determina si hay un terreno impenetrable por un ataque
    // en la posicion (x,y)
    const bool attackImpenetrableTerrainInPosition(position_t new_pos);

    // Determina si hay un player en la posicion (x,y)
    const bool playerInPosition(position_t new_pos);

    // Determina si hay una criatura en la posicion (x,y)
    const bool creatureInPosition(position_t new_pos);

    // Determina si hay un NPC en la posicion (x,y)
    const bool NPCInPosition(position_t new_pos);

    // Determina si hay un item en la posicion (x,y)
    const bool itemInPosition(position_t new_pos);

    // Determina si hay un oro en la posicion (x,y)
    const bool goldInPosition(position_t new_pos);

    // Determina si hay una colision de ataque
    // Lo ejecuta en caso afirmativo
    void attackInCollision(Attack* new_attack);

    // Elimina los ataques que llegaron a su rango de alcance
    void removeRangeReachedAttacks();

public:
    // Constructor
    explicit World(GameParams& params, ItemFactory& item_factory,
            std::map<int,ProtectedQueue<std::string>>& messagesQueuePerPlayer);

    // Constructor y asignacion por copia deshabilitados
    World(const World& other) = delete;
    World& operator=(const World& other) = delete;

    // Destructor
    // Libera la memoria reservada para los items que esten en el mundo
    ~World();

    // -------------------------------------------- //
    // Metodos accedidos por threads (WorldMonitor) //
    // -------------------------------------------- //

    // Actualiza el mundo segun los milisegundos recibidos
    // Simula el paso del tiempo llamando al metodo update()
    // de todos los players y npcs
    void update(const int ms);

    // Agrega un Player al mundo
    void addPlayer(Player* player);

    // Remueve un Player del mundo segun su ID
    void removePlayer(const int id);

    // Devuelve los bloques de vision del player (en ancho)
    const int getPlayerWidth();

    // Devuelve los bloques de vision del player (en alto)
    const int getPlayerHeight();

    // Devuelve la matriz del mapa completo
    std::vector<std::vector<Terrain>> getMatrix() const;

    // Devuelve un vector de todos los npcs
    std::vector<NPC*> getNPCs() const;

    // Devuelve un vector de todos los players en la sub-matriz de 'player'
    // Incluye al mismo 'player' recibido por parametro
    std::vector<Player*> getPlayersAround(Player& player);

    // Devuelve un vector de todas las criaturas en la sub-matriz de 'player'
    std::vector<Creature*> getCreaturesAround(Player& player);

    // Devuelve un vector de todos los items en la sub-matriz de 'player'
    std::vector<Item*> getItemsAround(Player& player);

    // Devuelve un vector de todos los oros en la sub-matriz de 'player'
    std::vector<Gold*> getGoldsAround(Player& player);

    // Devuelve un vector de todos los ataques en la sub-matriz de 'player'
    std::vector<Attack*> getAttacksAround(Player& player);

    // Devuelve la base del mapa
    const int getWidth() const;

    // Devuelve la altura del mapa
    const int getHeight() const;

    // ------------------------------------------- //
    // Metodos accedidos por entidades del dominio //
    // ------------------------------------------- //

    // Determina si la posicion (x,y) esta dentro de los limites del mapa
    const bool inMapBoundaries(position_t new_pos);

    // Determina si hay un terreno considerado zona segura
    // en la posicion (x,y)
    const bool inSafeZone(position_t new_pos);

    // Determina si hay una colision de entidad en la posicion (x,y)
    const bool entityInCollision(position_t new_pos);

    // Determina si hay una colision de item en la posicion (x,y)
    const bool itemInCollision(position_t new_pos);

    // Agrega un item al mundo
    void addItem(Item* item);

    // Agrega un item al mundo segun 'type'
    void addItem(const int type, position_t new_pos);

    // Remueve un item del mundo segun su pos (x,y)
    Item* removeItem(position_t new_pos);

    // Agrega un oro al mundo
    void addGold(Gold* gold);

    // Remueve un oro del mundo segun su pos (x,y)
    Gold* removeGold(position_t new_pos);

    // Agrega un ataque al mundo
    void addAttack(Attack* new_attack);

    // Devuelve el NPC asociado a la posicion (pos_x, pos_y)
    NPC* getNPCByPos(position_t new_pos) const;

    // Devuelve la posicion del player mas cercano
    // a la posicion (pos_x, pos_y)
    position_t getClosestPlayerPos(position_t new_pos);

    // Devuelve la distancia en bloques de una posicion (x, y) a otra
    const int distanceInBlocks(position_t pos1, position_t pos2);

    // Devuelve la posicion del sacerdote mas cercano
    // a la posicion (pos_x, pos_y)
    position_t getClosestPriestPos(position_t new_pos);

    // Devuelve la distancia en ms de una posicion (pos_x, pos_y)
    // a la del sacerdote mas cercano segun la velocidad dada
    const int distanceInMsToClosestPriest(position_t new_pos,
            const int velocity);

    // Devuelve el largo maximo del inventario
    const int getInventoryLength() const;

    // Devuelve el nivel maximo de un newbie
    const int getMaxLevelNewbie() const;

    // Devuelve la diferencia de niveles maxima para atacar
    const int getMaxLevelDiff() const;

    // --------------------------------- //
    // Metodos accedidos por GameManager //
    // --------------------------------- //

    // Agrega un NPC al mundo
    void addNPC(NPC* npc);

    // Agrega una criatura al mundo
    void addCreature(Creature* creature);

    // Devuelve una posicion random para un player
    position_t loadPlayerPosition();

    // Devuelve una posicion random para una criatura fuera de una zona segura
    position_t loadCreaturePosition();

    // Devuelve una posicion random para un NPC dentro de una zona segura
    position_t loadNPCPosition();
};

#endif // GAME_WORLD_H
