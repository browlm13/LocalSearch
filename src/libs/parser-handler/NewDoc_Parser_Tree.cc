#include "NewDoc_Parser_Tree.h"

//--------------------------
//		NewDoc_Parser_Tree 					(definitions)	
//			--------------------------

void NewDoc_Parser_Tree::insert(string word, doc_id_packet id)
{	_insert(root, word, id);	}

void NewDoc_Parser_Tree::send_to_ih()
{	_send_to_ih(root);	}

void NewDoc_Parser_Tree::clear()
{ root = 0;}

void NewDoc_Parser_Tree::_insert(NDP_Node*& cur, std::string word, doc_id_packet id){

	//insert when null
	if(!cur)
		cur = new NDP_Node(word, id);

	//otherwise advance left or right
	else if(word.compare(cur->word) < 0)
		_insert(cur->left, word, id);

	else if(word.compare(cur->word) > 0)
		_insert(cur->right, word, id);

	//duplication handaling
	else
		cur->tf++;

	//balance Nodes involved in insert
	balance(cur);
}

void NewDoc_Parser_Tree::_send_to_ih(NDP_Node *ptr){

	//order it writes is not importaint
	if(ptr){

		_send_to_ih(ptr->left);
		_send_to_ih(ptr->right);

		word_packet	wp(ptr->word, ptr->id, ptr->tf);
		ih->addWord(wp);

		ptr->left = 0;
		ptr->right = 0;
		ptr = 0;

		/*
			strange behavior:	Why is this
								if statment needed?
														*/
									

		//if(ptr->word.size() > 0){

			/*
				edit:	should create word packets
						during ndp_tree, so should
						just use copy constructor bellow.
															*/


			//word_packet	wp(ptr->word, ptr->id, ptr->tf);
			//ih->newDoc_addWord(wp);

			//////////////////////no word_packet//////////////////////
			//ih->newDoc_addWord(ptr->word, ptr->id, ptr->tf);


			/*
				edit:	clear function needed.
												*/

			/*
			ptr->word = "";
			ptr->id.byte_location = 0;
			ptr->id.file_path = "";
			ptr->tf = 0;
			ptr = 0;
			*/
			///////////////////////end no word_packet//////////////////
		//}
	}
}