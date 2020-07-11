#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "window.h"
#include "../sdl/exception.h"
#define INVENTORY_MAX_TILES_WIDTH 2
#define INVENTORY_MAX_TILES_HEIGHT 5
#define EQUIPPED_MAX_TILES_WIDTH 4
#define LIST_MAX_TILES_WIDTH 10

SDLWindow::SDLWindow(const int screenWidth, const int screenHeight):
                screenHeight(screenHeight), screenWidth(screenWidth),
                measurements(){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        throw SDLException("\nError al inicializar SDL", SDL_GetError());

    if (SDL_CreateWindowAndRenderer(screenWidth, screenHeight,
            SDL_RENDERER_ACCELERATED, &window, &renderer) < 0)
        throw SDLException("\nError al crear la ventana", SDL_GetError());
    //todo aca chequeo de excepciones
    if (TTF_Init() < 0) {
        throw SDLException("\nNo se pudo inicializar ttf", SDL_GetError());
    }

}

SDLWindow::~SDLWindow() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}


void SDLWindow::fill(const int r, const int g, const int b, const int alpha) {
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderClear(renderer);
}

void SDLWindow::render() {
    SDL_RenderPresent(renderer);
}

SDL_Renderer* SDLWindow::getRenderer() const {
    return renderer;
}
SDL_Surface* SDLWindow::getSurface() const {
    return SDL_GetWindowSurface(window);
}

SDL_PixelFormat* SDLWindow::getSurfaceFormat() const {
    return SDL_GetWindowSurface(window)->format;
}

void SDLWindow::renderMapObject(int x, int y, Surface* character_surface) {
    game_area_t& frame_area = measurements.frame;
    SDL_Rect stretchRect;
    stretchRect.x = getXPixelPos(x);
    stretchRect.y = getYPixelPos(y);
    stretchRect.w = measurements.xWidthTileSize;
    stretchRect.h = measurements.yHeightTileSize;
    if ((stretchRect.x+measurements.xWidthTileSize
        >= frame_area.x_pixel_end) ||
        (stretchRect.y+measurements.yHeightTileSize
        >= frame_area.y_pixel_end)) return;
    SDL_BlitScaled(character_surface->getRenderableSurface(), NULL,
            getSurface(), &stretchRect);
}

void SDLWindow::renderTerrain(std::vector<std::vector<Terrain>>& matrix,
                              std::map<Terrain, Surface*>& surfaces_map) {
    int height_size = matrix.size();
    if (height_size <= 0) return;
    int width_size = matrix[0].size();
    if (width_size <= 0) return;
    SDL_Rect stretchRect;
    for (int y=0; y < height_size; y++) {
        for (int x=0; x < width_size; x++) {
            stretchRect.x = getXPixelPos(x);
            stretchRect.y = getYPixelPos(y);
            stretchRect.w = measurements.xWidthTileSize;
            stretchRect.h = measurements.yHeightTileSize;
            if (surfaces_map.find(matrix[y][x]) != surfaces_map.end()) {
                SDL_BlitScaled(surfaces_map.at(matrix[y][x])->
                getRenderableSurface(), NULL,
                getSurface(), &stretchRect);
            } else {
                SDL_BlitScaled(surfaces_map.at(TERRAIN_GRASS)->
                getRenderableSurface(), NULL,
                getSurface(), &stretchRect);
            }
        }
    }
}
void SDLWindow::renderEquipped(player_t& player,
                              std::map<int, Surface*>& surfaces_map) {
    game_area_t& equipped_area = measurements.equipped;
    int equipped_width = (equipped_area.x_pixel_end -
            equipped_area.x_pixel_begin) / EQUIPPED_MAX_TILES_WIDTH;
    SDL_Rect stretchRect;
    stretchRect.x = equipped_area.x_pixel_begin;
    stretchRect.y = equipped_area.y_pixel_begin;
    stretchRect.w = equipped_width;
    stretchRect.h = equipped_area.y_pixel_end-equipped_area.y_pixel_begin;
    //weapon
    if (player.weapon != NO_ITEM_EQUIPPED)
    SDL_BlitScaled(surfaces_map.at(player.weapon)->
                           getRenderableSurface(), NULL,
                   getSurface(), &stretchRect);
    //armor
    stretchRect.x = stretchRect.x + equipped_width;
    if (player.armor != NO_ITEM_EQUIPPED)
    SDL_BlitScaled(surfaces_map.at(player.armor)->
                           getRenderableSurface(), NULL,
                   getSurface(), &stretchRect);
    //helmet
    stretchRect.x = stretchRect.x + equipped_width;
    if (player.helmet != NO_ITEM_EQUIPPED)
    SDL_BlitScaled(surfaces_map.at(player.helmet)->
                           getRenderableSurface(), NULL,
                   getSurface(), &stretchRect);
    //shield
    stretchRect.x = stretchRect.x + equipped_width;
    if (player.shield != NO_ITEM_EQUIPPED)
    SDL_BlitScaled(surfaces_map.at(player.shield)->
                           getRenderableSurface(), NULL,
                   getSurface(), &stretchRect);
}

