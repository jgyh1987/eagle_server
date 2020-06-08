#include <iostream>
#include "json_value.h"
#include "json_writer.h"
#include <utility>
#include <stdexcept>
#include <cstring>
#include <cassert>
#include <cstddef>    // size_t
#include <stdlib.h>


namespace Json 
{

const Value Value::null;
Value Value::nul;
const Int Value::minInt = Int( ~(UInt(-1)/2) );
const Int Value::maxInt = Int( UInt(-1)/2 );
const UInt Value::maxUInt = UInt(-1);

ValueAllocator::~ValueAllocator()
{
}

class DefaultValueAllocator : public ValueAllocator
{
public:
   virtual ~DefaultValueAllocator()
   {
   }

   virtual char *makeMemberName( const char *memberName )
   {
      return duplicateStringValue( memberName );
   }

   virtual void releaseMemberName( char *memberName )
   {
      releaseStringValue( memberName );
   }

   virtual char *duplicateStringValue( const char *value, 
                                       unsigned int length = unknown )
   {
      if ( length == unknown )
         length = (unsigned int)strlen(value);
      char *newString = static_cast<char *>( malloc( length + 1 ) );
      memcpy( newString, value, length );
      newString[length] = 0;
      return newString;
   }

   virtual void releaseStringValue( char *value )
   {
      if ( value )
         free( value );
   }
};

static ValueAllocator *&valueAllocator()
{
   static DefaultValueAllocator defaultAllocator;
   static ValueAllocator *valueAllocator = &defaultAllocator;
   return valueAllocator;
}

static struct DummyValueAllocatorInitializer {
   DummyValueAllocatorInitializer() 
   {
      valueAllocator();      // ensure valueAllocator() statics are initialized before main().
   }
} dummyValueAllocatorInitializer;

// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// class Value::CZString
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////

// Notes: index_ indicates if the string was allocated when
// a string is stored.

Value::CZString::CZString( int index )
   : cstr_( 0 )
   , index_( index )
{
}

Value::CZString::CZString( const char *cstr, DuplicationPolicy allocate )
   : cstr_( allocate == duplicate ? valueAllocator()->makeMemberName(cstr) 
                                  : cstr )
   , index_( allocate )
{
}

Value::CZString::CZString( const CZString &other )
: cstr_( other.index_ != noDuplication &&  other.cstr_ != 0
                ?  valueAllocator()->makeMemberName( other.cstr_ )
                : other.cstr_ )
   , index_( other.cstr_ ? (other.index_ == noDuplication ? noDuplication : duplicate)
                         : other.index_ )
{
}

Value::CZString::~CZString()
{
   if ( cstr_  &&  index_ == duplicate )
      valueAllocator()->releaseMemberName( const_cast<char *>( cstr_ ) );
}

void 
Value::CZString::swap( CZString &other )
{
   std::swap( cstr_, other.cstr_ );
   std::swap( index_, other.index_ );
}

Value::CZString &
Value::CZString::operator =( const CZString &other )
{
   CZString temp( other );
   swap( temp );
   return *this;
}

bool 
Value::CZString::operator<( const CZString &other ) const 
{
   if ( cstr_ )
      return strcmp( cstr_, other.cstr_ ) < 0;
   return index_ < other.index_;
}

bool 
Value::CZString::operator==( const CZString &other ) const 
{
   if ( cstr_ )
      return strcmp( cstr_, other.cstr_ ) == 0;
   return index_ == other.index_;
}


int 
Value::CZString::index() const
{
   return index_;
}


const char *
Value::CZString::c_str() const
{
   return cstr_;
}

bool 
Value::CZString::isStaticString() const
{
   return index_ == noDuplication;
}

bool 
Value::CZString::isEmptyString() const
{
	return cstr_ == NULL ? true : false;
}


// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// class Value::Value
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////

/*! \internal Default constructor initialization must be equivalent to:
 * memset( this, 0, sizeof(Value) )
 * This optimization is used in ValueInternalMap fast allocator.
 */
Value::Value( ValueType type )
   : type_( type )
   , allocated_( 0 )
{
   switch ( type )
   {
   case nullValue:
      break;
   case intValue:
   case uintValue:
      value_.int_ = 0;
      break;
   case realValue:
      value_.real_ = 0.0;
      break;
   case stringValue:
      value_.string_ = 0;
      break;
   case objectValue:
      value_.map_ = new ObjectValues();
      break;
   case booleanValue:
      value_.bool_ = false;
      break;
   default:
      return;
   }
}


Value::Value( Int value )
   : type_( intValue )
{
   value_.int_ = value;
}


Value::Value( UInt value )
   : type_( uintValue )
{
   value_.uint_ = value;
}

Value::Value( double value )
   : type_( realValue )
{
   value_.real_ = value;
}

Value::Value( const char *value )
   : type_( stringValue )
   , allocated_( true )
{
   value_.string_ = valueAllocator()->duplicateStringValue( value );
}


Value::Value( const char *beginValue, 
              const char *endValue )
   : type_( stringValue )
   , allocated_( true )
{
   value_.string_ = valueAllocator()->duplicateStringValue( beginValue, 
                                                            UInt(endValue - beginValue) );
}


Value::Value( const std::string &value )
   : type_( stringValue )
   , allocated_( true )
{
   value_.string_ = valueAllocator()->duplicateStringValue( value.c_str(), 
                                                            (unsigned int)value.length() );
}


Value::Value( bool value )
   : type_( booleanValue )
{
   value_.bool_ = value;
}


Value::Value( const Value &other )
   : type_( other.type_ )
{
   switch ( type_ )
   {
   case nullValue:
   case intValue:
   case uintValue:
   case realValue:
   case booleanValue:
      value_ = other.value_;
      break;
   case stringValue:
      if ( other.value_.string_ )
      {
         value_.string_ = valueAllocator()->duplicateStringValue( other.value_.string_ );
         allocated_ = true;
      }
      else
         value_.string_ = 0;
      break;
   case objectValue:
      value_.map_ = new ObjectValues( *other.value_.map_ );
      break;
   default:
      return;
   }
}


Value::~Value()
{
   switch ( type_ )
   {
   case nullValue:
   case intValue:
   case uintValue:
   case realValue:
   case booleanValue:
      break;
   case stringValue:
      if ( allocated_ )
         valueAllocator()->releaseStringValue( value_.string_ );
      break;
   case objectValue:
      delete value_.map_;
      break;
   default:
      return;
   }
}

Value &
Value::operator=( const Value &other )
{
   Value temp( other );
   swap( temp );
   return *this;
}

void 
Value::swap( Value &other )
{
   ValueType temp = type_;
   type_ = other.type_;
   other.type_ = temp;
   std::swap( value_, other.value_ );
   int temp2 = allocated_;
   allocated_ = other.allocated_;
   other.allocated_ = temp2;
}

ValueType 
Value::type() const
{
   return type_;
}


bool 
Value::operator <( const Value &other ) const
{
   int typeDelta = type_ - other.type_;
   if ( typeDelta )
      return typeDelta < 0 ? true : false;
   switch ( type_ )
   {
   case nullValue:
      return false;
   case intValue:
      return value_.int_ < other.value_.int_;
   case uintValue:
      return value_.uint_ < other.value_.uint_;
   case realValue:
      return value_.real_ < other.value_.real_;
   case booleanValue:
      return value_.bool_ < other.value_.bool_;
   case stringValue:
      return ( value_.string_ == 0  &&  other.value_.string_ )
             || ( other.value_.string_  
                  &&  value_.string_  
                  && strcmp( value_.string_, other.value_.string_ ) < 0 );
   case objectValue:
      {
         int delta = int( value_.map_->size() - other.value_.map_->size() );
         if ( delta )
            return delta < 0;
         return (*value_.map_) < (*other.value_.map_);
      }
   default:
      return false;
   }
   return 0;  // unreachable
}

bool 
Value::operator <=( const Value &other ) const
{
   return !(other > *this);
}

bool 
Value::operator >=( const Value &other ) const
{
   return !(*this < other);
}

bool 
Value::operator >( const Value &other ) const
{
   return other < *this;
}

bool 
Value::operator ==( const Value &other ) const
{
   //if ( type_ != other.type_ )
   // GCC 2.95.3 says:
   // attempt to take address of bit-field structure member `Json::Value::type_'
   // Beats me, but a temp solves the problem.
   int temp = other.type_;
   if ( type_ != temp )
      return false;
   switch ( type_ )
   {
   case nullValue:
      return true;
   case intValue:
      return value_.int_ == other.value_.int_;
   case uintValue:
      return value_.uint_ == other.value_.uint_;
   case realValue:
      return value_.real_ == other.value_.real_;
   case booleanValue:
      return value_.bool_ == other.value_.bool_;
   case stringValue:
      return ( value_.string_ == other.value_.string_ )
             || ( other.value_.string_  
                  &&  value_.string_  
                  && strcmp( value_.string_, other.value_.string_ ) == 0 );
   case objectValue:
      return value_.map_->size() == other.value_.map_->size()
             && (*value_.map_) == (*other.value_.map_);
   default:
      return false;
   }
   return 0;  // unreachable
}

bool 
Value::operator !=( const Value &other ) const
{
   return !( *this == other );
}

const char *
Value::asCString() const
{
   if( type_ != stringValue )
	   return ""; 
   return value_.string_;
}


std::string 
Value::asString() const
{
   switch ( type_ )
   {
   case nullValue:
      return "";
   case stringValue:
      return value_.string_ ? value_.string_ : "";
   case booleanValue:
      return value_.bool_ ? "true" : "false";
   case intValue:
   case uintValue:
   case realValue:
   case objectValue:
   default:
      return "";
   }
   return ""; 
}

Value::Int 
Value::asInt() const
{
   switch ( type_ )
   {
   case nullValue:
      return 0;
   case intValue:
      return value_.int_;
   case uintValue:
      return value_.uint_;
   case realValue:
      return Int( value_.real_ );
   case booleanValue:
      return value_.bool_ ? 1 : 0;
   case stringValue:
   case objectValue:
   default:
      return 0;
   }
   return 0; 
}

Value::UInt 
Value::asUInt() const
{
   switch ( type_ )
   {
   case nullValue:
      return 0;
   case intValue:
      return value_.int_;
   case uintValue:
      return value_.uint_;
   case realValue:
      return UInt( value_.real_ );
   case booleanValue:
      return value_.bool_ ? 1 : 0;
   case stringValue:
   case objectValue:
   default:
      return 0;
   }
   return 0; 
}

double 
Value::asDouble() const
{
   switch ( type_ )
   {
   case nullValue:
      return 0.0;
   case intValue:
      return value_.int_;
   case uintValue:
      return value_.uint_;
   case realValue:
      return value_.real_;
   case booleanValue:
      return value_.bool_ ? 1.0 : 0.0;
   case stringValue:
   case objectValue:
   default:
      return 0;
   }
   return 0;
}

bool 
Value::asBool() const
{
   switch ( type_ )
   {
   case nullValue:
      return false;
   case intValue:
   case uintValue:
      return value_.int_ != 0;
   case realValue:
      return value_.real_ != 0.0;
   case booleanValue:
      return value_.bool_;
   case stringValue:
      return value_.string_  &&  value_.string_[0] != 0;
   case objectValue:
      return value_.map_->size() != 0;
   default:
      return false;
   }
   return false; 
}


bool 
Value::isConvertibleTo( ValueType other ) const
{
   switch ( type_ )
   {
   case nullValue:
      return true;
   case intValue:
      return ( other == nullValue  &&  value_.int_ == 0 )
             || other == intValue
             || ( other == uintValue  && value_.int_ >= 0 )
             || other == realValue
             || other == stringValue
             || other == booleanValue;
   case uintValue:
      return ( other == nullValue  &&  value_.uint_ == 0 )
             || ( other == intValue  && value_.uint_ <= (unsigned)maxInt )
             || other == uintValue
             || other == realValue
             || other == stringValue
             || other == booleanValue;
   case realValue:
      return ( other == nullValue  &&  value_.real_ == 0.0 )
             || ( other == intValue  &&  value_.real_ >= minInt  &&  value_.real_ <= maxInt )
             || ( other == uintValue  &&  value_.real_ >= 0  &&  value_.real_ <= maxUInt )
             || other == realValue
             || other == stringValue
             || other == booleanValue;
   case booleanValue:
      return ( other == nullValue  &&  value_.bool_ == false )
             || other == intValue
             || other == uintValue
             || other == realValue
             || other == stringValue
             || other == booleanValue;
   case stringValue:
      return other == stringValue
             || ( other == nullValue  &&  (!value_.string_  ||  value_.string_[0] == 0) );
   case objectValue:
      return other == objectValue
             ||  ( other == nullValue  &&  value_.map_->size() == 0 );
   default:
      return false;
   }
   return false;
}


/// Number of values in array or object
Value::UInt 
Value::size() const
{
   switch ( type_ )
   {
   case nullValue:
   case intValue:
   case uintValue:
   case realValue:
   case booleanValue:
   case stringValue:
      return 0;
   case objectValue:
      return Int( value_.map_->size() );
   default:
      return 0;
   }
   return 0; 
}


bool 
Value::empty() const
{
   if ( isNull() || isObject() )
	   return size() == 0u;
   else
      return false;
}


bool
Value::operator!() const
{
   return isNull();
}


void 
Value::clear()
{
   if ( type_ != nullValue  && type_ != objectValue )
	   return;
   switch ( type_ )
   {
   case objectValue:
      value_.map_->clear();
      break;
   default:
      break;
   }
}


Value &
Value::operator[]( UInt index )
{
   if ( type_ != nullValue  &&  type_ != objectValue )
	   return nul;
   if ( type_ == nullValue )
      *this = Value( objectValue );
   CZString key( index );
   ObjectValues::iterator it = value_.map_->lower_bound( key );
   if ( it != value_.map_->end()  &&  (*it).first == key )
      return (*it).second;

   ObjectValues::value_type defaultValue( key, null );
   it = value_.map_->insert( it, defaultValue );
   return (*it).second;
}


const Value &
Value::operator[]( UInt index ) const
{
   if ( type_ != nullValue  &&  type_ != objectValue )
		return null;
   if ( type_ == nullValue )
      return null;
   CZString key( index );
   ObjectValues::const_iterator it = value_.map_->find( key );
   if ( it == value_.map_->end() )
      return null;
   return (*it).second;

}


Value &
Value::operator[]( const char *key )
{
   return resolveReference( key, false );
}


Value &
Value::resolveReference( const char *key, 
                         bool isStatic )
{
	if ( type_ != nullValue  &&  type_ != objectValue )
		return nul;
	if ( type_ == nullValue )
		*this = Value( objectValue );
	int index = 0;
	ObjectValues::iterator it;
	CZString actualKey( key, isStatic ? CZString::noDuplication 
		: CZString::duplicateOnCopy );
	if (!this->isArray())
	{
		it = value_.map_->lower_bound( actualKey );
		if ( it != value_.map_->end()  &&  (*it).first == actualKey )
			return (*it).second;
	}
	else
	{
		CZString strkey( index );
		it = value_.map_->lower_bound( index );
		for (; it != value_.map_->end(); it++ )
		{
			index ++;
			const Value &childValue = (*it).second;
			if (childValue.type_ != objectValue)
			{
				break;
			}

			ObjectValues::iterator itNext = childValue.value_.map_->lower_bound( actualKey );
			if ( itNext != childValue.value_.map_->end()  &&  (*itNext).first == actualKey )
			{
				return (*itNext).second;
			}
		}
		Value &arrayValue = (*this)[ index ];
		arrayValue = Value( objectValue );
		it = arrayValue.value_.map_->lower_bound( actualKey );
		ObjectValues::value_type defaultValue( actualKey, null );
		it = arrayValue.value_.map_->insert( it, defaultValue );
		Value &value = (*it).second;
		return value;
	}
	ObjectValues::value_type defaultValue( actualKey, null );
	it = value_.map_->insert( it, defaultValue );
	Value &value = (*it).second;
	return value;
}


Value 
Value::get( UInt index, 
            const Value &defaultValue ) const
{
   const Value *value = &((*this)[index]);
   return value == &null ? defaultValue : *value;
}


bool 
Value::isValidIndex( UInt index ) const
{
   return index < size();
}



const Value &
Value::operator[]( const char *key ) const
{
   if( type_ != nullValue  &&  type_ != objectValue )
		return null;
   if ( type_ == nullValue )
      return null;
   CZString actualKey( key, CZString::noDuplication );
   ObjectValues::const_iterator it = value_.map_->find( actualKey );
   if ( it == value_.map_->end() )
      return null;
   return (*it).second;
}


Value &
Value::operator[]( const std::string &key )
{
   return (*this)[ key.c_str() ];
}


const Value &
Value::operator[]( const std::string &key ) const
{
   return (*this)[ key.c_str() ];
}


Value &
Value::append( const Value &value )
{
   return (*this)[size()] = value;
}


Value 
Value::get( const char *key, 
            const Value &defaultValue ) const
{
   const Value *value = &((*this)[key]);
   return value == &null ? defaultValue : *value;
}


Value 
Value::get( const std::string &key,
            const Value &defaultValue ) const
{
   return get( key.c_str(), defaultValue );
}

Value
Value::removeMember( const char* key )
{
   if ( type_ != nullValue  &&  type_ != objectValue )
	   return null;
   if ( type_ == nullValue )
      return null;
   CZString actualKey( key, CZString::noDuplication );
   ObjectValues::iterator it = value_.map_->find( actualKey );
   if ( it == value_.map_->end() )
      return null;
   Value old(it->second);
   value_.map_->erase(it);
   return old;
}

Value
Value::removeMember( const std::string &key )
{
   return removeMember( key.c_str() );
}

bool 
Value::isMember( const char *key ) const
{
   const Value *value = &((*this)[key]);
   return value != &null;
}


bool 
Value::isMember( const std::string &key ) const
{
   return isMember( key.c_str() );
}


Value::Members 
Value::getMemberNames() const
{
   if ( type_ != nullValue  &&  type_ != objectValue )
	   return Value::Members();
   if ( type_ == nullValue )
       return Value::Members();
   Members members;
   members.reserve( value_.map_->size() );
   ObjectValues::const_iterator it = value_.map_->begin();
   ObjectValues::const_iterator itEnd = value_.map_->end();
   for ( ; it != itEnd; ++it )
      members.push_back( std::string( (*it).first.c_str() ) );
   return members;
}



bool
Value::isNull() const
{
   return type_ == nullValue;
}


bool 
Value::isBool() const
{
   return type_ == booleanValue;
}


bool 
Value::isInt() const
{
   return type_ == intValue;
}


bool 
Value::isUInt() const
{
   return type_ == uintValue;
}


bool 
Value::isIntegral() const
{
   return type_ == intValue  
          ||  type_ == uintValue  
          ||  type_ == booleanValue;
}


bool 
Value::isDouble() const
{
   return type_ == realValue;
}


bool 
Value::isNumeric() const
{
   return isIntegral() || isDouble();
}


bool 
Value::isString() const
{
   return type_ == stringValue;
}


bool 
Value::isArray() const
{
	if (!value_.map_->empty())
	{
		ObjectValues::iterator it = value_.map_->begin();
		return (*it).first.isEmptyString() ? true : false;
	}
	return false;
}


bool 
Value::isObject() const
{
   return type_ == nullValue  ||  type_ == objectValue;
}



std::string 
Value::toStyledString() const
{
   Writer writer;
   return writer.write( *this );
}

} // namespace Json
