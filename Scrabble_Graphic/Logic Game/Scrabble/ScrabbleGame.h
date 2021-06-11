//
//  ScrabbleGame.hpp
//  Letris
//
//  Created by Enric Vergara on 13/02/2021.
//  Copyright © 2021 CompiledCreations. All rights reserved.
//

#ifndef ScrabbleGame_hpp
#define ScrabbleGame_hpp

#include <stdio.h>
#include "Board.h"
#include "Player.h"
#include "lettersBag.h"
#include "Button.h"
#include "../GraphicManager.h"


using namespace std;


int const NUM_PLAYERS = 3;

class ScrabbleGame
{
public:
    ScrabbleGame();
    ~ScrabbleGame();
    
    void updateAndRender    (int mousePosX, int mousePosY,bool mouseStatus);
    bool update ( int mousePosX, int mousePosY, bool mouseIsPressed);
    void render ();

    
    
private:
    Board m_board;
    int m_currentPlayer;
    Player m_Players[NUM_PLAYERS];
	lettersBag m_lettersBag;
	Button m_buttonRecall;
	Button m_buttonShuffle;
	Button m_buttonSend;
	Button m_buttonPass;

};

#endif /* ScrabbleGame_hpp */
