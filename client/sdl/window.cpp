#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include "window.h"
#include "exception.h"

SDLWindow::SDLWindow(const int screenWidth, const int screenHeight):
                screenHeight(screenHeight), screenWidth(screenWidth),
                measurements(){
    int s;
    if ((s = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)))
        throw SDLException("Error al inicializar SDL", SDL_GetError());

    if ((s = SDL_CreateWindowAndRenderer(screenWidth, screenHeight,
            SDL_RENDERER_ACCELERATED, &window, &renderer)))
        throw SDLException("Error al crear la ventana", SDL_GetError());
    setTilesSize(9, 9);
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

void SDLWindow::stampSurface(Surface& surface, Area& area) {
    SDL_Rect rect;
    rect.x = area.getX();
    rect.y = area.getY();
    rect.w = area.getWidth();
    rect.h = area.getHeight();
    SDL_BlitScaled(surface.getRenderableSurface(), NULL, getSurface(), &rect);
}

void SDLWindow::renderNpc(int x, int y, Surface* character_surface) {
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

    for (int y=0; y < height_size; y++) {
        for (int x=0; x < width_size; x++) {
            SDL_Rect stretchRect;
            stretchRect.x = getXPixelPos(x);
            stretchRect.y = getYPixelPos(y);
            stretchRect.w = measurements.xWidthTileSize;
            stretchRect.h = measurements.yHeightTileSize;
            /*if (debug) {
                std::cout << "Intento de estampar el terrain con valor: "
                        << matrix[y][x] << "\n";
                std::cout << "En los indices y:"
                        << y << " x:" << x << "\n";
                std::cout << "Esta en el mapa de superficies? "
                <<(surfaces_map.find(matrix[y][x]) != surfaces_map.end())
                << "\n";
                std::cout << "lo meto en este pixel x" << stretchRect.x
                            << " y este pixel y " << stretchRect.y
                            << "de este ancho " << stretchRect.w
                            << "y este alto " << stretchRect.h << "\n";
            }*/
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
void SDLWindow::renderEquipped(player_t player,
                              std::map<int, Surface*>& surfaces_map) {
    game_area_t& equipped_area = measurements.equipped;
    int equipped_width = (equipped_area.x_pixel_end -
            equipped_area.x_pixel_begin) / 4;
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
    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = screenWidth;
    stretchRect.h = screenHeight;
    SDL_BlitScaled(surface->getRenderableSurface(), NULL,
                   getSurface(), &stretchRect);
}

void SDLWindow::renderInventoryGold(Surface* surface) {
    game_area_t& gold_area = measurements.inventory_gold;
    int x,y, w, h;
    //TODO EL 2 Y EL 5 SACAR AFUERA A CONSTANTES
    w = (gold_area.x_pixel_end-gold_area.x_pixel_begin);
    h = (gold_area.y_pixel_end-gold_area.y_pixel_begin);
    x = gold_area.x_pixel_begin;
    y = gold_area.y_pixel_begin;
    SDL_Rect stretchRect;
    stretchRect.x = x;
    stretchRect.y = y;
    stretchRect.w = w;
    stretchRect.h = h;
    SDL_BlitScaled(surface->getRenderableSurface(), NULL,
                   getSurface(), &stretchRect);
}


void SDLWindow::renderListGold(Surface* surface) {
    //todo codigo repetido los 2 golds juntar?
    game_area_t& gold_area = measurements.list_gold;
    int x,y, w, h;
    //TODO EL 2 Y EL 5 SACAR AFUERA A CONSTANTES
    w = (gold_area.x_pixel_end-gold_area.x_pixel_begin);
    h = (gold_area.y_pixel_end-gold_area.y_pixel_begin);
    x = gold_area.x_pixel_begin;
    y = gold_area.y_pixel_begin;
    SDL_Rect stretchRect;
    stretchRect.x = x;
    stretchRect.y = y;
    stretchRect.w = w;
    stretchRect.h = h;
    SDL_BlitScaled(surface->getRenderableSurface(), NULL,
                   getSurface(), &stretchRect);
}


void SDLWindow::renderInventory(std::vector<Surface*>& surfaces) {
    game_area_t& inventory_area = measurements.inventory;
    int x,y, w, h;
    //TODO EL 2 Y EL 5 SACAR AFUERA A CONSTANTES
    w = (inventory_area.x_pixel_end-inventory_area.x_pixel_begin)/2;
    h = (inventory_area.y_pixel_end-inventory_area.y_pixel_begin)/5;
    x = inventory_area.x_pixel_begin;
    y = inventory_area.y_pixel_begin;
    int surfaces_size = surfaces.size();
    int current_index = 0;
    while (current_index < surfaces_size) {
        SDL_Rect stretchRect;
        stretchRect.x = x;
        stretchRect.y = y;
        stretchRect.w = w;
        stretchRect.h = h;
        SDL_BlitScaled(surfaces[current_index]->getRenderableSurface(), NULL,
                       getSurface(), &stretchRect);
        y = y + h;
        current_index ++;
        if (current_index == 5){
            x = x + w;
            y = inventory_area.y_pixel_begin;
        }
    }
}

void SDLWindow::renderPlayerInfo(std::map<int, float> player_info,
        std::map<int, Surface *> info_surfaces_map) {
    game_area_t& life_area = measurements.life;
    SDL_Rect stretchRect;
    stretchRect.x = life_area.x_pixel_begin;
    stretchRect.y = life_area.y_pixel_begin;
    stretchRect.w = life_area.x_pixel_end - life_area.x_pixel_begin;
    stretchRect.h = life_area.y_pixel_end - life_area.y_pixel_begin;
    SDL_BlitScaled(info_surfaces_map[BACKGROUND]->getRenderableSurface(), NULL,
                   getSurface(), &stretchRect);

    //TODO usar player info
    float life_percentage = player_info[LIFE];
    stretchRect.x = life_area.x_pixel_begin;
    stretchRect.y = life_area.y_pixel_begin;
    stretchRect.w = (int) ((float)(life_area.x_pixel_end -
            life_area.x_pixel_begin))*life_percentage;
    stretchRect.h = life_area.y_pixel_end - life_area.y_pixel_begin;

    SDL_BlitScaled(info_surfaces_map[LIFE]->getRenderableSurface(), NULL,
                   getSurface(), &stretchRect);
    game_area_t& mana_area = measurements.mana;
    stretchRect.x = mana_area.x_pixel_begin;
    stretchRect.y = mana_area.y_pixel_begin;
    stretchRect.w = mana_area.x_pixel_end - mana_area.x_pixel_begin;
    stretchRect.h = mana_area.y_pixel_end - mana_area.y_pixel_begin;
    SDL_BlitScaled(info_surfaces_map[BACKGROUND]->getRenderableSurface(), NULL,
                   getSurface(), &stretchRect);

    //TODO usar player info
    float mana_percentage = player_info[MANA];
    stretchRect.x = mana_area.x_pixel_begin;
    stretchRect.y = mana_area.y_pixel_begin;
    stretchRect.w = (int) ((float)(mana_area.x_pixel_end -
            mana_area.x_pixel_begin))*mana_percentage;
    stretchRect.h = mana_area.y_pixel_end - mana_area.y_pixel_begin;
    SDL_BlitScaled(info_surfaces_map[MANA]->getRenderableSurface(), NULL,
                   getSurface(), &stretchRect);
    game_area_t& experience_area = measurements.experience;
    stretchRect.x = experience_area.x_pixel_begin;
    stretchRect.y = experience_area.y_pixel_begin;
    stretchRect.w = experience_area.x_pixel_end -
            experience_area.x_pixel_begin;
    stretchRect.h = experience_area.y_pixel_end -
            experience_area.y_pixel_begin;
    SDL_BlitScaled(info_surfaces_map[BACKGROUND]->getRenderableSurface(), NULL,
                   getSurface(), &stretchRect);

    //TODO usar player info
    float experience_percentage = player_info[EXPERIENCE];
    stretchRect.x = experience_area.x_pixel_begin;
    stretchRect.y = experience_area.y_pixel_begin;
    stretchRect.w = (int) ((float)(experience_area.x_pixel_end -
            experience_area.x_pixel_begin))*experience_percentage;
    stretchRect.h = experience_area.y_pixel_end -
            experience_area.y_pixel_begin;
    SDL_BlitScaled(info_surfaces_map[EXPERIENCE]->getRenderableSurface(), NULL,
                   getSurface(), &stretchRect);
}



void SDLWindow::renderList(std::vector<Surface*>& surfaces) {
    game_area_t& list_area = measurements.list;
    int x,y, w, h;
    //TODO 10 es el maximo de items en la lista , sacar AFUERA A CONSTANTES
    w = (list_area.x_pixel_end-list_area.x_pixel_begin)/10;
    h = w;
    x = list_area.x_pixel_begin;
    y = list_area.y_pixel_begin;
    int surfaces_size = surfaces.size();
    int current_index = 0;
    while (current_index < surfaces_size) {
        SDL_Rect stretchRect;
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
    w = (inventory_area.x_pixel_end-inventory_area.x_pixel_begin)/2;
    h = (inventory_area.y_pixel_end-inventory_area.y_pixel_begin)/5;
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
        if (current_index == 5){
            x = x + w;
            y = inventory_area.y_pixel_begin;
        }
    }
    return -1;
}


int SDLWindow::getRenderedListIndexByPosition(int xClicked,
        int yClicked, size_t list_length) {
    //codigo repetido con render list, sacarlo afuera
    game_area_t& list_area = measurements.list;
    int x,y, w, h;
    //TODO 10 es el maximo de items en la lista , sacar AFUERA A CONSTANTES
    w = (list_area.x_pixel_end-list_area.x_pixel_begin)/10;
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
    return (((x >= stretchRect.x) and (x < (stretchRect.x + stretchRect.w)))
        and ((y >= stretchRect.y) and (y < (stretchRect.y + stretchRect.h))));
}


int SDLWindow::isInsideGameArea(game_area_t& area, int x, int y) {
    return (((x >= area.x_pixel_begin) and (x < area.x_pixel_end))
            and ((y >= area.y_pixel_begin) and (y < (area.y_pixel_end))));
}

int SDLWindow::isClickingListItems(int x, int y) {
    return isInsideGameArea(measurements.list, x, y);
}

int SDLWindow::isClickingListGold(int x, int y) {
    return isInsideGameArea(measurements.list_gold, x, y);
}
int SDLWindow::isClickingInventoryItems(int x, int y) {
    return isInsideGameArea(measurements.inventory, x, y);
}

int SDLWindow::isClickingInventoryGold(int x, int y) {
    return isInsideGameArea(measurements.inventory_gold, x, y);
}
