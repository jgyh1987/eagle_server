#ifndef JSONDLL_JSON_WRITER_H_INCLUDE
#define JSONDLL_JSON_WRITER_H_INCLUDE
# include "json_value.h"
# include <vector>
# include <string>
# include <iostream>

namespace Json
{
	
	class Value;

	class Writer
	{
	public:
		Writer();
		virtual ~Writer();
		std::string write( const Value &root );

	private:
		void writeValue( const Value &value );
		void writeArrayValue( const Value &value );
		void writeObjectValue( const Value &value );
		void pushValue( const std::string &value );
		void writeIndent();
		void writeWithIndent( const std::string &value );
		void indent();
		void unindent();
		typedef std::vector<std::string> ChildValues;

		ChildValues childValues_;
		std::string document_;
		std::string indentString_;
		int indentSize_;
		bool addChildValues_;
	};

	std::string valueToString( int value );
	std::string valueToString( unsigned int value );
	std::string valueToString( double value );
	std::string valueToString( bool value );
	std::string valueToQuotedString( const char *value );




}	// namespace Json






#endif	//JSONDLL_JSON_WRITER_H_INCLUDE
