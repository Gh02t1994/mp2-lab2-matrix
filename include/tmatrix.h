// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
      throw out_of_range("Vector size should be less than MAX_VECTOR_SIZE");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
    sz = v.sz;
    pMem = new T[sz];

    for (int i = 0; i < sz; ++i)
    {
      pMem[i] = v.pMem[i];
    }
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
    sz = v.sz;
    pMem = v.pMem;

    v.sz = 0;
    v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
    delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if (this == &v)
      return *this;
    else
    {
      sz = v.sz;
      delete[] pMem;
      pMem = new T[sz];

      for (int i = 0; i < sz; ++i)
        pMem[i] = v.pMem[i];
      
      return *this; 
    }
  }

  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    if (this != &v)
    {
      delete[] pMem;

      sz = v.sz;
      pMem = v.pMem;

      v.sz = 0;
      v.pMem = nullptr;
    }

    return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
    return pMem[ind];
  }

  const T& operator[](size_t ind) const
  {
    return pMem[ind];
  }

  // индексация с контролем
  T& at(int ind)
  {
    if (ind < 0 || ind >= sz)
        throw out_of_range("Vector index out of range");

    return pMem[ind];
  }
  const T& at(int ind) const
  {
    if (ind < 0 || ind >= sz)
        throw out_of_range("Vector index out of range");

    return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
    if (sz != v.sz)
      return false;
    else
    {
      for (int i = 0; i < sz; ++i)
        if (pMem[i] != v[i])
          return false;
    }

    return true;
  }

  bool operator!=(const TDynamicVector& v) const noexcept
  {
    return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
    TDynamicVector tmp(*this);

    for (int i = 0; i < sz; ++i)
    {
      tmp.pMem[i] += val;
    }

    return tmp;
  }
  TDynamicVector operator-(T val)
  {
    TDynamicVector tmp(*this);

    for (int i = 0; i < sz; ++i)
    {
      tmp.pMem[i] -= val;
    }

    return tmp;
  }
  TDynamicVector operator*(T val)
  {
    TDynamicVector tmp(*this);

    for (int i = 0; i < sz; ++i)
    {
      tmp.pMem[i] *= val;
    }

    return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if (sz != v.sz)
      throw invalid_argument("Different sizes");
    
      TDynamicVector tmp(sz);

      for (int i = 0; i < sz; ++i)
      {
        tmp.pMem[i] = pMem[i] + v.pMem[i]; 
      }

      return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
    if (sz != v.sz)
      throw invalid_argument("Different sizes");
    
      TDynamicVector tmp(sz);

      for (int i = 0; i < sz; ++i)
      {
        tmp.pMem[i] = pMem[i] - v.pMem[i]; 
      }

      return tmp;
  }
  T operator*(const TDynamicVector& v)
  {
    if (sz != v.sz)
      throw invalid_argument("Different sizes");
    
      T res = 0; // res{};

      for (int i = 0; i < sz; ++i)
      {
        res += pMem[i] * v.pMem[i]; 
      }

      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (sz == 0)
      throw out_of_range("Matrix size cant be less then zero");
    if (sz > MAX_MATRIX_SIZE)
      throw out_of_range("Matrix size cant be greater then MAX_MATRIX_SIZE");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::at;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
    if (this == &m)
      return true;
    
    if (sz != m.sz)
      return false;
    
    for (int i = 0; i < sz; i++)
      for (int j = 0; j < sz; j++)
        if (pMem[i][j] != m.pMem[i][j])
          return false;

    return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
    TDynamicMatrix<T> tmp(*this);

    for (int i = 0; i < sz; ++i)
    {
      tmp.pMem[i] = pMem[i] * val; 
    }

    return tmp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    if (sz != v.sz())
        throw invalid_argument("Different sizes");

    TDynamicVector<T> tmp(sz);

    for (int i = 0; i < sz; i++)
     tmp[i] = pMem[i] * v;

    return tmp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    if (sz != m.sz)
        throw invalid_argument("Different sizes");

    TDynamicMatrix tmp(sz);

    for (int i = 0; i < sz; ++i)
      tmp.pMem[i] = pMem[i] + m.pMem[i];

    return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    if (sz != m.sz)
        throw invalid_argument("Different sizes");

    TDynamicMatrix tmp(sz);

    for (int i = 0; i < sz; ++i)
      tmp.pMem[i] = pMem[i] - m.pMem[i];

    return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    if (sz != m.sz)
        throw invalid_argument("Different sizes");

    TDynamicMatrix tmp(sz);
    T sum;

    for (int i = 0; i < sz; ++i)
      for (int j = 0; j < sz; ++j)
      {
        sum = 0;

        for (int k = 0; k < sz; k++)
          sum += pMem[i][k] * m[k][j];
        
        tmp[i][j] = sum;
      }

    return tmp;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& m)
  {
    for (int i = 0; i < m.sz; i++)
      for (int j = 0; j < m.sz; j++)
        istr >> m.pMem[i][j];
      
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
  {
    for (int i = 0; i < m.sz; i++)
    {
      for (int j = 0; j < m.sz; j++)
        ostr << m.pMem[i][j] << ' ';
      ostr << '\n';
    }
      
    return ostr;
  }
};

#endif
