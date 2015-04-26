#include "DataBase_Parser.h"
#include "formatting/FormatText.h"
#include <iostream>

using namespace std;
//--------------------------
//				Events		
//			--------------------------

void DataBase_Parser::startTag_event(string &tag_name){
	if(tag_name.compare("dataStruct_type") == 0)
		set_collect_characters(true);

	if(tag_name.compare("title") == 0)
		set_collect_characters(true);

	if(tag_name.compare("full") == 0)
		set_collect_characters(true);

	if(tag_name.compare("index") == 0)
		set_collect_characters(true);
}

void DataBase_Parser::endTag_event(string &tag_name){

	if(tag_name.compare("dataStruct_type") == 0){
		int type;
		string raw_type = get_characters();
		type = atoi(raw_type.c_str());
		database_ptr->dataStruct_type = type;
	}

	if(tag_name.compare("title") == 0)
		dp.title = get_characters();

	if(tag_name.compare("full") == 0)
		dp.fullDoc_path = get_characters();

	if(tag_name.compare("index") == 0)
		dp.indexDoc_path = get_characters();

	if(tag_name.compare("document") == 0)
		database_ptr->indexed_docs.push_back(dp);
}

void DataBase_Parser::endDoc_event()
	{ih->set_dataStruct(database_ptr->dataStruct_type);}

//--------------------------
//			parse	dataBase	
//			--------------------------
void DataBase_Parser::parse_dataBase(std::string path_to_dataBase,  database_packet &database_arg){			//will remove path arg
	database_ptr = &database_arg;
	_parse(path_to_dataBase, 0);	//use ( database_ptr->get_database_path() ) for path
}


/*
//--------------------------
//		add	doc to dataBase	
//			--------------------------
void DataBase_Parser::add_doc_to_dataBase(std::string new_path, database_packet &database){			//creates the files, copies, adds and updates, calls ih save with new index file

	database.add_doc(new_path);
	//dp = database.get_doc(database.size());			//needs copy constructor, "class member dp"

	//copy file to full file to internal database (dp.fullDoc_path)
		//if not already there...(should handle duplicate names later)
		if(dp.fullDoc_path.compare(new_path) != 0){
		    std::ifstream  src(new_path, std::ios::binary);
     		std::ofstream  dst(dp.fullDoc_path,   std::ios::binary);
     		dst << src.rdbuf();
     	}

														//create new file for index (dp.indexDoc_path)			//should be handled by builder avl tree
	//save builder tree to index file
	ih->saveIndex(dp.indexDoc_path);						//will create and write to index, file.open(dp.indexDoc_path/ihversion, fstream::out);
}
*/
//--------------------------
//			save	dataBase	(to be private)
//			--------------------------
void DataBase_Parser::save_dataBase(std::string path_to_dataBase, database_packet database){			//will remvoe path
	open_file(path_to_dataBase);	//use (database_ptr->get_database_path()) for path
	file.write(database.toString().c_str(), database.toString().size());
	close_file();
}