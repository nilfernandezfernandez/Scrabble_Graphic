//
//  Board.cpp
//  Scrabble
//

#include "Board.h"
#include <algorithm>
#include <iostream>
#include <fstream>


Board::Board(){
	int columna = 0, fila = 0;
	string tablero = " ";
	ifstream fitxeroBoard;

	fitxeroBoard.open("/home/nil/C++/Eclipse/Scrabble/data/Configuration/board.txt");
	//fitxeroBoard.open("../data/Configuration/board.txt");

	//Incializamos el tablero:
	if(fitxeroBoard.is_open()){
		//fitxeroBoard >> columna >> fila >> tablero;
		while(!fitxeroBoard.eof()){
			fitxeroBoard >> columna >> fila >> tablero;
			if(tablero.compare("DL") == 0){

				m_cells[columna][fila].setScoreEffect(DL);
			}else if(tablero.compare("DW") == 0){

				m_cells[columna][fila].setScoreEffect(DW);
			}else if(tablero.compare("TW") == 0){

				m_cells[columna][fila].setScoreEffect(TW);
			}else if(tablero.compare("TL") == 0){

				m_cells[columna][fila].setScoreEffect(TL);
			}
		}
		fitxeroBoard.close();
	}
m_dictionary.setLanguage(ENGLISH);
firstWord = true;
}

PositionResult Board::setTile(Tile &tile,const BoardPosition& boardpos){
	if(boardpos.getCol() <= BOARD_COLS_AND_ROWS && boardpos.getRow() <= BOARD_COLS_AND_ROWS && boardpos.getCol() >= 0 && boardpos.getRow() >= 0){
		if(m_cells[boardpos.getCol()][boardpos.getRow()].getEmpty() == true)
		{
			m_currentWord.push_back(boardpos);
			m_cells[boardpos.getCol()][boardpos.getRow()].setTile(tile);
			m_cells[boardpos.getCol()][boardpos.getRow()].setTilePlayed(true);
			return VALID_POSITION;
		}else{
			return NOT_EMPTY;
		}
	}else{
		return INVALID_POSITION;
	}
}

void Board::removeCurrentWord(){

	int max = m_currentWord.size();
	for(int i = 0; i < max;i++){
		m_cells[m_currentWord[i].getCol()][m_currentWord[i].getRow()].setTilePlayed(false);
		m_cells[m_currentWord[i].getCol()][m_currentWord[i].getRow()].setEmpty(true);
	}
	m_currentWord.clear();
}

void Board::sendCurrentWordToBoard(){
	int max = m_currentWord.size();
	BoardPosition bp;

	for(int i = 0; i < max; i++){
		bp.setCol(m_currentWord[i].getCol());
		bp.setRow(m_currentWord[i].getRow());
		m_cells[m_currentWord[i].getCol()][m_currentWord[i].getRow()].setTilePlayed(true);
		m_cells[m_currentWord[i].getCol()][m_currentWord[i].getRow()].setEmpty(false);
		m_lastWord.push_back(bp);
	}
	m_currentWord.clear();
	firstWord = false;
}

bool Board::comprovarAlineacio(TipusAlineacio& alineacio){
	bool alignedHorizontal = true;
	bool alignedVertical = true;
	bool aligned = true;
	int endLoop = m_currentWord.size();
	int col = m_currentWord[0].getCol();
	int row = m_currentWord[0].getRow();
	int i = 0;

	//Miramos si esta alineado HORIZONTALMENTE
	while(i < endLoop && alignedHorizontal == true)
	{
		//Buscamos que todas las posiciones tengan la misma fila
		if(m_currentWord[i].getRow() != row)
		{
			alignedHorizontal = false;
		}else{
			i++;
		}
	}

	//Miramos si esta alineado VERTICALMENTE
	while(i < endLoop && alignedVertical == true)
	{
		//Buscamos que todas las posiciones tengan la misma columna
		if(m_currentWord[i].getCol() != col)
		{
			alignedHorizontal = false;
		}else{
			i++;
		}
	}

	if(alignedHorizontal){
		alineacio = HORITZONTAL;
	}else if(alignedVertical){
		alineacio = VERTICAL;
	}else{
		aligned = false;
	}

	return aligned;
}

