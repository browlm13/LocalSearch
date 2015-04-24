#ifndef NEWDOC_PARSER_TREE_H
#define NEWDOC_PARSER_TREE_H

#include "index-handler/IndexHandler.h"

		/*
			Description:	Basially a term frequency calculator.
							Once its filled for a pages worth
							the tree will write to ih, 
							clearring the entire tree.
							It must write and clear 
							before every new page.
																	*/


//---------------------------------------------------------------------------------------------------//
//		NewDoc_Parser_Tree 	Prototype
//---------------------------------------------------------------------------------------------------//

//--------------------------
//		NewDoc_Parser_Tree	NODE
//			--------------------------

struct NDP_Node {
		NDP_Node(string word, doc_id_packet id)	: 	
					word(word), id(id),
					tf(1),
					height(0), balance(0), 
					left(0), right(0) {	}

		//new members
		string word;
		doc_id_packet id;

		int tf;

		//mandatory members
		int height, balance;
		NDP_Node *left, *right;
};
//--------------------------
//		NewDoc_Parser_Tree			
//			--------------------------

class NewDoc_Parser_Tree : public avl<NDP_Node> {

private:

	IndexHandler *ih;
	NDP_Node *root;

	//compares words
	//Duplications: ++tf
	void _insert(NDP_Node*& cur, std::string word, doc_id_packet id);


	//sends words to index handler with: title, path, loc, tf	
	//clears struct
	void _write(NDP_Node *ptr);

public:
	void insert(std::string word, doc_id_packet id);
	void write();
	void clear();

	NewDoc_Parser_Tree(IndexHandler &ih)	: 
			ih(&ih), root(0) { }
	~NewDoc_Parser_Tree()	{ };								//not sure what needs to be done here
};

#endif	//NEWDOC_PARSER_TREE_H