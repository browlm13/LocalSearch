#include "IndexedDoc_Parser.h"

		/*
			description:	sends over line
							by line to index handler
							t, gtf, tf, loc, p
														*/

//--------------------------
//				Events		
//			--------------------------

void IndexedDoc_Parser::startTag_event(string &tag_name){
	
	if(tag_name.compare("t") == 0)
		set_collect_characters(true);

	if(tag_name.compare("gtf") == 0)
		set_collect_characters(true);

	if(tag_name.compare("tf") == 0)
		set_collect_characters(true);

	if(tag_name.compare("loc") == 0)
		set_collect_characters(true);

	if(tag_name.compare("p") == 0)
		set_collect_characters(true);
}

void IndexedDoc_Parser::endTag_event(string &tag_name){

	if(tag_name.compare("t") == 0)
		wp.word = get_characters();

	if(tag_name.compare("gtf") == 0)
		wp.globaltf = 3; //atoi( get_characters().c_str() );

	if(tag_name.compare("tf") == 0)
		wp.tf = 2; //atoi( get_characters().c_str() );

	if(tag_name.compare("loc") == 0)
		wp.id.byte_location = 1; //atoi( get_characters().c_str() );

	if(tag_name.compare("p") == 0)
		wp.id.file_path = get_characters();

	if(tag_name.compare("e") == 0)
		ih->addWord(wp);
}

//--------------------------
//				parse		
//			--------------------------
void IndexedDoc_Parser::parse(string path, database_packet &database){
	database_ptr = &database;
	ih->set_dataStruct(database_ptr->get_dataStruct_type());
  	_parse(path, 0);	
}
