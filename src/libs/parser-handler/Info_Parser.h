#ifndef INFO_PARSER_H
#define INFO_PARSER_H

#include <iostream>
#include <vector>
#include "xmlshark/XMLShark.h"

#include "../data-packets/Data_Packets.h"

//--------------------------
//		Info_Parser		
//			--------------------------

class Info_Parser : public XMLShark {

private:

	info_packet tmp;
	vector<info_packet> info_packets;
	database_packet *database_ptr;


		//Events (called by Shark)
	void startDoc_event();
	void endDoc_event()	{}	//does nothing
	void startTag_event(string &tag_name);			
	void endTag_event(string &tag_name);				
	
public:
		//private caller
	std::vector<info_packet> parse(std::vector<word_packet> raw_results, database_packet &database);	

	Info_Parser(){}	
	~Info_Parser(){}
};

#endif // INFO_PARSER_H