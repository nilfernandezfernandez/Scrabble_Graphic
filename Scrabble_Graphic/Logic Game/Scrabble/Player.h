/*
 * Player.h
 *
 *  Created on: Jun 6, 2021
 *      Author: nil
 */

#ifndef LOGIC_GAME_SCRABBLE_PLAYER_H_
#define LOGIC_GAME_SCRABBLE_PLAYER_H_

#include <stdio.h>
#include "Tile.h"
#include "PlayerTile.h"
#include "Board.h"
#include "lettersBag.h"
#include "BoardPosition.h"

int const MAX_TILES = 7;
int const SEPARATION_BTW_TILES = 5;
int const TILE_SIZE = 100;
int const TILE_POS_Y = BOARD_POS_Y + BOARD_SIZE + 10;
int const TILE_POS_X = SCREEN_SIZE_X*0.5 - ((TILE_SIZE + SEPARATION_BTW_TILES)*MAX_TILES)*0.5;

class Player {
public:
	Player();
	virtual ~Player();

	void setPuntuacion(const int puntuacioJugador){m_puntuacioJugador = puntuacioJugador;}
	int getPuntuacio()const{return m_puntuacioJugador;}

	void setPlayerTile(const PlayerTile tile);

	void bagTiles(lettersBag lBag);
	void renderTiles();
	void recall();

	bool tilesOnBoard();
	bool tileBeeingPlaced(const int& mousePosX,const int& mousePosY,const int& mouseStatus);
	void displayMessages();
	void positionResult(const PositionResult& postionResult);
	void wordToBoard(Board& board);

private:
	int m_currentTile;
	bool m_beeingPlaced;
	int m_puntuacioJugador;
	PlayerTile m_Playertiles[MAX_TILES];
	Board board;
	BoardPosition m_boardPosition;
	string greenMessage;
	string redMessage;
	PositionResult pr;

};

#endif /* LOGIC_GAME_SCRABBLE_PLAYER_H_ */
