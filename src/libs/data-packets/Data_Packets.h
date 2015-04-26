#ifndef DATA_PACKETS_H
#define DATA_PACKETS_H

#include <string>
#include "formatting/FormatText.h"
	/*
		Description:	One include file
						where all packets and enums are defined.
																	*/
//--------------------------
//		Enums
//			--------------------------

enum DataStuct_Types{
	//possible datastucts
	AVL,
	HASH,
	BUILDER
};

//--------------------------
//		Document Identifier Packet		
//			--------------------------
struct doc_id_packet{

	//constructor
	doc_id_packet(std::string file_path, long byte_location)	: 	
		file_path(file_path), byte_location(byte_location) {}

	//empty constructor
	doc_id_packet()	: 	
		file_path(""), byte_location(0) {}

	//members
	std::string file_path;
	long byte_location;
};

//--------------------------
//		Word Packet		
//			--------------------------

struct word_packet{

	//members
	std::string word;
	int globaltf;
	doc_id_packet id;
	int tf;

	//constructor
	word_packet(std::string word, doc_id_packet id, int tf)	: 	
		word(word), globaltf(tf), id(id), tf(tf) {}

	//constructor2 (with globaltf)
	word_packet(std::string word, int globaltf, doc_id_packet id, int tf)	: 	
		word(word), globaltf(globaltf), id(id), tf(tf) {}

	//empty constructor
	word_packet()	: 	
		word(""), globaltf(0), tf(0) {}

	//copy constructor 													//id pointer could cause trouble
	word_packet(const word_packet &wp)	:
		word(wp.word), globaltf(wp.globaltf), id(wp.id), tf(wp.tf) {}

	//destructor
	~word_packet(){ }

		//( toStirng Methods )
	//parent_head_toString();
	std::string parent_head_toString(){
		std::string s;

		s += "<w>\n";

		s += "\t<t>";
		s += word;
		s += "</t>\n";

		s += "\t<gtf>";
		s += FormatText::to_string(globaltf);
		s += "</gtf>\n";

		return s;
	}

	//parent_tail_toString();
	std::string parent_tail_toString(){
		std::string s;

		s += "</w>\n";

		return s;
	}

	//child_toString();
	std::string child_toString(){
		std::string s;

		s += "\t<e>\n";

		s += "\t\t<tf>";
		s += FormatText::to_string(tf);
		s += "</tf>\n";

		s += "\t\t<l>";
		s += FormatText::to_string(id.byte_location);
		s += "</l>\n";

		s += "\t\t<p>";
		s += id.file_path;
		s += "</p>\n";

		s += "\t</e>\n";

		return s;
	}
};

//--------------------------
//		Page Packet	
//			--------------------------
struct page_packet;

//--------------------------
//		Info Packet	
//			--------------------------
struct info_packet;

//--------------------------
//		Doc Packet	
//			--------------------------
struct doc_packet{

	std::string title;
	std::string fullDoc_path;
	std::string indexDoc_path;
};

#endif	//DATA_PACKETS_H
