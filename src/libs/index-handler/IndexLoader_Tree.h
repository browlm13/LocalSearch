#ifndef INDEXLOADER_TREE_H
#define INDEXLOADER_TREE_H

#include <string>
#include <vector>

#include "data-structs/avl.h"
#include "IndexLoader_Interface.h"
#include "IndexLoader_Tree_Child.h"
#include "data-packets/Data_Packets.h"

//--------------------------
//		Index Loader Node	(Parent)	(Struct)
//			--------------------------

struct IL_Node {
	
	word_packet parent_wp; 
	IndexLoader_Tree_Child 	child_tree;

	//mandatory members
	int height, balance;
	IL_Node *left, *right;

	IL_Node(word_packet wp)	: 	
			parent_wp(),
			height(0), balance(0), 
			left(0), right(0) {
				parent_wp.word = wp.word;
				parent_wp.globaltf = wp.globaltf;
			}
};

//--------------------------
//		Index Loader Tree				(Class)							
//			--------------------------

class IndexLoader_Tree : public avl<IL_Node>, public IndexLoader_Interface {

	//private members
	IL_Node 			*root;

	void _addWord( IL_Node*& cur, word_packet &wp );
	void _search( IL_Node*& cur, std::string &query, std::vector<word_packet> &top_results );
public:

	void addWord( word_packet &wp );				
	void search(std::string &querty, std::vector<word_packet> &top_results);
	void clear();


	IndexLoader_Tree()	: root( 0 ) {}
	~IndexLoader_Tree()	{ }								//not sure what needs to be done here
};

#endif	//INDEXLOADER_TREE_H