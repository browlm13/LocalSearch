#include "QueryEngine.h"

#include <iostream>
#include <string>
#include <vector>
#include "data-packets/Data_Packets.h"

using namespace std;

//--------------------------
//		private		
//			--------------------------

void QueryEngine::load_dataBase(){
	ph->parse_dataBase(database);
}

//--------------------------
//		public
//			--------------------------

void QueryEngine::load_doc(int selection){ //{ph.load_doc( dataBase[selection].path_to_IndexedDoc );}
	current_doc = database.get_doc(selection);
	ph->load_doc(current_doc.indexDoc_path);
}

void QueryEngine::add_newDoc(string path_to_doc) {
	new_path = path_to_doc;
	ph->add_newDoc(path_to_doc);
}

void QueryEngine::save_newDoc(){
	ph->add_doc_to_dataBase(new_path, database);		//will return error
}

//user interface funcitons
database_packet QueryEngine::get_dataBase(){
	load_dataBase();
	return database;
}