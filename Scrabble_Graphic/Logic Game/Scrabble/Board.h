//
//  Board.hpp
//  Scrabble
//


#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>



#include "Cell.h"
#include "Dictionary.h"
#include "BoardPosition.h"
#include "../Scrabble_Defs.h"


using namespace std;

// (0,0) ----> X
//   |  (col:0, row:0), (col:1, row:0)
//   |  (col:0, row:1), (col:1, row:1)
//   |     <- Size X (width)->
//   |      Coordinate system
//   v
//   Y

typedef enum {
    VALID_POSITION = 0,
    INVALID_POSITION,
    NOT_EMPTY
} PositionResult;

typedef enum {
    ALL_CORRECT = 0,
    //Tiles must be vertically or horizontally aligned and together
    INVALID_NOT_ALIGNED,
    //At least one letter must be next to the rest of the words.
    INVALID_NOT_CONNECTION,
    //You have to start using the center position
    INVALID_START_NOT_IN_CENTER,
    //Only words of two or more letters
    INVALID_WORD_OF_ONE_LETTER,
    //The new words are not in the dictionary
    INVALID_WORDS_NOT_IN_DICTIONARY,
} CurrentWordResult;
//-----------------------------

typedef enum{
	//Alineacio Horitzontal
	HORITZONTAL = 0,
	//Alineacio Vertical
	VERTICAL,
	//Ni Vertical Ni Horitzontal
	NOTHING,
}TipusAlineacio;



class Board
{
public:
    Board();
    ~Board(){}
     
    PositionResult setTile(Tile &tile, const BoardPosition& boardPos);
    CurrentWordResult checkCurrentWord(int& points);
    bool comprovarAlineacio(TipusAlineacio& alineacio);
    bool comprovarConsecuitiva(const TipusAlineacio alineacio, int& min, int& max);
    bool comprovarDictionary(const TipusAlineacio alineacio ,int& min, int& max, int& auxMin, int &auxMax);
    bool comprovarConnexio(const TipusAlineacio alineacio, const int min, const int max);
    void calcularPuntuacio(int& point,const int min, const int max, const TipusAlineacio alineacio,int& auxMin, int& auxMax);
    void sendCurrentWordToBoard();
    void removeCurrentWord();
    
        
private:
    Cell m_cells[BOARD_COLS_AND_ROWS][BOARD_COLS_AND_ROWS];
    Dictionary m_dictionary;
    VectorOfPositions m_currentWord;
    VectorOfPositions m_lastWord;
    bool firstWord;
};

#endif /* Board_hpp */
