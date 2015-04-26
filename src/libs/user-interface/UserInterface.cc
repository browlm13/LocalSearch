#include "UserInterface.h"

#include <vector>
#include "data-packets/Data_Packets.h"
#include "formatting/FormatText.h"

using namespace std;

string UserInterface::dataBase_toString(){
	string s;
	database_packet dataBase;

	//refresh then get
	qe->load_dataBase();
	dataBase = qe->get_dataBase();

	int max_len =15;
	for(int i = 0; i < dataBase.indexed_docs.size(); i++){
		if(max_len < dataBase.indexed_docs[i].title.size())
			max_len = dataBase.indexed_docs[i].title.size() + 5;
	}

	string title = "DATABASE";
	s += border('-', max_len, title );
	s += "\n";
	for(int i = 0; i < dataBase.indexed_docs.size(); i++){
		int len;
		s += "\n| [";
		s += FormatText::to_string(i+1);
		s += "] ";
		s += dataBase.indexed_docs[i].title;
		len = max_len - dataBase.indexed_docs[i].title.size() - 4;
		s += border(' ', len);
		s += '|';
	}
	s += "\n\n";
	s += border('-', max_len);

	return s;
}

/*
	edit:	create a menue toString
			with border title, and
			vector with selection numbers
			and strings.
											*/

string UserInterface::border(char c, int length){
	string s;
	for(int i = 0; i < length; i++ )
		s += c;
	return s;
}

string UserInterface::border(char c, int length, string title){
	string s;
	int len = (length - title.size()) /2;
	for(int i = 0; i < len; i++ )
		s += c;
	s += title;
	for(int i = 0; i < len; i++ )
		s += c;
	return s;
}