#include <iostream>
#include <cstdio>
#include "DataBase_Parser.h"

#include "formatting/FormatText.h"

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
void DataBase_Parser::parse_dataBase(database_packet &database_arg){								//return error
	database_ptr = &database_arg;
	_parse(database_ptr->get_database_path(), 0);
}
//--------------------------
//			close	docs	
//			--------------------------
void DataBase_Parser::close_docs(database_packet &database_arg){								//return error
	database_ptr = &database_arg;
	database_ptr->close();
	ih->close();
}

//--------------------------
//		add	doc to dataBase	
//			--------------------------
//creates the files, copies, adds and updates, calls ih save with new index file
void DataBase_Parser::save(database_packet &database){			//return error

	/*
		edit:	will save all  if(unsaved && open)  files
															*/
	database_ptr = &database;

	//if there are unsaved documents
	if(database_ptr->doc_is_unsaved()){
		doc_packet unsaved_doc;

		unsaved_doc = database_ptr->get_unsaved();

		//if no duplicate names
		if(database_ptr->add_doc(unsaved_doc.title)){
			doc_packet new_doc;

			//add new file to resevoir
			save_dataBase();
			new_doc = database_ptr->get_doc(database.size() - 1);

		    std::ifstream  src(unsaved_doc.fullDoc_path, std::ios::binary);
	 		std::ofstream  dst(new_doc.fullDoc_path,   std::ios::binary);

	 		dst << src.rdbuf();
	 		dst.close();

	 		ih->saveIndex(new_doc.indexDoc_path);
		}else{
			cout << "duplicate file name" << endl;
		}

	} else{
		cout << "no unsaved documents." << endl;
	}
	//if(database_ptr->add_doc())
	/*
	if(database_ptr->add_doc(new_path)){
		save_dataBase();
		dp = database_ptr->get_doc(database.size() - 1);

	    std::ifstream  src(new_path, std::ios::binary);
 		std::ofstream  dst(dp.fullDoc_path,   std::ios::binary);

 		dst << src.rdbuf();
 		dst.close();

 		ih->saveIndex(dp.indexDoc_path);

 			//set saved flag
		database_ptr->set_savedFlag(dp.title, true);

 	} else{
 			//TMP error handling
     		perror( "Error duplicate file" );
     	}//return ERROR_DUPLICATE_FILE;
    */
}

//--------------------------
//		remove	doc from dataBase	
//			--------------------------
//deletes files from index, documents, database, and relodes database
void DataBase_Parser::remove_doc_from_dataBase(int selection, database_packet &database){			//return error
	database_ptr = &database;
	dp = database_ptr->get_doc(selection);

	//delete index file 				//error exit and return
	delete_file(dp.indexDoc_path);

	//delete documents file 			//error exit and return
	delete_file(dp.fullDoc_path);

	//delete from database list
	database_ptr->remove_doc(selection);

	save_dataBase();					//error exit and return
}

//--------------------------
//			save	dataBase	(private)
//			--------------------------
void DataBase_Parser::save_dataBase(){
	//open and empty													//return error
	open_empty_file(database_ptr->get_database_path());
	file.write(database_ptr->toString().c_str(), database_ptr->toString().size());
	close_file();
}

//--------------------------
//			save	dataBase	(private)
//			--------------------------
void DataBase_Parser::delete_file(string path){														//return error

	if( remove( path.c_str() ) != 0 )
    	perror( "Error deleting file" );	//return error
	else
    	puts( "File successfully deleted" );//return error
}