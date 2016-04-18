#include "stdafx.h"
#include "String.h"
#include <cstring>
#include <stdexcept>
#include <string>

String::String()
	: myCStr(new char[11]), mySize(0), myCapacity(10)
{
}

String::~String()
{
	delete[] myCStr;
}

String::String(const String& rhs)
{
	myCStr = new char[rhs.mySize + 1];
	memcpy(myCStr, rhs.myCStr, rhs.mySize + 1);

	mySize = rhs.mySize;
	myCapacity = rhs.mySize;
}

String::String(String&& rhs)
	: myCStr(rhs.myCStr), mySize(rhs.mySize), myCapacity(rhs.myCapacity)
{
	rhs.myCStr = nullptr;
	rhs.mySize = 0;
	rhs.myCapacity = 0;
}

String::String(const char* cstr)
{
	int length = strlen(cstr);

	myCStr = new char[length + 1];
	memcpy(myCStr, cstr, length + 1);

	mySize = length;
	myCapacity = length;
}

char& String::at(const int i)
{
	if (i < 0 || i >= mySize)
		throw std::out_of_range("Index out of range");
	return myCStr[i];
}

const char& String::at(const int i) const
{
	if (i < 0 || i >= mySize)
		throw std::out_of_range("Index out of range");
	return myCStr[i];
}

void String::push_back(const char c)
{
	if (myCapacity == mySize)
		reserve(myCapacity * 2);
	myCStr[mySize] = c;
	++mySize;
}

void String::copy(const int size)
{
	if (size != myCapacity) {
		char* tmp = new char[size + 1];
		memcpy(tmp, myCStr, size + 1);
		delete[] myCStr;
		myCStr = tmp;
		myCapacity = size;
	}
}

void String::reserve(const int newSize)
{
	if (newSize > myCapacity) {
		copy(newSize);
	}
}

void String::shrink_to_fit()
{
	copy(mySize);
}

void String::resize(const int newSize)
{
	if(newSize > myCapacity)
		copy(newSize);

	if (newSize > mySize)
	{
		for (int i = mySize; i < newSize; i++)
			myCStr[i] = char();
	}
	
	mySize = newSize;
}

String& String::operator=(const String& rhs)
{
	if (this != &rhs)
	{
		if (rhs.mySize > myCapacity || myCStr == nullptr) {
			delete[] myCStr;
			myCStr = new char[rhs.mySize + 1];
			myCapacity = rhs.mySize;
		}
		memcpy(myCStr, rhs.myCStr, rhs.mySize + 1);
		
		mySize = rhs.mySize;
	}

	return *this;
}

String& String::operator=(String&& rhs)
{
	if (this != &rhs)
	{
		delete[] myCStr;

		myCStr = rhs.myCStr;
		mySize = rhs.mySize;
		myCapacity = rhs.myCapacity;

		rhs.myCStr = nullptr;
		rhs.mySize = 0;
		rhs.myCapacity = 0;
	}
	return *this;
}

String& String::operator=(const char* cstr)
{
	int length = strlen(cstr);

	if (length > myCapacity || myCStr == nullptr) {
		delete[] myCStr;
		myCStr = new char[length + 1];
		myCapacity = length;
	}

	memcpy(myCStr, cstr, length + 1);
	
	mySize = length;

	return *this;
}

String& String::operator=(char ch)
{
	if (myCapacity > 1 || myCStr == nullptr) {
		delete[] myCStr;
		myCStr = new char[2];
		myCapacity = 1;
	}
	myCStr[0] = ch;
	mySize = 1;

	return *this;
}

String& String::operator+=(const String& rhs)
{
	if (rhs.myCStr != NULL) {
		reserve(mySize + rhs.mySize);
		memcpy(myCStr + mySize, rhs.myCStr, rhs.mySize + 1);
		mySize += rhs.mySize;
	}
	return *this;
}

String& String::operator+=(char* cstr)
{
	int length = strlen(cstr);
	reserve(mySize + length);
	memcpy(myCStr + mySize, cstr, length + 1); //add
	mySize += length;

	return *this;
}

//////////////////////////////////////////////////////////////
//GLOBAL

String operator+(const String& lhs, const String& rhs) {
	String tmp = String(lhs);
	tmp += rhs;

	return tmp;
}

bool operator==(const String& lhs, const String& rhs)
{
	if (lhs.mySize != rhs.mySize)
		return false;
	for (int i = 0; i < lhs.mySize; i++)
		if (lhs.myCStr[i] != rhs.myCStr[i])
			return false;
	return true;
}

std::ostream& operator<<(std::ostream& os, const String& s)
{
	std::string ss;
	for (int i = 0; i < s.mySize; i++)
		ss += s.myCStr[i];
	return os << ss;
}