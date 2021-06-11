/*
 * lettersBag.h
 *
 *  Created on: Jun 6, 2021
 *      Author: nil
 */

#ifndef LOGIC_GAME_SCRABBLE_LETTERSBAG_H_
#define LOGIC_GAME_SCRABBLE_LETTERSBAG_H_

#include <vector>
#include "Tile.h"
#include <stdio.h>
using namespace std;

class lettersBag {
public:
	lettersBag();
	virtual ~lettersBag();
	Tile getLetter();
	bool isEmpty();
	int tilesRemaining();
private:
	vector<Tile> m_Letters;
	vector<int> n_lletresArray;
};

#endif /* LOGIC_GAME_SCRABBLE_LETTERSBAG_H_ */
