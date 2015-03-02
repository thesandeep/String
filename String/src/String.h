/*	A Custom String Class
 *
 * Copyright (c) 2015, Sandeep V. Sabnani
 * Twitter: @sandeepsabnani
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIEDWARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <iterator>
#include <stddef.h>
#include <exception>

#ifndef STRING_H_
#define STRING_H_

#define SMALL_SIZE 2

class StringIterator; //Forward declaration

// Private helper methods in this namespace
namespace StringHelper
{
	/*
	 * Simple  method to count the elemens in a
	 * const char * array.
	 *
	 * */
	inline size_t getLength(const char* s)
	{
		size_t len = 0;
		while ( *s )
		{
			len++;
			++s;
		}
		return len;
	};
}

/*
 *  A Custom String Class
 *
 *
 * This class provides mechanisms for handling strings.
 *
 * Assuming most strings are going to be 5 characters or less,
 * this class provides fast access to such small strings by
 * allocating them on stack. The small string size is given by SMALL_SIZE.
 *
 * For strings larger than SMALL_SIZE, heap allocation is used.
 *
 *
 * */
class String {

	friend class StringIterator;

public:

	typedef StringIterator iterator;

	// Explicit default constructor
	explicit String();

	// Copy Constructor
	String (const String& str);

	// Constructor which takes a const char*
	String(const char *s);

	// Destructor
	virtual ~String();

	// Returns a StringIterator to the beginning of the string
	iterator begin();

	// Returns a StringIterator to the end of the string
	iterator end();

	// Returns the size of the string in bytes
	size_t size();

	// Returns the maximum size of the string in bytes
	size_t max_size();

	// Resize the string to length 'n'
	void resize(size_t n);

	// Return size of allocated storage
    size_t capacity() const;

	// Request a change in capacity
	void reserve(size_t s);

	// Clear the data
	void clear();

    // Test if string is empty
	bool empty() const;

	// Get character of string
	char& operator[] (size_t i);

	// Get character of string
	char& at (size_t i);

	// Concatenate two strings
	String operator+= (String str);

	// Assign a String to another String
	String& operator= (String& str);

	// Append to existing string
	String& append (const String& str);

	// Append a character to a string
    void push_back(char c);

	// Assign content to string
	String& assign(const String& str);

	// Insert into string
	String& insert(size_t pos, const String str);

	// Erase characters from string
	String& erase(size_t pos, size_t len);

    // Replace portion of string
	String& replace(size_t pos, size_t len, const String str);

	// Swap two strings
	void swap(String& str);

	// Return C string equivalent
	const char* c_str() const;

	// Get string data
	const char* data() const;

private:
	inline void WriteNull()
	{
		if(category() == small)
		{
			_small[_smallSize] = '\0';
		}
		else if (category() == large)
		{
			_large._data[_large._size] = '\0';
		}
	}

	struct Large {
		char * _data;
		size_t _size;
		size_t _capacity;
	};

	Large  _large;
	char   _small[SMALL_SIZE+1];
	size_t _smallSize;

	enum Category {
		small, large
	};

	Category _cat;

	// Get string category (small or large)
	Category category() const { return _cat; };
};


// StringIterator, derived from std::iterator
class StringIterator : public std::iterator<std::input_iterator_tag, int>
{
  String* _s; // String
  size_t  _p; // Position
public:
  StringIterator(String* str, size_t pos) :_s(str), _p(pos) {}

  char& operator*()
  {
	  if((*_s).category() == (*_s).small)
	  {
		  return (*_s)._small[_p];
	  }
	  else
	  {
		  return (*_s)._large._data[_p];
	  }
  }

  char* operator->() { return &(operator*()); }

  char& operator++()
  {
	  ++_p;
	  return operator*();
  }

  bool operator==(StringIterator other) const
  {
	  return(&_s == &(other._s));
  }

  bool operator!=(StringIterator other) const
  {
	  return(&_s != &(other._s));
  }
};


/**
 * StringException Class
 *
 * A class used to define exceptions raised by the String class
 *
 * */

class StringException: public std::exception {
public:
	explicit StringException(const char* err) : _errorText(err) {};
	const char * what () const throw ()
	{
		return _errorText;
	}

private:
	const char* _errorText;

};


#endif /* STRING_H_ */
