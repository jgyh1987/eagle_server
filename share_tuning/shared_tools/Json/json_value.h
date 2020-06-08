#ifndef JSONDLL_JSON_VALUE_H_INCLUDE
#define JSONDLL_JSON_VALUE_H_INCLUDE
#include <string>
#include <vector>
#include <map>

namespace Json 
{
	typedef int Int;
	typedef unsigned int UInt;
   /** \brief Type of the value held by a Value object.
    */
   enum ValueType
   {
      nullValue = 0, ///< 'null' value
      intValue,      ///< signed integer value
      uintValue,     ///< unsigned integer value
      realValue,     ///< double value
      stringValue,   ///< UTF-8 string value
      booleanValue,  ///< bool value
  //    arrayValue,    ///< array value (ordered list)
      objectValue    ///< object value (collection of name/value pairs).
   };

   enum CommentPlacement
   {
      commentBefore = 0,        ///< a comment placed on the line before a value
      commentAfterOnSameLine,   ///< a comment just after a value on the same line
      commentAfter,             ///< a comment on the line after a value (only make sense for root value)
      numberOfCommentPlacement
   };


   class Value 
   {
   public:
      typedef std::vector<std::string> Members;
      typedef Json::UInt UInt;
      typedef Json::Int Int;
      typedef UInt ArrayIndex;

      static const Value null;
      static const Int minInt;
      static const Int maxInt;
      static const UInt maxUInt;
	  static Value nul;
   private:
      class CZString 
      {
      public:
         enum DuplicationPolicy 
         {
            noDuplication = 0,
            duplicate,
            duplicateOnCopy
         };
         CZString( int index );
         CZString( const char *cstr, DuplicationPolicy allocate );
         CZString( const CZString &other );
         ~CZString();
         CZString &operator =( const CZString &other );
         bool operator<( const CZString &other ) const;
         bool operator==( const CZString &other ) const;
         int index() const;
         const char *c_str() const;
         bool isStaticString() const;
		 bool isEmptyString() const;
      private:
         void swap( CZString &other );
         const char *cstr_;
         int index_;
      };

   public:
		typedef std::map<CZString, Value> ObjectValues;


   public:
      /** \brief Create a default Value of the given type.

        This is a very useful constructor.
        To create an empty array, pass arrayValue.
        To create an empty object, pass objectValue.
        Another Value can then be set to this one by assignment.
	This is useful since clear() and resize() will not alter types.

        Examples:
	\code
	Json::Value null_value; // null
	Json::Value arr_value(Json::arrayValue); // []
	Json::Value obj_value(Json::objectValue); // {}
	\endcode
      */
      Value( ValueType type = nullValue );
      Value( Int value );
      Value( UInt value );
      Value( double value );
      Value( const char *value );
      Value( const char *beginValue, const char *endValue );
      /** \brief Constructs a value from a static string.

       * Like other value string constructor but do not duplicate the string for
       * internal storage. The given string must remain alive after the call to this
       * constructor.
       * Example of usage:
       * \code
       * Json::Value aValue( StaticString("some text") );
       * \endcode
       */
    //  Value( const StaticString &value );
      Value( const std::string &value );
      Value( bool value );
      Value( const Value &other );
      virtual ~Value();

      Value &operator=( const Value &other );
      /// Swap values.
      /// \note Currently, comments are intentionally not swapped, for
      /// both logic and efficiency.
      void swap( Value &other );

      ValueType type() const;

      bool operator <( const Value &other ) const;
      bool operator <=( const Value &other ) const;
      bool operator >=( const Value &other ) const;
      bool operator >( const Value &other ) const;

      bool operator ==( const Value &other ) const;
      bool operator !=( const Value &other ) const;


      const char *asCString() const;
      std::string asString() const;
      Int asInt() const;
      UInt asUInt() const;
      double asDouble() const;
      bool asBool() const;

      bool isNull() const;
      bool isBool() const;
      bool isInt() const;
      bool isUInt() const;
      bool isIntegral() const;
      bool isDouble() const;
      bool isNumeric() const;
      bool isString() const;
      bool isArray() const;
      bool isObject() const;

      bool isConvertibleTo( ValueType other ) const;

      /// Number of values in array or object
      UInt size() const;

      /// \brief Return true if empty array, empty object, or null;
      /// otherwise, false.
      bool empty() const;

