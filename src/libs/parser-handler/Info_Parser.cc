#include <iostream>
#include <string>
#include "Info_Parser.h"

using namespace std;

//--------------------------
//				Events		
//			--------------------------

void Info_Parser::startDoc_event(){}	

void Info_Parser::startTag_event(string &tag_name){
	if(tag_name.compare("title") == 0)
		set_collect_characters(true);

	if(tag_name.compare("contributors") == 0)
		set_collect_characters(true);

	if(tag_name.compare("text") == 0)
		set_collect_characters(true);
}

void Info_Parser::endTag_event(string &tag_name){
	if(tag_name.compare("title") == 0){
		string title = get_characters();
		tmp.title = title;
	}

	if(tag_name.compare("contributors") == 0){
		string contributors = get_characters();
		tmp.contributors = contributors;
	}


	if(tag_name.compare("text") == 0){
		string text = get_characters();
		tmp.text = text;
	}

	if(tag_name.compare("page") == 0){
		info_packets.push_back(tmp);
		tmp.clear();
		close_file();
	}
}

//--------------------------
//				parse		
//			--------------------------

//calls private with path and starting location 0
vector<info_packet> Info_Parser::parse(vector<word_packet> raw_results, database_packet &database){
	info_packets.clear();
	database_ptr = &database;

	//call parse on each
	for(int i=0; i < raw_results.size(); i++)
		_parse( database_ptr->get_fullDoc_path(raw_results[i].id.file_path) ,raw_results[i].id.byte_location );

	return info_packets;
}