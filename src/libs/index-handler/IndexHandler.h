#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include <string>
#include <iostream>
#include <cstdlib>

#include "IndexBuilder_Tree.h"
#include "IndexLoader_Tree.h"
#include "IndexLoader_Hash.h"

using namespace std;

class IndexHandler {

private:
	int dataStruct_type;
	int result_amount;

	/*
		edit: currently nessicary because
			there is know new gaurd;
			if a something like an emptyFlag is
			use to gaurd clear() and settype()
			then new may be used					*/

	//test tmp
	IndexLoader_Tree			loader_avl;
	IndexLoader_Hash			loader_hash;
	IndexBuilder_Tree 			builder_avl;

	IndexLoader_Interface		*loader;

	//disable copy constructor
	IndexHandler(const IndexHandler &ih);

public:
	//possibly index file locaiton as arg
	IndexHandler() {result_amount = 999999;}				//make this automatically return entire tree
	~IndexHandler() {}

	void 			set_dataStruct( int type );	

	//setup
	void addWord( word_packet wp );

	//maintinence
	void 			saveIndex 	( std::string path );
	void 			close 		();

	//searching
	vector<word_packet> 	search 		( const string query_term );
};


#endif	//INDEXHANDLER_H