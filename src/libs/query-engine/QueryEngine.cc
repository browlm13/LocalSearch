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
	ph->load_doc(selection, database);
}

void QueryEngine::add_newDoc(string path_to_doc) {
	ph->add_newDoc(path_to_doc, database);
}

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
bool QueryEngine::search(std::string raw_query){
	bool results_found = false;
	string formatted_query;

	wp_results = ih->search(raw_query);
	ip_results = ph->fetch_info(wp_results, database);

	if(ip_results.size() > 0)
		results_found = true;

	/////////////////////////////////////////////////////

	//format query
	//formatted_query = FormatTest::format_query(raw_query);

	//get raw doc results
	//raw_results = ih->search(formatted_query);

	//get info packets
	//results = ph->fetch_info(raw_rseults);

	return results_found;
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

vector<word_packet> QueryEngine::get_wp_results(){
	return wp_results;
}

vector<info_packet> QueryEngine::get_ip_results(){
	return ip_results;
}