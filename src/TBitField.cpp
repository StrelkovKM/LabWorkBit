#include "TBitField.h"
#include <cmath>

#define ERROR(err,...) throw TError(err, __func__, __FILE__, __LINE__)

constexpr int SIZE_TELEM_BIT = 8 * sizeof(TELEM);

TBitField::TBitField()
{
	bitLen = 0;
	pMem = nullptr;
	memLen = 0;
}

TBitField::TBitField(int len)
{
	if (len > 0)
	{
		bitLen = len;
		memLen = ceil((double)len / sizeof(TELEM));
		pMem = new TELEM[memLen]{ 0 };
	}
	else if (len == 0)
	{
		bitLen = 0;
		memLen = 0;
		pMem = nullptr;
	}
	else ERROR("Error_size");
}

TBitField::TBitField(const TBitField& obj) // конструктор копирования
{
	if (obj.pMem)
	{
		bitLen = obj.bitLen;
		memLen = obj.memLen;
		pMem = new TELEM[memLen];
		for (int i = 0; i < memLen; ++i)
			pMem[i] = obj.pMem[i];
	}
	else
	{
		bitLen = 0;
		memLen = 0;
		pMem = nullptr;
	}
}

TBitField::~TBitField()
{
	if (pMem)
	{
		delete[] pMem;
		pMem = nullptr;
		bitLen = 0;
		memLen = 0;
	}
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n > -1 && n < bitLen) return (n / SIZE_TELEM_BIT);
	else ERROR("Error_size");
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n > -1 && n < bitLen) return static_cast<TELEM>(1) << (n % SIZE_TELEM_BIT);
	else ERROR("Error_size");
}

TBitField::TBitField(TBitField&& obj) noexcept
{
	bitLen = obj.bitLen;
	memLen = obj.memLen;
	pMem = obj.pMem;
	obj.pMem = nullptr;
	obj.bitLen = 0;
	obj.memLen = 0;
}

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return bitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n > -1 && n < bitLen) pMem[GetMemIndex(n)] |= GetMemMask(n);
	else ERROR("Error_size");
}

void TBitField::ClrBit(const int n)
{
	if (n < 0 || n >= bitLen)
		ERROR("Error_size");
	int index = GetMemIndex(n);
	TELEM mask = ~GetMemMask(n);
	pMem[index] &= mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n > -1 && n < bitLen) return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
	else ERROR("Error_size");
}

TBitField& TBitField::operator=(const TBitField& obj) // присваивание
{
	if (*this != obj)
	{
		if (obj.pMem)
		{
			bitLen = obj.bitLen;
			memLen = obj.memLen;
			pMem = new TELEM[memLen];
			for (int i = 0; i < memLen; ++i)
				pMem[i] = obj.pMem[i];
		}
		else
		{
			bitLen = 0;
			memLen = 0;
			pMem = nullptr;
		}
		return *this;
	}
}

bool TBitField::operator==(const TBitField& obj) const
{
	if (bitLen != obj.bitLen) return false;

	for (int i = 0; i < bitLen; ++i)
		if (this->GetBit(i) != obj.GetBit(i)) return false;

	return true;
}

bool TBitField::operator!=(const TBitField& obj) const
{
	if (bitLen != obj.bitLen) return true;

	for (int i = 0; i < bitLen; ++i)
		if (this->GetBit(i) != obj.GetBit(i)) return true;

	return false;
}

TBitField& TBitField::operator=(TBitField&& obj) noexcept
{
	if (*this != obj)
	{
		bitLen = obj.bitLen;
		memLen = obj.memLen;
		pMem = obj.pMem;
		obj.pMem = nullptr;
		obj.bitLen = 0;
		obj.memLen = 0;
		return *this;
	}
}

TBitField TBitField::operator|(const TBitField& obj) // операция "или"
{
	if (!obj.pMem || !pMem) ERROR("Error_size");
	else
	{
		TBitField res((bitLen > obj.bitLen) ? bitLen : obj.bitLen);
		for (int i = 0; i < ((memLen < obj.memLen) ? memLen : obj.memLen); ++i)
			res.pMem[i] = pMem[i] | obj.pMem[i];
		if (memLen > obj.memLen)
			for (int i = obj.memLen + 1; i < res.memLen; ++i)
				res.pMem[i] = pMem[i];
		else
			for (int i = memLen + 1; i < res.memLen; ++i)
				res.pMem[i] = obj.pMem[i];

		return TBitField(res);
	}
}

TBitField TBitField::operator&(const TBitField& obj) // операция "и"
{
	if (!obj.pMem || !pMem) ERROR("Error_size");
	else
	{
		TBitField res((bitLen > obj.bitLen) ? bitLen : obj.bitLen);
		for (int i = 0; i < res.memLen; i++)
			res.pMem[i] = pMem[i] & obj.pMem[i];
		return res;
	}
}

TBitField TBitField::operator~()
{
	if (!pMem)
		ERROR("lg == nullptr");
	TBitField res(bitLen);
	for (int i = 0; i < memLen; ++i)
		res.pMem[i] = ~pMem[i];
	TELEM mask = (static_cast<TELEM>(1) << (bitLen % SIZE_TELEM_BIT)) - 1;
	res.pMem[memLen - 1] &= mask;
	return TBitField(res);
}

istream& operator>>(istream& instr, TBitField& obj)
{
	int len;
	cout << "Enter count of bits: "; instr >> len;
	TBitField res(len);
	cout << "Enter bits: \n";
	for (int i = 0; i < len; ++i)
	{
		char c;
		instr >> c;
		if (c == '1')
			res.SetBit(len-i-1);
	}
	obj = move(res);
	return instr;
}

ostream& operator<<(std::ostream& ostr, const TBitField& obj)
{
	ostr << "bitLen: " << obj.bitLen << '\n'
		<< "memLen: " << obj.memLen << '\n'
		<< "Field: " << '\n';
	for (int i = obj.GetLength(); i >= 0; i--)
		ostr << obj.GetBit(i);
	ostr << '\n';
	return ostr;
}

ostream& operator<<(std::ostream& ostr, TBitField& obj)
{
	ostr << "bitLen: " << obj.bitLen << '\n'
		<< "memLen: " << obj.memLen << '\n'
		<< "Field: " << '\n';
	for (int i = obj.GetLength()-1; i >= 0; i--)
		ostr << obj.GetBit(i);
	ostr << '\n';
	return ostr;
}