#ifndef NEWDOC_PARSER_H
#define NEWDOC_PARSER_H

#include "NewDoc_Parser_Tree.h"
#include "xmlshark/XMLShark.h"

#include <iostream>
#include <string>

using namespace std;

		/*
			Description:	Class for handaling new document
							parsing of xml format specific to 
							project 6. Works with ND_Parser_Tree
							to send index building information over
							to the IndexHandler
																		*/

//--------------------------
//		NewDoc_Parser		
//			--------------------------

class NewDoc_Parser : public XMLShark {

private:
	//IndexHandler ih;						//edit, removed ih and initilization from class, not from struct

	struct Word_Maker{
		doc_id_packet id;
		NewDoc_Parser_Tree avl;

		Word_Maker(IndexHandler &ih)	: 	avl(ih){}
	} wm;


		//Events (called by Shark)
	void startDoc_event();
	void endDoc_event()	{}											//does nothing
	void startTag_event(string &tag_name);			
	void endTag_event(string &tag_name);				
	
public:
		//private caller
	void parse(string path);

	NewDoc_Parser(IndexHandler &ih) : wm(ih) {}						//edit, removed initilizatio here
	~NewDoc_Parser(){}
};

#endif // NEWDOC_PARSER_H