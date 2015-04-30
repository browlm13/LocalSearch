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
	HASH,
	AVL,
	BUILDER
};

enum File_Errors{
	ERROR_DUPLICATE_FILE,
	ERROR_OPENING_FILE
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

		s += "<w>";

		s += "<t>";
		s += word;
		s += "</t>";

		s += "<gtf>";
		s += FormatText::to_string(globaltf);
		s += "</gtf>";

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

		s += "\n<e>";

		s += "<tf>";
		s += FormatText::to_string(tf);
		s += "</tf>";

		s += "<l>";
		s += FormatText::to_string(id.byte_location);
		s += "</l>";

		s += "<p>";
		s += id.file_path;
		s += "</p>";

		s += "</e>";

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
struct info_packet{
	doc_id_packet id;
	std::string title;
	string contributors;
	std::string text;

	void clear(){
		title = "no title";
		contributors = "no contributors";
		text = "no text";
	}

	std::string toString(){
		string s;
		s += "\n\t\t[";
		s += title;
		s += ", ";
		s += contributors;
		s += ".]\n\t ";
		s += text;
		s += "\n";
		return s;
	}
};

//--------------------------
//		Doc Packet	
//			--------------------------
struct doc_packet{

	std::string title;
	std::string fullDoc_path;
	std::string indexDoc_path;

	//flags
	const bool savedFlag;
	bool openFlag;

		//( constructors )

	//saved document constructor (saved always true)
	doc_packet() : savedFlag(true), openFlag(false) {}

	//tmp document constructor 	 (saved always false)
	doc_packet(bool tmp_document) : savedFlag(false), openFlag(true) {
		indexDoc_path = "TMP_DOC_UNSAVED";
	}

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

	//add a new document (saved)
	bool add_doc(std::string original_path){
		doc_packet dp;
		dp.title = remove_path(original_path);
		dp.fullDoc_path = path_to_fullDoc + dp.title;
		dp.indexDoc_path = path_to_indexDoc + index_prefix + dp.title;

		//check if allready there, return false if a match
		bool not_duplicate = true;
		for(int i= 0; i < indexed_docs.size(); i++){
			if (dp.title.compare(indexed_docs[i].title) == 0)
				not_duplicate = false;
		}
		if(not_duplicate)
			indexed_docs.push_back(dp);
		return not_duplicate;
	}

	//add a temporary document (unsaved)
	void add_tmp_doc(std::string original_path){
		doc_packet dp(true);
		dp.title = remove_path(original_path);
		dp.fullDoc_path = original_path;
		indexed_docs.push_back(dp);
	}

	//remove a document
	void remove_doc(int index){
		vector<doc_packet> new_index_list;

		for(int i=0; i < index; i++){
			new_index_list.push_back(indexed_docs[i]);
		}
		for(int i= index +1; i < indexed_docs.size(); i++){
			new_index_list.push_back(indexed_docs[i]);
		}
		indexed_docs.clear();
		indexed_docs = new_index_list;
	}

	//remove unsaved document
	void remove_unsaved_doc(){

		//locate unsaved document and remove
		for(int i= 0; i < indexed_docs.size(); i++){
			if (indexed_docs[i].savedFlag == false)
				remove_doc(i);
		}
	}

	//clear
	void clear(){
		indexed_docs.clear();
	}

	//flags	
	void set_openFlag(std::string path, bool state){
		string document_to_check = remove_path(path);

		for(int i= 0; i < indexed_docs.size(); i++){
			if (document_to_check.compare(indexed_docs[i].title) == 0){
				indexed_docs[i].openFlag = state;
			}
		}
	}

	//sets all doc flags to close
	void close(){
		for(int i= 0; i < indexed_docs.size(); i++){
			if(indexed_docs[i].savedFlag == false)
				remove_doc(i);
		}
		for(int i= 0; i < indexed_docs.size(); i++){
			indexed_docs[i].openFlag = false;
		}	
	}

	//check for open doc
	bool doc_is_open(){
		bool is_open = false;

		for(int i= 0; i < indexed_docs.size(); i++){
			if (indexed_docs[i].openFlag == true)
				is_open = true;
		}

		return is_open;
	}
	//check for open doc at index
	bool doc_is_open(int index){
		bool is_open = false;

		if (indexed_docs[index].openFlag == true)
			is_open = true;

		return is_open;
	}
	//check for unsaved doc
	bool doc_is_unsaved(){
		bool is_unsaved = false;

		for(int i= 0; i < indexed_docs.size(); i++){
			if (indexed_docs[i].savedFlag == false)
				is_unsaved = true;
		}

		return is_unsaved;
	}
	//return open doc
	doc_packet get_open(){
		for(int i= 0; i < indexed_docs.size(); i++){
			if (indexed_docs[i].openFlag == true)
				return indexed_docs[i];
		}
	}

	//return unsaved doc
	doc_packet get_unsaved(){
		for(int i= 0; i < indexed_docs.size(); i++){
			if (indexed_docs[i].savedFlag == false)
				return indexed_docs[i];
		}
	}

	std::string get_database_path()
	{return path_to_database + database_filename;}		//returns full path to file

	void set_dataStruct_type(int type)
	{dataStruct_type = type;}
	int get_dataStruct_type()
	{return dataStruct_type;}

	void set_indexed_docs(std::vector<doc_packet> i_d)
	{indexed_docs = i_d;}
	std::vector<doc_packet> get_indexed_docs()
	{return indexed_docs;}

	int	size()
	{return indexed_docs.size();}

	doc_packet 	get_doc(int index)
	{return indexed_docs[index];}

	//finds the full document path from matching info
	std::string get_fullDoc_path(std::string path){
		string title = remove_path(path);
		bool found = false;

		//return full path
		for(int i = 0; i < indexed_docs.size(); i++){
			if(title.compare(indexed_docs[i].title) == 0){
				return indexed_docs[i].fullDoc_path;
				found = true;
			}
		}
		if (!found)
			std::cout << "document not recognized in database\n";
	}

	//to string
	std::string toString(){
		std::string s;

		s += "<database>\n";

		s += "<dataStruct_type>";
		s += FormatText::to_string(dataStruct_type);
		s += "</dataStruct_type>\n";

		for(int i=0; i < indexed_docs.size(); i++){
			if(indexed_docs[i].savedFlag == true)
				s += indexed_docs[i].toString();
		}

		s += "</database>";
		return s;
	}
};

#endif	//DATA_PACKETS_H
