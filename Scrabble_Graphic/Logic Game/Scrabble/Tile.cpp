//
//  Tile.cpp
//  Scrabble
//

#include "Tile.h"

Tile::Tile(){
	m_score = 0;
	m_letter = ' ';
}
Tile::Tile(const char letter,const int score){
	m_score = score;
	m_letter = letter;
}

void Tile::removeTile(){
	m_score = 0;
	m_letter = ' ';
}
