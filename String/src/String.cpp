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

#include "String.h"
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <math.h>

typedef StringIterator iterator;

// Default constructor
String::String()
{
	_cat = small;
	_smallSize = 0;
	WriteNull();
}

// Copy Constructor
String::String (const String& str)
{
	if(str.category() == small)
	{
		_cat = small;
		_smallSize = str._smallSize;
		for(int i = 0; i < str._smallSize; ++i)
		{
			_small[i] = str._small[i];
		}
	}
	else if (str.category() == large)
	{
		_cat = large;
		_large._size = str._large._size;
		_large._data = new char[_large._size];
		memcpy(_large._data, str._large._data, _large._size);
		_smallSize = 0;
		_large._capacity = _large._size;
	}
}

// Constructor which takes a const char*
String::String(const char *s)
{
	size_t len = StringHelper::getLength(s);
	if(len <= SMALL_SIZE)
	{
		for(int i = 0; i < len; ++i)
		{
			_small[i] = s[i];
		}
		_smallSize = len;
		_cat = small;
		WriteNull();
	}
	else
	{
		_cat = large;
		_large._size = StringHelper::getLength(s);
		_large._data = new char[_large._size+1];
		memcpy(_large._data, s, _large._size);
		_large._capacity = _large._size;
		WriteNull();
	}
}

// Destructor (not necessary that this be virtual)
String::~String()
{
	if(category() == large)
	{
		delete [] _large._data;
		_large._size = 0;
		_large._capacity = 0;
	}
}

// Return the data contained by the object
const char* String::data() const
{
	return c_str();
}

// Assign a String to another String
String& String::operator= (String& str)
{
	assign(str);

	return *this;
}

// Is string empty?
bool String::empty() const
{
	bool ret = false;
	if(category() == small)
	{
		ret = (_smallSize == 0) ? true:false;
	}
	else if(category() == large)
	{
		ret = (_large._size == 0) ? true:false;
	}
	return ret;
}

// Return string size
size_t String::size()
{
	size_t retSize;
	if(category() == small)
	{
		retSize = _smallSize;
	}
	else if (category() == large)
	{
		retSize = _large._size;
	}
	return retSize;
}

// Clear the string
void String::clear()
{
	if(category() == small)
	{
		_small[0] = '\0';
	}
	else
	{
		memset(_large._data, 0, sizeof(*_large._data));
		_large._size = 0;
		_large._capacity = 0;
	}
}

// Return C string equivalent
const char* String::c_str() const
{
	if(category() == small)
	{
		assert(_small[_smallSize] == '\0');
		return _small;
	}
	else
	{
		assert(_large._data[_large._size] == '\0');
		return _large._data;
	}
}


// Append a character to a string
void String::push_back(char c)
{
	if(category() == small)
	{
		resize(_smallSize+1);
		if(category() == small)
		{
			_small[_smallSize+1] = c;
			_smallSize += 1;
			WriteNull();
		}
		else
		{
			_large._data[_large._size-1] = c;
			WriteNull();
		}
	}
	else if (category() == large)
	{
		char* temp = new char[_large._size+1];
		for(int i = 0; i < _large._size;++i)
		{
			temp[i] = _large._data[i];
		}
		temp[_large._size] = c;

		_large._data = temp;
		_large._size++;
		WriteNull();
	}
}

// Append a new string to this string
String& String::append (const String& str)
{
	size_t newLen = 0;
	size_t lhsOldSize;


	if(category() == small)
	{
		if(str.category() == small)
		{
			newLen = _smallSize + str._smallSize;
			lhsOldSize = _smallSize;
		}
		else if(str.category() == large)
		{
			newLen = _smallSize + str._large._size;
			lhsOldSize = _smallSize;
		}
	}
	else if(category() == large)
	{
		if(str.category() == small)
		{
			newLen = _large._size + str._smallSize;
			lhsOldSize = _large._size;
		}
		else if(str.category() == large)
		{
			newLen = _large._size + str._large._size;
			lhsOldSize = _large._size;
		}
	}

	if(newLen <= SMALL_SIZE)
	{
		resize(newLen);
		for(int i = 0; i< str._smallSize; ++i)
		{
			_small[_smallSize+i] = str._small[i];
		}
		WriteNull();
	}

	resize(newLen);

	int i = 0;

	if(str.category() == small)
	{
		while(i<str._smallSize)
		{
			_large._data[lhsOldSize] = str._small[i];
			++i;
		}
	}
	else if(str.category() == large)
	{
		while(i < str._large._size)
		{
			_large._data[lhsOldSize+i] = str._large._data[i];
			++i;
		}
	}

	return *this;
}

