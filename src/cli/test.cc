#include <time.h>  
//#include <fstream>
//#include <iostream>
//#include <string>
//#include <vector>

//#include "data-packets/Data_Packets.h"
//#include "index-handler/IndexHandler.h"

//***tmp***
#include "parser-handler/NewDoc_Parser.h"
#include "parser-handler/IndexedDoc_Parser.h"


#include "parser-handler/ParserHandler.h"
#include "query-engine/QueryEngine.h"
#include "user-interface/UserInterface.h"

//tmp
//#include "parser-handler/DataBase_Parser.h"

using namespace std;


//calculate file size
std::ifstream::pos_type filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}

//add prefix
vector<string> add_prefix( const char *prefix, const vector<string> file_names ){
	vector<string> full_path_documents;

	for(int i=0; i<file_names.size(); i++){
		string full_path(prefix);
		full_path += file_names[i];
		full_path_documents.push_back(full_path);
	}

	return full_path_documents;
}

//add prefix
string add_prefix( const char *prefix, const char* file_name ){
	string full_document_path(prefix);
	full_document_path += file_name;

	return full_document_path;
}


int main(){

//---------------------------------------------------------------------------------------------------//
//		Folder Paths
//---------------------------------------------------------------------------------------------------//

//--------------------------
//		"Index" prefix
//			--------------------------------

	//Document Path Prefix
	const char* const 	database_pathPrefix = 	"../database/";

//--------------------------
//		"documents" prefix
//			--------------------------------

	//Document Path Prefix
	const char* const 	documents_pathPrefix = 	"../database/documents/";											//const1 = const contents,	 const2 = const ptr

	//Associated Documents Vector
	std::vector<string> document_files_tmp;

//--------------------------
//		"Index" prefix
//			--------------------------------

	//Document Path Prefix
	const char* const 	index_pathPrefix = 	"../database/index/";

//--------------------------
//		"resources" prefix
//			--------------------------------

	//Document Path Prefix
	const char* const 	resource_pathPrefix = 	"../resources/";	

//--------------------------
//		file names
//			--------------------------------

	/*
		edit:	Documents to be added  durring
				user input
												*/
	/*
		edit:	Make timming and testing
				seperate function to be called
				by main?
												*/
	//Documents	
	const char* const 	testDoc0_fileName 	= 	"testDoc0.xml";
	document_files_tmp.push_back(testDoc0_fileName);
	const char* const 	testDoc1_fileName 	= 	"testDoc1.xml";
	//document_files_tmp.push_back(testDoc1_fileName);
	const char* const 	testDoc2_fileName 	= 	"testDoc2.xml";
	//document_files_tmp.push_back(testDoc2_fileName);
	const char* const 	testDoc3_fileName 	= 	"testDoc3.xml";
	//document_files_tmp.push_back(testDoc3_fileName);
	const char* const 	testDoc4_fileName 	= 	"testDoc4.xml";
	//document_files_tmp.push_back(testDoc4_fileName);
	const char* const	wikibooks_fileName 	= 	"enwikibooks-20140519-pages-meta-current.xml";
	//document_files_tmp.push_back(wikibooks_fileName);

	document_files_tmp = add_prefix(documents_pathPrefix, document_files_tmp);


	/*
		edit: make extern and const?
										*/

	//Index
	const char* const 	index_fileName 		= 	"index.xml";
	string index_file = add_prefix(index_pathPrefix, index_fileName);

	//StopWords
	const char* const 	stopWords_fileName	=	"stopWords.txt";
	string stopWords_file = add_prefix(resource_pathPrefix, stopWords_fileName);

//---------------------------------------------------------------------------------------------------//
//		Launch
//---------------------------------------------------------------------------------------------------//

		//( Program )
    //initilize program
    IndexHandler ih;
    //tmp
    NewDoc_Parser ndp(ih);
    IndexedDoc_Parser idp(ih);

    ParserHandler ph(ih);
    QueryEngine qe(ph, ih);
    UserInterface ui(qe);


    //tmp
    //string test_path_doc = "../database/documents/testDoc0.xml";
    //string test_path_index = "../database/index/index-testDoc0.xml";

    //start up example
    ui.init();
    //cout << ui.dataBase_toString();

    //enters new doc path
    //get doc path, save that shit
    //add new doc
    /*
    ih.set_dataStruct(DataStuct_Types::BUILDER);
    ih.set_savedFlag(false);
    ndp.parse(test_path_doc);
	*/

	/*
    //save
    ih.saveIndex(test_path_index);
    ih.set_savedFlag(true);
	*/

	/*
    //load from databse
    ih.set_dataStruct(DataStuct_Types::BUILDER);
    idp.parse(test_path_index);
	*/

    //cout << ui.dataBase_toString();
    //qe.load_dataBase();
	//NewDoc_Parser ndp(ih);
	/*
	DataBase_Parser dbp;

	//test
	string path = "../database/database.xml";
	vector<doc_packet> indexed_docs;
	int type;
	dbp.parse_dataBase(path, indexed_docs, type);

	cout << type << endl;
	for(int i = 0; i<indexed_docs.size(); i++)
		cout << indexed_docs[i].title << endl;
	*/

	return 0;
}