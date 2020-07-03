#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <vector>
#include <set>
#include "params.h"
#include "../../common/defines/terrains.h"
#include "entities/player.h"
#include "entities/npcs_and_creatures/creature.h"
#include "entities/npcs_and_creatures/npc.h"
#include "entities/gold.h"
#include "entities/attack.h"

class World {
    GameParams& params;
    std::vector<std::vector<Terrain>> matrix;
    std::set<Terrain> entitiesImpenetrableTerrains;
    std::set<Terrain> attacksImpenetrableTerrains;
    std::vector<Player*> players;
    std::vector<Creature*> creatures;
    std::vector<NPC*> npcs;
    std::vector<Item*> items;
    std::vector<Gold*> golds;
    std::vector<Attack*> attacks;
    int worldWidth, worldHeight;
    int playerWidth, playerHeight;

    // Llena el vector de terrenos impenetrables por un player o criatura
    void loadEntitiesImpenetrableTerrains();

    // Llena el vector de terrenos impenetrables por un ataque
    void loadAttacksImpenetrableTerrains();

    // Llena la matriz (mapa) segun el json generado por Tiled
    void loadMatrix();

    // Determina si una posicion (x,y) esta dentro de los limites de 'player'
    const bool inPlayerBoundaries(Player& player,
            const int pos_x, const int pos_y);

    // Detecta una colision de ataque y lo ejecuta en caso de colisionar
    void detectAttackCollision(Attack* new_attack);

    // Elimina los ataques que llegaron a su rango de alcance
    void removeRangeReachedAttacks();

public:
    // Constructor
    explicit World(GameParams& params);

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

    // Devuelve la base del mapa
    const int getWidth() const;

    // Devuelve la altura del mapa
    const int getHeight() const;

    // ------------------------------------------- //
    // Metodos accedidos por entidades del dominio //
    // ------------------------------------------- //

    // Determina si la posicion (x,y) esta dentro de los limites del mapa
    const bool inMapBoundaries(const int pos_x, const int pos_y);

    // Determina si hay algun Player o NPC en la posicion (x,y)
    const bool inCollision(const int pos_x, const int pos_y);

    // Determina si hay algun Item en la posicion (x,y)
    const bool itemInPosition(const int pos_x, const int pos_y);

    // Agrega un item al mundo
    void addItem(Item* item);

    // Remueve un item del mundo segun su pos (x,y)
    Item* removeItem(const int pos_x, const int pos_y);

    // Agrega un oro al mundo
    void addGold(Gold* gold);

    // Remueve un oro del mundo segun su pos (x,y)
    Gold* removeGold(const int pos_x, const int pos_y);

    // Agrega un ataque al mundo
    void addAttack(Attack* new_attack);

    // Devuelve el NPC asociado a la posicion (pos_x, pos_y)
    NPC* getNPCByPos(const int pos_x, const int pos_y) const;

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

    // Devuelve una posicion random para un NPC dentro de una zona segura
    std::vector<int> loadNPCPosition();

    // Devuelve una posicion random para una criatura fuera de una zona segura
    std::vector<int> loadCreaturePosition();
};

#endif // GAME_WORLD_H
