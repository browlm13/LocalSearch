#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>
#include <vector>
#include <fstream>

#include "query-engine/QueryEngine.h"

class UserInterface {
	QueryEngine *qe;

	//dimensions
	int screen_width;


	enum Screens{

			HOME,
			NEWDOC,
			SEARCH,
			CONFIG,
			QUIT,
			INFO,
			PAGE
	};

	//cmd handling
	struct cmd{
		std::string display_name;
		std::string trigger;

		void set(std::string display_name_arg, std::string trigger_arg){
			display_name = display_name_arg;
			trigger = trigger_arg;
		}

	} quit, home, config, newDoc, back, save, display, next, previous, toggle;
	std::vector<cmd> cur_cmds;

public:
	UserInterface(QueryEngine qe) : qe(&qe)	{

		//get screen dimensions
		screen_width = 120;

		//info info
		page_max = 3;
		cur_page = 0;

		//page info
		char_count = 0;
		last_page_page = false;
		first_page_page = true;
		change_page_page = false;

		//info setup
		results_found = true;

		//init
		hidden = true;

		quit.set("(q)uit", "q");
		home.set("(h)ome", "h");
		config.set("(c)onfig", "c");
		newDoc.set("(n)ewDoc", "n");
		back.set("(b)ack", "b");
		save.set("(s)ave", "s");
		display.set("(d)isplay", "d");
		next.set("(j) next page", "j");
		previous.set("(k) previous page", "k");
		toggle.set("(t)oggle datastructure type", "t");

	}

	void init();

	/*
		edit: enum of screen value, each
		should return a number speccific to theres.
													*/

	//navigation
	void back_screen();

	//screens
	void homeScreen();
	void searchScreen();
	void newDocScreen();
	void configScreen();
	void quitScreen();
	void infoScreen();
	void pageScreen(int selection, bool change_page);

	//display
	std::string results_toString();
	std::string dataBase_toString();		//calls query engine function
	std::string cmds_toString();
	std::string display_cur_doc(int orientation);
	std::string message_toString(std::string message);
	//art
	std::string display_glasses(int orientation);

	//navigation
	//cur_screen
	int cur_screen;
	//history vector
	vector<int> history;

	//page/info naviagation
	int cur_page;
	int page_max;
	bool last_page;
	int char_count;
	vector<int> char_count_history;
	bool last_page_page;
	bool first_page_page;
	bool change_page_page;

	int page_selection;

	//info tmp
	bool results_found;


	//flags
	bool hidden;

	//cmd handling
	void set_cmds(std::vector<cmd> cmds);
	bool run_cmd(std::string cmd);

	//user input helpers
	bool is_int(std::string in_question);
	std::ifstream::pos_type filesize(const char* filename);


	//TMP (some display functions to be contained in FormatText namespace)
	void header(string title, string message, string art);
	std::string prompt(string prompt);

	std::string options_box(vector<string> options, std::string title);
	std::string options_box(vector<string> options, std::string title, int screen_width, int orientation);

	std::string border(char c, int length);
	std::string border(char c, int length, int newline);
	std::string border(char c, int length, std::string title);
	std::string border(char c, int length, std::string title, int newline);
};

#endif	//USERINTERFACE_H

			// ( screens )
	//homeScreen	//options: (q)uit, (c)onfig , (n)ew
		//[# of saved doc] 
	//searchScreen 	//options: (q)uit, (c)onfig, (h)ome, ( (s)ave )
		//[query]
	//infoScreen	//options: (q)uit, (h)ome, (b)ack, (j)scroll down, (k)scroll up
		//[# doc selection]
	//pageScreen	//options: (q)uit, (h)ome, (b)ack, (j)scroll down, (k)scroll up
	//configScreen	//options: (q)uit, (home)
		//[config cmds]