      /// Return isNull()
      bool operator!() const;

      /// Remove all object members and array elements.
      /// \pre type() is arrayValue, objectValue, or nullValue
      /// \post type() is unchanged
      void clear();

      /// Resize the array to size elements. 
      /// New elements are initialized to null.
      /// May only be called on nullValue or arrayValue.
      /// \pre type() is arrayValue or nullValue
      /// \post type() is arrayValue
      /// void resize( UInt size );

      /// Access an array element (zero based index ).
      /// If the array contains less than index element, then null value are inserted
      /// in the array so that its size is index+1.
      /// (You may need to say 'value[0u]' to get your compiler to distinguish
      ///  this from the operator[] which takes a string.)
      Value &operator[]( UInt index );
      /// Access an array element (zero based index )
      /// (You may need to say 'value[0u]' to get your compiler to distinguish
      ///  this from the operator[] which takes a string.)
      const Value &operator[]( UInt index ) const;
      /// If the array contains at least index+1 elements, returns the element value, 
      /// otherwise returns defaultValue.
      Value get( UInt index, 
                 const Value &defaultValue ) const;
      /// Return true if index < size().
      bool isValidIndex( UInt index ) const;
      /// \brief Append value to array at the end.
      ///
      /// Equivalent to jsonvalue[jsonvalue.size()] = value;
      Value &append( const Value &value );

      /// Access an object value by name, create a null member if it does not exist.
      Value &operator[]( const char *key );
      /// Access an object value by name, returns null if there is no member with that name.
      const Value &operator[]( const char *key ) const;
      /// Access an object value by name, create a null member if it does not exist.
      Value &operator[]( const std::string &key );
      /// Access an object value by name, returns null if there is no member with that name.
      const Value &operator[]( const std::string &key ) const;
      /** \brief Access an object value by name, create a null member if it does not exist.

       * If the object as no entry for that name, then the member name used to store
       * the new entry is not duplicated.
       * Example of use:
       * \code
       * Json::Value object;
       * static const StaticString code("code");
       * object[code] = 1234;
       * \endcode
       */

      /// Return the member named key if it exist, defaultValue otherwise.
      Value get( const char *key, 
                 const Value &defaultValue ) const;
      /// Return the member named key if it exist, defaultValue otherwise.
      Value get( const std::string &key,
                 const Value &defaultValue ) const;
      /// \brief Remove and return the named member.  
      ///
      /// Do nothing if it did not exist.
      /// \return the removed Value, or null.
      /// \pre type() is objectValue or nullValue
      /// \post type() is unchanged
      Value removeMember( const char* key );
      /// Same as removeMember(const char*)
      Value removeMember( const std::string &key );

      /// Return true if the object has a member named key.
      bool isMember( const char *key ) const;
      /// Return true if the object has a member named key.
      bool isMember( const std::string &key ) const;

      /// \brief Return a list of the member names.
      ///
      /// If null, return an empty list.
      /// \pre type() is objectValue or nullValue
      /// \post if type() was nullValue, it remains nullValue
      Members getMemberNames() const;


      std::string toStyledString() const;


   private:
      Value &resolveReference( const char *key, 
                               bool isStatic );

   private:
      union ValueHolder
      {
         Int int_;
         UInt uint_;
         double real_;
         bool bool_;
         char *string_;
         ObjectValues *map_;
      } value_;
      ValueType type_ : 8;
      int allocated_ : 1;     // Notes: if declared as bool, bitfield is useless.
   };

   /** \brief Experimental do not use: Allocator to customize member name and string value memory management done by Value.
    *
    * - makeMemberName() and releaseMemberName() are called to respectively duplicate and
    *   free an Json::objectValue member name.
    * - duplicateStringValue() and releaseStringValue() are called similarly to
    *   duplicate and free a Json::stringValue value.
    */
   class ValueAllocator
   {
   public:
      enum { unknown = (unsigned)-1 };

      virtual ~ValueAllocator();

      virtual char *makeMemberName( const char *memberName ) = 0;
      virtual void releaseMemberName( char *memberName ) = 0;
      virtual char *duplicateStringValue( const char *value, 
                                          unsigned int length = unknown ) = 0;
      virtual void releaseStringValue( char *value ) = 0;
   };


} // namespace Json


#endif	//JSONDLL_JSON_VALUE_H_INCLUDE