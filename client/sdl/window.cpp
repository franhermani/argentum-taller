#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "window.h"
#include <utility>
#include "../sdl/exception.h"
#define INVENTORY_MAX_TILES_WIDTH 2
#define INVENTORY_MAX_TILES_HEIGHT 5
#define EQUIPPED_MAX_TILES_WIDTH 4
#define LIST_MAX_TILES_WIDTH 10

SDLWindow::SDLWindow(const int screenWidth, const int screenHeight):
                screenHeight(screenHeight), screenWidth(screenWidth),
                measurements(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw SDLException("\nError al inicializar SDL", SDL_GetError());

    window = SDL_CreateWindow("Argentum",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            screenWidth, screenHeight, 0);
    if (window == NULL)
        throw SDLException("\nError al crear la ventana", SDL_GetError());
    if (TTF_Init() < 0) {
        SDL_DestroyWindow(window);
        throw SDLException("\nNo se pudo inicializar ttf", SDL_GetError());
    }
    fullscreen = false;
}

SDLWindow::~SDLWindow() {
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_VideoQuit();
}

void SDLWindow::toggleFullscreen() {
    if (fullscreen) {
        //to window mode
        SDL_SetWindowFullscreen(window, 0);
        fullscreen = false;
        measurements.updateResolution(screenWidth, screenHeight);
    } else {
        //to fullscreen
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        fullscreen = true;
        SDL_DisplayMode dm;
        SDL_GetDesktopDisplayMode(0, &dm);
        measurements.updateResolution(dm.w, dm.h);
    }
}

SDL_Surface* SDLWindow::getSurface() const {
    return SDL_GetWindowSurface(window);
}

SDL_PixelFormat* SDLWindow::getSurfaceFormat() const {
    return SDL_GetWindowSurface(window)->format;
}


void SDLWindow::renderPlayerInfo(std::map<int, float>& player_info,
        std::map<int, Surface *>& info_surfaces_map,
        Surface* level_surface, Surface* name_surface) {
    Surface* background = info_surfaces_map[BACKGROUND];
    renderInfoBar(info_surfaces_map[LIFE], background,
                  measurements.life, player_info[LIFE]);
    renderInfoBar(info_surfaces_map[MANA], background,
            measurements.mana, player_info[MANA]);
    renderInfoBar(info_surfaces_map[EXPERIENCE],background,
            measurements.experience, player_info[EXPERIENCE]);
    renderLevel(level_surface);
    renderName(name_surface);
}

int SDLWindow::isOutsideFrameArea(SDL_Rect& stretch_rect,
        game_area_t& frame_area) {
    return ((stretch_rect.x+measurements.xWidthTileSize
         >= frame_area.x_pixel_end) ||
        (stretch_rect.y+measurements.yHeightTileSize
         >= frame_area.y_pixel_end));
}


SDL_Rect SDLWindow::calculateMapObjectRect(int x, int y) {
    SDL_Rect stretchRect;
    stretchRect.x = getXPixelPos(x);
    stretchRect.y = getYPixelPos(y);
    stretchRect.w = measurements.xWidthTileSize;
    stretchRect.h = measurements.yHeightTileSize;
    return std::move(stretchRect);
}

void SDLWindow::renderMapObject(int x, int y, Surface* character_surface) {
    game_area_t& frame_area = measurements.frame;
    SDL_Rect stretchRect = calculateMapObjectRect(x,y);
    if (isOutsideFrameArea(stretchRect, frame_area)) return;
    SDL_BlitScaled(character_surface->getRenderable(), NULL,
                   getSurface(), &stretchRect);
}

void SDLWindow::renderAnimatedMapObject(int x, int y,
        Surface* character_surface, int iteration) {
    game_area_t& frame_area = measurements.frame;
    SDL_Rect stretchRect = calculateMapObjectRect(x,y);
    if (isOutsideFrameArea(stretchRect, frame_area)) return;
    SDL_Rect origin_rect = measurements.measureAnimatedRect(iteration);
    SDL_BlitScaled(character_surface->getRenderable(), &origin_rect,
                   getSurface(), &stretchRect);
}