int SDLWindow::getXPixelPos(int x_tile_position) {
    game_area_t& frame_area = measurements.frame;
    return frame_area.x_pixel_begin + x_tile_position *
        measurements.xWidthTileSize;
}
int SDLWindow::getYPixelPos(int y_tile_position) {
    game_area_t& frame_area = measurements.frame;
    return frame_area.y_pixel_begin + y_tile_position *
        measurements.yHeightTileSize;
}


void SDLWindow::UpdateWindowSurface() {
    SDL_UpdateWindowSurface(window);
}

void SDLWindow::renderGameFrame(Surface* surface) {
    SDL_BlitScaled(surface->getRenderableSurface(), NULL,
                   getSurface(), &measurements.gameFrameStaticRect);
}

void SDLWindow::renderInventoryGolds(Surface* surface, Surface* quantity) {
    SDL_BlitScaled(quantity->getRenderableSurface(), NULL,
                   getSurface(), &measurements.inventoryGoldStaticRect);
}


void SDLWindow::renderListGold(Surface* surface) {
    SDL_BlitScaled(surface->getRenderableSurface(), NULL,
                   getSurface(), &measurements.listGoldStaticRect);
}


void SDLWindow::renderInventory(std::vector<uint8_t>& inventory,
        std::map<int,Surface*>& surfaces) {
    game_area_t& inventory_area = measurements.inventory;
    int x,y, w, h;
    w = (inventory_area.x_pixel_end-inventory_area.x_pixel_begin)/
            INVENTORY_MAX_TILES_WIDTH;
    h = (inventory_area.y_pixel_end-inventory_area.y_pixel_begin)/
            INVENTORY_MAX_TILES_HEIGHT;
    x = inventory_area.x_pixel_begin;
    y = inventory_area.y_pixel_begin;
    int surfaces_size = inventory.size();
    int current_index = 0;
    while (current_index < surfaces_size) {
        SDL_Rect stretchRect;
        stretchRect.x = x;
        stretchRect.y = y;
        stretchRect.w = w;
        stretchRect.h = h;
        SDL_BlitScaled(surfaces[inventory[current_index]]->
                        getRenderableSurface(), NULL,
                       getSurface(), &stretchRect);
        y = y + h;
        current_index ++;
        if (current_index == INVENTORY_MAX_TILES_HEIGHT){
            x = x + w;
            y = inventory_area.y_pixel_begin;
        }
    }
}

void SDLWindow::renderLife(std::map<int, float>& player_info,
                           std::map<int, Surface *> info_surfaces_map) {
    game_area_t& life_area = measurements.life;
    SDL_Rect stretchRect;
    float life_percentage = player_info[LIFE];
    stretchRect.x = life_area.x_pixel_begin;
    stretchRect.y = life_area.y_pixel_begin;
    stretchRect.w = (int) ((float)(life_area.x_pixel_end -
                                   life_area.x_pixel_begin))*life_percentage;
    stretchRect.h = life_area.y_pixel_end - life_area.y_pixel_begin;

    SDL_BlitScaled(info_surfaces_map[LIFE]->getRenderableSurface(), NULL,
                   getSurface(), &stretchRect);

    stretchRect.x = stretchRect.x + stretchRect.w;
    stretchRect.y = life_area.y_pixel_begin;
    stretchRect.w = life_area.x_pixel_end -
            life_area.x_pixel_begin - stretchRect.w;
    stretchRect.h = life_area.y_pixel_end - life_area.y_pixel_begin;
    SDL_BlitScaled(info_surfaces_map[BACKGROUND]->getRenderableSurface(), NULL,
                   getSurface(), &stretchRect);
}

