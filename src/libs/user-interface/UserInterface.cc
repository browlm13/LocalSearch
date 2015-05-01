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

				/*
					edit:	need diffrent types of messages
																*/

				/*
					edit:	need banner that dispalays header
						and cmds below, with hide option.
																*/

//--------------------------
//		screens
//			--------------------------
void UserInterface::init(){
	qe->load_dataBase();
	homeScreen();
}

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
	system("clear");

	//display comds
	cout << cmds_toString();

	cout << border('=', screen_width, " local SEARCH ", 2) << endl << endl;

	cout << dataBase_toString() << endl;


	//start
	string ui = prompt("\n[#]: ");

	//check if ui is a number
	if(is_int(ui)){
		int selection = atoi( ui.c_str() );
		database_packet database = qe->get_dataBase();
		//check if there is a corresponding doc
		if(selection <= database.size()){
				//if document is already open
				if(database.doc_is_open(selection - 1)){
					searchScreen();
				}
				else{

					/*
						edit:	can this be an unsaved 
								warning function?
														*/

					//if there is an open and unsaved doc give warning
					if(database.doc_is_open() && database.doc_is_unsaved()){

						//warning message
						cout << "\n\t\tUnsaved document will be closed\n\t\tWould you like to save it?\n";
						ui = prompt("[y/N]: ");

						//ui = FormatText::lower_case(ui);
						if(ui.compare("y") == 0)
							qe->save_newDoc();
						else{
							cout << "\nDocument not saved.\n";
							qe->load_doc(selection - 1);		//error return
							searchScreen();
						}

					}else{
						qe->load_doc(selection - 1);		//error return
						searchScreen();
					}
				}

					/*
						edit:	can this be an unsaved 
								warning function?
														*/

		}
	}
	else{
		run_cmd(ui);
	}

}

void UserInterface::newDocScreen(){
		//NewDoc Screen CMDS
	vector<cmd> newDocScreen_cmds;
	newDocScreen_cmds.push_back(home);
	newDocScreen_cmds.push_back(config);
	newDocScreen_cmds.push_back(quit);

	set_cmds(newDocScreen_cmds);

	//start
	system("clear");

	//display comds
	cout << cmds_toString();

	cout << border('*', screen_width, " open a new document? ", 2) << endl << endl;

	string ui = prompt("\n[path]: ");

	//check if ui is a cmd
	if(!run_cmd(ui)){
		//search

		//TMP
		cout << "opening " << ui << endl;
		qe->add_newDoc(ui);
	}

	searchScreen();

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

		//Search Screen CMDS
	vector<cmd> searchScreen_cmds;
	searchScreen_cmds.push_back(home);
	searchScreen_cmds.push_back(config);
	searchScreen_cmds.push_back(quit);

	set_cmds(searchScreen_cmds);

	/*
		edit:	screens may require a check
			for open (searchable) files,
			and/or unsaved files.		*/


	//header
	system("clear");

	//display comds
	cout << cmds_toString();

	cout << border('?', screen_width, " search ", 2) << endl << endl;


		/*
			edit:	should have a ui function that displays
					relevant doc info.						*/

	//TMP should be message
	if(qe->get_unsavedFlag()){
		cout << "\n\t\t\tUNSAVED DOCUMENT\n";
	}
	//should display document information
	cout << display_cur_doc() << endl;

	//start
	string ui = prompt("\n[query]: ");

	//check if ui is a cmd
	if(!run_cmd(ui)){
		//search
		//if results found
		if(qe->search(ui))
			cout << "call infoScreen";//infoScreen();
		else
			searchScreen();
	}

	//string query = prompt("[?query?]: ");
		//***still working***
		//*will jump into in*
		//*-foScreen() if su*
		//*-sessful.        *
		//*******************

	/*
		edit: "s" should only be visible when
				possible.
													*/

	//if s
	//qe->save_NewDoc();			//error return

	//drops through to info screen if success
	//infoScreen();
}

