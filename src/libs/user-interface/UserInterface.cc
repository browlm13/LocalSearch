#include "UserInterface.h"

#include <sstream>
#include <vector>
#include "data-packets/Data_Packets.h"
#include "formatting/FormatText.h"

using namespace std;

/*
	things to think about:	doc concistancy when switching screens.
		 					back and forward screen navigation.
		 					just like (s)ave can appear and dissapear...
		 					some letter will always bring you to search
		 					if avaible from any screen.
																				*/

void UserInterface::homeScreen(){
	//header
	cout << border('=', 100, " local SEARCH ") << endl << endl;

	cout << dataBase_toString() << endl;

	//start
	//int selection = atoi( prompt("[#]: ").c_str() );

	//if (correct) #
	//qe->load_doc(selection);		//error return
	//searchScreen();

	//if n
	//newDocScreen();


	//if c
	//configScreen();

	//if q
	//quitScreen();

	//tail
	cout << border('=', 100) << endl;
}

void UserInterface::newDocScreen(){

	/*
		edit:		if you must search cmds
					use quotes.				*/


	//string new_path = prompt("[new path]: ");
	//qe->add_newDoc(new_path);			//error return


	//if h
	//homeScreen();

	//if s
	//qe->save_newDoc();				//error return


	//if c
	//configScreen();


	//if q
	//quitScreen();

	//drops through to search screen if success
	//searchScreen();
}

void UserInterface::searchScreen(){

	//string query = prompt("[?query?]: ");
		//***still working***
		//*will jump into in*
		//*-foScreen() if su*
		//*-sessful.        *
		//*******************

	//if h
	//homeScreen();

	/*
		edit: "s" should only be visible when
				possible.
													*/

	//if s
	//qe->save_NewDoc();			//error return

	//if c
	//configScreen();

	//if q
	//quitScreen();

	//drops through to info screen if success
	//infoScreen();
}

void UserInterface::configScreen(){

	//string settings = prompt("[set]: ");
		//***still working***

	//if h
	//homeScreen();

	//if q
	//quitScreen();
}

void UserInterface::quitScreen(){
	//checks if unsaved doc
	//if unsaved gives warning
	//if you choose not to quit
	//after warning, brings you
	//back to screen q was pressed
}

void UserInterface::infoScreen(){}
void UserInterface::pageScreen(){}



string UserInterface::dataBase_toString(){
	string s;
	database_packet dataBase;
	vector<string> saved_docs;

	//refresh then get
	dataBase = qe->get_dataBase();

	if(dataBase.size() > 0){
		for(int i = 0 ; i < dataBase.indexed_docs.size(); i++)
			saved_docs.push_back(dataBase.indexed_docs[i].title);

		s = options_box(saved_docs, " Saved Documents ");
	}
	else
		s = "No saved Documents";

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