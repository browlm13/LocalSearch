#ifndef STOPWORDS_HASH_H
#define STOPWORDS_HASH_H

#include <fstream>
#include <string>
#include <cstdlib>
#include "data-structs/hash_table.h"
//#include "../data-structs/hash.h"

/*
	edit: open and close
	file  should be contained
	in seperate namespcae
							*/
class StopWords_Hash : public hash_table<std::string> {

	std::fstream file;
	std::string file_name;

	void _load();
	void _open_file(std::string file_name);
	void _close_file();

public:

	bool is_stop_word(std::string unkown);

	StopWords_Hash(){
		file_name = "../resources/stopWords.txt";
		_load();
	}

	~StopWords_Hash(){}
};

bool StopWords_Hash::is_stop_word(std::string unkown){
	bool on_list = false;

	if(get(unkown))
		on_list = true;

	return on_list;
}

//-------------------------
//	open close load files	
//	------------------------------

void StopWords_Hash::_load(){

	_open_file(file_name);

	//add each line into hash;
	while(!file.eof() && file.is_open()){
		std::string stop_word;
		getline(file, stop_word);
		add(stop_word, stop_word);
	}

	_close_file();
}

void StopWords_Hash::_open_file(std::string path){
	file.open(path.c_str());
	if(file.fail()){
		std::cout << "error opening" << path << std::endl;
		exit(1);
	}
}

void StopWords_Hash::_close_file()
{file.close();}

#endif //STOPWORDS_HASH_H