// Assign content to string
String& String::assign(const String& str)
{
	if(str.category() == small)
	{
		_smallSize = str._smallSize;
		_cat = small;
		int i =0;
		while(i <= str._smallSize)
		{
			_small[i] = str._small[i];
			++i;
		}
		WriteNull();
	}
	else if(str.category() == large)
	{
		char * temp = new char[str._large._size+1];
		_large._size = str._large._size;
		_large._capacity = str._large._capacity;
		_cat = large;
		int i = 0;
		while(i < str._large._size)
		{
			temp[i] = str._large._data[i];
			++i;
		}

		_large._data = temp;
		WriteNull();
	}
	return *this;
}

// Erase characters from string
String& String::erase(size_t pos, size_t len)
{
	if(category() == small)
	{
		size_t newLen = _smallSize -len;
		assert(newLen >= 0);

		char temp[newLen];

		int i = 0; int j = 0;
		while(i <= _smallSize)
		{
			if(i == pos)
			{
				i += len;
			}
			else
			{
				temp[j] = _small[i];
				++i; ++j;
			}
		}

		i = 0;
		while(i < newLen)
		{
			_small[i] = temp[i];
			++i;
		}

		_smallSize = newLen;
		WriteNull();
	}

	else if (category() == large)
	{
		size_t newLen = _large._size - len;
		if(newLen <= SMALL_SIZE)
		{
			// Erasing from large so it becomes small
			_smallSize = newLen+1;
			_cat = small;
		}

		char *temp = new char[newLen+1];

		int i = 0; int j = 0;
		while(i <= _large._size && j <= newLen)
		{
			if (i == pos)
			{
				// Skip from here to pos + len
				i = pos + len;
			}
			else
			{
				if(category() == large)
				{
					temp[j] = _large._data[i];
				}
				else
				{
					_small[j] = _large._data[i];
				}
				++i;
				++j;
			}
		}

		if(category() == large)
		{
			_large._size = newLen+1;
			_large._data = temp;
		}
		else
		{
			delete [] temp;
		}
		WriteNull();
	}
	return *this;
}

// Insert into string
String& String::insert(size_t pos, const String str)
{
	size_t newLen = 0;

	if(category() == small && str.category() == small)
	{
		newLen = _smallSize + str._smallSize;
	}
	else if(category() == small && str.category() == large)
	{
		newLen = _smallSize + str._large._size;
	}
	else if(category() == large && str.category() == small)
	{
		newLen = _large._size + str._smallSize;
	}
	else if(category() == large && str.category() == large)
	{
		newLen = _large._size + str._large._size;

	}

	if(newLen <= SMALL_SIZE)
	{
		// Both small, new string is also small
		int i = 0; int j = 0; int k = 0;
		char temp[newLen +1];
		while(i < pos)
		{
			temp[i] = _small[i];
			++i;
		}

		k = i;

		while(j < str._smallSize)
		{
			temp[i] = str._small[j];
			++i;
			++j;
		}

		while(i < newLen)
		{
			temp[i] = _small[k];
			++i;
			++k;
		}
		_smallSize = newLen;
		WriteNull();
	}
	else
	{
		// New string is large
		char *temp = new char[newLen +1];

		if(category() == small)
		{
			int i = 0;

			// Copy until we reach 'pos'
			while (i < pos)
			{
				temp[i] = _small[i];
				++i;
			}

			// Note where we stopped copying from 'this' string
			int k = i;

			// Copy 'len' characters starting at 'pos'
			int j = 0;
			while(j < str._large._size)
			{
				temp[i] = str._large._data[j];
				++j;
				++i;
			}

			// Copy from where we stopped in 'this' string
			while( i < newLen)
			{
				temp[i] = _small[k];
				++i;
				++k;
			}
		}
		else if(category() == large && str.category() == small)
		{
			// large, small - result is large
			int i = 0;

			// Copy until we reach 'pos'
			while (i < pos)
			{
				temp[i] = _large._data[i];
				++i;
			}

			// Note where we stopped copying from 'this' string
			int k = i;

			// Copy 'len' characters starting at 'pos'
			int j = 0;
			while(j < str._smallSize)
			{
				temp[i] = str._small[j];
				++j;
				++i;
			}

			// Copy from where we stopped in 'this' string
			while( i < newLen)
			{
				temp[i] = _large._data[k];
				++i;
				++k;
			}
		}
		else if(category() == large && str.category() == large)
		{
			// large, large - result is large
			int i = 0;

			// Copy until we reach 'pos'
			while (i < pos)
			{
				temp[i] = _large._data[i];
				++i;
			}

			// Note where we stopped copying from 'this' string
			int k = i;

			// Copy 'len' characters starting at 'pos'
			int j = 0;
			while(j < str._large._size)
			{
				temp[i] = str._large._data[j];
				++j;
				++i;
			}

			// Copy from where we stopped in 'this' string
			while( i < newLen)
			{
				temp[i] = _large._data[k];
				++i;
				++k;
			}
		}

		// Re-assign instance variables
		_cat = large;
		_large._size = newLen;
		_large._data = temp;
		WriteNull();
	}
	return *this;
}

