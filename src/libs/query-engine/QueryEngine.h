#ifndef QUERYENGINE_H
#define QUERYENGINE_H

//#include <fstream>
#include <vector>

#include "parser-handler/ParserHandler.h"
//#include "IndexHandler"

//TMP****
//#include "porter2-stemmer/porter2_stemmer.h"

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

	//ui functions
	bool search(std::string raw_query);

	database_packet get_dataBase();
	bool get_unsavedFlag();
	vector<word_packet> get_wp_results();
	vector<info_packet> get_ip_results();

	
	//maitince mode:
		//choose index type		//set in index

	//interactive mode:
		//query
			//ih.searchDocs(query_term) //search for each term in query
			//perform operations
			//parser.getInfo(word_packet)
			//display results

	//void query(raw_query);
		//{
			  /*
					edit: word_packet or top
						  results word packet.
						  with vector instead of tree
						  packets need retooling.
			  											*/

			/*
				description:	basically we take a raw_string
								and turn it into a list of doc id's. (location and path)
								then we send these to the parser.fetch_info
								one by one. and add the returned info_packets
								to a vector<info_packet> that gets displayed
								with numbers.

																		*/

			/*

				boolean operation:		(id,id,id) + (id,id,id,id) - (id, id) etc...
										//use doc word packet to store vital info
										(dwp,dwp,dwp) + (dwp,dwp,dwp,dwp) - (dwp, dwp) etc...
																						*/

			  //vector<string> format_query(raw_query);
			  //vector<info_packets> process_query(vector<string> formatted_query);
			  		//{		//int current_operation;
			  				//vector<string> formatted_query
			  				//vector<word_packet> running_total

			  								//use enum here
			  				//void change_operation(int cmd);
			  				//void perform_operation( int (current_operation) &operation , vector<word_packet> &running_total, string (formatted_query[i]) next_word);
			  						//{		
			  								//word packet, or ( topResults_word_packet ) //vector indead of tree
			  								//word_packet cur_word;
			  									//index handler
			  								//cur_word = searchDoc(next_word);

			  								//perform operation with cur_word and runningtotal
									//}
			  				//

						  //chop running total down to size
						  //for each, 
						  //return vector<info_packet> info_packets_to_display = parserhandler.fetch_info(running_total[i]);
						  //or parserhandler.fetch_info()
					//}
		//}

		//parser handler fetch page(info_packet) //should take an info packet
};


#endif	//QUERYENGINE_H