bool Board::comprovarConsecuitiva(const TipusAlineacio alineacio, int& min, int& max){
	bool consecutiva = true;
	int i = 0;

	//Horitzontal Consecutiva
	if(alineacio == HORITZONTAL){
		min = m_currentWord[0].getCol();
		max = m_currentWord[0].getCol();
		//Buscamos el valor minimo y el maximo
		for(int i = 0; i < m_currentWord.size(); i++)
		{
			if(min > m_currentWord[i].getCol()){
				min = m_currentWord[i].getCol();
			}
			if(max < m_currentWord[i].getCol()){
				max = m_currentWord[i].getCol();
			}
		}
		while(i < m_currentWord.size() && !consecutiva){
			if(m_cells[min + i][m_currentWord[0].getRow()].getEmpty() == true)
			{
				consecutiva = false;
			}else{
				i++;
			}
		}
	}

	//Vertical Consecutiva
	if(alineacio == VERTICAL){
		min = m_currentWord[0].getRow();
		max = m_currentWord[0].getRow();
		//Buscamos el valor minimo y el maximo
		for(int i = 0; i < m_currentWord.size(); i++){
			if(min > m_currentWord[i].getRow()){
				min = m_currentWord[i].getRow();
			}
			if(max < m_currentWord[i].getRow()){
				max = m_currentWord[i].getRow();
			}
		}
		while(i < m_currentWord.size() && !consecutiva){
			if(m_cells[m_currentWord[0].getCol()][min + i].getEmpty() == true){
				consecutiva = false;
			}else{
				i++;
			}
		}
	}
	return consecutiva;
}


bool Board::comprovarDictionary(const TipusAlineacio alineacio,int& min, int& max, int& auxMin, int &auxMax){
	bool estaAlDictionary = false;
	vector<char>currentWordLetters;
	auxMin = min;
	auxMax = max;
	//Horitzontal
	if(alineacio == HORITZONTAL){
		while(m_cells[min - 1][m_currentWord[0].getRow()].getEmpty() == false){
			min--;
		}while(m_cells[max + 1][m_currentWord[0].getRow()].getEmpty() == false){
			max++;
		}
		for(int i = min; i <= max; i++){
			currentWordLetters.push_back(m_cells[i][m_currentWord[0].getRow()].getTile().getLetter());
		}
	}
	//Vertical
	if(alineacio == VERTICAL){
		while(m_cells[min - 1][m_currentWord[0].getRow()].getEmpty() == false){
			min--;
		}while(m_cells[max + 1][m_currentWord[0].getRow()].getEmpty() == false){
			max++;
		}
		for(int i = min; i <= max; i++){
			currentWordLetters.push_back(m_cells[m_currentWord[0].getCol()][i].getTile().getLetter());
		}
	}
	//Convertimos el vector char a una string
	string word = "";
	for(int i = 0; i < currentWordLetters.size(); i++){
		word = word + currentWordLetters[i];
	}

	estaAlDictionary = m_dictionary.check(word); //Llamamos a la funcion check de dictionary para comprovar si es igual

	return estaAlDictionary;
}

bool Board::comprovarConnexio(const TipusAlineacio alineacio, const int min, const int max){
	bool connexio = false;
	int i = 0;
	int j = 0;
	int k = 0;
	//MIRAMOS CONEXIONES HORIZONTALES
	if(alineacio == HORITZONTAL){
		//Check Right/Left Position

			if(min - 1 >= 0 && max + 1 <= BOARD_COLS_AND_ROWS){
				if(m_cells[min - 1][m_currentWord[0].getRow()].getEmpty() == false || m_cells[max + 1][m_currentWord[0].getRow()].getEmpty() == false){
					while(j < m_lastWord.size() && connexio == false){
						if(m_lastWord[j].getRow() == m_currentWord[0].getRow() && m_lastWord[j].getCol() + 1 == min){
							connexio = true;
						}
						if(m_lastWord[j].getRow() == m_currentWord[0].getRow() && m_lastWord[j].getCol() - 1 == max){
							connexio = true;
						}
						j++;
					}
				}
				while(k < m_currentWord.size() && connexio == false){
					i = 0;
					while(i < m_lastWord.size() && connexio == false){
						if(m_cells[min + k][m_currentWord[0].getRow() - 1].getEmpty() == false || m_cells[min + k][m_currentWord[0].getRow() + 1].getEmpty() == false){
							if(m_currentWord[0].getRow() - 1 == m_lastWord[i].getRow() && min + k == m_lastWord[i].getCol()){//Revisar
								connexio = true;
							}
							if(m_currentWord[0].getRow() + 1 == m_lastWord[i].getRow() && min + k == m_lastWord[i].getCol()){//Revisar
								connexio = true;
							}
						}
					i++;
					}
				k++;
			}
		}
	}

	//MIRAMOS CONEXIONES VERTICALES
	if(alineacio == VERTICAL){
			//Check Right/Left Position

				if(min - 1 >= 0 && max + 1 <= BOARD_COLS_AND_ROWS){
					if(m_cells[m_currentWord[0].getCol()][min - 1].getEmpty() == false || m_cells[m_currentWord[0].getCol()][max + 1].getEmpty() == false){
						while(j < m_lastWord.size() && !connexio){
							if(m_lastWord[j].getCol() == m_currentWord[0].getCol() && m_lastWord[j].getRow() + 1 == min){
								connexio = true;
							}
							if(m_lastWord[j].getCol() == m_currentWord[0].getCol() && m_lastWord[j].getRow() - 1 == max){
								connexio = true;
							}
							j++;
						}
					}
					while(k < m_currentWord.size() && connexio == false){
						i = 0;
						while(i < m_lastWord.size() && connexio == false){
							if(m_cells[m_currentWord[0].getCol() - 1][min + k].getEmpty() == false || m_cells[m_currentWord[0].getCol() + 1][min + k].getEmpty() == false){
								if(m_currentWord[0].getCol() - 1 == m_lastWord[i].getCol() && min + k	== m_lastWord[i].getRow()){
									connexio = true;
								}
								if(m_currentWord[0].getCol() + 1 == m_lastWord[i].getCol() && min + k	== m_lastWord[i].getRow()){
									connexio = true;
								}
							}
							i++;
						}
					k++;
				}
			}
		}

	return connexio;
}