// Resize the string to length 'n'
void String::resize(size_t n)
{
	if (n < 1)
	{
		StringException ex("Negative size");
		throw ex;
	}

	if(((_smallSize + n) <= SMALL_SIZE))
	{
		_smallSize += n;
	}
	else
	{
		if(category() == large)
		{
			if((n+1) > _large._capacity)
			{
				char * temp = new char[n+1];
				memcpy(temp, _large._data, _large._size);
				_large._data = temp;
				_large._size = n;
				_large._capacity = _large._size;
				_cat = large;
				WriteNull();
			}
		}
		else if(category() == small)
		{
			char * temp = new char[n+1];
			for(int i = 0; i<=_smallSize; ++i)
			{
				temp[i] = _small[i];
			}

			_large._data = temp;
			_large._size = n;
			_large._capacity = _large._size;
			_cat = large;
			WriteNull();

			_smallSize = 0;
			_small[0] = '\0';
		}
	}
}

// Swap two strings
void String::swap(String& str)
{
	if(category() == small)
	{
		if(str.category() == small)
		{
			std::swap(_small, str._small);
		}
		else if (str.category()  == large)
		{
			resize(str._large._size);
			std::swap(_large._data, str._large._data);
			std::swap(_large._size, str._large._size);
			std::swap(_smallSize, str._smallSize);
			_small[0] = '\0';
			_smallSize = 0;
		}
	}
	else if(category() == large)
	{
		if (str.category() == small)
		{
			str.resize(_large._size);
			std::swap(_large._data, str._large._data);
			std::swap(_large._size, str._large._size);
			std::swap(_smallSize, str._smallSize);
			str._small[0] = '\0';
			str._smallSize = 0;
		}
		else if(str.category() == large)
		{
			std::swap(_large._data, str._large._data);
		}
	}
}


