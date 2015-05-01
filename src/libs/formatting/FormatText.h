#ifndef FORMATTEXT_H
#define	FORMATTEXT_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using std::string;
using std::vector;

		/*
			Description:	Static Functions for all types
							of generic text formatting.
																*/

//---------------------------------------------------------------------------------------------------//
/*
*		FormatText	(Prototypes)
*/
//---------------------------------------------------------------------------------------------------//

class FormatText {

public:
	//text formatting
	static string format_word( const string raw_word );
	static vector<string> format_query( const string raw_query );
	
	static string lower_case( const string raw_word );
	static string conv_case( const string &word, int arg );
	static vector<string> break_apart( const string raw_line );
	static void conv_operands(string &raw_word);
	static bool stop_word( const string unkown );

	/*
		edit: should be namespace
		and functions no class.

										*/

	template<class T>
	static string to_string( const T &numeric_value ){
		//poratble using sstream
		std::string string_number;
		std::stringstream strstream;
		strstream << numeric_value;
		strstream >> string_number;
		return string_number;
	}
};

#endif //FORMATTEXT_H