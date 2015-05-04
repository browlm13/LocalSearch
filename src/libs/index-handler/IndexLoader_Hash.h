#ifndef INDEXLOADER_HASH_H
#define INDEXLOADER_HASH_H

#include <iostream>
#include <string>
#include <vector>

#include "data-structs/avl.h"
#include "IndexLoader_Interface.h"
#include "IndexBuilder_Tree_Child.h"
#include "data-packets/Data_Packets.h"

using namespace std;

class IndexLoader_Hash : public IndexLoader_Interface {

	unsigned size;	//some prime number

	//element
	struct element{
		element(std::string key, IndexBuilder_Tree_Child value) : key(key), value(value){}
		std::string key;
		IndexBuilder_Tree_Child value;
	};

	vector<element> *table;

	unsigned 					index 	(std::string key);		//returns index
	void 						_add	(std::string key, word_packet wp);
	IndexBuilder_Tree_Child* 	_get	(std::string key);

public:
	void 	clear			();
	void search(std::string query, std::vector<word_packet> &top_results);
	void addWord(word_packet &wp);

	IndexLoader_Hash() {
		size = 2027;
		table = new vector<element> [size];
	}
	~IndexLoader_Hash(){
		delete [] table;
	}
};

void IndexLoader_Hash::search(std::string query, std::vector<word_packet> &top_results){
	IndexBuilder_Tree_Child *ibc = &(*(_get(query)));
	if(ibc)
		ibc->topResults(top_results, 999999999);
}

void IndexLoader_Hash::addWord(word_packet &wp)
{_add(wp.word, wp);}

unsigned IndexLoader_Hash::index(std::string key){
	//primes
	const unsigned A = 54059;
	const unsigned B = 76963;
	unsigned d = 31;

	for(int i=0; i<key.size(); i++)
		d = (d * A) ^ (key[i] * B);

	return d % size;
}

//index loader hash add
void IndexLoader_Hash::_add(std::string key, word_packet wp ){
	unsigned loc = index(key);

	if(_get(key))
	{
		for(int i=0; i<table[loc].size(); i++){
			if(table[loc][i].key.compare(key) == 0)
				table[loc][i].value.insert(wp);
		}
	}
	else 
	{
		IndexBuilder_Tree_Child ibct;
		ibct.insert(wp);
		element e(key, ibct);			//value = index_builder_child_tree
		table[loc].push_back(e);
	}
}

IndexBuilder_Tree_Child* IndexLoader_Hash::_get(std::string key){
	IndexBuilder_Tree_Child* v = 0;
	unsigned loc = index(key);

	if(table[loc].size() > 0){
		for (int i=0; i<table[loc].size(); i++){
			if(table[loc][i].key.compare(key) == 0)
				v = &table[loc][i].value;
		}
	}

	return v;
}	

void IndexLoader_Hash::clear(){
	delete [] table;
}
#endif //INDEXLOADER_HASH_H