// Replace portion of string
String& String::replace(size_t pos, size_t len, const String str)
{
	size_t newLen = 0;

	if(category() == small && str.category() == small)
	{
		if((pos + len) <= _smallSize)
		{
			newLen = _smallSize + str._smallSize - len;
		}
	}
	else if(category() == small && str.category() == large)
	{
		newLen = _smallSize + str._large._size - len;
	}
	else if(category() == large && str.category() == small)
	{
		newLen = _large._size + str._smallSize - len;
	}
	else if(category() == large && str.category() == large)
	{
		if((pos + len) < _large._size)
		{
			newLen = _large._size - len + str._large._size;
		}
		else
		{
			newLen = pos + std::min(len, str._large._size);
		}
	}

	if(newLen <= SMALL_SIZE)
	{
		// Both small, new string is also small
		int i = 0; int j = 0; int k = 0;
		char temp[newLen +1];
		while(i < pos)
		{
			temp[i] = _small[i];
			++i;
		}

		while(j < len)
		{
			temp[i] = str._small[j];
			++i;
			++j;
		}

		while(i < newLen)
		{
			temp[i] = _small[pos];
			++i;
			++pos;
		}
		_smallSize = newLen;
		WriteNull();
	}
	else
	{
		// New string is large
		char *temp = new char[newLen +1];

		if(category() == small) // TODO
		{
			int i = 0;

			// Copy until we reach 'pos'
			while (i < pos)
			{
				temp[i] = _small[i];
				++i;
			}

			// Note where we stopped copying from 'this' string
			int k = i+len;

			// Copy 'len' characters starting at 'pos'
			int j = 0;
			while(j < (str._large._size) && j < len)
			{
				temp[i] = str._large._data[j];
				++j;
				++i;
			}

			// Copy from where we stopped in 'this' string
			while( i < newLen)
			{
				temp[i] = _small[k];
				++i;
				++k;
			}
		}
		else if(category() == large && str.category() == small)
		{
			// large, small - result is large
			int i = 0;

			// Copy until we reach 'pos'
			while (i < pos)
			{
				temp[i] = _large._data[i];
				++i;
			}

			// Note where we stopped copying from 'this' string
			int k = i+len;

			// Copy 'len' characters starting at 'pos'
			int j = 0;
			while(j < (str._smallSize) && j < len)
			{
				temp[i] = str._small[j];
				++j;
				++i;
			}

			// Copy from where we stopped in 'this' string
			while( i < newLen)
			{
				temp[i] = _large._data[k];
				++i;
				++k;
			}
		}
		else if(category() == large && str.category() == large)
		{
			// large, large - result is large
			int i = 0;

			// Copy until we reach 'pos'
			while (i < pos)
			{
				temp[i] = _large._data[i];
				++i;
			}

			// Note where we stopped copying from 'this' string
			int k = i + len;

			// Copy 'len' characters starting at 'pos'
			int j = 0;
			while((i < newLen) && (j < str._large._size))
			{
				temp[i] = str._large._data[j];
				++j;
				++i;
			}

			// Copy from where we stopped in 'this' string
			while( i < newLen)
			{
				temp[i] = _large._data[k];
				++i;
				++k;
			}
		}

		// Re-assign instance variables
		_cat = large;
		_large._size = newLen;
		_large._data = temp;
		WriteNull();
	}
	return *this;
}

// Returns the maximum size of the string in bytes
size_t String::max_size()
{
	return std::numeric_limits<size_t>::max();
}

// Concatenate two strings
String String::operator+= (String str)
{
	return append(str);
}

// Get character of string
char& String::at (size_t i)
{
	if(category() == small && i < _smallSize)
	{
		return _small[i];
	}
	else if (category() == large && i < _large._size)
	{
		return _large._data[i];
	}
	else
	{
		// Throw Exception
		StringException ex("Access Out of Bound");
		throw ex;
	}
}

// Get character of string
char& String::operator[] (size_t i)
{
	 char& ret = at(i);
	 return ret;
}

// Returns a StringIterator to the beginning of the string
iterator String::begin()
{
	return iterator(this, 0);
}

// Returns a StringIterator to the end of the string
iterator String::end()
{
	return iterator(this, (size()));
}

// Reserve the capacity of the string
void String::reserve(size_t s = 0)
{
	if(category() == small && (_smallSize + s) > SMALL_SIZE)
	{
		// Small To Large
		char * temp = new char[_smallSize + s];

		int i = 0;
		while(_small[i])
		{
			temp[i] = _small[i];
			++i;
		}

		_large._size = _smallSize;
		_large._capacity = s;
		_large._data = temp;
		_cat = large;
		WriteNull();

	}
	else if(category() == large)
	{
		// Large To Large
		char * temp = new char[_large._size + s];

		int i = 0;
		while(_large._data[i])
		{
			temp[i] = _large._data[i];
			++i;
		}

		_large._capacity = s;
		_large._data = temp;
		_cat = large;
		WriteNull();
	}
}

// Return size of allocated storage
size_t String::capacity() const
{
	size_t ret;

	if(category() == small)
	{
		ret = _smallSize;
	}
	else if(category() == large)
	{
		ret = _large._capacity;
	}

	return ret;
}




