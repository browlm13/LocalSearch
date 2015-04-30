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

	if(tag_name.compare("l") == 0)
		set_collect_characters(true);

	if(tag_name.compare("p") == 0)
		set_collect_characters(true);
}

void IndexedDoc_Parser::endTag_event(string &tag_name){

	if(tag_name.compare("t") == 0)
		wp.word = get_characters();

	if(tag_name.compare("gtf") == 0)
		wp.globaltf = atoi( get_characters().c_str() );

	if(tag_name.compare("tf") == 0)
		wp.tf = atoi( get_characters().c_str() );

	if(tag_name.compare("l") == 0)
		wp.id.byte_location = atoi( get_characters().c_str() );

	if(tag_name.compare("p") == 0)
		wp.id.file_path = get_characters();

	if(tag_name.compare("e") == 0)
		ih->addWord(wp);
}

//--------------------------
//				parse		
//			--------------------------ph->load_doc(database.get_doc(selection).indexDoc_path, database);
void IndexedDoc_Parser::parse(int selection, database_packet &database){
	database_ptr = &database;
	
	//close open, rest and set flags
	ih->close();
	ih->set_dataStruct(database_ptr->get_dataStruct_type());

	database_ptr->close();

	database_ptr->set_openFlag(database_ptr->get_doc(selection).title, true);

	//TMP***
	cout << "\nselection = " << database_ptr->get_doc(selection).title << endl;

	//TMP***
	cout << "\nselection = " << selection << endl;

  	_parse(database_ptr->get_doc(selection).indexDoc_path, 0);
}
