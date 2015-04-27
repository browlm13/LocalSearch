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
	std::string new_path;

public:

	QueryEngine(ParserHandler &ph, IndexHandler &ih) : ph(&ph), ih(&ih) {}

	void load_dataBase();	//refreshes or loads database object member

	void load_doc(int selection); //{ph.load_doc( dataBase[selection].path_to_IndexedDoc );}

	void add_newDoc(std::string path_to_doc);  //{ph.add_newDoc(path_to_doc);}
	void save_newDoc();

	//ui functions
	database_packet get_dataBase();

	//maitince mode:
		//add new Doc(path/to/doc)			//communicates with parser
			//mabey copies doc into local repository
			//save index			//calls save index automatically after add newDoc
		//clear index			//communicates with index
		//choose index type		//set in index

	//interactive mode:
		//load index			//load if not correct type

		//query
			//ih.searchDocs(query_term) //search for each term in query
			//perform operations
			//parser.getInfo(word_packet)
			//display results

	/*
		edit: use enum for
			  dataStruct type.
								*/

								//with style:
			// ( files: )
	//dataBase/dataBase.xml					//list of saved docs and their info, and saved config settings
	//dataBase/index/docName.xml			//indexed version
	//dataBase/documents/docName.xml		//full version


			//( boot/database interface )
		//query engine
	//void init();
		//{
			//parser handler
		//vector<doc_packet> parse_dataBase(&dataStruct_type, path/to/doc?);	//changes data struct type
			//index handler
		//set_dataStruct(dataStruct);
		//}


			//( searching doc from database )
		//query engine
	//void load_database_doc(doc_packet);
		//{
			//parser handler
		//void load_doc( doc_packet.path/to/doc );
			//(possibly) query engine
		//void query(raw_query);
		//}


			//( new doc searching )
		//query engine
	//void search_newDoc();
		//{
			//parser handler
		//void add_newDoc(path/to/doc);
			//(possibly)query engine
		//void query(raw_query);
			//(possibly)index handler
		//void save_newDoc();
		//}

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
				//is there a way to do this while saving importaint info??? (ie. the word and tf for each id, ***word packet** tada, word packet for individual docs)
					//word packets for individual docs with (word, global tf(corresponding to doc_id_packet, doc_id_packet )
					//more accuratley names doc_word_packet //probaly useful in many places
					//or mabey something better.. cause doc mean a couple things
//***page_word_packet*** (already used but needs to be page_retooled and renamed)

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


		//saving:
			/*
				query engine will remeber the path/to/document that was loaded into the builder tree.
				it will create a copy and move the doc to its internal spot.
				it will add an extension to the name and create a blank file in the indexs folder.
				it will create a key value pair or shome packet for the database original doc its new index doc path
				when you write it will pass the new index doc path to ih which will pass to builder tree.write(path/to/doc)
			*/

};


#endif	//QUERYENGINE_H
