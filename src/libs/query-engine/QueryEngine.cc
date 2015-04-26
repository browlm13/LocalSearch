#include "QueryEngine.h"

#include <iostream>
#include <string>
#include <vector>
#include "data-packets/Data_Packets.h"

using namespace std;

void QueryEngine::load_dataBase(){
	//tmp**
	string path_to_dataBase = "../database/database.xml";
	ph->parse_dataBase(path_to_dataBase, database);
	ih->set_dataStruct(database.dataStruct_type);
}

void QueryEngine::save_dataBase(){
	//tmp**
	string path_to_dataBase = "../database/database.xml";
	ph->save_dataBase(path_to_dataBase, database);
	//WHY THIS LINE ^^^???
}

database_packet QueryEngine::get_dataBase()
	{return database;}