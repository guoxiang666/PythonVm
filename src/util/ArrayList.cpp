#include "ArrayList.hpp"
#include <cstdio>
#include <exception>

template<typename T>
ArrayList<T>::ArrayList(int initial_cap)
{
    if (initial_cap <= 0) {
      initial_cap = 16;
    }
    this->m_capacity = initial_cap;
    this->m_size = 0;
    this->m_data = new T[initial_cap];
}

// Copy constructor implementation.
template<typename T>
ArrayList<T>::ArrayList(const ArrayList& rhs)
{

}

// Operator= implementation.
template<typename T>
ArrayList& ArrayList<T>::operator=(const ArrayList& rhs)
{

}

// Returns a Reference instead of a Copy to the element at position n in the vector container.
// so we can have the usage like: list[0] = 3
// like std::vector, the operator[] wont do the range check.
template<typename T>
T& ArrayList<T>::operator[](int index)
{

}

template<typename T>
void ArrayList<T>::add(T t)
{
    if(this->m_size >= m_capacity) {
        this->expandCapacity();
    }
    this->m_data[m_size++] = t;
}

template<typename T>
void ArrayList<T>::insert(int index, T t)
{
    if (this->m_size >= this->m_capacity) {
      this->expandCapacity();
    }
    for(int i = this->m_size; i > index; i--)
    {
      m_data[i] = m_data[i-1];
    }
    m_data[index] = t;
}

// Range checked
template<typename T>
T ArrayList<T>::get(int index)
{
  if (index >= m_size) {
      throw std::out_of_range();
  }
  return m_data[index];
}

// TODO
template<typename T>
void ArrayList<T>::set(int index, T t)
{
    while(index >= (this->m_size-1)) {
      this->expandCapacity();
    }
    this->m_data[index] = t;
}

template<typename T>
void ArrayList<T>::expandCapacity()
{
    T *new_space = new T[m_capacity << 1]; // capacity expands to 2 times.
    for (size_t i = 0; i < m_capacity; i++) {
        new_space[i] = m_data[i];
    }
    delete[] m_data;
    m_data = new_space;
    m_capacity <<= 1;
}

template<typename T>
int ArrayList<T>::size()
{
    return this->m_size;
}
template<typename T>
int ArrayList<T>::capacity()
{
   return this->m_capacity;
}
template<typename T>
T ArrayList<T>::pop()
{
    return m_data[--m_size];
}
template<typename T>
bool ArrayList<T>::isEmpty()
{
    return this->m_size == 0;
}
