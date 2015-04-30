#include "NewDoc_Parser.h"
#include <iostream>

//--------------------------
//				Events		
//			--------------------------

/**
*	sets file path in Word_Maker object
*/
void NewDoc_Parser::startDoc_event(){
	wm.id.file_path = get_path();
}	

void NewDoc_Parser::startTag_event(string &tag_name){
	if(tag_name.compare("page") == 0)
		wm.id.byte_location = get_location();

	if(tag_name.compare("text") == 0)
		set_collect_formatted_strings(true);
}

void NewDoc_Parser::endTag_event(string &tag_name){
	//if (title)

	if(tag_name.compare("text") == 0){
		//get formatted text and insert into tree
		vector<string> text = get_formatted_strings();
		for(int i =0; i < text.size(); i++)
			wm.avl.insert(text[i], wm.id);
	}

	if(tag_name.compare("page") == 0){
		wm.avl.send_to_ih();
		wm.avl.clear();
	}
}

//--------------------------
//				parse		
//			--------------------------

//calls private with path and starting location 0
void NewDoc_Parser::parse(string path, database_packet &database){
	database_ptr = &database;
	
	//close open, rest and set flags
	ih->close();
	ih->set_dataStruct(DataStuct_Types::BUILDER);

	database_ptr->close();
	database_ptr->add_tmp_doc(path);

	_parse(path, 0);	
}