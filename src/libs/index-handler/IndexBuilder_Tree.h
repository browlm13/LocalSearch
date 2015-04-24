#ifndef INDEXBUILDER_TREE_H
#define INDEXBUILDER_TREE_H

#include <fstream>
#include <cstdlib>
#include <string>

#include "IndexBuilder_Tree_Child.h"
#include "data-packets/Data_Packets.h"
//#include "formatting/FormatText.h"
#include "data-structs/avl.h"

/*
	edit: add child_toString() and parent_toString() to data packet word packet
			text formatting will be done here there convert indexBilderTree gtf and string 
			to word_packet (no id, no tf)

			that way these trees really just move around wp's
																							*/

//--------------------------
//		Index Builder Node	(Parent)	(Struct)
//			--------------------------

struct IB_Node {
	
	word_packet parent_wp; 
	IndexBuilder_Tree_Child 	child_tree;

	//mandatory members
	int height, balance;
	IB_Node *left, *right;

	IB_Node(word_packet wp)	: 	
			parent_wp(),
			height(0), balance(0), 
			left(0), right(0) {parent_wp.word = wp.word;}
};

//--------------------------
//		Index Builder Tree				(Class)							
//			--------------------------

class IndexBuilder_Tree : public avl<IB_Node> {

	//private members
	IB_Node 			*root;
	fstream				 index_file;
	string				 index_file_name;

	void _insert( IB_Node*& cur, word_packet &wp );

	void _write( IB_Node *ptr );
	void _search( IB_Node*& cur, std::string &query, std::vector<word_packet> &top_results );
	void open_file( string name );
	void close_file();

	//disable copy constructor
	IndexBuilder_Tree( const IndexBuilder_Tree &ib_tree );

public:

	void insert( word_packet &wp );

	//void write(string path);{//first just sets index_file_name}
	void write();							
	void search(std::string &querty, std::vector<word_packet> &top_results);
	void clear();

	IndexBuilder_Tree( std::string index_file_name )	: root( 0 ), index_file_name( index_file_name ) { };	//should not be passed in here
	~IndexBuilder_Tree()	{ };								//not sure what needs to be done here
};

#endif	//INDEXBUILDER_TREE_H
