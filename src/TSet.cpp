
#include "TSet.h"
#include <vector>
#include "TError.h"

#define ERROR(err,...) throw TError(err, __func__, __FILE__, __LINE__)

TSet::TSet(int mp) : bitField(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : bitField( s.bitField )
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf)
{
  this->bitField = bf;
}

TSet::operator TBitField()
{
  return this->bitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return this->bitField.GetLength();
}

int TSet::IsMember(const int index) const // элемент множества?
{
  return this->bitField.GetBit(index);
}

void TSet::InsElem(const int index) // включение элемента множества
{
  this->bitField.SetBit(index);
}

void TSet::DelElem(const int index) // исключение элемента множества
{
  this->bitField.ClrBit(index);
}

// теоретико-множественные операции

TSet& TSet::operator= (const TSet &s) // присваивание
{
  this->bitField = s.bitField;
  return *this;
}

bool TSet::operator== (const TSet &s) const // сравнение
{
  return this->bitField == s.bitField;
}

bool TSet::operator!= (const TSet &s) const // сравнение
{
  return this->bitField != s.bitField;
}

TSet TSet::operator+ (const TSet &s) // объединение
{
  TSet res(0);
  res.bitField = this->bitField | s.bitField;
  return res;
}

TSet TSet::operator+ (const int Elem) // объединение с элементом
{ 
  TSet res(*this);
  res.InsElem(Elem);
  return res;
}

TSet TSet::operator- (const int Elem) // разность с элементом
{
  TSet res(*this);
  res.DelElem(Elem);
  return res;
}

TSet TSet::operator* (const TSet &s) // пересечение
{
  TSet res(0);
  res.bitField = this->bitField & s.bitField;
  return res;
}

TSet TSet::operator~ (void) // дополнение
{
  TSet res(0);
  res.bitField = ~this->bitField;
  return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
  int capacity{}, i{};
  cout << "Enter capacity of set: "; istr >> capacity;

  if (capacity > -1)
  {
    TBitField res(capacity);
    s.bitField = res;

    cout << "Enter elements which are in the set (to stop, enter -1 or last element): ";
    istr >> i;
    while (i > -1 && i < s.GetMaxPower())
    {
      s.InsElem(s.GetMaxPower() - i - 1);
      istr >> i;
    }

    return istr;
  }
  else ERROR("Error_size");
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
  ostr << "{ ";

  for (int i = 0; i < s.GetMaxPower(); ++i)
    if (s.IsMember(s.GetMaxPower()-i-1)) ostr << i << " ";

  ostr << "}";

  return ostr;
}
