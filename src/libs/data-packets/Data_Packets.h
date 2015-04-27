#ifndef DATA_PACKETS_H
#define DATA_PACKETS_H

#include <string>
#include <vector>

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

enum File_Errors{
	ERROR_DUPLICATE_FILE
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

		//overloads
	doc_packet& operator=( const doc_packet &rhs ){
		
		title = rhs.title;
		fullDoc_path = rhs.fullDoc_path;
		indexDoc_path = rhs.indexDoc_path;

		return *this;
	}

		//child_toString();
	std::string toString(){
		std::string s;

		s += "<document>\n";

		s += "\t<title>";
		s += title;
		s += "</title>\n";

		s += "\t<full>";
		s += fullDoc_path;
		s += "</full>\n";

		s += "\t<index>";
		s += indexDoc_path;
		s += "</index>\n";

		s += "</document>\n";

		return s;
	}
};

/*
	edit: put deffinitions
			in seperate file.
								*/
//--------------------------
//		Database Packet
//			--------------------------
struct database_packet {

	//members (currently public)
	std::string path_to_database;
	std::string path_to_fullDoc;
	std::string path_to_indexDoc;
	std::string index_prefix;
	std::string database_filename;

	int dataStruct_type;
	std::vector<doc_packet> indexed_docs;

	//private functions (currently public)
	std::string remove_path(std::string original_path){
		std::string title;
		std::string backwords_title;

		for( int i = original_path.size() -1; i >= 0; i-- ){
			if( original_path.at(i) != '/' ){
				backwords_title += original_path.at(i);
			}
			else{
				break;
			}
		}
		
		for(int i= backwords_title.size() - 1; i >=0; i--)
			title += backwords_title.at(i);

		return title;
	}

	//constructor
	database_packet(){
		path_to_database 	= 	"../database/";
		path_to_fullDoc		=	path_to_database + "documents/";
		path_to_indexDoc	=	path_to_database + "index/";
		index_prefix		=	"index-";
		database_filename	=	"database.xml";
	}
	//copy constructor/=operator
	//destructor

	//add a new document
	void add_doc(std::string original_path){
		doc_packet dp;
		dp.title = remove_path(original_path);
		dp.fullDoc_path = path_to_fullDoc + dp.title;
		dp.indexDoc_path = path_to_indexDoc + index_prefix + dp.title;
		indexed_docs.push_back(dp);
	}

	//add_doc instead of this vvv
	void add_doc_packet(doc_packet dp){indexed_docs.push_back(dp);}
	//add_doc instead of this ^^^

	//setters and getters
	std::string 				get_database_path()
	{return path_to_database + database_filename;}		//returns full path to file

	void 						set_dataStruct_type(int type)
	{dataStruct_type = type;}
	int 						get_dataStruct_type()
	{return dataStruct_type;}

	void 						set_indexed_docs(std::vector<doc_packet> i_d)
	{indexed_docs = i_d;}
	std::vector<doc_packet> 	get_indexed_docs()
	{return indexed_docs;}

	int							size()
	{return indexed_docs.size();}

	doc_packet 					get_doc(int index)
	{return indexed_docs[index];}

	//to string
	std::string toString(){
		std::string s;

		s += "<database>\n";

		s += "<dataStruct_type>";
		s += FormatText::to_string(dataStruct_type);
		s += "</dataStruct_type>\n";

		for(int i=0; i < indexed_docs.size(); i++)
			s += indexed_docs[i].toString();

		s += "</database>";
		return s;
	}
};

#endif	//DATA_PACKETS_H
