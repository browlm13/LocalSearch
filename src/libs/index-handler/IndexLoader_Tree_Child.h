#ifndef INDEXLOADER_TREE_CHILD_H
#define INDEXLOADER_TREE_CHILD_H

#include <vector>
#include "data-structs/avl.h"
#include "data-packets/Data_Packets.h"


//--------------------------
//		Index Loader Node Child		(Struct)		
//			--------------------------

struct IL_Node_Child {

	word_packet wp;

	int height, balance;
	IL_Node_Child *left, *right;

	IL_Node_Child(word_packet &wp) :
		wp(wp),
		height(0), balance(0), 
		left(0), right(0) {}
};

//--------------------------
//		Index Loader Tree Child		(Class)								
//			--------------------------

class IndexLoader_Tree_Child : public avl<IL_Node_Child> {

	//root node
	IL_Node_Child 	*child_root;
	int result_amount;

	void _insert( IL_Node_Child*& cur, word_packet &wp );
	void _topResults( IL_Node_Child *ptr, std::vector<word_packet> &results, int &result_count);

public:

	void insert(word_packet &wp);
	void topResults(std::vector<word_packet> &results, int result_amount_arg);

	IndexLoader_Tree_Child()	: child_root(0){ };
	~IndexLoader_Tree_Child()	{ }	
	
};

#endif //INDEXLOADER_TREE_CHILD_H
