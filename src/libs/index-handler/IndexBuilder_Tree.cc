#include "IndexBuilder_Tree.h"

//--------------------------
//				public
//			--------------------------

void IndexBuilder_Tree::addWord(word_packet &wp)
	{_addWord(root, wp);}

void IndexBuilder_Tree::save(string path){ 
	open_file(path);
	_write(root);
	close_file();
}

void IndexBuilder_Tree::search( std::string &query, std::vector<word_packet> &top_results )
	{_search(root, query, top_results);}

void IndexBuilder_Tree::clear()
	{ root = 0;}

//--------------------------
//				private	
//			--------------------------

void IndexBuilder_Tree::_addWord( IB_Node*& cur, word_packet &wp ){	
	//TMP
	//cout << wp.word << endl;
	if(!cur){
		cur = new IB_Node( wp );
		cur->parent_wp.globaltf = wp.tf;
		cur->child_tree.insert( wp );		
	}
	else if( wp.word.compare(cur->parent_wp.word) < 0 )
		_addWord( cur->left, wp );
	else if( wp.word.compare(cur->parent_wp.word) > 0 )
		_addWord( cur->right, wp );
	else{
		cur->parent_wp.globaltf += wp.tf;
		cur->child_tree.insert( wp );
	}

	balance( cur );
}

void IndexBuilder_Tree::_write( IB_Node *ptr ){
		if( ptr ){
			//TMP
			//cout << "saving..." << endl;
			_write( ptr->left );
			_write( ptr->right );

			if( index_file.is_open() ){
				string segment;

				segment += ptr->parent_wp.parent_head_toString();
				segment += ptr->child_tree.toString();
				segment += ptr->parent_wp.parent_tail_toString();

				index_file.write(segment.c_str(), segment.size() );
			}
			else
				cout << "index file not open";
		}
}

void IndexBuilder_Tree::_search( IB_Node*& cur, std::string &query, std::vector<word_packet> &top_results ){

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

void IndexBuilder_Tree::open_file( string path ){

	index_file.open( path.c_str() );
	if( index_file.fail() ){
		cout << "error opening" << path << endl;
		exit( 1 );
	}
}

void IndexBuilder_Tree::close_file()
	{	index_file.close();	}
