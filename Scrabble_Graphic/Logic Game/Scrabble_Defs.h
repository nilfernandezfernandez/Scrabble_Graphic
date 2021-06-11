//
//  Scrabble.h
//  MP_Practica
//
//  Created by Enric Vergara on 14/03/2021.
//  Copyright © 2021 CompiledCreations. All rights reserved.
//


#ifndef Scrabble_h
#define Scrabble_h

#include <iostream>
#include <vector>
#include "Scrabble/BoardPosition.h"
using namespace std;
// Screen size (W,H)=(750,850)
int const  SCREEN_SIZE_X = 750;
int const SCREEN_SIZE_Y = 850;
int const BOARD_SIZE = 600;
int const BOARD_COLS_AND_ROWS = 15;
int const BOARD_TILE_SIZE  = (BOARD_SIZE / BOARD_COLS_AND_ROWS);


//TODO 1.4
/*---Codi a fer:
const int BOARD_POS_X = SCREEN_SIZE_X * 0.5 - BOARD_SIZE * 0.5;
const int BOARD_POS_Y = 40;
*/

int const BOARD_POS_X = (SCREEN_SIZE_X * 0.5 - BOARD_SIZE * 0.5);
int const BOARD_POS_Y = 40;
typedef vector<BoardPosition> VectorOfPositions;

#endif
