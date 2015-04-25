/*
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// IndexHandler ///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////// IndexHandler Major Functions ///////////////////////////////////////////////////////////

		( Maintince Mode Functions ):

add_NewDoc( "path/to/doc" ) 					{	// convert and save new pages to persistant index. }					//calls parser, then calls saveIndex
clearIndex()			  						{	// obvious. possibly with extra specification 
														//for certain documents : date added, doc name, etc.. (much later). }
(-?)saveIndex()									{	// possibly private, possibly public with parameter for index doc location. }


		( Interactive Mode Functions ):
loadIndex( 0 for hash, 1 for avl ) 				{	// reloade index into selected data structue. }
searchDocs( searched word )						{	// returns doc path and byte_locaiton (how?) . }

---------------------------------- additional functions --------------------------------------------------------------

IndexHandler( Parser, "path/to/storedDoc" )		{	// }
		
		( Building Data Structure Funtions ):
		//add_newDoc() uses diffrent addWord(), newDoc_addWord(), to save time on calculations (int gloabltf) 

addWord( string title, int globaltf, doc_id_packet id, int tf )		{	// adds word elements to data structure. (for loadIndex()) }
newDoc_addWord( string word, doc_id_packet id, int tf )				{	// calculates globaltf while Building.	 (happens in add_newDoc()) }

*********************************************************************************************************************
*/

#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include <string>
#include <iostream>
#include <cstdlib>

//TMP****
//#include "porter2-stemmer/porter2_stemmer.h"

#include "IndexBuilder_Tree.h"

using namespace std;

class IndexHandler {

private:
	int dataStruct_type;

	IndexBuilder_Tree 			builder_avl;

	//IndexLoader_Interface			loader;
			//IndexLoader_Tree			loader_avl;
			//IndexLoader_Hash			loader_hash;

	//disable copy constructor (fuck fstream)
	IndexHandler(const IndexHandler &ih);

public:
	//possibly index file locaiton as arg
	IndexHandler()	{}

	void newDoc_addWord( word_packet wp );

	void 			set_dataStruct(int type);						//sets data struct type, invoked on loadIndex()
	void 			saveIndex 	( std::string path );				//call save on current data structure
																	//only builder avl needs a save, called by query en.
																	//save index will write to a specified file


	void 			loadIndex 	();				//integrate choice with set_data_structure()
	void 			clearIndex 	();				//problem fstream cannot be located in ih, could
												//have fstream fuction namespace ie:open, close clear
	word_packet 	searchDocs 		( const string &query_term );

	//tmp
	void tmp_search(string q);
	//tmp
};


#endif	//INDEXHANDLER_H





/*
//query ready at the end of funtions ??? how to update query ???
	//should return ints

//where to put ii option ?? in load_index parameter ??
//should functions like raw_query pass through index handler at all ??

//query exposed functions:

		//returns id's/locs in order of relevance
		//fetch_id
		//vector<string> get_ids_for_word( string word ); 		//id's...loc...what do we do here?
		vector<string> get_docs_for_word( string word );

//////////////////////////////////////////////////////////////////////////////////////////////////
	//basically just an extra step unless 
	//there could be duplicate long
	//byte locations...	
		//send id or loc
		//if we send loc directly then query may be able to communicate directly with parser
		string fetch_info(int id);
		string fetch_page(long loc);
//////////////////////////////////////////////////////////////////////////////////////////////////

	//loads from (original docs) index_outfile			//specified doc***
	//specific avl tree. then saves
		//possibly returns int 0 or 1 (or short)
		//void create_index();
		void add_docs(string specified_doc_name);		//path??? (said path in sheet)

		//possibly returns int 0 or 1
		void clear_index();

	//loads from index into choice
	//avl or hash ( choice here or elsewhere?? )
		//possibly returns int 0 or 1
		void load_index();

//private functions:

	//called by :	( create index )
		//possibly return int 0 or 1
		void save_index();
/*
private members:
	string index_doc_name;

	Parser p;
	Query q;

	IndexInterface ii;

	//avl_ib_parent builder_tree;	//local to create_index() ??
	//ofstream index_outfile;		//local to save_index() ??



	//for initial build...
//create_index()

	//		p.parse_original(this, original_doc_name);

	//exposed methods:	(exposed to avl_p_original   (in parser))...

	//		builder_tree.insert(string word, int id, int tf)				//?? diffrent ?? //long loc

	//				calls correct child tree node with members:
	//					 ( string word, int globaltf, avl_ib_child *avl )...

	//		avl.insert(int id, int tf);										//long loc;

	//then somthing like...

	//		??.save_index();

//save_index() 					//??? not needed seperate method ??
	//		outfile.open(index_doc_name);

	//				then calls write function on builder_tree...

	//		builder_tree.write(ofstream index_outfile);

	//				which writes some stuff,
	//					then passes along the outfile to its child tree...

	//		avl.write(index_outfile);

	//then probably closes it...
	//		index_outfile.close();



	//otherwise not initial build... 		( for both hash and avl data structures )
//load_index()

	//		p.parse_index(this, index_doc);
	//		ii.add_word(string word, int id, int tf, int globaltf); 		//long loc;
*/
