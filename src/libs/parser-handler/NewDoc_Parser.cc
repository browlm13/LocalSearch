#include "NewDoc_Parser.h"
#include <iostream>

//---------------------------------------------------------------------------------------------------//
//		NewDoc_Parser 	Definitions
//---------------------------------------------------------------------------------------------------//
//--------------------------
//				Events		
//			--------------------------

/**
*	sets file path in Word_Maker object
*/
void NewDoc_Parser::startDoc_event()
	{	wm.id.file_path = get_path();	}	

void NewDoc_Parser::startTag_event(string &tag_name){
	//start page event
	if(tag_name.compare("page") == 0)
		wm.id.byte_location = get_location();

	//start text event
	if(tag_name.compare("text") == 0)
		set_collect_formatted_strings(true);
}

void NewDoc_Parser::endTag_event(string &tag_name){
	//if title

	//end text event
	if(tag_name.compare("text") == 0){
		//get formatted text and insert into tree
		vector<string> text = get_formatted_strings();
		for(int i =0; i < text.size(); i++)
			wm.avl.insert(text[i], wm.id);
	}

	//end page event
	if(tag_name.compare("page") == 0){
		wm.avl.write();
		wm.avl.clear();
	}
}
//--------------------------
//				parse		
//			--------------------------

void NewDoc_Parser::parse(string path){
	//call private with path and starting location 0
	_parse(path, 0);
}