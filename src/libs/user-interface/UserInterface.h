#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>
#include <vector>

#include "query-engine/QueryEngine.h"

class UserInterface {
	QueryEngine *qe;

	//dimensions
	int screen_width;

	//cmd handling
	struct cmd{
		std::string display_name;
		std::string trigger;

		void set(std::string display_name_arg, std::string trigger_arg){
			display_name = display_name_arg;
			trigger = trigger_arg;
		}

	} quit, home, config, newDoc, save;
	std::vector<cmd> cur_cmds;

public:
	UserInterface(QueryEngine qe) : qe(&qe)	{

		screen_width = 120;

		quit.set("(q)uit", "q");
		home.set("(h)ome", "h");
		config.set("(c)onfig", "c");
		newDoc.set("(n)ewDoc", "n");
		save.set("(s)ave", "s");

	}

	void homeScreen();
	void searchScreen();
	void newDocScreen();
	void configScreen();
	void quitScreen();
	void infoScreen();
	void pageScreen();

	std::string dataBase_toString();		//calls query engine function
	std::string cmds_toString();

	//cmd handling
	void set_cmds(std::vector<cmd> cmds);
	void run_cmd(std::string cmd);

	//user input helpers
	bool is_int(std::string in_question);


	//TMP (display functions to be contained in FormatText namespace)
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
