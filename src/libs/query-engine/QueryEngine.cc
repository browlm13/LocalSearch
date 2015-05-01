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
//		query processsing
//			--------------------------
void QueryEngine::perform_operation(string unkown, vector<word_packet> &running_results, string &cur_operation){
	//change operation if necssicary
	if(unkown.compare("||") == 0)
		cur_operation = "||";

	else if(unkown.compare("&&") == 0)
		cur_operation = "&&";

	else if(unkown.compare("!!") == 0)
		cur_operation = "!!";

	else{

		//retrieve search results
		vector<word_packet> new_results;
		vector<word_packet> wps;
		wps = ih->search(unkown);

		if(wps.size() > 0){

			//or
			if(cur_operation.compare("||") == 0){
				//add all
				for(int i= 0; i<running_results.size(); i++)
					new_results.push_back(running_results[i]);
				for(int i= 0; i<wps.size(); i++)
					new_results.push_back(wps[i]);
			}

			//and
			if(cur_operation.compare("&&") == 0){
				for(int i=0; i < running_results.size(); i++){
					for(int j=0; j < wps.size(); j++){

						//if doc ids match
						if(running_results[i].id==wps[j].id){
							cout << running_results[i].id.byte_location << " == " << wps[i].id.byte_location << endl;
							new_results.push_back(wps[j]);
						}
					}
				}
			}

			//not
			if(cur_operation.compare("!!") == 0){
				for(int i=0; i < running_results.size(); i++){
					bool match = false;
					for(int j=0; j < wps.size(); j++){

						//if doc ids match
						if(running_results[i].id == wps[j].id){
							cout << running_results[i].id.byte_location << " == " << wps[i].id.byte_location << endl;
							match = true;
						}
					}
					if(!match)
						new_results.push_back(running_results[i]);
				}
			}

		}

		running_results = new_results;
	}

}
//--------------------------
//		searching
//			--------------------------

bool QueryEngine::search(std::string raw_query){
	bool results_found = false;
	vector<string> formatted_query;

	//clear last search results
	wp_results.clear();
	ip_results.clear();

	//format query
	formatted_query = FormatText::format_query(raw_query);

	string cur_operation = "||";
	vector<word_packet> running_results;

	for(int i=0; i < formatted_query.size(); i++)
		perform_operation( formatted_query[i], running_results, cur_operation);

	wp_results = running_results;
	ip_results = ph->fetch_info(running_results, database);


//TMP***
		for(int i =0; i< ip_results.size(); i++)
			cout << ip_results[i].toString();
//TMP***

	//get info packets 								//could this retrieve the line with word?
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