void SDLWindow::renderMapObjectLifeBar(int x, int y, Surface* bar,
        float percentage) {
    game_area_t& frame_area = measurements.frame;
    SDL_Rect stretchRect;
    //TODO sacar el 0.6 , 0.2 y 0.1 a measurements
    float bar_width = measurements.xWidthTileSize*0.6 * percentage;
    stretchRect.x = getXPixelPos(x) + (measurements.xWidthTileSize) * 0.2;
    stretchRect.y = getYPixelPos(y);
    stretchRect.w = bar_width;
    stretchRect.h = (measurements.yHeightTileSize)*0.1;
    if (isOutsideFrameArea(stretchRect, frame_area)) return;
    SDL_BlitScaled(bar->getRenderable(), NULL,
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

SDL_Rect SDLWindow::getFrameRectByPosition(Surface* surface,
        position_t position,
        int dimensions_width, int dimensions_height) {
    float tile_size_pix_x = surface->getRenderable()->w / dimensions_width;
    float tile_size_pix_y = surface->getRenderable()->h /
                            dimensions_height;
    int vision_width = measurements.numberOfTilesInWidth;
    int vision_height = measurements.numberOfTilesInHeight;
    SDL_Rect src_rect;
    src_rect.x = (int) (tile_size_pix_x*(position.x-(vision_width/2)));
    src_rect.y = (int) (tile_size_pix_y*(position.y-(vision_height/2)));
    src_rect.w = (int) (tile_size_pix_x*vision_width);
    src_rect.h = (int) (tile_size_pix_y*vision_height);
    return src_rect;
}

void SDLWindow::renderWorld(Surface* surface,  position_t positon,
                            int dimensions_width, int dimensions_height) {
    SDL_Rect src_rect =
            getFrameRectByPosition(surface, positon,
                    dimensions_width, dimensions_height);

    SDL_BlitScaled(surface->getRenderable(), &src_rect,
                   getSurface(), &measurements.worldStaticRect);
}


void SDLWindow::renderGameFrame(Surface* surface) {
    SDL_BlitScaled(surface->getRenderable(), NULL,
                   getSurface(), &measurements.gameFrameStaticRect);
}

void SDLWindow::renderInventoryGolds(Surface* surface, Surface* quantity) {
    SDL_BlitScaled(quantity->getRenderable(), NULL,
                   getSurface(), &measurements.inventoryGoldStaticRect);
}


void SDLWindow::renderListGold(Surface* surface, Surface* quantity_surface) {
    SDL_BlitScaled(quantity_surface->getRenderable(), NULL,
                   getSurface(), &measurements.listGoldQuantityStaticRect);
    SDL_BlitScaled(surface->getRenderable(), NULL,
                   getSurface(), &measurements.listGoldStaticRect);
}



void SDLWindow::renderInfoBar(Surface * bar, Surface* background,
        game_area_t& area, float percentage) {
    SDL_Rect stretchRect;
    stretchRect.x = area.x_pixel_begin;
    stretchRect.y = area.y_pixel_begin;
    stretchRect.w = (int) ((float)(area.x_pixel_end -
            area.x_pixel_begin))*percentage;
    stretchRect.h = area.y_pixel_end - area.y_pixel_begin;
    SDL_BlitScaled(bar->getRenderable(), NULL,
                   getSurface(), &stretchRect);
    stretchRect.x = stretchRect.x + stretchRect.w;
    stretchRect.y = area.y_pixel_begin;
    stretchRect.w = area.x_pixel_end -
                    area.x_pixel_begin - stretchRect.w;
    stretchRect.h = area.y_pixel_end - area.y_pixel_begin;
    SDL_BlitScaled(background->getRenderable(), NULL,
                   getSurface(), &stretchRect);
}

void SDLWindow::renderInventory(std::vector<uint8_t>& inventory,
                                std::map<int,Surface*>& surfaces) {
    game_area_t& inventory_area = measurements.inventory;
    SDL_Rect stretchRect = calculateInventoryStartRect();
    int surfaces_size = inventory.size(), current_index = 0;
    while (current_index < surfaces_size) {
        SDL_BlitScaled(surfaces[inventory[current_index]]->
                               getRenderable(), NULL,
                       getSurface(), &stretchRect);
        stretchRect.y = stretchRect.y + stretchRect.h;
        current_index ++;
        if (current_index == INVENTORY_MAX_TILES_HEIGHT){
            stretchRect.x = stretchRect.x + stretchRect.w;
            stretchRect.y = inventory_area.y_pixel_begin;
        }
    }
}

void SDLWindow::renderEqIfExists(std::map<int, Surface*>& surfaces_map,
        SDL_Rect& rect, int item) {
    if (surfaces_map.find(item) == surfaces_map.end()) return;
    SDL_BlitScaled(surfaces_map.at(item)->
        getRenderable(), NULL, getSurface(), &rect);
}

void SDLWindow::renderEquipped(player_t& player,
        std::map<int, Surface*>& surfaces_map) {
    SDL_Rect stretchRect = calculateEquippedStartRect();
    int equipped_width = stretchRect.w;
    renderEqIfExists(surfaces_map, stretchRect, player.weapon);
    stretchRect.x = stretchRect.x + equipped_width;
    renderEqIfExists(surfaces_map, stretchRect, player.armor);
    stretchRect.x = stretchRect.x + equipped_width;
    renderEqIfExists(surfaces_map, stretchRect, player.helmet);
    stretchRect.x = stretchRect.x + equipped_width;
    renderEqIfExists(surfaces_map, stretchRect, player.shield);
}



void SDLWindow::renderLevel(Surface* level_surface) {
    SDL_BlitScaled(level_surface->getRenderable(), NULL,
                   getSurface(), &measurements.levelStaticRect);
}
void SDLWindow::renderName(Surface* level_surface) {
    SDL_BlitScaled(level_surface->getRenderable(), NULL,
                   getSurface(), &measurements.nameStaticRect);
}


void SDLWindow::renderList(std::vector<Surface*>& surfaces) {
    renderListArea(measurements.list, surfaces);
}

void SDLWindow::renderListPrices(std::vector<Surface*>& surfaces) {
    renderListArea(measurements.list_prices, surfaces);
}




void SDLWindow::setTilesSize(int tileWidth, int tileHeight) {
    measurements.initialize(tileWidth,
                            tileHeight, screenWidth, screenHeight);
}


SDL_Rect SDLWindow::calculateInventoryStartRect() {
    game_area_t& inventory_area = measurements.inventory;
    SDL_Rect stretchRect = {
            inventory_area.x_pixel_begin,
            inventory_area.y_pixel_begin,
            (inventory_area.x_pixel_end-inventory_area.x_pixel_begin)/
            INVENTORY_MAX_TILES_WIDTH,
            (inventory_area.y_pixel_end-inventory_area.y_pixel_begin)/
            INVENTORY_MAX_TILES_HEIGHT
    };
    return stretchRect;
}

int SDLWindow::getRenderedItemIndexByPosition(int xClicked,
        int yClicked, size_t inventory_length) {
    game_area_t& inventory_area = measurements.inventory;
    size_t current_index = 0;
    SDL_Rect stretchRect = calculateInventoryStartRect();
    while (current_index < inventory_length) {
        if (isInsideArea(stretchRect, xClicked, yClicked))
            return current_index;
        stretchRect.y = stretchRect.y + stretchRect.h;
        current_index ++;
        //new column
        if (current_index == INVENTORY_MAX_TILES_HEIGHT){
            stretchRect.x = stretchRect.x + stretchRect.w;
            stretchRect.y = inventory_area.y_pixel_begin;
        }
    }
    return -1;
}

SDL_Rect SDLWindow::calculateEquippedStartRect() {
    game_area_t& equipped_area = measurements.equipped;
    int equipped_width = (equipped_area.x_pixel_end -
            equipped_area.x_pixel_begin) / EQUIPPED_MAX_TILES_WIDTH;
    SDL_Rect stretchRect;
    stretchRect.x = equipped_area.x_pixel_begin;
    stretchRect.y = equipped_area.y_pixel_begin;
    stretchRect.w = equipped_width;
    stretchRect.h = equipped_area.y_pixel_end-equipped_area.y_pixel_begin;
    return stretchRect;
}

int SDLWindow::getRenderedEquipedTypeByPosition(int x, int y) {
    SDL_Rect stretchRect = calculateEquippedStartRect();
    int equipped_width = stretchRect.w;
    if (isInsideArea(stretchRect, x, y)) return UNEQUIP_WEAPON;
    stretchRect.x = stretchRect.x + equipped_width;
    if (isInsideArea(stretchRect, x, y)) return UNEQUIP_ARMOR;
    stretchRect.x = stretchRect.x + equipped_width;
    if (isInsideArea(stretchRect, x, y)) return UNEQUIP_HELMET;
    stretchRect.x = stretchRect.x + equipped_width;
    if (isInsideArea(stretchRect, x, y)) return UNEQUIP_SHIELD;
    return -1;
}

void SDLWindow::renderListArea(game_area_t& list_area,
                               std::vector<Surface*>& surfaces) {
    int surfaces_size = surfaces.size();
    int current_index = 0;
    SDL_Rect stretchRect = calculateListStartRect(list_area);
    while (current_index < surfaces_size) {
        SDL_BlitScaled(surfaces[current_index]->getRenderable(), NULL,
                       getSurface(), &stretchRect);
        stretchRect.x = stretchRect.x + stretchRect.w;
        current_index ++;
    }
}
SDL_Rect SDLWindow::calculateListStartRect(game_area_t& list_area) {
    int side = (list_area.x_pixel_end - list_area.x_pixel_begin) /
            LIST_MAX_TILES_WIDTH;
    SDL_Rect stretchRect = {
            list_area.x_pixel_begin,
            list_area.y_pixel_begin,
            side, side
    };
    return stretchRect;
}


int SDLWindow::getRenderedListIndexByPosition(int xClicked,
        int yClicked, size_t list_length) {
    size_t current_index = 0;
    SDL_Rect stretchRect = calculateListStartRect(measurements.list);
    while (current_index < list_length) {
        if (isInsideArea(stretchRect, xClicked, yClicked))
            return current_index;
        stretchRect.x = stretchRect.x + stretchRect.w;
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
