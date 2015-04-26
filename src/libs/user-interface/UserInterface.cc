#include "UserInterface.h"

#include <sstream>
#include <vector>
#include "data-packets/Data_Packets.h"
#include "formatting/FormatText.h"

using namespace std;

void UserInterface::homeScreen(){
	//header
	cout << border('=', 100, " local SEARCH ") << endl << endl;

	cout << dataBase_toString() << endl;

	//user input
	//cout << prompt("[#]: ") << endl;
	string new_path = prompt("[new path]: ");

	//TMP
	string test_path_doc = "../database/documents/testDoc0.xml";
	string test_path_index = "../database/index/index-testDoc0.xml";
	qe->add_newDoc(test_path_doc);
	qe->save_newDoc(test_path_index);

	//tail
	cout << border('=', 100) << endl;
}

string UserInterface::dataBase_toString(){
	string s;
	database_packet dataBase;
	vector<string> saved_docs;

	//refresh then get
	qe->load_dataBase();
	dataBase = qe->get_dataBase();

	for(int i = 0 ; i < dataBase.indexed_docs.size(); i++)
		saved_docs.push_back(dataBase.indexed_docs[i].title);

	s = options_box(saved_docs, " Saved Documents ");

	return s;
}

/*
	edit:	create a menue toString
			with border title, and
			vector with selection numbers
			and strings.
											*/


string UserInterface::prompt(string prompt){
	string input;
	cout << prompt;
	getline(cin, input);
	return input;
}

string UserInterface::options_box(vector<string> options, string title){
	string s;
	int max_len = 0;

	for(int i = 0; i < options.size(); i++){
		if(max_len < options[i].size())
			max_len = options[i].size() + 10;
	}
	s += border('-', max_len, title );
	s += "\n";
	for(int i = 0; i < options.size(); i++){
		s += " \n[";
		s += FormatText::to_string(i+1);
		s += "] ";
		s += options[i];
	}
	s += "\n\n";
	s += border('-', max_len);
	s += "\n";

	return s;
}

/*
string UserInterface::options_box(vector<option_cmd_packet>  option_cmd, string title){
	
}
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