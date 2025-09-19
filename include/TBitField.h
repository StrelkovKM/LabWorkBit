#pragma once
#include <iostream>
#include "TError.h"

typedef unsigned int TELEM;

class TBitField {
private:
	int bitLen;
	TELEM* pMem;
	int memLen;

	int GetMemIndex(const int n) const;
	TELEM GetMemMask(const int n) const;

public:
	TBitField();
	TBitField(int len);
	TBitField(const TBitField& obj);
	TBitField(TBitField&& obj) noexcept;
	~TBitField();

	int GetLength() const;
	void SetBit(const int n);
	void ClrBit(const int n);
	int GetBit(const int n) const;

	bool operator==(const TBitField& obj) const;
	bool operator!=(const TBitField& obj) const;
	TBitField& operator=(const TBitField& obj);
	TBitField& operator=(TBitField&& obj) noexcept;
	TBitField operator|(const TBitField& obj);
	TBitField operator&(const TBitField& obj);
	TBitField operator~();

	friend std::istream& operator>> (std::istream& in, TBitField&bf);
	friend std::ostream& operator<< (std::ostream& out, TBitField& bf);
	friend std::ostream& operator<<(std::ostream& out, const TBitField& bf);
};