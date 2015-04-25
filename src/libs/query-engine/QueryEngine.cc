#include "QueryEngine.h"

#include <iostream>
#include <string>
#include <vector>
#include "data-packets/Data_Packets.h"

using namespace std;

void QueryEngine::load_dataBase(){
	//tmp**
	string path_to_dataBase = "../database/database.xml";
	ph->parse_dataBase(path_to_dataBase, dataBase, dataStruct_type);
	ih->set_dataStruct(dataStruct_type);
}

std::vector<doc_packet> QueryEngine::get_dataBase()
	{return dataBase;}