//
//  Cell.cpp
//  Scrabble
//


#include "Cell.h"

Cell::Cell()
{
	m_empty = true;
	m_tilePlayed = false;
	m_scoreEffect = NO_EFFECT;
}

void Cell::setTile(const Tile tile){
	m_tile = tile;
	m_empty = false;
}
