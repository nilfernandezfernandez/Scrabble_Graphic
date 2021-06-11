//
//  Cell.hpp
//  Scrabble
//


#ifndef Cell_hpp
#define Cell_hpp

#include <stdio.h>
#include <string>
#include "Tile.h"


typedef enum {
    DL = 0,
    TL,
    DW,
    TW,
    NO_EFFECT
} ScoreEffect;

class Cell
{
public:
	Cell();
	~Cell(){}
	void setTile(const Tile tile);

	Tile getTile()const{return m_tile;}

	void setTilePlayed(const bool played){m_tilePlayed = played;}
	bool getTilePlayed()const {return m_tilePlayed;}
	void setEmpty(const bool empty){m_empty = empty;}
	bool getEmpty()const{return m_empty;}

	void setScoreEffect(ScoreEffect score){m_scoreEffect = score;}
	ScoreEffect getScoreEffect()const{return m_scoreEffect;}
	void comerMacarrones();

private:
    ScoreEffect m_scoreEffect;
    Tile m_tile;
    bool m_empty;
    bool m_tilePlayed;
};


#endif /* Cell_hpp */
