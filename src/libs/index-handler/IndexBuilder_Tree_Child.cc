#include "IndexBuilder_Tree_Child.h"

//--------------------------
//				public			
//			--------------------------

	void IndexBuilder_Tree_Child::insert(word_packet &wp)
		{_insert(child_root, wp);}

	string IndexBuilder_Tree_Child::toString(){
		std::string entries = "";
		_gather( child_root, entries );
		return entries;		
	}

	void IndexBuilder_Tree_Child::topResults(vector<word_packet> &results){
		int result_count = 0;
		_topResults( child_root, results, result_count );
	}
//--------------------------
//				private								
//			--------------------------

		void IndexBuilder_Tree_Child::_insert( IB_Node_Child *&cur, word_packet &wp ){

		//insert when null
		if( !cur )
			cur = new IB_Node_Child( wp );

		//otherwise advance left or right
		else if(wp.tf <= cur->wp.tf)
			_insert( cur->left, wp );

		else if(wp.tf > cur->wp.tf)
			_insert( cur->right, wp );

		//balance Nodes involved in insert
		balance( cur );
	}

void IndexBuilder_Tree_Child::_gather( IB_Node_Child *ptr, string &entries ){
		if( ptr ){
			_gather(ptr->left, entries);
			_gather(ptr->right, entries);

			entries += ptr->wp.child_toString();
		}
	}
	void IndexBuilder_Tree_Child::_topResults( IB_Node_Child *ptr, vector<word_packet> &results, int &result_count){

		if( ptr ){
			_topResults( ptr->right, results, result_count);
			_topResults( ptr->left, results, result_count);

			if(result_count < result_amount){
				results.push_back(ptr->wp);
				result_count++;
			}
		}

	}
