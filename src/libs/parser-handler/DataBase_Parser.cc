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
void DataBase_Parser::parse_dataBase(database_packet &database_arg){
	database_ptr = &database_arg;
	_parse(database_ptr->get_database_path(), 0);
}

//--------------------------
//		add	doc to dataBase	
//			--------------------------
//creates the files, copies, adds and updates, calls ih save with new index file
void DataBase_Parser::add_doc_to_dataBase(std::string new_path, database_packet &database){			//return error
	database_ptr = &database;
	database_ptr->add_doc(new_path);
	save_dataBase();
	dp = database_ptr->get_doc(database.size() - 1);

	//copy file to full file to internal database (dp.fullDoc_path)
		//if not already there...(should handle duplicate names later)
		if(dp.fullDoc_path.compare(new_path) != 0){

		    std::ifstream  src(new_path, std::ios::binary);
     		std::ofstream  dst(dp.fullDoc_path,   std::ios::binary);

     		dst << src.rdbuf();
     		dst.close();
     	}
     	else{}//return ERROR_DUPLICATE_FILE;

	ih->saveIndex(dp.indexDoc_path);
}

//--------------------------
//			save	dataBase	(private)
//			--------------------------
void DataBase_Parser::save_dataBase(){
	open_file(database_ptr->get_database_path());
	file.write(database_ptr->toString().c_str(), database_ptr->toString().size());
	close_file();
}