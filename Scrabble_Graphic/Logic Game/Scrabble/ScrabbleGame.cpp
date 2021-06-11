//
//  ScrabbleGame.cpp
//  Letris
//
//  Created by Enric Vergara on 13/02/2021.
//  Copyright © 2021 CompiledCreations. All rights reserved.
//

#include "ScrabbleGame.h"
#include "../Scrabble_Defs.h"
#include "../GraphicManager.h"

const int SIZE_BUTTON_RECALL = 100;
const int SIZE_BUTTON_SHUFFLE = 100;

const int SIZE_W_BUTTON_SEND = 139;
const int SIZE_H_BUTTON_SEND = 100;
const int SIZE_W_BUTTON_PASS = 139;
const int SIZE_H_BUTTON_PASS = 100;

const int MAIN_BUTTON_POS_X = SCREEN_SIZE_X*0.5 - SIZE_W_BUTTON_SEND*0.5;
const int MAIN_BUTTON_POS_Y = SCREEN_SIZE_Y - SIZE_H_BUTTON_SEND;
const int RECALL_BUTTON_POS_X =  SCREEN_SIZE_X*0.5 - SIZE_W_BUTTON_SEND*0.5 - SIZE_BUTTON_RECALL - 10;
const int RECALL_BUTTON_POS_Y = SCREEN_SIZE_Y - SIZE_BUTTON_RECALL;
const int SHUFFLE_BUTTON_POS_X = SCREEN_SIZE_X*0.5 + SIZE_W_BUTTON_SEND*0.5 + 10;
const int SHUFFLE_BUTTON_POS_Y = SCREEN_SIZE_Y - SIZE_BUTTON_SHUFFLE;

ScrabbleGame::ScrabbleGame():
		m_buttonRecall(IMAGE_BUTTON_RECALL_NORMAL, IMAGE_BUTTON_RECALL_PRESSED, RECALL_BUTTON_POS_X, RECALL_BUTTON_POS_Y, SIZE_BUTTON_RECALL, SIZE_BUTTON_RECALL),
		m_buttonSend(IMAGE_BUTTON_SEND_NORMAL, IMAGE_BUTTON_SEND_PRESSED, MAIN_BUTTON_POS_X, MAIN_BUTTON_POS_Y, SIZE_W_BUTTON_SEND, SIZE_H_BUTTON_SEND),
		m_buttonShuffle(IMAGE_BUTTON_SHUFFLE_NORMAL, IMAGE_BUTTON_SHUFFLE_PRESSED, SHUFFLE_BUTTON_POS_X, SHUFFLE_BUTTON_POS_Y, SIZE_BUTTON_SHUFFLE, SIZE_BUTTON_SHUFFLE),
		m_buttonPass(IMAGE_BUTTON_PASS_NORMAL, IMAGE_BUTTON_PASS_PRESSED, MAIN_BUTTON_POS_X, MAIN_BUTTON_POS_Y,SIZE_W_BUTTON_PASS, SIZE_H_BUTTON_PASS),
		m_currentPlayer(0)
{

	for(int i = 0; i < NUM_PLAYERS; i++){
		m_Players[i].bagTiles(m_lettersBag);
	}
}

ScrabbleGame::~ScrabbleGame(){

}

void ScrabbleGame::updateAndRender (int mousePosX, int mousePosY, bool mouseStatus){
////////////////FONDO DEL JUEGO DEJAR SIEMPRE ARRIBA//////////////////
	GraphicManager::getInstance()->drawSprite(IMAGE_BACKGROUND, 0, 0);
	GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, int(SCREEN_SIZE_X * 0.5 - BOARD_SIZE*0.5), 40);
//////////////////////////////////////////////////////////////////////

//////////////////////BOTON DE PASS//////////////////////////////////
///EL BOTON DE PASS ES EL PRIMERO QUE LE HA DE APARECER AL JUGADOR///
	if(!m_Players[m_currentPlayer].tilesOnBoard()){
		if(m_buttonPass.update(mousePosX, mousePosY, mouseStatus)){
			m_currentPlayer++;
			if(m_currentPlayer > 2){
				m_currentPlayer = 0;
			}
		}
	}
//////////////////////////////////////////////////////////////////////

//////////////////////BOTON DE SEND//////////////////////////////////
///EL BOTON DE SEND ES EL SEGUNDO QUE LE HA DE APARECER AL JUGADOR///
	if(m_Players[m_currentPlayer].tilesOnBoard()){
		if(m_buttonSend.update(mousePosX, mousePosY, mouseStatus)){
			m_Players[m_currentPlayer].wordToBoard(m_board);

		}
	}
////////////////////////////////////////////////////////////////////

//////////////////////BOTON DE SHUFFLE//////////////////////////////////
//////////EL BOTON DE SHUFFLE ES EL QUE MEZCLA LAS TILES////////////////
	if(m_buttonShuffle.update(mousePosX, mousePosY, mouseStatus)){

	}

////////////////////////////////////////////////////////////////////////

//////////////////////BOTON DE RECALL//////////////////////////////////
//////////EL BOTON DE RECALL ES EL QUE PIDE LAS TILES//////////////////
	if(m_buttonRecall.update(mousePosX, mousePosY, mouseStatus)){
		m_Players[m_currentPlayer].recall();
		m_board.removeCurrentWord();
	}
////////////////////////////////////////////////////////////////////////

	if(m_Players[m_currentPlayer].tilesOnBoard()){
		if(m_buttonSend.update(mousePosX, mousePosY, mouseStatus)){

		}
	}
//////////////////SE MUESTRAN LETRAS PLAYER/////////////////////////////
//////////////////////PLAYER ACTUAL/////////////////////////////////////

m_Players[m_currentPlayer].renderTiles();

/////////////////SI LETRA PRESIONADA///////////////////////////////////
//////////////////////MOVER LETRA/////////////////////////////////////
if(m_Players[m_currentPlayer].tileBeeingPlaced(mousePosX, mousePosY, mouseStatus)){

}
m_Players[m_currentPlayer].displayMessages();
///////////////////////RENDERITCEM AMB RENDER//////////////////////////
m_buttonShuffle.render();
m_buttonSend.render();
m_buttonPass.render();
m_buttonRecall.render();


//////////////////////MOSTRAMOS EL TURNO DEL JUGADOR///////////////////
GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 50, 0, 0.7, "Player turn: " + to_string(m_currentPlayer+1));

//////////////////////////PUNTUACION/////////////////////////////
////////////////////MOSTRAMOS LOS JUGAORES///////////////////////
int index = 0;
for(int i = 0; i < NUM_PLAYERS;i++){
	string playerScoreJugador = "Score Player " + to_string(i + 1) + " = " + to_string(m_Players[i].getPuntuacio());
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 0, 750 + index, 0.5, playerScoreJugador);
	index += 25;
}

///////////////TILES IN THE BAG/////////////////////////////////
string tileNumber = "Tiles in the bag: " + to_string(m_lettersBag.tilesRemaining());
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 600, 750, 0.5, tileNumber);


////////////POSICION DEL RATON ELMINAR AL FINAL////////////////////
std::string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 550, 10, 0.6, msg);
}





