#include "IndexHandler.h"
//#include "data-packets/Data_Packets.h"

//TMP
#include <iostream>
using namespace std;
void IndexHandler::tmp_search(string q){
	//TMP***search
	vector<word_packet> results;
	builder_avl.search(q, results);
	cout << endl << "search = " << q;
	for (int i=0; i<results.size(); i++)
		cout << "\n\t" <<results[i].word << ", gtf: " << results[i].globaltf << ", tf: " << results[i].tf << ", path: " << results[i].id.file_path << ", loc: " << results[i].id.byte_location;	
	results.clear();
}
//TMP

void IndexHandler::set_dataStruct(int type){
	dataStruct_type = type;

	if(type == DataStuct_Types::AVL)
		loader = &loader_avl;
	if(type == DataStuct_Types::BUILDER)
		loader = &builder_avl;
}

void IndexHandler::addWord( word_packet wp ){
	//TMP
	loader->addWord(wp);
	cout << wp.word << wp.globaltf << endl;
}

void IndexHandler::newDoc_addWord( word_packet wp ){
	set_dataStruct(DataStuct_Types::BUILDER);
	addWord(wp);
}
	//{builder_avl.addWord( wp );}

//--------------------------
//		File Functions:		
//			--------------------------

void IndexHandler::saveIndex(string path){

	//TMP***search
	vector<string> test_search_terms;
	string a = "trex";
	test_search_terms.push_back(a);
	string b = "batman";
	test_search_terms.push_back(b);
	string c = "evolution";
	test_search_terms.push_back(c);
	string d = "microwave";
	test_search_terms.push_back(d);
	string e = "dna";
	test_search_terms.push_back(e);
	string f = "coffee";
	test_search_terms.push_back(f);
	string g = "fashion";
	test_search_terms.push_back(g);
	string h = "lead";
	test_search_terms.push_back(h);
	string i = "africa";
	test_search_terms.push_back(i);

/*
	for(int i=0; i < test_search_terms.size(); i ++)
	{tmp_search(test_search_terms[i]);}
*/
			//tmp
	//string index_path = "../resources/index.xml";
	builder_avl.save(path);
	
	//seperate function call needs to be specified
	builder_avl.clear();
}