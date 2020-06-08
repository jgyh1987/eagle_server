#include "json_writer.h"
#include "json_value.h"
#include <iostream>
#include <assert.h>
#include <utility>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

namespace Json
{

	Writer::Writer()
	:indentSize_( 3 )
	{
		addChildValues_ = false;
	}
	Writer::~Writer()
	{

	}
	std::string Writer::write( const Value &root )
	{
		document_ = "";
		addChildValues_ = false;
		indentString_ = "";
		writeValue( root );
		document_ += "\n";
		return document_;

	}

	void Writer::writeValue( const Value &value )
	{
		switch ( value.type() )
		{
		case nullValue:
			pushValue( "null" );
			break;
		case intValue:
			pushValue( valueToString( value.asInt() ) );
			break;
		case uintValue:
			pushValue( valueToString( value.asUInt() ) );
			break;
		case realValue:
			pushValue( valueToString( value.asDouble() ) );
			break;
		case stringValue:
			pushValue( valueToQuotedString( value.asCString() ) );
			break;
		case booleanValue:
			pushValue( valueToString( value.asBool() ) );
			break;
		case objectValue:
			if ( value.isArray() )
				writeArrayValue( value );
			else
				writeObjectValue( value );
			break;
		}
	}

	void Writer::writeObjectValue( const Value &value )
	{
		Value::Members members( value.getMemberNames() );
		if ( members.empty() )
			pushValue( "{}" );
		else
		{
			writeWithIndent( "{" );
			indent();
			Value::Members::iterator it = members.begin();
			while ( true )
			{
				const std::string &name = *it;
				const Value &childValue = value[name];
				writeWithIndent( valueToQuotedString( name.c_str() ) );
				document_ += " : ";
				writeValue( childValue );
				if ( ++it == members.end() )
				{
					break;
				}
				document_ += ",";
			}
			unindent();
			writeWithIndent( "}" );
		}
	}

	void Writer::writeArrayValue( const Value &value )
	{
		unsigned size = value.size();
		if ( size == 0 )
			pushValue( "[]" );
		else
		{
			if ( true )
			{
				writeWithIndent( "[" );
				indent();
				bool hasChildValue = !childValues_.empty();
				unsigned index =0;
				while ( true )
				{
					const Value &childValue = value[index];
					if ( hasChildValue )
						writeWithIndent( childValues_[index] );
					else
					{
						writeIndent();
						writeValue( childValue );
					}
					if ( ++index == size )
					{
						break;
					}
					document_ += ",";
				}
				unindent();
				writeWithIndent( "]" );
			}
			else // output on a single line
			{
				assert( childValues_.size() == size );
				document_ += "[ ";
				for ( unsigned index =0; index < size; ++index )
				{
					if ( index > 0 )
						document_ += ", ";
					document_ += childValues_[index];
				}
				document_ += " ]";
			}
		}
	}
	void Writer::pushValue( const std::string &value )
	{
		if ( addChildValues_ )
			childValues_.push_back( value );
		else
			document_ += value;
	}

	void Writer::writeIndent()
	{
		if ( !document_.empty() )
		{
			char last = document_[document_.length()-1];
			if ( last == ' ' )     // already indented
				return;
			if ( last != '\n' )    // Comments may add new-line
				document_ += '\n';
		}
		document_ += indentString_;
	}

	void Writer::writeWithIndent( const std::string &value )
	{
		writeIndent();
		document_ += value;
	}


	void Writer::indent()
	{
		indentString_ += std::string( indentSize_, ' ' );
	}


	void Writer::unindent()
	{
		assert( int(indentString_.size()) >= indentSize_ );
		indentString_.resize( indentString_.size() - indentSize_ );
	}
	static bool isControlCharacter(char ch)
	{
		return ch > 0 && ch <= 0x1F;
	}

	static bool containsControlCharacter( const char* str )
	{
		while ( *str ) 
		{
			if ( isControlCharacter( *(str++) ) )
				return true;
		}
		return false;
	}
	static void uintToString( unsigned int value, 
		char *&current )
	{
		*--current = 0;
		do
		{
			*--current = (value % 10) + '0';
			value /= 10;
		}
		while ( value != 0 );
	}
	std::string valueToString( Int value )
	{
		char buffer[32];
		char *current = buffer + sizeof(buffer);
		bool isNegative = value < 0;
		if ( isNegative )
			value = -value;
		uintToString( UInt(value), current );
		if ( isNegative )
			*--current = '-';
		assert( current >= buffer );
		return current;
	}


	std::string valueToString( UInt value )
	{
		char buffer[32];
		char *current = buffer + sizeof(buffer);
		uintToString( value, current );
		assert( current >= buffer );
		return current;
	}

	std::string valueToString( double value )
	{
		char buffer[32];
#if defined(_MSC_VER) && defined(__STDC_SECURE_LIB__) // Use secure version with visual studio 2005 to avoid warning. 
		sprintf_s(buffer, sizeof(buffer), "%#.16g", value); 
#else	
		sprintf(buffer, "%#.16g", value); 
#endif
		char* ch = buffer + strlen(buffer) - 1;
		if (*ch != '0') return buffer; // nothing to truncate, so save time
		while(ch > buffer && *ch == '0'){
			--ch;
		}
		char* last_nonzero = ch;
		while(ch >= buffer){
			switch(*ch){
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				--ch;
				continue;
			case '.':
				// Truncate zeroes to save bytes in output, but keep one.
				*(last_nonzero+2) = '\0';
				return buffer;
			default:
				return buffer;
			}
		}
		return buffer;
	}


	std::string valueToString( bool value )
	{
		return value ? "true" : "false";
	}

	std::string valueToQuotedString( const char *value )
	{
		// Not sure how to handle unicode...
		if (strpbrk(value, "\"\\\b\f\n\r\t") == NULL && !containsControlCharacter( value ))
			return std::string("\"") + value + "\"";
		// We have to walk value and escape any special characters.
		// Appending to std::string is not efficient, but this should be rare.
		// (Note: forward slashes are *not* rare, but I am not escaping them.)
		unsigned maxsize = strlen(value)*2 + 3; // allescaped+quotes+NULL
		std::string result;
		result.reserve(maxsize); // to avoid lots of mallocs
		result += "\"";
		for (const char* c=value; *c != 0; ++c)
		{
			switch(*c)
			{
			case '\"':
				result += "\\\"";
				break;
			case '\\':
				result += "\\\\";
				break;
			case '\b':
				result += "\\b";
				break;
			case '\f':
				result += "\\f";
				break;
			case '\n':
				result += "\\n";
				break;
			case '\r':
				result += "\\r";
				break;
			case '\t':
				result += "\\t";
				break;
				//case '/':
				// Even though \/ is considered a legal escape in JSON, a bare
				// slash is also legal, so I see no reason to escape it.
				// (I hope I am not misunderstanding something.
				// blep notes: actually escaping \/ may be useful in javascript to avoid </ 
				// sequence.
				// Should add a flag to allow this compatibility mode and prevent this 
				// sequence from occurring.
			default:
				if ( isControlCharacter( *c ) )
				{
// 					std::ostringstream oss;
// 					oss << "\\u" << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << static_cast<int>(*c);
// 					result += oss.str();
				}
				else
				{
					result += *c;
				}
				break;
			}
		}
		result += "\"";
		return result;
	}

































}
