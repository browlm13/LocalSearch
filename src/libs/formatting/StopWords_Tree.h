#ifndef STOPWORDS_TREE_H
#define STOPWORDS_TREE_H

#include "data-structs/avl.h"

#include <fstream>

		/*
			Description:	
							*/


//---------------------------------------------------------------------------------------------------//
/*
*		StopWords_Tree 	Prototype
*/
//---------------------------------------------------------------------------------------------------//

//--------------------------
//		StopWords_tree	NODE
//			--------------------------

struct SWT_Node {

		//new members
		string word;

		//mandatory members
		int height, balance;
		SWT_Node *left, *right;

		SWT_Node(string word)	: 	
			word(word),
			height(0), balance(0), 
			left(0), right(0) {	}
};

//--------------------------
//		StopWords_Tree			
//			--------------------------

class StopWords_Tree : public avl<SWT_Node> {

private:

	fstream file;
	string file_path;
	SWT_Node *root;

	void _insert(SWT_Node*& cur, std::string word);
	void _search(SWT_Node*& cur, string unkown, bool &found);

public:
	bool stop_word(const string &unkown);
	void load();
	void load(const string path);
	void clear();

	StopWords_Tree()					:   root(0) { }
	StopWords_Tree(string file_path)	:  file_path(file_path), root(0) { }
	~StopWords_Tree()	{ };								//not sure what needs to be done here
};
//---------------------------------------------------------------------------------------------------//
/*
*		StopWords_Tree 	Definitions
*/
//---------------------------------------------------------------------------------------------------//

//--------------------------
//		StopWords_Tree 					(definitions)	
//			--------------------------

bool StopWords_Tree::stop_word(const string &unkown){
	bool is_stop_word = false;
	_search(root, unkown, is_stop_word);
	return is_stop_word;
}

void StopWords_Tree::_search(SWT_Node*& cur, string unkown, bool &found){
	if(!found && cur){
			if(unkown.compare(cur->word) == 0)
				found = true;
			else if(unkown.compare(cur->word) < 0)
				_insert(cur->left, unkown);
			else if(unkown.compare(cur->word) > 0)
				_insert(cur->right, unkown);
	}
}

void StopWords_Tree::load(){
	clear();
	file.open(file_path.c_str());


	/*
		check for failure
							*/

	//string word;
	string stop_word;
	char *word;
	while(!file.eof()){
		file.getline(word,20,'\n');
		stop_word = word;
		_insert(root, word);
	}

}

void StopWords_Tree::load(const string path){
	clear();
	file.open(path.c_str());


	/*
		check for failure
							*/

	//string word;
	string stop_word;
	char *word;
	while(!file.eof()){
		file.getline(word,20,'\n');
		stop_word = word;
		_insert(root, word);
	}

}

void StopWords_Tree::clear()
{ root = 0;}

void StopWords_Tree::_insert(SWT_Node*& cur, std::string word){

	//insert when null
	if(!cur)
		cur = new SWT_Node(word);

	//otherwise advance left or right
	else if(word.compare(cur->word) < 0)
		_insert(cur->left, word);

	else if(word.compare(cur->word) > 0)
		_insert(cur->right, word);

	//balance Nodes involved in insert
	balance(cur);
}

#endif	//STOPWORDS_TREE_H