void Board::calcularPuntuacio(int& points,const int min,const int max, const TipusAlineacio alineacio, int& auxMin, int& auxMax){ //calcular la puntuacio
	points = 0;

	if(alineacio == HORITZONTAL){
		for(int i = min; i <= max; i++){
			if(m_cells[i][m_currentWord[0].getRow()].getScoreEffect() == DL && m_cells[i][m_currentWord[0].getRow()].getTilePlayed() == true){
				points += m_cells[i][m_currentWord[0].getRow()].getTile().getScore()*2;
				m_cells[i][m_currentWord[0].getRow()].setScoreEffect(NO_EFFECT);
			}else if(m_cells[i][m_currentWord[0].getRow()].getScoreEffect() == TL && m_cells[i][m_currentWord[0].getRow()].getTilePlayed() == true){
				points += m_cells[i][m_currentWord[0].getRow()].getTile().getScore()*3;
				m_cells[i][m_currentWord[0].getRow()].setScoreEffect(NO_EFFECT);
			}else{
				points += m_cells[i][m_currentWord[0].getRow()].getTile().getScore();
			}
		}
		for(int i = min; i <= max; i++){
			if(m_cells[i][m_currentWord[0].getRow()].getScoreEffect() == DW && m_cells[i][m_currentWord[0].getRow()].getTilePlayed() == true){
				points = points*2;
				m_cells[i][m_currentWord[0].getRow()].setScoreEffect(NO_EFFECT);
			}else if(m_cells[i][m_currentWord[0].getRow()].getScoreEffect() == TW && m_cells[i][m_currentWord[0].getRow()].getTilePlayed() == true){
				points = points*3;
				m_cells[i][m_currentWord[0].getRow()].setScoreEffect(NO_EFFECT);
			}
		}

	}
	if(alineacio == VERTICAL){
		for(int i = min; i <= max; i++){
			if(m_cells[m_currentWord[0].getCol()][i].getScoreEffect() == DL){
				points += m_cells[m_currentWord[0].getCol()][i].getTile().getScore()*2;
				m_cells[m_currentWord[0].getCol()][i].setScoreEffect(NO_EFFECT);
			}else if(m_cells[m_currentWord[0].getCol()][i].getScoreEffect() == TL){
				points += m_cells[m_currentWord[0].getCol()][i].getTile().getScore()*3;
				m_cells[m_currentWord[0].getCol()][i].setScoreEffect(NO_EFFECT);
			}else{
				points += m_cells[m_currentWord[0].getCol()][i].getTile().getScore();
			}
		}
		for(int i = min; i <= max; i++){
			if(m_cells[m_currentWord[0].getCol()][i].getScoreEffect() == DW){
				points = points*2;
				m_cells[m_currentWord[0].getCol()][i].setScoreEffect(NO_EFFECT);
			}else if(m_cells[m_currentWord[0].getCol()][i].getScoreEffect() == TW){
				points = points*3;
				m_cells[m_currentWord[0].getCol()][i].setScoreEffect(NO_EFFECT);
			}
		}
	}
}

CurrentWordResult Board::checkCurrentWord(int& point){
	int min = 0;
	int max = BOARD_COLS_AND_ROWS;
	int auxMin = 0;
	int auxMax = BOARD_COLS_AND_ROWS;
	TipusAlineacio alineacio = NOTHING;
	int centralPosition = BOARD_COLS_AND_ROWS/2;

	if(firstWord == true)
	{
		if(m_currentWord[0].getCol() != centralPosition && m_currentWord[0].getRow() != centralPosition)
		{
			return INVALID_START_NOT_IN_CENTER;
		}
	}

	if(m_currentWord.size() < 2){
		return INVALID_WORD_OF_ONE_LETTER;
	}

	if(comprovarAlineacio(alineacio) == false){
		return INVALID_NOT_ALIGNED;
	}

	if(comprovarConsecuitiva(alineacio, min, max) == false){
		return INVALID_NOT_CONNECTION;
	}

	if(comprovarDictionary(alineacio, min, max,auxMin,auxMax) == false){
		return INVALID_WORDS_NOT_IN_DICTIONARY;
	}



	if(firstWord == false){
		if(comprovarConnexio(alineacio, min, max) == false){
			return INVALID_NOT_CONNECTION; //es un invalid not connection con otras palabras del tablero
		}
	}

	calcularPuntuacio(point,min,max,alineacio,auxMin, auxMax);


	return ALL_CORRECT;
}















