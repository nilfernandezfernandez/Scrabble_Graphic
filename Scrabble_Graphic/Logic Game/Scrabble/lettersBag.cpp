/*
 * lettersBag.cpp
 *
 *  Created on: Jun 6, 2021
 *      Author: nil
 */

#include "lettersBag.h"
#include <fstream>
#include "Tile.h"
#include <cstdlib>


lettersBag::lettersBag() {
	// TODO Auto-generated constructor stub
	vector<char> lletresArray;
	vector<int> puntuacionArray;
	ifstream lettersBagFile;
	int totalTileNumber;
	lettersBagFile.open("/home/nil/C++/Eclipse/Scrabble_Graphic/data/Configuration/lettersBag.txt");
	if(lettersBagFile.is_open()){

		char lletres;
		int puntuacion, n_lletres;

		lettersBagFile >> lletres >> puntuacion >> n_lletres;
		while(!lettersBagFile.eof()){

			lletresArray.push_back(lletres);
			puntuacionArray.push_back(puntuacion);
			n_lletresArray.push_back(n_lletres);
			lettersBagFile >> lletres >> puntuacion >> n_lletres;
		}
		lettersBagFile.close();
	}

	for(int aux = 0; aux < lletresArray.size(); aux++){
		for(int i = 0; i < n_lletresArray[aux];i++){
			m_Letters.push_back(Tile(lletresArray[aux], puntuacionArray[aux])); //Guardamos los valores de los vectores creados anteriormente en el vector Tile
		}
	}
}

lettersBag::~lettersBag() {
	// TODO Auto-generated destructor stub
}

int lettersBag::tilesRemaining(){
	return (int)m_Letters.size();
}

bool lettersBag::isEmpty(){
	bool empty = false;

	if(m_Letters.size() == 0){
		empty = true;
	}

	return empty;
}


Tile lettersBag::getLetter(){
	srand(time(0));
	int max = m_Letters.size();
	int random = rand() % max;
	Tile letter = m_Letters[random];
	m_Letters.erase(m_Letters.begin() + random);
	return letter;
}


