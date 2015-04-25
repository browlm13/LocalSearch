#include "IndexLoader_Tree.h"

//--------------------------
//				public
//			--------------------------

void IndexLoader_Tree::addWord(word_packet &wp)
	{_addWord(root, wp);}

void IndexLoader_Tree::search( std::string &query, std::vector<word_packet> &top_results )
	{_search(root, query, top_results);}

void IndexLoader_Tree::clear()
	{ root = 0;}

//--------------------------
//				private	
//			--------------------------

void IndexLoader_Tree::_addWord( IL_Node*& cur, word_packet &wp ){			

	if(!cur){
		cur = new IL_Node( wp );
		cur->parent_wp.globaltf = wp.tf;
		cur->child_tree.insert( wp );		
	}
	else if( wp.word.compare(cur->parent_wp.word) < 0 )
		_addWord( cur->left, wp );
	else if( wp.word.compare(cur->parent_wp.word) > 0 )
		_addWord( cur->right, wp );
	else
		cur->child_tree.insert( wp );

	balance( cur );
}

void IndexLoader_Tree::_search( IL_Node*& cur, std::string &query, std::vector<word_packet> &top_results ){

	//insert when null, then insert into child tree
	if( !cur ){}

	//otherwise advance left or right
	else if( query.compare( cur->parent_wp.word ) < 0 )
		_search( cur->left, query, top_results);

	else if( query.compare( cur->parent_wp.word ) > 0 )
		_search( cur->right, query, top_results );

	else{

		cur->child_tree.topResults(top_results);

		//update globaltf on word packets, only an issue in indexBuilder
		for(int i=0; i<top_results.size(); i++)
			top_results[i].globaltf = cur->parent_wp.globaltf;
	}
}