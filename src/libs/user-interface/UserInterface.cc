#include <sstream>
#include <cstdlib>
#include "UserInterface.h"

#include "data-packets/Data_Packets.h"
#include "formatting/FormatText.h"

using namespace std;

				/*
					edit:	need diffrent types of messages
																*/

//--------------------------
//		screens
//			--------------------------
void UserInterface::init(){
	qe->load_dataBase();
	homeScreen();
}

//launches the next screen
void UserInterface::back_screen(){

	//if not more in history vector, set tto home
	//set last element of history vector to current screen
	//pop_back history vector

	if(history.size() <= 1)
		homeScreen();

	//otherwise set last screen to current screen, and remove from history
	history.pop_back();
	cur_screen = history[history.size() - 1];
	history.pop_back();


	if(cur_screen == HOME)
		homeScreen();
	else if(cur_screen == SEARCH)
		searchScreen();
	else if(cur_screen == NEWDOC)
		newDocScreen();
	else if(cur_screen == CONFIG)
		configScreen();
	else if(cur_screen == QUIT)
		quitScreen();
	else if(cur_screen == INFO)
		infoScreen();
	/*
	if(cur_screen == PAGE)
		pageScreen();
	*/
}

void UserInterface::homeScreen(){

	//naviation init home screen clears history
	cur_screen = HOME;
	history.clear();
	history.push_back(cur_screen);

	//Home Screen CMDS
	vector<cmd> homeScreen_cmds;
	homeScreen_cmds.push_back(newDoc);
	homeScreen_cmds.push_back(config);
	homeScreen_cmds.push_back(quit);
	homeScreen_cmds.push_back(display);

	set_cmds(homeScreen_cmds);

	/*
		edit:	screens may require a check
			for open (searchable) files,
			and/or unsaved files.		*/

	string message = "Enter a number to load a saved document.";

	if(hidden)
		message = "Enter a number to load a saved document, or hit 'd' for more options.";


	header(" HOME ", message, "make an art function");

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

	homeScreen();
}