void SDLWindow::renderMana(std::map<int, float>& player_info,
                           std::map<int, Surface *> info_surfaces_map) {
    SDL_Rect stretchRect;

    game_area_t& mana_area = measurements.mana;
    float mana_percentage = player_info[MANA];
    stretchRect.x = mana_area.x_pixel_begin;
    stretchRect.y = mana_area.y_pixel_begin;
    stretchRect.w = (int) ((float)(mana_area.x_pixel_end -
                                   mana_area.x_pixel_begin))*mana_percentage;
    stretchRect.h = mana_area.y_pixel_end - mana_area.y_pixel_begin;
    SDL_BlitScaled(info_surfaces_map[MANA]->getRenderableSurface(), NULL,
                   getSurface(), &stretchRect);

    stretchRect.x = stretchRect.x + stretchRect.w;
    stretchRect.y = mana_area.y_pixel_begin;
    stretchRect.w = mana_area.x_pixel_end -
            mana_area.x_pixel_begin - stretchRect.w;
    stretchRect.h = mana_area.y_pixel_end - mana_area.y_pixel_begin;
    SDL_BlitScaled(info_surfaces_map[BACKGROUND]->getRenderableSurface(), NULL,
                   getSurface(), &stretchRect);
}

void SDLWindow::renderExperience(std::map<int, float>& player_info,
                           std::map<int, Surface *> info_surfaces_map) {
    SDL_Rect stretchRect;
    game_area_t& experience_area = measurements.experience;

    float experience_percentage = player_info[EXPERIENCE];
    stretchRect.x = experience_area.x_pixel_begin;
    stretchRect.y = experience_area.y_pixel_begin;
    stretchRect.w = (int) ((float)(experience_area.x_pixel_end -
            experience_area.x_pixel_begin))*experience_percentage;
    stretchRect.h = experience_area.y_pixel_end -
                    experience_area.y_pixel_begin;
    SDL_BlitScaled(info_surfaces_map[EXPERIENCE]->getRenderableSurface(), NULL,
                   getSurface(), &stretchRect);

    stretchRect.x = experience_area.x_pixel_begin  + stretchRect.w;
    stretchRect.y = experience_area.y_pixel_begin;
    stretchRect.w = experience_area.x_pixel_end -
                    experience_area.x_pixel_begin - stretchRect.w;
    stretchRect.h = experience_area.y_pixel_end -
                    experience_area.y_pixel_begin;
    SDL_BlitScaled(info_surfaces_map[BACKGROUND]->getRenderableSurface(), NULL,
                   getSurface(), &stretchRect);
}

void SDLWindow::renderLevel(Surface* level_surface) {
    SDL_BlitScaled(level_surface->getRenderableSurface(), NULL,
                   getSurface(), &measurements.levelStaticRect);
}

void SDLWindow::renderText(Surface* surface) {
        SDL_Rect Message_rect; //create a rect
    Message_rect.x = 300;  //controls the rect's x coordinate
    Message_rect.y = 300; // controls the rect's y coordinte
    Message_rect.w = 120; // controls the width of the rect
    Message_rect.h = 120; // controls the height of the rect

    SDL_BlitScaled(surface->getRenderableSurface(), NULL,
                   getSurface(), &Message_rect);
    //el free se hace aca?

}

void SDLWindow::renderPlayerInfo(std::map<int, float>& player_info,
        std::map<int, Surface *> info_surfaces_map,
        Surface* level_surface) {
    renderLife(player_info, info_surfaces_map);
    renderMana(player_info, info_surfaces_map);
    renderExperience(player_info, info_surfaces_map);
    renderLevel(level_surface);
}





void SDLWindow::renderList(std::vector<Surface*>& surfaces) {
    game_area_t& list_area = measurements.list;
    int x,y, w, h;
    w = (list_area.x_pixel_end-list_area.x_pixel_begin)/LIST_MAX_TILES_WIDTH;
    h = w;
    x = list_area.x_pixel_begin;
    y = list_area.y_pixel_begin;
    int surfaces_size = surfaces.size();
    int current_index = 0;
    SDL_Rect stretchRect;
    while (current_index < surfaces_size) {
        stretchRect.x = x;
        stretchRect.y = y;
        stretchRect.w = w;
        stretchRect.h = h;
        SDL_BlitScaled(surfaces[current_index]->getRenderableSurface(), NULL,
                       getSurface(), &stretchRect);
        x = x + w;
        current_index ++;
    }
}


