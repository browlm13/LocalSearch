#include <sstream>
#include "UserInterface.h"

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

	//Home Screen CMDS
	vector<cmd> homeScreen_cmds;
	homeScreen_cmds.push_back(newDoc);
	homeScreen_cmds.push_back(config);
	homeScreen_cmds.push_back(quit);

	set_cmds(homeScreen_cmds);

	/*
		edit:	screens may require a check
			for open (searchable) files,
			and/or unsaved files.		*/


	//header
	cout << border('=', screen_width, " local SEARCH ", 2) << endl << endl;

	cout << dataBase_toString() << endl;

	cout << cmds_toString();



	//start
	string ui = prompt("[#]: ");

	//check if ui is a number
	if(is_int(ui)){
		int selection = atoi( ui.c_str() );
		database_packet database = qe->get_dataBase();
		//check if there is a corresponding doc
		if(selection < database.size()){
				qe->load_doc(selection);		//error return
				searchScreen();
		}
	}
	else{
		run_cmd(ui);
	}

	//if command function (display commands)

	//if n
	//newDocScreen();


	//if c
	//configScreen();

	//if q
	//quitScreen();

	//tail
	cout << border('=', screen_width, 0) << endl;
}

void UserInterface::newDocScreen(){
	cout << "newDocScreen" << endl;
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
	cout << "searchScreen" << endl;
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
	cout << "configScreen" << endl;
	//string settings = prompt("[set]: ");
		//***still working***

	//if h
	//homeScreen();

	//if q
	//quitScreen();
}

void UserInterface::quitScreen(){
	cout << "quitScreen" << endl;
	//checks if unsaved doc
	//if unsaved gives warning
	//if you choose not to quit
	//after warning, brings you
	//back to screen q was pressed
}

void UserInterface::infoScreen(){}
void UserInterface::pageScreen(){}

//--------------------------
//		command handling
//			--------------------------

void UserInterface::set_cmds(vector<cmd> cmds){
	cur_cmds.clear();
	for(int i=0; i< cmds.size(); i++){
		cur_cmds.push_back(cmds[i]);
	}

	if(!qe->get_savedFlag())
		cur_cmds.push_back(save);
}


void UserInterface::run_cmd(string cmd){

	//cmd = FormatText::lower_case(cmd);

	//make sure it is in current cmd list...
	bool available = false;
	for(int i=0; i<cur_cmds.size() ; i++){
		if(cmd.compare(cur_cmds[i].trigger) == 0)
			available = true;
	}

	if(available){
		//quit
		if(cmd.compare(quit.trigger) == 0)
			quitScreen();
		//home
		if(cmd.compare(home.trigger) == 0)
			homeScreen();
		//config
		if(cmd.compare(config.trigger) == 0)
			configScreen();
		//new doc
		if(cmd.compare(newDoc.trigger) == 0)
			newDocScreen();
	}
	else
		cout << "command not available\n";

}

//--------------------------
//		toString	
//			--------------------------

string UserInterface::cmds_toString(){

	string command_box;
	command_box = border('_', screen_width, 2);
	command_box += "CMDS:\t";

	for(int i=0; i<cur_cmds.size(); i++){
		command_box += cur_cmds[i].display_name;
		command_box += "\t";
	}

	return  command_box;
}

string UserInterface::dataBase_toString(){
	string s;
	database_packet dataBase;
	vector<string> saved_docs;

	//refresh then get
	dataBase = qe->get_dataBase();

	if(dataBase.size() > 0){
		for(int i = 0 ; i < dataBase.indexed_docs.size(); i++)
			saved_docs.push_back(dataBase.indexed_docs[i].title);

		s = options_box(saved_docs, " Saved Documents ", screen_width, 1 );
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

//--------------------------
//		eye candy	
//			--------------------------

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

//oreientation, 0 = left, 1 = center, 2 = right
string UserInterface::options_box(vector<string> options, string title, int screen_width, int orientation){
	string s;
	int max_len = 5;
	int indent;


	//caluclate border size
	for(int i = 0; i < options.size(); i++){
		if(max_len < options[i].size())
			max_len = options[i].size() + 10;
	}

	//calulcate indent from orientation
	//center
	if(orientation == 1)
		indent = (screen_width/2) - (max_len/2);
	//right
	if(orientation == 2)
		indent = screen_width - max_len - indent;

	s += border(' ', indent);
	s += border('-', max_len, title );

	s += "\n";
	for(int i = 0; i < options.size(); i++){
		s += border(' ', indent, 0);
		s += "[";
		s += FormatText::to_string(i+1);
		s += "] ";
		s += options[i];
	}
	s += "\n";
	s += border(' ', indent, 0);
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

//border new line control; 0 = indent before, 1, = indent after, 2 = indent both
string UserInterface::border(char c, int length, int indent ){
	string s;

	if(indent == 0 || indent == 2)
		s += "\n";

	for(int i = 0; i < length; i++ )
		s += c;

	if(indent == 1 || indent == 2)
		s += "\n";

	return s;
}

//border new line control; 0 = indent before, 1, = indent after, 2 = indent both
string UserInterface::border(char c, int length, string title, int indent){
	string s;

	if(indent == 0 || indent == 2)
		s += "\n";

	int len = (length - title.size()) /2;
	for(int i = 0; i < len; i++ )
		s += c;
	s += title;
	for(int i = 0; i < len; i++ )
		s += c;

	if(indent == 1 || indent == 2)
		s += "\n";

	return s;
}

//--------------------------
//		ui helpers	
//			--------------------------
bool UserInterface::is_int(std::string in_question){
	bool is_int = true;

	for(int i =0; i< in_question.length(); i++){
		int c = (int)in_question.at(i);
		if( c < 48 || c> 57){
			is_int = false;
		}
	}

	return is_int;
}
