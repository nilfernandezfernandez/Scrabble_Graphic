//
//  Tile.hpp
//  Scrabble
//

#ifndef Tile_hpp
#define Tile_hpp


class Tile
{
public:
	Tile();
	Tile(const char letter,const int score);
	~Tile(){}

	char getLetter()const{return m_letter;}
	int getScore()const{return m_score;}
	void removeTile();
private:
    char m_letter;
    unsigned int m_score;
};


#endif /* Tile_hpp */
