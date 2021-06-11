//
//  Dictionary.cpp


#include "Dictionary.h"

#include <fstream>
#include <string>

using namespace std;


Dictionary::Dictionary()
{
	m_currentLanguage = NO_LANGUAGE;
}

void Dictionary::setLanguage(Language language){
	m_currentLanguage = language;
	ifstream dictionaryFile;
	string word;

	m_languagesPath[ENGLISH] = "/home/nil/C++/Eclipse/Scrabble/data/Dictionaries/English.dic";
	m_languagesPath[SPANISH] = "/data/Dictionaries/Spanish.dic";
	m_languagesPath[CATALAN] = "/Scrabble/data/Dictionaries/Catalan.dic";

	dictionaryFile.open(m_languagesPath[m_currentLanguage]);

	if(dictionaryFile.is_open()){
		dictionaryFile >> word;
		do{
			m_words.push_back(word);
			dictionaryFile >> word;
		}while(!dictionaryFile.eof());
	}
	dictionaryFile.close();
}

bool Dictionary::check(const string& word){

	bool estaAlDictionary = false;
	int i = 0;
	while(!estaAlDictionary && i < m_words.size()){
		if(m_words[i] == word){
			estaAlDictionary = true;
		}else{
			i++;
		}
	}


	return estaAlDictionary;
}