void UserInterface::configScreen(){
			//NewDoc Screen CMDS
	vector<cmd> newDocScreen_cmds;
	newDocScreen_cmds.push_back(home);
	newDocScreen_cmds.push_back(config);
	newDocScreen_cmds.push_back(newDoc);
	newDocScreen_cmds.push_back(quit);

	set_cmds(newDocScreen_cmds);

	//start
	system("clear");

	cout << border('%', screen_width, " configuration ", 2) << endl << endl;

	cout << dataBase_toString() << endl;

	cout << cmds_toString();


	//start
	string ui = prompt("\n[# to delete]: ");

	//check if ui is a number
	if(is_int(ui)){
		int selection = atoi( ui.c_str() );
		database_packet database = qe->get_dataBase();

		//check if there is a corresponding doc
		if(selection <= database.size()){
				qe->remove_doc(selection - 1);		//error return
				configScreen();
		}
	}
	else{
		run_cmd(ui);
	}

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
	system("clear");
}

void UserInterface::infoScreen(){
	//Info Screen CMDS
	vector<cmd> infoScreen_cmds;
	infoScreen_cmds.push_back(home);
	infoScreen_cmds.push_back(newDoc);
	infoScreen_cmds.push_back(back);
	infoScreen_cmds.push_back(quit);

	set_cmds(infoScreen_cmds);

	//start
	system("clear");

	cout << border('V', screen_width, " search results ", 2) << endl << endl;

	cout << results_toString();
/*
	string ui = prompt("\n[#]: ");

	//check if ui is a number
	if(is_int(ui)){
		int selection = atoi( ui.c_str() );
		cout << "\nOPEN.";
	}
	else{
		run_cmd(ui);
	}
*/
}
void UserInterface::pageScreen(){}





//--------------------------
//		command handling
//			--------------------------

void UserInterface::set_cmds(vector<cmd> cmds){
	cur_cmds.clear();
	for(int i=0; i< cmds.size(); i++){
		cur_cmds.push_back(cmds[i]);
	}

	if(qe->get_unsavedFlag())
		cur_cmds.push_back(save);
}


bool UserInterface::run_cmd(string cmd){
	bool is_cmd = false;

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
		//save
		if(cmd.compare(save.trigger) == 0){
			qe->save_newDoc();

			//tmp
			homeScreen();
		}
		//back
		if(cmd.compare(back.trigger) == 0){
			//will return to previous 
			//screen
			//tmp
			cout << "\nback";
			
		}
		is_cmd = true;
	}

	return is_cmd;
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

string UserInterface::results_toString(){

	/*
		edit: need a way to keep
		track of the page your on and 
		the result count so far.

										*/
	string s;
	vector<word_packet> word_packet_results = qe->get_wp_results();
	vector<info_packet> paginated_results = qe->get_ip_results();
/*
	if(word_packet_results.size() > 0){
		int page_max = 5;

		s += "\nSearch terms: ";

		for(int i=0; i< word_packet_results.size();i++){
			s += " ";
			s += word_packet_results[i].word;
		}

		s += "\n\n";

		for(int i=0; i< page_max; i++){
			s += border('-', screen_width/2, FormatText::to_string(i + 1));
			s += "\n[";
			s += FormatText::to_string(i + 1);
			s += "]";
			s += /paginated_results[i].toString();
			s += border('-', screen_width/2, FormatText::to_string(i + 1));
			s += "\n";
		}
	}
	else
		s += "\nNO RESULTS FOUND.\n";
*/

	return s;
}

string UserInterface::dataBase_toString(){
	string s;
	database_packet dataBase;
	vector<string> saved_docs;

	dataBase = qe->get_dataBase();

	if(dataBase.size() > 0){
		for(int i = 0 ; i < dataBase.indexed_docs.size(); i++){
			string display_title;

			//if open
			if(dataBase.indexed_docs[i].openFlag){
				doc_packet dp = dataBase.get_open();
				display_title += ">>";
			}

			display_title += dataBase.indexed_docs[i].title;

			//if unsaved
			if(!dataBase.indexed_docs[i].savedFlag)
				display_title += " (unsaved)";
	
			saved_docs.push_back(display_title);
		}

		s = options_box(saved_docs, " Database ", screen_width, 1 );
	}
	else
		s = "No Documents";

	return s;
}

//display current doc
string UserInterface::display_cur_doc(){
	string s;
	database_packet dataBase = qe->get_dataBase();

	//doc information
	if(dataBase.doc_is_open()){
		doc_packet dp = dataBase.get_open();
		s += "DOCUMENT TITLE: ";
		s += dp.title;
	}
	else{
		s += "NO OPEN DOCUMENTS";
	}

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
