#include <iostream>
#include <string>
#include <vector>
#include "QueryEngine.h"

#include "data-packets/Data_Packets.h"

using namespace std;

//--------------------------
//		private		
//			--------------------------

void QueryEngine::load_dataBase(){
	ph->parse_dataBase(database);						//will return error
}

//--------------------------
//		public
//			--------------------------

void QueryEngine::load_doc(int selection){ 

	/*
		edit: pass database as argumment
			to load doc as well.
										*/

	current_doc = database.get_doc(selection);
	ph->load_doc(current_doc.indexDoc_path);			//will return error
}

void QueryEngine::add_newDoc(string path_to_doc) {
	new_path = path_to_doc;
	ph->add_newDoc(path_to_doc);						//will return error
}

void QueryEngine::save_newDoc(){
	ph->add_doc_to_dataBase(new_path, database);		//will return error
}

void QueryEngine::remove_doc(int selection){
	ph->remove_doc_from_dataBase(selection, database);	//will return error
}

//--------------------------
//		user interface functions
//			--------------------------
database_packet QueryEngine::get_dataBase(){
	load_dataBase();
	return database;
}

bool QueryEngine::get_savedFlag(){
	return ih->get_savedFlag();
}