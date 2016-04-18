#pragma once
#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
#include <ostream> 
#include "StringItt.h"

class String
{
private:
	char* myCStr;
	int mySize, myCapacity;
	void copy(const int size);
public:
	typedef Iterator iterator;
	typedef ReverseIterator reverse_iterator;

	typedef ConstIterator const_iterator;
	typedef ConstReverseIterator const_reverse_iterator;

	String();
	~String();

	String(const String& rhs);
	String(String&& rhs); //VG
	String(const char* cstr);

	inline char& operator[](int i) {
		return myCStr[i];
	}

	inline const char& operator[](int i) const {
		return myCStr[i];
	}

	inline const char* data() const {
		if (mySize == 0)
			return nullptr;
		else 
			return myCStr;
	}

	inline int size() const {
		return mySize;
	}

	inline int capacity() const {
		return myCapacity;
	}

	char& at(const int i);
	const char& at(const int i) const;
	void push_back(const char c);
	void reserve(const int newSize);
	void shrink_to_fit();
	void resize(const int newSize);

	//=
	String& operator=(const String& rhs);
	String& operator=(String&& rhs); //VG
	String& operator=(const char* cstr);
	String& operator=(char ch);

	//+=
	String& operator+=(const String& rhs);
	String& operator+=(char* cstr);

	//
	friend String operator+(const String& lhs, const String& rhs);

	friend bool operator==(const String&lhs, const String& rhs);

	friend std::ostream& operator<< (std::ostream& stream, const String& s);

	//Iterator
	inline iterator begin() const {
		return iterator(myCStr);
	}
	inline iterator end() const {
		return iterator(myCStr + mySize);
	}

	//Reverse Iterator
	inline reverse_iterator rbegin() const {
		return reverse_iterator(myCStr + mySize -1);
	}
	inline reverse_iterator rend() const {
		return reverse_iterator(myCStr-1);
	}

	//const Iterator
	inline const_iterator cbegin() const {
		return const_iterator(myCStr);
	}
	inline const_iterator cend() const {
		return const_iterator(myCStr + mySize);
	}

	//const Reverse Iterator
	inline const_reverse_iterator crbegin() const {
		return const_reverse_iterator(myCStr + mySize - 1);
	}
	inline const_reverse_iterator crend() const {
		return const_reverse_iterator(myCStr - 1);
	}
};

