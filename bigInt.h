#pragma once
#include <iostream>
#include "IbigInt.h"
typedef unsigned int digit;
typedef long long int longDigit;
typedef unsigned long long int unsLongDigit;

#define BASE 4294967296 // 2^32

//#define forVS // если компилируется в Visual Studio
#define forGCC

#define MAX_10_LEN 2000000	// ограничение на максимальное число разрядов 10-ричного числа 
							// (вызвано ограничением new для строки, в которую будет записано число

#define DIVISION_BY_ZERO 1

class bigInt : public IbigInt
{
public:
	bigInt();
	bigInt(const char* string);
	bigInt(const bigInt &rhv);
	bigInt(long long int value);
	virtual ~bigInt();
	virtual void release();

	static bigInt* CreateInstance()
	{
		return new bigInt;
	}

	static bigInt* CreateInstanceString(const char* string)
	{
		return new bigInt(string);
	}

	static bigInt* CreateInstanceVal(long long int val)
	{
		return new bigInt(val);
	}

	char* getString();
	bool getFromTextFile(const char* filename);
	bool saveToTextFile(const char* filename);
	bool saveToBinFile(const char* filename);
	bool getFromBinFile(const char* filename);


	bigInt& operator=(const bigInt& rhv);
	bigInt& operator=(const longDigit value);

	bigInt operator+(const bigInt& right) const;

	bigInt operator-() const;
	bigInt operator-(const bigInt& right) const;
	bigInt operator*(const bigInt& right) const;
	bigInt operator/(const bigInt& right) const;
	bigInt operator%(const bigInt& right) const;
	bigInt operator^(const bigInt& right) const;

	bigInt operator+=(const bigInt& right);
	bigInt operator-=(const bigInt& right);
	bigInt operator*=(const bigInt& right);
	bigInt operator/=(const bigInt& right);
	bigInt operator%=(const bigInt& right);

	bigInt* operator++();
	bigInt operator++(int);
	bigInt operator--();
	bigInt operator--(int);
	
	bool operator>(const bigInt& B);
	bool operator>=(const bigInt& B);
	bool operator<(const bigInt& B);
	bool operator<=(const bigInt& B);
	bool operator==(const bigInt& B);
	bool operator!=(const bigInt& B);

	friend std::ostream& operator<<(std::ostream &out, bigInt A);
	friend std::istream& operator>>(std::istream &is, bigInt &A);


private:
	// можно было бы взять unsigned long long int для _size
	// но у оператора new есть ограничение на максимальный размер массива 0x7fffffff байт. 
	// Так что это, по сути, и ограничивает максимальную длинну числа
	int _size;
	digit* _digits;
	int _sign;

	char* _viewNumber();
	void _setSize(int size);
	digit & operator[](int i);
	digit operator[](int i) const;
	void _copy(const bigInt &rhv);
	void _delLeadZeros();
	longDigit _cmp(const bigInt& B);
	void _shiftLeft(int s);

	friend const bigInt _simpleSum(const bigInt& left, const bigInt& right);
	friend const bigInt _simpleMul(const bigInt& A, const bigInt& B);
	friend const bigInt _divividing(const bigInt& A, const bigInt& B, bigInt &remainder);
	friend const bigInt _divColumn(const bigInt& A, const bigInt& B, bigInt &remainder);
	friend const bigInt _divBinSearch(const bigInt& A, const bigInt& B, bigInt &remainder);
};
const bigInt _simpleSum(const bigInt& left, const bigInt& right);
const bigInt _simpleMul(const bigInt& A, const bigInt& B);
const bigInt _divividing(const bigInt& A, const bigInt& B, bigInt &remainder);
const bigInt _divColumn(const bigInt& A, const bigInt& B, bigInt &remainder);
const bigInt _divBinSearch(const bigInt& A, const bigInt& B, bigInt &remainder);

const bigInt pow(const bigInt& A, const bigInt& B, bigInt& modulus);



extern "C" IbigInt* CreatebigInt();
extern "C" IbigInt* CreatebigIntString(const char* string);
extern "C" IbigInt* CreatebigIntVal(long long int value);

IbigInt* CreatebigInt()
{
	return bigInt::CreateInstance();
}

IbigInt* CreatebigIntString(const char* string)
{
	return bigInt::CreateInstanceString(string);
}

IbigInt* CreatebigIntVal(long long int value)
{
	return bigInt::CreateInstanceVal(value);
}
