#ifndef INDEXBUILDER_TREE_H
#define INDEXBUILDER_TREE_H

#include <fstream>
#include <cstdlib>
#include <string>

#include "IndexLoader_Interface.h"
#include "IndexBuilder_Tree_Child.h"
#include "data-packets/Data_Packets.h"
//#include "formatting/FormatText.h"
#include "data-structs/avl.h"

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

class IndexBuilder_Tree : public avl<IB_Node>, public IndexLoader_Interface {

	//private members
	IB_Node 			*root;
	fstream				 index_file;
	//string				 index_file_name;

	void _addWord( IB_Node*& cur, word_packet &wp );
	void _write( IB_Node *ptr );
	void _search( IB_Node*& cur, std::string &query, std::vector<word_packet> &top_results );
	void open_file( string name );
	void close_file();

	//disable copy constructor
	IndexBuilder_Tree( const IndexBuilder_Tree &ib_tree );

public:

	void addWord( word_packet &wp );				
	void search(std::string &querty, std::vector<word_packet> &top_results);
	void clear();
	void save(std::string path);

	IndexBuilder_Tree()	: root( 0 ) {};
	~IndexBuilder_Tree()	{ };								//not sure what needs to be done here
};

#endif	//INDEXBUILDER_TREE_H
