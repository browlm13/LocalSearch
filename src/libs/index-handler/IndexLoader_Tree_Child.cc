#include "IndexLoader_Tree_Child.h"

//--------------------------
//				public			
//			--------------------------
void IndexLoader_Tree_Child::insert(word_packet &wp)
	{_insert(child_root, wp);}

void IndexLoader_Tree_Child::topResults(vector<word_packet> &results, int result_amount_arg){
	result_amount = result_amount_arg;
	int result_count = 0;
	_topResults( child_root, results, result_count );
}

//--------------------------
//				private								
//			--------------------------
void IndexLoader_Tree_Child::_insert( IL_Node_Child *&cur, word_packet &wp ){

	//insert when null
	if( !cur )
		cur = new IL_Node_Child( wp );

	//otherwise advance left or right
	else if(wp.tf <= cur->wp.tf)
		_insert( cur->left, wp );

	else if(wp.tf > cur->wp.tf)
		_insert( cur->right, wp );

	//balance Nodes involved in insert
	balance( cur );
}

void IndexLoader_Tree_Child::_topResults( IL_Node_Child *ptr, vector<word_packet> &results, int &result_count){

	if( ptr ){
		_topResults( ptr->right, results, result_count);
		_topResults( ptr->left, results, result_count);

		if(result_count < result_amount){
			results.push_back(ptr->wp);
			result_count++;
		}
	}

}
