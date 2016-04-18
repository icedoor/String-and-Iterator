#pragma once
#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

typedef char value_type;

////////////////////////////////////////////////////////////////////////////
//ITERATOR//
class Iterator
{
protected:
	value_type * myData;
public:
	Iterator() :myData(nullptr) {}

	Iterator(const Iterator& rhs) :myData(rhs.myData) {}

	Iterator(value_type* data) :myData(data) {}

	~Iterator() {}

	//=
	Iterator& operator=(const Iterator& rhs) = default;

	//*
	value_type& Iterator::operator*() const {
		return *myData;
	}

	//++
	Iterator& operator++() { //++x
		++myData;
		return *this;
	}

	Iterator operator++(const int i) { //x++
		Iterator cpy = *this;
		++myData;
		return cpy; //return as before increment
	}

	//+
	Iterator& operator+(const int i) const {
		return Iterator(myData + i);
	}

	//[]
	value_type& operator[](const int i)	const {
		return *Iterator(myData + i);
	}

	friend const bool operator==(const Iterator& lhs, const Iterator& rhs)  {
		return (lhs.myData == rhs.myData);
	}
	friend const bool operator!=(const Iterator& lhs, const Iterator& rhs)  {
		return (lhs.myData != rhs.myData);
	}
};

////////////////////////////////////////////////////////////////////////////
//REVERSE//
class ReverseIterator : public Iterator
{
public:
	ReverseIterator():Iterator(){}
	ReverseIterator(value_type* data) :Iterator(data) {}
	ReverseIterator(const ReverseIterator& rhs) :Iterator(rhs) {}

	~ReverseIterator() {}

	//+
	ReverseIterator& operator+(const int i) const {
		return ReverseIterator(myData - i);
	}
	//++
	ReverseIterator& operator++() { //++x
		--myData;
		return *this;
	}
	ReverseIterator operator++(const int i) { //x++
		ReverseIterator cpy = *this;
		--myData;
		return cpy; //return as before increment
	}
	//[]
	value_type& operator[](const int i) const {
		return *Iterator(myData - i);
	}
};

////////////////////////////////////////////////////////////////////////////
//CONST ITERATOR//
class ConstIterator : public Iterator
{
public:
	ConstIterator() :Iterator() {}
	ConstIterator(value_type* data) :Iterator(data) {}
	ConstIterator(const ConstIterator& rhs) :Iterator(rhs) {}

	~ConstIterator() {}

	//=
	ConstIterator operator=(const ConstIterator& rhs) {
		if (this != &rhs)
			myData = rhs.myData;
		ConstIterator tmp = *this;
		return tmp;
	}
	//*
	const value_type& operator*() const {
		return *myData;
	}

	//[]
	const value_type& operator[](const int i) const{
		return *Iterator(myData + i);
	}
};

////////////////////////////////////////////////////////////////////////////
//CONST REVERSE//
class ConstReverseIterator : public ReverseIterator
{
public:
	ConstReverseIterator() :ReverseIterator() {}
	ConstReverseIterator(value_type* data) :ReverseIterator(data) {}
	ConstReverseIterator(const ReverseIterator& rhs) :ReverseIterator(rhs) {}

	~ConstReverseIterator() {}

	//=
	ConstReverseIterator operator=(const ConstReverseIterator& rhs) {
		if (this != &rhs)
			myData = rhs.myData;
		ConstReverseIterator tmp = *this;
		return tmp;
	}
	//*
	const value_type& operator*() const {
		return *myData;
	}
};