#include "QueryEngine.h"

#include <iostream>
#include <string>
#include <vector>
#include "data-packets/Data_Packets.h"

using namespace std;

void QueryEngine::load_dataBase(){
	//tmp**
	string path_to_dataBase = "../database/database.xml";		//gets this from database, only needs one argument then
	ph->parse_dataBase(path_to_dataBase, database);				//will not need path
}

//will delete this function
void QueryEngine::save_dataBase(){
	//tmp**
	string path_to_dataBase = "../database/database.xml";
	ph->save_dataBase(path_to_dataBase, database);				//will not need path
}
//to be deleted


void QueryEngine::add_newDoc(string path_to_doc) {
	ph->add_newDoc(path_to_doc);
}

void QueryEngine::save_newDoc(string path_to_doc){		//string new path
	//ph->add_doc_to_dataBase(new_path, database)

	//will be deleted
	ih->saveIndex(path_to_doc);
	//will be deleted
}

//user interface funcitons
database_packet QueryEngine::get_dataBase()
	{return database;}