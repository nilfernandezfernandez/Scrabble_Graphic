/*
 * Player.cpp
 *
 *  Created on: Jun 6, 2021
 *      Author: nil
 */

#include "Player.h"
#include "../GraphicManager.h"

Player::Player() {
	// TODO Auto-generated constructor stub
	m_currentTile = 0;
	m_puntuacioJugador = 0;
}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

void Player::setPlayerTile(const PlayerTile tile){
	if(m_currentTile < MAX_TILES){
		m_Playertiles[m_currentTile] = tile;
		m_currentTile++;
	}
}

void Player::bagTiles(lettersBag lBag){
	for(int i = 0; i < MAX_TILES; i++){
		if((m_Playertiles[i].isEmpty() == true) || (lBag.isEmpty() == false)){
			m_Playertiles[i].setTile(lBag.getLetter());
		}
	}
	recall();
}

void Player::recall (){
    float posY = TILE_POS_Y;
    float posX = TILE_POS_X;
    for (int i = 0; i < MAX_TILES; i++) {
        m_Playertiles[i].setPos(posX, posY);
        m_Playertiles[i].recall();
        posX  += TILE_SIZE + SEPARATION_BTW_TILES;
    }
}

void Player::renderTiles(){
	for(int i = 0; i < MAX_TILES; i++){
		if(m_beeingPlaced && i  == m_currentTile){
			m_Playertiles[i].render(SMALL);
		}else{
			m_Playertiles[i].render(BIG);
		}
	}
}


void Player::wordToBoard(Board& board){

}

bool Player::tileBeeingPlaced(const int& mousePosX,const int& mousePosY,const int& mouseStatus){

	int choseSize;

	float tamañoCelda = BOARD_SIZE/BOARD_COLS_AND_ROWS;
	int col = int((mousePosX - BOARD_POS_X)/tamañoCelda);
	int row = int((mousePosY - BOARD_POS_Y)/tamañoCelda);

	if(m_beeingPlaced){
		    m_Playertiles[m_currentTile].setPos(mousePosX, mousePosY);
		    if(!mouseStatus){
		    	m_beeingPlaced = false;
		    	if((mousePosX > BOARD_POS_X) && (mousePosX < BOARD_POS_X + BOARD_SIZE) && (mousePosY > BOARD_POS_Y) && (mousePosY < BOARD_POS_Y + BOARD_SIZE)){
		    		m_boardPosition.setCol(col);
		    		m_boardPosition.setRow(row);
		    		pr = board.setTile(m_Playertiles[m_currentTile].getTile(), m_boardPosition);
		    	}else{
		    		pr = INVALID_POSITION;
		    	}
		    	positionResult(pr); //ENVIAMOS EL RESULTADO DE POSICION A POSITION RESULT
		    }
	}else if (mouseStatus){
	        for (int i = 0; i < MAX_TILES; i++) {
	            if (!m_Playertiles[i].isEmpty()){
	                if(m_Playertiles[i].isOnBoard()){
	                	choseSize = BOARD_TILE_SIZE;
	                }else{
	                	choseSize = TILE_SIZE;
	                }

	                if (mousePosX >= m_Playertiles[i].getPosX() && mousePosX <= m_Playertiles[i].getPosX() + choseSize &&
	                    mousePosY >= m_Playertiles[i].getPosY() && mousePosY <= m_Playertiles[i].getPosY() + choseSize){
	                    m_beeingPlaced = true;
	                    m_currentTile = i;
	                    if(m_Playertiles[i].isOnBoard()){
	                    	m_Playertiles[i].setIsOnBoard(false);
	                    }

	                }
	            }
	        }
	    }


return m_beeingPlaced;

}


void Player::positionResult(const PositionResult& positionResult){

    int posX = BOARD_POS_X + m_boardPosition.getCol()*BOARD_TILE_SIZE;
    int posY = BOARD_POS_Y + m_boardPosition.getRow()*BOARD_TILE_SIZE;
    float posicionInicialX = TILE_POS_X + (TILE_SIZE + SEPARATION_BTW_TILES)*m_currentTile;
    float posicionInicialY = TILE_POS_Y;
    int points = 0;
    CurrentWordResult checkCurrentWordPr;
	switch (positionResult) {
		case INVALID_POSITION:
			//VOLVEMOS A PONER LA FITXA EN LA POSICION INICIAL//
			m_Playertiles[m_currentTile].setPos(posicionInicialX,posicionInicialY);
			break;
		case VALID_POSITION:
			m_Playertiles[m_currentTile].setPos(posX, posY);
			m_Playertiles[m_currentTile].setBoardPos(m_boardPosition);
			redMessage = "";
			//COMPROVAMOS LA BOARD PARA VER QUE TODO ESTE CORRECTO
			//UTILIZAMOS LA FUNCION DE CHECKCURRENTWORD DE BOARD.CPP PARA COMPRVAR QUE ESTE TODO CORRECOT
			checkCurrentWordPr = board.checkCurrentWord(points);
			switch (checkCurrentWordPr) {
				case ALL_CORRECT:
					greenMessage = "POINTS: " + to_string(points);
					redMessage = "";
					break;
				case INVALID_NOT_ALIGNED:
					redMessage = "INVALID NOT ALIGNED";
					greenMessage = "";
					break;
				case INVALID_NOT_CONNECTION:
					redMessage = "TILES MUST BE CONNECTED";
					greenMessage = "";
					break;
				case INVALID_START_NOT_IN_CENTER:
					redMessage = "TILE MUST START IN CENTER";
					greenMessage = "";
					break;
				case INVALID_WORDS_NOT_IN_DICTIONARY:
					redMessage = "WORD DOESN'T EXIST";
					greenMessage = "";
					break;
				case INVALID_WORD_OF_ONE_LETTER:
					redMessage = "WORD MUST HAVE MORE THAN ONE LETTER";
					greenMessage = "";
					break;
				default:
					break;
			}
			break;
		case NOT_EMPTY:
			m_Playertiles[m_currentTile].setPos(posicionInicialX,posicionInicialY);
			greenMessage = "";
			redMessage = "CELL IT'S NOT EMPTY";
			break;
	}
}

void Player::displayMessages(){
	GraphicManager::getInstance()->drawFont(FONT_GREEN_30, SCREEN_SIZE_X*0.5 - 150, 5, 0.7, greenMessage);
	GraphicManager::getInstance()->drawFont(FONT_RED_30, SCREEN_SIZE_X*0.5 - 150, 5, 0.7, redMessage);
}

bool Player::tilesOnBoard(){
	bool tileOnBoard = false;
	int i = 0;
	while(!tileOnBoard && i < MAX_TILES){
		if(m_Playertiles[i].isEmpty() && m_Playertiles[i].isOnBoard()){
			tileOnBoard = true;
		}else{
			i++;
		}
	}
	return tileOnBoard;
}
