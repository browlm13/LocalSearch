#include "IndexHandler.h"

//#include "data-packets/Data_Packets.h"

//TMP
#include <iostream>
using namespace std;

//--------------------------
//		searching		
//			--------------------------
vector<word_packet> IndexHandler::search(const string query_term){
	vector<word_packet> results;

	loader->search(query_term, results);

	return results;
}

//--------------------------
//		setup
//			--------------------------
void IndexHandler::set_dataStruct(int type){

	/*
		edit:	could use a gaurd
			in the case the tree is full.	*/

	dataStruct_type = type;

	if(dataStruct_type == DataStuct_Types::AVL){
		loader = &loader_avl;
		//loader = new IndexLoader_Tree;
	}

	if(dataStruct_type == DataStuct_Types::BUILDER){
		loader = &builder_avl;
		//loader = new IndexBuilder_Tree;
	}
}


void IndexHandler::addWord( word_packet wp )
	{loader->addWord(wp);}

//--------------------------
//		Maintincene		
//			--------------------------

void IndexHandler::saveIndex(string path){

	//can only save under two condition (unsaved && builder)
	if( (dataStruct_type == DataStuct_Types::BUILDER) ){
		loader->save(path);
	}
}

void IndexHandler::close (){

	loader->clear();
}