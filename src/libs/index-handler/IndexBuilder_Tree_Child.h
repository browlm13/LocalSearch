#ifndef INDEXBUILDER_TREE_CHILD_H
#define INDEXBUILDER_TREE_CHILD_H

#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>

#include "data-packets/Data_Packets.h"
//#include "formatting/FormatText.h"
#include "data-structs/avl.h"

using namespace std;
//--------------------------
//		Index Builder Node Child		(Struct)		
//			--------------------------

struct IB_Node_Child {

	word_packet wp;

	int height, balance;
	IB_Node_Child *left, *right;

	IB_Node_Child(word_packet &wp) :
		wp(wp),
		height(0), balance(0), 
		left(0), right(0) {}
};

//--------------------------
//		Index Builder Tree Child		(Class)								
//			--------------------------

class IndexBuilder_Tree_Child : public avl<IB_Node_Child> {

	//root node
	IB_Node_Child 	*child_root;
	int result_amount;

	void _insert( IB_Node_Child*& cur, word_packet &wp );
	void _gather( IB_Node_Child *ptr, std::string &entries );
	void _topResults( IB_Node_Child *ptr, std::vector<word_packet> &results, int &result_count);

public:

	void insert(word_packet &wp);
	std::string toString();
	void topResults(std::vector<word_packet> &results);
	void set_result_amount(int new_result_amount) {result_amount = new_result_amount;}

	IndexBuilder_Tree_Child()	: 
			child_root(0), result_amount(3)	{ };						//tmp*** init result amount
	~IndexBuilder_Tree_Child()	{ };									//not sure what needs to be done here
	
};

	#endif //INDEXBUILDER_TREE_CHILD_H
