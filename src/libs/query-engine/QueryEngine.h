#ifndef QUERYENGINE_H
#define QUERYENGINE_H

#include <vector>
#include "parser-handler/ParserHandler.h"

using namespace std;

class QueryEngine {

private:

	//fstream file;
	ParserHandler *ph;
	IndexHandler *ih;
	database_packet database;

	//search results
	vector<word_packet> wp_results;
	vector<info_packet> ip_results;

public:

	QueryEngine(ParserHandler &ph, IndexHandler &ih) : ph(&ph), ih(&ih) {}

	void close_docs();
	void load_doc(int selection);
	void add_newDoc(std::string path_to_doc);			//should be titled "load_newDoc"
	void save_newDoc();
	void remove_doc(int selection);						//should be titled "delete_doc"

	//refreshes or loads database object member
	void load_dataBase();
	//sets datastruct type
	void toggle_type();

	//query proccessing
	void perform_operation(std::string unkown, vector<word_packet> &running_results, std::string &cur_operation);

	//ui functions
	bool search(std::string raw_query);

	database_packet get_dataBase();
	bool get_unsavedFlag();
	vector<word_packet> get_wp_results();
	vector<info_packet> get_ip_results();
};


#endif	//QUERYENGINE_H
