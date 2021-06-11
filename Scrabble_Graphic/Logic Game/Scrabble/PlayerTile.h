/*
 * PlayerTile.h
 *
 *  Created on: Jun 6, 2021
 *      Author: nil
 */

#ifndef LOGIC_GAME_SCRABBLE_PLAYERTILE_H_
#define LOGIC_GAME_SCRABBLE_PLAYERTILE_H_

#include <iostream>
#include "Tile.h"
#include "Board.h"


typedef enum
{
	BIG = 0,
	SMALL
}LetterSize;


class PlayerTile {
public:

	PlayerTile();
	virtual ~PlayerTile();
	bool isEmpty(){return m_isEmpty;}
	bool isOnBoard(){return m_isOnBoard;}
	float getPosX(){return m_posX;}
	float getPosY(){return m_posY;}
	Tile& getTile(){return m_tile;}
	BoardPosition getBoardPos(){return m_boardPosition;}


	void setPos(const float posX, const float posY);
	void setIsOnBoard(const bool& onBoard){m_isOnBoard = onBoard;}
	void setEmpty(const bool& empty){m_isEmpty = empty;}
	void setBoardPos(const BoardPosition& bp){m_boardPosition = bp;}
	void recall();

	void render(const LetterSize size);
	void setTile(const Tile& tile);
private:
	Tile m_tile;
	bool m_isEmpty;
	float m_posX,m_posY;
	bool m_isOnBoard;
	BoardPosition m_boardPosition;
};

#endif /* LOGIC_GAME_SCRABBLE_PLAYERTILE_H_ */
