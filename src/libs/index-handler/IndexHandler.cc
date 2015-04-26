#include "IndexHandler.h"
//#include "data-packets/Data_Packets.h"

//TMP
#include <iostream>
using namespace std;
void IndexHandler::tmp_search(string q){
	//TMP***search
	vector<word_packet> results;
	//builder_avl.search(q, results);
	loader->search(q, results);
	cout << endl << "search = " << q;
	for (int i=0; i<results.size(); i++)
		cout << "\n\t" <<results[i].word << ", gtf: " << results[i].globaltf << ", tf: " << results[i].tf << ", path: " << results[i].id.file_path << ", loc: " << results[i].id.byte_location;	
	results.clear();
}
//TMP

void IndexHandler::set_dataStruct(int type){
	dataStruct_type = type;

	if(dataStruct_type == DataStuct_Types::AVL){
		loader = new IndexLoader_Tree;
		//loader = &loader_avl;
	}
	if(dataStruct_type == DataStuct_Types::BUILDER){
		loader = new IndexBuilder_Tree;
		//loader = &builder_avl;
	}
}

void IndexHandler::set_savedFlag(bool status)
	{saved = status;}

void IndexHandler::addWord( word_packet wp )
	{loader->addWord(wp);}

//--------------------------
//		File Functions:		
//			--------------------------

void IndexHandler::saveIndex(string path){
/*
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
	//builder_avl.save(path);
	
	//seperate function call needs to be specified
	//builder_avl.clear();

	//can only save under two condition (unsaved && builder)
	if( (!saved) && (dataStruct_type == DataStuct_Types::BUILDER) ){
		loader->save(path);
		set_savedFlag(true);
	}
	else{
		set_savedFlag(false);
		cout << "SAVED." << endl;
	}
}