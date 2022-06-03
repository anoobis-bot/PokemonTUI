#ifndef CONFIGURATION
#define CONFIGURATION

#define HEIGHT 17
#define WIDTH 75        // content width

#define LEFT_MARGIN 2   // margin on the left side of TUI

#define RIGHT_PAD 1     // padding on the right side of TUI
#define LEFT_PAD 1      // padding on the left side of TUI

// these are fot the box art
#define UP_LEFT_CORNER 218      // "┌"
#define UP_RIGHT_CORNER 191     // "┐"
#define MID_LEFT_CORNER 195     // ├
#define MID_RIGHT_CORNER 180    // ┤
#define DOWN_LEFT_CORNER 192    // "└"
#define DOWN_RIGHT_CORNER 217   // "┘"
#define V_LINE "|"
#define H_LINE "-"

// these are for the grass tiles art
#define GRASS_UP_LEFT 214       // ╓
#define GRASS_UP_RIGHT 183      // ╖
#define GRASS_DOWN_LEFT 211     // ╙
#define GRASS_DOWN_RIGHT 189    // ╜
#define D_V_LINE 186            // ║
#define GRASS_TILE 178          // ▓
#define TRAINER_SPRITE 154      // Ü

// these are for the box tiles art
#define BOX_TILE_UP_LEFT 201    // ╔
#define BOX_TILE_UP_RIGHT 187   // ╗
#define BOX_TILE_DOWN_LEFT 200  // ╚
#define BOX_TILE_DOWN_RIGHT 188 // ╝
#define BOX_TILE_V_LINE 186     // ║
#define BOX_TILE_H_LINE 205     // ═
#define BOX_TILE_OCCUPY 177     // ▒

#define COLOR_ENABLE 1

#define DEX_MAX 150             // maximuim number of entities in the fakedex database

#define BOX_MAX 100             // maximum number of fakemon that the box can carry

#define MON_PAGE 5              // how many fakemon to display in a page in view dex

#define BOX_MON_PAGE 8          // how many fakemon to display in a page in view Box

#define FILE_NAME_LEN 14

#define MAX_SAV_FILES 3

#define EXPLORE_COLUMN 7        // how much horizontal tiles for the exploration part

// dimenstions on how many rows and columns in viewBox per page
#define NUM_BOX_COLUMN 4
#define NUM_BOX_ROW 2

#endif