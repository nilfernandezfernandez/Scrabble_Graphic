/*
 * PlayerTile.cpp
 *
 *  Created on: Jun 6, 2021
 *      Author: nil
 */

#include "PlayerTile.h"
#include "../GraphicManager.h"

PlayerTile::PlayerTile(){
	// TODO Auto-generated constructor stub
	m_isOnBoard = false;
	m_isEmpty = true;
}

PlayerTile::~PlayerTile() {
	// TODO Auto-generated destructor stub
}

void PlayerTile::render(const LetterSize size){
	if(!m_isOnBoard && !m_isEmpty){
		int index = m_tile.getLetter() - 'a';//CODIGO ASCII
        if (!SMALL){
        	index += 26;
       	}
        GraphicManager::getInstance()->drawSprite(IMAGE_NAME(index), m_posX, m_posY);
    }
}

void PlayerTile::recall(){
    if (!m_isEmpty){
        m_isOnBoard = false;
    }
}

void PlayerTile::setPos(const float posX, const float posY){
	m_posX = posX;
	m_posY = posY;
}

void PlayerTile::setTile(const Tile& tile){
	m_isOnBoard = false;
	m_isEmpty = false;
	m_tile = tile;
}


