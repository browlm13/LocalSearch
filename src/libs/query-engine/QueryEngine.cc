#include <iostream>
#include <string>
#include <vector>
#include "QueryEngine.h"

#include "data-packets/Data_Packets.h"

using namespace std;

//--------------------------
//		private		
//			--------------------------

void QueryEngine::load_dataBase(){
	ph->parse_dataBase(database);						//will return error
}

//--------------------------
//		public
//			--------------------------

//--------------------------
//		set up
//			--------------------------
void QueryEngine::close_docs(){
	ph->close_docs(database);
}

void QueryEngine::load_doc(int selection){ 

	/*
		edit: should be no current_doc,
			just a get open doc function
			from database (doc_is open())
			then (get_open())
											*/

	ph->load_doc(selection, database);

/*
	//try to work around this
	current_doc = database.get_doc(selection);
	ph->load_doc(current_doc.indexDoc_path, database);			//will return error
*/
}

void QueryEngine::add_newDoc(string path_to_doc) {

	ph->add_newDoc(path_to_doc, database);
	//trying to work around new path
	/*
	new_path = path_to_doc;
	ph->add_newDoc(path_to_doc, database);
	*/

/*
	//try to work around this
	current_doc = database.get_doc(database.size() - 1);
	new_path = path_to_doc;
	ph->add_newDoc(path_to_doc);						//will return error
*/
}

	/*
		edit: 	make add_doc_to_adatBase
			not take a new path, just add to
			database imidealty with original 
			path stored???

												*/
void QueryEngine::save_newDoc(){
	ph->save(database);		//will return error	
}

void QueryEngine::remove_doc(int selection){
	ph->remove_doc_from_dataBase(selection, database);	//will return error
}

//--------------------------
//		searching
//			--------------------------
//vector<info_packet> QueryEngine::search(std::string raw_query){
void QueryEngine::search(std::string raw_query){
	string formatted_query;
	vector<word_packet> raw_results;

	//TMP
	raw_results = ih->search(raw_query);
	for(int i=0; i< raw_results.size();i++){
		cout << "\nword found: " << raw_results[i].word << ", gtf: " << raw_results[i].globaltf << ", tf: " << raw_results[i].tf << ", path: " << raw_results[i].id.file_path << ", loc: " << raw_results[i].id.byte_location << endl;
	}

	//vector<info_packet> results;

	//format query
	//formatted_query = FormatTest::format_query(raw_query);

	//get raw doc results
	//raw_results = ih->search(formatted_query);

	//get info packets
	//results = ph->fetch_info(raw_rseults);

	//return results;
}

//--------------------------
//		user interface functions
//			--------------------------
database_packet QueryEngine::get_dataBase(){
	return database;
}

bool QueryEngine::get_unsavedFlag(){
	return database.doc_is_unsaved();
}