void SDLWindow::setTilesSize(int tileWidth, int tileHeight) {
    measurements.initialize(tileWidth,
                            tileHeight, screenWidth, screenHeight);
}

int SDLWindow::getRenderedItemIndexByPosition(int xClicked,
        int yClicked, size_t inventory_length) {
    game_area_t& inventory_area = measurements.inventory;
    int x,y, w, h;
    w = (inventory_area.x_pixel_end-inventory_area.x_pixel_begin)/
            INVENTORY_MAX_TILES_WIDTH;
    h = (inventory_area.y_pixel_end-inventory_area.y_pixel_begin)/
            INVENTORY_MAX_TILES_HEIGHT;
    x = inventory_area.x_pixel_begin;
    y = inventory_area.y_pixel_begin;
    size_t current_index = 0;
    SDL_Rect stretchRect;
    while (current_index < inventory_length) {
        stretchRect.x = x;
        stretchRect.y = y;
        stretchRect.w = w;
        stretchRect.h = h;
        if (isInsideArea(stretchRect, xClicked, yClicked))
            return current_index;
        y = y + h;
        current_index ++;
        //new column
        if (current_index == INVENTORY_MAX_TILES_HEIGHT){
            x = x + w;
            y = inventory_area.y_pixel_begin;
        }
    }
    return -1;
}

int SDLWindow::getRenderedEquipedTypeByPosition(int x, int y) {
    game_area_t& equipped_area = measurements.equipped;
    int equipped_width = (equipped_area.x_pixel_end -
                          equipped_area.x_pixel_begin) / EQUIPPED_MAX_TILES_WIDTH;
    SDL_Rect stretchRect;
    stretchRect.x = equipped_area.x_pixel_begin;
    stretchRect.y = equipped_area.y_pixel_begin;
    stretchRect.w = equipped_width;
    stretchRect.h = equipped_area.y_pixel_end-equipped_area.y_pixel_begin;
    if (isInsideArea(stretchRect, x, y)) return UNEQUIP_WEAPON;
    stretchRect.x = stretchRect.x + equipped_width;
    if (isInsideArea(stretchRect, x, y)) return UNEQUIP_ARMOR;
    stretchRect.x = stretchRect.x + equipped_width;
    if (isInsideArea(stretchRect, x, y)) return UNEQUIP_HELMET;
    stretchRect.x = stretchRect.x + equipped_width;
    if (isInsideArea(stretchRect, x, y)) return UNEQUIP_SHIELD;
    return -1;
}



int SDLWindow::getRenderedListIndexByPosition(int xClicked,
        int yClicked, size_t list_length) {
    //codigo repetido con render list, sacarlo afuera
    game_area_t& list_area = measurements.list;
    int x,y, w, h;
    w = (list_area.x_pixel_end-list_area.x_pixel_begin)/LIST_MAX_TILES_WIDTH;
    h = w;
    x = list_area.x_pixel_begin;
    y = list_area.y_pixel_begin;
    size_t current_index = 0;
    SDL_Rect stretchRect;
    while (current_index < list_length) {
        stretchRect.x = x;
        stretchRect.y = y;
        stretchRect.w = w;
        stretchRect.h = h;
        if (isInsideArea(stretchRect, xClicked, yClicked))
            return current_index;
        x = x + w;
        current_index ++;
    }
    return -1;
}

int SDLWindow::isInsideArea(SDL_Rect& stretchRect, int x, int y) {
    return (x >= stretchRect.x) && (x < (stretchRect.x + stretchRect.w))
        && (y >= stretchRect.y) && (y < (stretchRect.y + stretchRect.h));
}


int SDLWindow::isInsideGameArea(game_area_t& area, int x, int y) {
    return (x >= area.x_pixel_begin) && (x < area.x_pixel_end)
            && (y >= area.y_pixel_begin) && (y < area.y_pixel_end);
}

int SDLWindow::isClickingListItems(int x, int y) {
    return isInsideGameArea(measurements.list, x, y);
}

int SDLWindow::isClickingListGold(int x, int y) {
    return isInsideGameArea(measurements.listGold, x, y);
}
int SDLWindow::isClickingInventoryItems(int x, int y) {
    return isInsideGameArea(measurements.inventory, x, y);
}

int SDLWindow::isClickingInventoryGold(int x, int y) {
    return isInsideGameArea(measurements.inventoryGold, x, y);
}