void UserInterface::newDocScreen(){

		//naviation init
	cur_screen = NEWDOC;
	if(cur_screen != history[history.size()-1])
		history.push_back(cur_screen);

		//NewDoc Screen CMDS
	vector<cmd> newDocScreen_cmds;
	newDocScreen_cmds.push_back(home);
	newDocScreen_cmds.push_back(config);
	newDocScreen_cmds.push_back(back);
	newDocScreen_cmds.push_back(quit);
	newDocScreen_cmds.push_back(display);

	set_cmds(newDocScreen_cmds);

	//start
	header(" NEW doc ", "Open a new document?", "make an art function");

	string ui = prompt("\n[path]: ");

	//check if ui is a cmd
	if(!run_cmd(ui)){
		//search

		//TMP
		cout << "opening " << ui << endl;
		qe->add_newDoc(ui);
	}else{
		newDocScreen();
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

	//warning top
		//TMP should be message
	if(qe->get_unsavedFlag())
		cout << "UNSAVED DOCUMENT";

	if(!results_found)
		cout << "\tNOT FOUND";

	results_found = true;

		//naviation init
	cur_screen = SEARCH;
	if(cur_screen != history[history.size()-1])
		history.push_back(cur_screen);

		//Search Screen CMDS
	vector<cmd> searchScreen_cmds;
	searchScreen_cmds.push_back(home);
	searchScreen_cmds.push_back(config);
	searchScreen_cmds.push_back(back);
	searchScreen_cmds.push_back(quit);
	searchScreen_cmds.push_back(display);

	set_cmds(searchScreen_cmds);

	//reset cur_page
	cur_page = 0;

	/*
		edit:	screens may require a check
			for open (searchable) files,
			and/or unsaved files.		*/


	header(" SEARCH ", "Type a word or phrase to search open document.", display_glasses(1));

		/*
			edit:	should have a ui function that displays
					relevant doc info.						*/

	//should display document information
	cout << display_cur_doc(2) << endl;

	//start
	string ui = prompt("\n[query]: ");

	//check if ui is a cmd
	if(!run_cmd(ui)){
		//if results found
		if(qe->search(ui)){
			infoScreen();
			results_found = true;
		}
		else
			results_found = false;
	}
	searchScreen();

	//if s
	//qe->save_NewDoc();			//error return

	//drops through to info screen if success
	//infoScreen();
}

void UserInterface::configScreen(){

			//naviation init
	cur_screen = CONFIG;
	if(cur_screen != history[history.size()-1])
		history.push_back(cur_screen);

			//NewDoc Screen CMDS
	vector<cmd> configScreen_cmds;
	configScreen_cmds.push_back(home);
	configScreen_cmds.push_back(config);
	configScreen_cmds.push_back(newDoc);
	configScreen_cmds.push_back(back);
	configScreen_cmds.push_back(toggle);
	configScreen_cmds.push_back(quit);
	configScreen_cmds.push_back(display);

	set_cmds(configScreen_cmds);

	header(" Configure ", "Remove a document from database?", "make an art function");

	cout << dataBase_toString() << endl;

	//datastruct type
	database_packet database;
	database = qe->get_dataBase();

	int type = database.get_dataStruct_type();
	string string_type;

	string_type += border(' ', screen_width/2 - screen_width/10);
	string_type += "Datastructure type: ";

	if(type == DataStuct_Types::AVL)
		string_type += "AVL";
	else
		string_type += "HASH";

	cout << string_type << endl;


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

	configScreen();
}

void UserInterface::quitScreen(){
	//checks if unsaved doc
	//if unsaved gives warning
	//if you choose not to quit
	//after warning, brings you
	//back to screen q was pressed
	system("clear");
	exit(1);
}

void UserInterface::infoScreen(){
	//naviation init
	cur_screen = INFO;
	if(cur_screen != history[history.size()-1])
		history.push_back(cur_screen);

	//reset char_count
	char_count = 0;
	char_count_history.clear();

	vector<info_packet> paginated_results = qe->get_ip_results();

	//Info Screen CMDS
	vector<cmd> infoScreen_cmds;
	infoScreen_cmds.push_back(home);
	infoScreen_cmds.push_back(config);
	infoScreen_cmds.push_back(newDoc);
	infoScreen_cmds.push_back(display);
	infoScreen_cmds.push_back(next);
	infoScreen_cmds.push_back(previous);
	infoScreen_cmds.push_back(back);
	infoScreen_cmds.push_back(quit);

	set_cmds(infoScreen_cmds);

	//start
	system("clear");

	header(" Search Results ", " Enter # to view full page. ", "make an art function");

	//cout << results_toString();
	string s;
	string info;

	if(paginated_results.size() > 0){

		//calculate info
		for(int i=0; i< page_max; i++){
			if(i + (cur_page * page_max) < paginated_results.size()){

				//display
				info += border(' ', 15, 0);
				info += border('-', (screen_width - screen_width/6) , FormatText::to_string((page_max*cur_page) +i  + 1));

				info += "\n[";
				info += FormatText::to_string(i + 1);
				info += "]";
				info += paginated_results[i + (cur_page * page_max)].toString();

				info += border(' ', 15);
				info += border('-', (screen_width - screen_width/6), FormatText::to_string((page_max*cur_page) +i  + 1));
				info += "\n";

				if(i + (cur_page * page_max) +1 >= paginated_results.size())
					last_page = true;
				else
					last_page = false;
			}
		}
	}
	else
		info += "\nNO RESULTS FOUND.\n";

	//create s
	s += "\n";
	//s += border(' ', screen_width/2 - );
	s += "PAGE ";

	s += FormatText::to_string(cur_page + 1);
	s += "/";
	s += FormatText::to_string( (paginated_results.size()/page_max) + (paginated_results.size()%page_max) );
	s += "\nSEARCH RESULTS: ";
	s += FormatText::to_string(paginated_results.size());
	s += "\n";

	//append info to s
	s += info;
	cout << s;

	string ui = prompt("\n[#]: ");

	//check if ui is a number
	if(is_int(ui)){
		page_selection = atoi( ui.c_str() );

		if(page_selection <= page_max)
			pageScreen((cur_page * page_max) + page_selection -1, change_page_page);
		else
			cout << "out of range.";
	}
	else{
		run_cmd(ui);
	}

	infoScreen();

}
void UserInterface::pageScreen(int selection, bool change_page){
	//naviation init for PAGE does not add to history// just for special back function
	cur_screen = PAGE;

	vector<info_packet> paginated_results = qe->get_ip_results();

	//Info Screen CMDS
	vector<cmd> infoScreen_cmds;
	infoScreen_cmds.push_back(home);
	infoScreen_cmds.push_back(config);
	infoScreen_cmds.push_back(newDoc);
	infoScreen_cmds.push_back(display);
	infoScreen_cmds.push_back(next);								//should be command specific to page
	infoScreen_cmds.push_back(previous);							//should be command specific to current page
	infoScreen_cmds.push_back(back);
	infoScreen_cmds.push_back(quit);

	set_cmds(infoScreen_cmds);

	//start
	system("clear");

	string title = "\"";
	title += paginated_results[selection].title;
	title += "\"";

	header( title, " ", "make an art function");
	cout <<  paginated_results[selection].page_toString(char_count, last_page_page, first_page_page, change_page_page);					//should be page version to string	
	change_page_page = false;

	string ui = prompt("\n[?]: ");
	run_cmd(ui);

	pageScreen(page_selection, change_page_page);
}





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

	//make sure it is in current cmd list...						//should be run for individual commands for multiple functions to a key
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
			homeScreen();							//change shouldnt close upon saving
		}
		//toggle
		if(cmd.compare(toggle.trigger) == 0)
			qe->toggle_type();
		//display
		if(cmd.compare(display.trigger) == 0){
			if(hidden)
				hidden = false;
			else
				hidden = true;
		}
		//next
		if(cmd.compare(next.trigger) == 0){
			if(cur_screen == INFO){
				if(!last_page)
					cur_page++;
				
				infoScreen();
			}
			if(cur_screen == PAGE){
				if(!last_page_page){
					change_page_page = true;																									//issue
					char_count_history.push_back(char_count);
					pageScreen(page_selection, change_page_page);
				}
				else
					pageScreen(page_selection, change_page_page);
			}

		}
		//previous
		if(cmd.compare(previous.trigger) == 0){
			if(cur_screen == INFO){
				if(cur_page <= 0){
					searchScreen();
				}
				else{
					cur_page--;
					infoScreen();
				}
			}
			if(cur_screen == PAGE){

				if( (!first_page_page) && (char_count_history.size() > 0)){
					change_page_page = true;
					char_count_history.pop_back();
					char_count = char_count_history[char_count_history.size()-1];
					char_count_history.pop_back();
					pageScreen(page_selection, change_page_page);
				}
				else
					infoScreen();
			}
		}
		//back
		if(cmd.compare(back.trigger) == 0){
			if(cur_screen == PAGE)
				infoScreen();
			else
				back_screen();
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
	//command_box = border('_', screen_width, 2);
	command_box += "\n\n";
	command_box += "CMDS:\t";

	for(int i=0; i<cur_cmds.size(); i++){
		command_box += cur_cmds[i].display_name;
		command_box += "\t";
	}

	//command_box += border('_', screen_width, 2);

	return  command_box;
}

