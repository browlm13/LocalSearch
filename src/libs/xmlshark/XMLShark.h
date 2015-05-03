#ifndef XMLSHARK_H
#define XMLSHARK_H

#include <string>
#include <vector>
#include <fstream>

//using namespace std;
using std::string;
using std::vector;
using std::fstream;


	 /*
			edit:	Needs to return a vector
					of formatted strings for
					for this project. Should
					be a bool option.
												*/

	 /*
			edit:	You should be able
					to feed it a folder, 
					not just single file.
												*/
	/*
			edit:	stop words hash
					should be contained
					in formattext namespace
												*/

class XMLShark {
protected:
	fstream file;
	string path_name;

	//collection of raw characters
	string characters;
	bool collect_characters;

	//collection of formatted strings
	//vector<string> formatted_strings;
	string str;
	vector<string> fm_strs;
	bool collect_formatted_strings;

	//-----------------
	//NON USER FUNCTIONS
	//------------------

	void _parse(string path, long location);

	//collection of raw characters
	void set_characters(string new_characters);

	//collection of formatted strings
	void set_formatted_strings(vector<string> new_formatted_strings);

	//test inline
	void inline format_push_clear(vector<string> &v, string &s);

	//--------------
	//USER FUNCTIONS
	//-------------

		//( Files )
	void open_file(string file_name);
	void open_empty_file(string file_path);
	void close_file();
	string get_path()	{	return path_name;	}

		//( Text Between <Tags> )
	//collection of raw characters
	void set_collect_characters(bool state);
	string get_characters();

	//collection of formatted strings
	void set_collect_formatted_strings(bool state);
	vector<string> get_formatted_strings();

		//( Byte Location )
	long get_location();
	void set_location(long location);

//==============================================
//		 VIRTUAL
//==============================================

		//Events
	virtual void startDoc_event() = 0;
	virtual void endDoc_event() = 0;
	virtual void startTag_event(string &tag_name) = 0;
	virtual void endTag_event(string &tag_name) = 0;

	
public:
		//private caller
	//virtual void parse(string path);

//==============================================
//		 VIRTUAL
//==============================================

	XMLShark()	{};										//TMP***
	~XMLShark(){};

};

#endif //XMLSHAR_H
