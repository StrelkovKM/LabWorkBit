
#include "TBitField.h"

class TSet
{
private:
  TBitField bitField; // битовое поле для хранения характеристического вектора
public:
  TSet(int capacity);
  TSet(const TSet &other);       // конструктор копирования
  TSet(const TBitField &bf); // конструктор преобразования типа
  operator TBitField();      // преобразование типа к битовому полю

  // доступ к битам
  int GetMaxPower(void) const;     // максимальная мощность множества
  void InsElem(const int index);       // включить элемент в множество
  void DelElem(const int index);       // удалить элемент из множества
  int IsMember(const int index) const; // проверить наличие элемента в множестве

  // теоретико-множественные операции
  bool operator== (const TSet &s) const; // сравнение
  bool operator!= (const TSet &s) const; // сравнение
  TSet& operator=(const TSet &s);  // присваивание
  TSet operator+ (const int Elem); // объединение с элементом
                                   // элемент должен быть из того же универса
  TSet operator- (const int Elem); // разность с элементом
                                   // элемент должен быть из того же универса
  TSet operator+ (const TSet &s);  // объединение
  TSet operator* (const TSet &s);  // пересечение
  TSet operator~ (void);           // дополнение

  friend istream &operator>>(istream &istr, TSet &bf);
  friend ostream &operator<<(ostream &ostr, const TSet &bf);
};