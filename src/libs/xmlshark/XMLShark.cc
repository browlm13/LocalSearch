#include <cstdlib>
#include <iostream>
#include "XMLShark.h"

#include "formatting/FormatText.h"

//TMP***
#include "formatting/StopWords_Hash.h"
#include "porter2-stemmer/porter2_stemmer.h"

using namespace std;

//-------------------------
//	text between tags	
//	------------------------------

//string get characters can be called at end tag event
string XMLShark::get_characters()
	{return characters;}

//bool set collect characters to be called at start tag event
void XMLShark::set_collect_characters(bool state)
	{collect_characters = state;}

//vector get strings can be called at end tag event
vector<string> XMLShark::get_formatted_strings()
	{return fm_strs;}//{return formatted_strings;}

//bool set collect strings to be called at start tag event
void XMLShark::set_collect_formatted_strings(bool state)
	{collect_formatted_strings = state;}

//-------------------------
//	byte location	
//	------------------------------

//can be called at any event
long XMLShark::get_location(){
	long l = file.tellg();
	return l;
}

//can be called by any event
void XMLShark::set_location(long location)
{file.seekg(location);}

//-------------------------
//	open close files	
//	------------------------------

void XMLShark::open_file(string path){
	file.open(path.c_str());
	if(file.fail()){
		cout << "error opening" << path << endl;
		exit(1);
	}
}

void XMLShark::open_empty_file(string path){
	file.open(path.c_str(), std::ofstream::out | std::ofstream::trunc);
	if(file.fail()){
		cout << "error opening" << path << endl;
		exit(1);
	}
}

void XMLShark::close_file()
{file.close();}

//-------------------------
//		_parse
//	------------------------------
void XMLShark::_parse(string path, long location){

	/*
		edit:	handle blank documents
				and first line.
										*/
	/*
		edit:	stop words hash
				should be contained
				in formattext namespace
											*/

		//TMP***
	StopWords_Hash swh;

	//save path
	path_name = path;
	
	//make sure files are closed, then open new file
	close_file();
	open_file(path);

	//starting byte location
	set_location(location);

	//call start doc event virtual function
	if(get_location() == 0)
		{startDoc_event();}

	char c;

	//run program loop
	while(!file.eof() && file.is_open()){

		c = file.get();

		if( c != '<'){//not tag
			if(collect_formatted_strings){
				str.clear();
				fm_strs.clear();

				while(c != '<'){
					
					//if upper case convert to lower case
					if ( c > 64 && c < 91 )
						c += 32;

					/*
					//if ( c is a digit, or a letter )
					if( (c > 47 && c < 58) || (c > 96 && c < 123) )
						str += c;
					*/
					//if ( c is a letter )
					if( (c > 96 && c < 123) )
						str += c;

					//ELSE ( c is not a digit or a leter ) && ( str size is > 0)
					else if ( str.size() > 0 ){
						format_push_clear(fm_strs, str);

						//TMP
							//bool stop_word = false;

							//lower case
							//FormatText::lower_case(str);

							//remove stop word
							//stop_word = swh.is_stop_word(str);

							//stem
							//Porter2Stemmer::stem(str);

							//add if not a stop word
							//if(!stop_word){
								//fm_strs.push_back(str);
								//str.clear();
							//}
						//TMP
					}

					c = file.get();
				}

				//laggers not pretty
				if ( str.size() > 0 ){
						//format_push_clear(fm_strs, str);
						fm_strs.push_back(str);
						str.clear();
					}

				collect_formatted_strings = false;
			}

			if(collect_characters){
				characters.clear();
				while(c != '<'){
					characters += c;
					c = file.get();
				}

				collect_characters = false;
			}
		}

		//cannot be else for transition
		if( c == '<'){//tag

			c = file.get();

			if( c != '/' ){//start tag

				string startTag;

				while(c != '>'){
					
					if(c != ' '){
						startTag += c;
						c = file.get();
					}
					else{
						while(c != '>')
							{c = file.get();}
					}
					
				}
				startTag_event(startTag);	//pass by refrence
			}//end start tag

			else{//end tag

				string endTag;
				c = file.get();

				while(c != '>'){
					endTag += c;
					c = file.get();
				}
				endTag_event(endTag);	//pass by refrence
			}//end end  tag

		}//end if('<')

	}//end file while

	//call enddoc event virtual function
	endDoc_event();

	set_collect_characters(false);
	set_collect_formatted_strings(false);

	//close file
	file.close();
}

//inline function to format push and clear current string
void XMLShark::format_push_clear(vector<string> &v, string &s){
/*
	/*
		edit: should call
		formattext
						*/

	FormatText::lower_case(s);
	Porter2Stemmer::stem(s);
	v.push_back(s);
	s.clear();
/*
	bool stop_word = false;

	//lower case
	FormatText::lower_case(s);

	//remove stop word
	stop_word = swh.is_stop_word(s);

	//stem
	Porter2Stemmer::stem(s);

	//add if not a stop word
	if(!stop_word){
		v.push_back(s);
		s.clear();
	}
*/
					//	FORMAT STRING:
					//(stem, remove stop word) (FormatTest::)
					//	ADD STRING:
					//fm_strs.push_back(str);
					//	RESET
					//str.clear();
}

//set current character string
void XMLShark::set_characters(string new_characters)
{characters = new_characters;}

//set current formatted strings vector
void XMLShark::set_formatted_strings(vector<string> new_formatted_strings)
//{formatted_strings = new_formatted_strings;}
{}


/*
	post edit:	Should be inline functions.
												*/