string UserInterface::results_toString(){

	/*
		edit: need a way to keep
		track of the page your on and 
		the result count so far.

										*/
	string s;
	//vector<word_packet> word_packet_results = qe->get_wp_results();
	vector<info_packet> paginated_results = qe->get_ip_results();

	if(paginated_results.size() > 0){
		int page_max = 5;

		s += "\n\n";

		for(int i=0; i< page_max; i++){
			if(i < paginated_results.size()){
				/*
				//calculate info
				for(int i=0; i< word_packet_results.size();i++){
					if(paginated_results[i].id == word_packet_results[i].id){
						s += word_packet_results[i].word;
						s += ", gtf:";
						s += word_packet_results[i].globaltf;
						s += ", tf:";
						s += word_packet_results[i].tf;
						s += "\n";
					}
				}
				*/
				//display
				s += border(' ', 10);
				s += border('-', (screen_width - screen_width/4) , FormatText::to_string(i + 1));

				s += "\n[";
				s += FormatText::to_string(i + 1);
				s += "]";
				s += paginated_results[i].toString();

				s += border(' ', 10);
				s += border('-', screen_width/2, FormatText::to_string(i + 1));
				s += "\n";
			}
		}
	}
	else
		s += "\nNO RESULTS FOUND.\n";

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
string UserInterface::display_cur_doc(int orientation){

	//should be right oriented
	int indent = 5;
	int max = 15;

	string s;
	database_packet dataBase = qe->get_dataBase();

	//doc information
	if(dataBase.doc_is_open()){
		doc_packet dp = dataBase.get_open();

			//calculate indent
			//max
			if(dp.fullDoc_path.size() > max)
				max = dp.fullDoc_path.size();

			//center
			if(orientation == 1)
				indent = screen_width/2 - max/2;
			//right
			if(orientation == 2)
				indent = screen_width - max - indent;

		s += border(' ', indent);
		s += border('-', max);
		s += "\n";
		s += border(' ', indent);
		s += "DOCUMENT TITLE: ";
		s += dp.title;
		s += "\n";
		s += border(' ', indent);
		s += "file size: ";
		s += FormatText::to_string( filesize(dp.fullDoc_path.c_str()) );
		s += " bytes";
		s += border(' ', indent, 0);
		s += border('-', max);

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

void UserInterface::header(string title, string message, string art){
	system("clear");

	cout << border('_', screen_width, 2);
	cout << border(' ', screen_width, title, 0);
	if(!hidden)
		cout << cmds_toString();

		//will be fucntion
	//cout << endl << art << endl;

	cout << message_toString(message) << endl;
}

string UserInterface::message_toString(string message){
	string s;
	int message_width = 25;
	int offset = 5;
	
	vector<string> broken = FormatText::break_apart(message);

	s += "\n\n";

	int i = 0;
	while( i < broken.size() ){

		int indent = screen_width/2 - message_width/2 - offset;
		int total = 0;

		//tab
		if(i == 0){
			indent = screen_width/2 - message_width/2;
			total = 5;
		}

		//new line
		s += "\n";
		s += border(' ', indent);

		while(total < message_width){

			s += broken[i];
			s += " ";

			total += broken[i].size();
			i++;

			if(!(i < broken.size()))
				total = message_width;
		}
	}

	s += "\n";

	return s;
}

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

string UserInterface::display_glasses(int orientation){
	string s;
	int max = 0;
	int indent = 5;

	vector<string> segments;
	//string s0 =   "          _,--,            _ ";
	//string s1 =   "    ___,-'    |____      /' | ";
	//string s2 = "   /     \\,--,/     \\  /'   | "; 
	//string s3 =  "  |       )  (       |' ";
	//string s4 = "   \\_____/    \\_____/";

	string s0 = " _________                            .__      ";
	string s1 = "/   _____/ ____ _____ _______    ____ |  |__   ";
	string s2 = "\\_____ \\_/ __ \\\\_\\ _  __\\_/ __\\|  |  \\ ";
	string s3 = " /       \\  ___/ / __\\|  | \\/\\ \\__|   Y  \\";
	string s4 = "/_______  /\\__  >____  /__|    \\___  >___|  / ";
	string s5 = "       \\/    \\/    \\/           \\/    \\/  ";

	segments.push_back(s0);
	segments.push_back(s1);
	segments.push_back(s2);
	segments.push_back(s3);
	segments.push_back(s4);

	//get max string length;
	for(int i=0; i < segments.size(); i++){
		if (segments[i].size() > max)
			max = segments[i].size();
	}


	//set indent
	//middle
	if(orientation == 1)
		indent = screen_width/2 - max/2;
	if(orientation == 2)
		indent = screen_width - max - indent;

	//to string
	for(int i =0; i < segments.size(); i++){
		s += "\n";
		s += border(' ', indent);
		s += segments[i];
	}

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

//calculate file size
std::ifstream::pos_type UserInterface::filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}