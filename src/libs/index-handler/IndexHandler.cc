#include "IndexHandler.h"

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

/*
	edit: remove add_NewDoc,
			not under ih control.
									*/

void IndexHandler::add_NewDoc(string path){
		//first fill up builder tree by calling parser
	//ParserHandler ph();
	//ph.parse_newDoc(path);


		//then write builder to index file
	//saveIndex();

	//TMP*************
	//string index_filename = "index.txt";
	//IndexBuilder_Tree avl_builder(index_filename);
}


void IndexHandler::newDoc_addWord( word_packet wp )
	{builder_avl.insert( wp );}

//--------------------------
//		File Functions:		
//			--------------------------

void IndexHandler::saveIndex(){
	/*
	//open_file(index_filename.c_str());
	//***tmp***
	string index_filename = "index.txt";
	open_file(index_filename);
	//builder_avl.write();
	close_file();
	*/

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
	builder_avl.write();
	
	builder_avl.clear();

}
/*
void IndexHandler::open_file(string path){
	/*
	index_file.open(path.c_str());
	if(index_file.fail()){
		cout << "error opening" << path << endl;
		exit(1);
	}
	*/
//}
/*
void IndexHandler::close_file()
{}
//{index_file.close();}

*/
