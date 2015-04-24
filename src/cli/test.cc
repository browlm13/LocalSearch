#include <time.h>  
//#include <fstream>
//#include <iostream>
//#include <string>
//#include <vector>

//#include "data-packets/Data_Packets.h"
//#include "index-handler/IndexHandler.h"
//***tmp***
#include "parser-handler/NewDoc_Parser.h"

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
//		Resource Files
//---------------------------------------------------------------------------------------------------//

//--------------------------
//		"resources" prefix
//			--------------------------------

	//Path Prefix
	const char* const 	resource_pathPrefix = 	"../resources/";												//const1 = const contents,	 const2 = const ptr

	//Associated Documents Vector
	std::vector<string> document_files_tmp;

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

	document_files_tmp = add_prefix(resource_pathPrefix, document_files_tmp);


	/*
		edit: make extern and const?
										*/

	//Index
	const char* const 	index_fileName 		= 	"index.xml";
	string index_file = add_prefix(resource_pathPrefix, index_fileName);

	//StopWords
	const char* const 	stopWords_fileName	=	"stopWords.txt";
	string stopWords_file = add_prefix(resource_pathPrefix, stopWords_fileName);

//---------------------------------------------------------------------------------------------------//
//		Launch
//---------------------------------------------------------------------------------------------------//

		//( Program )
    //initilize program
    IndexHandler ih(index_file);
	NewDoc_Parser ndp(ih);

	//Number of trials
    int num_reps = 2;
    int num_docs = document_files_tmp.size();

    for (int i = 0; i < num_docs; i++){

		float ave_mb_per_sec = 0;
		float ave_sort_time_sec = 0;

    	//cur size
		float testDoc_mbs = filesize(document_files_tmp[i].c_str()) / 1000000.0;

		//"*************************************************"
		//"			../rescources/testDoc4.xml				"
		//"				file size: 720.671 MB 				"
		//"	Trials RRS Time:								"
		std::cout << std::string(75, '_');
    	printf ("\n\n\t\t\t%s\n\nfile (SIZE): %f mb\n\n  load time:\t\t\tload speed:",document_files_tmp[i].c_str(), testDoc_mbs);

    	for (int j = 0; j < num_reps; j++){
			//clear index file for trial

			//CLOCK START
			clock_t t;
			t = clock();



			//( Program )
			//TMP***
			ndp.parse(document_files_tmp[i]);



			//CLOCK END
			t = clock() - t;

			//time
			float sort_time_sec = ((float)t) / CLOCKS_PER_SEC;
			float mb_per_sec = testDoc_mbs / sort_time_sec;

			//"Trail 4. RRS time:		130 sec,	8.4 mb/sec";
			printf ("\n  %d. %f secs,\t\t%f mb/sec.",(j+1) ,sort_time_sec, mb_per_sec);

			ave_mb_per_sec += mb_per_sec;
			ave_sort_time_sec += sort_time_sec;


			//( Program )
	  		ih.saveIndex();
	  	}

	  	//time
		ave_mb_per_sec /= num_reps;
		ave_sort_time_sec /= num_reps;

		//"			average mb/sec:	7.999								"
		printf ("\n\naverage (SPEED): %f mb/sec\n\n",ave_mb_per_sec);
	}

	return 0;
}