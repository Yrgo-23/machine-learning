/********************************************************************************
 * @brief Implementation details for the container::Vector class.
 * 
 * @note Don't include this file directly.
 ********************************************************************************/
#pragma once 

#include "utils.h"

namespace container
{

// -----------------------------------------------------------------------------
template <typename T>
Vector<T>::Vector() = default;

// -----------------------------------------------------------------------------
template <typename T>
Vector<T>::Vector(const size_t size) { resize(size); }

// -----------------------------------------------------------------------------
template <typename T>
template <typename... Values>
Vector<T>::Vector(const Values&&... values) 
{
    const T array[sizeof...(values)]{(values)...};
    addValues(array);
}

// -----------------------------------------------------------------------------
template <typename T>
Vector<T>::Vector(const Vector<T>& source) { copy(source); }

// -----------------------------------------------------------------------------
template <typename T>
Vector<T>::Vector(Vector&& source) 
{
    myData = source.myData;
    mySize = source.mySize;
    source.myData = nullptr;
    source.mySize = 0;
}

// -----------------------------------------------------------------------------
template <typename T>
Vector<T>::~Vector() { clear(); }

// -----------------------------------------------------------------------------
template <typename T>
T& Vector<T>::operator[](const size_t index) { return myData[index]; }

// -----------------------------------------------------------------------------
template <typename T>
const T& Vector<T>::operator[](const size_t index) const { return myData[index]; }

// -----------------------------------------------------------------------------
template <typename T>
template <typename... Values>
void Vector<T>::operator=(const Values&&... values) 
{
    clear();
    copy(values...);
}

// -----------------------------------------------------------------------------
template <typename T>
void Vector<T>::operator=(const Vector<T>& source) 
{
    clear();
    copy(source);
}

// -----------------------------------------------------------------------------
template <typename T>
template <size_t NumValues>
void Vector<T>::operator+=(const T (&values)[NumValues]) { addValues(values); }

// -----------------------------------------------------------------------------
template <typename T>
void Vector<T>::operator+=(const Vector<T>& source) { addValues(source); }

// -----------------------------------------------------------------------------
template <typename T>
const T* Vector<T>::data() const { return myData; }

// -----------------------------------------------------------------------------
template <typename T>
size_t Vector<T>::size() const { return mySize; }

// -----------------------------------------------------------------------------
template <typename T>
bool Vector<T>::empty() const { return mySize == 0; }

// -----------------------------------------------------------------------------
template <typename T>
typename Vector<T>::Iterator Vector<T>::begin() { return Iterator{myData}; }

// -----------------------------------------------------------------------------
template <typename T>
typename Vector<T>::ConstIterator Vector<T>::begin() const 
{ 
    return ConstIterator{myData};
}

// -----------------------------------------------------------------------------
template <typename T>
typename Vector<T>::Iterator Vector<T>::end() 
{ 
    return Iterator{myData + mySize}; 
}

// -----------------------------------------------------------------------------
template <typename T>
typename Vector<T>::ConstIterator Vector<T>::end() const 
{ 
    return ConstIterator{myData + mySize};
}

// -----------------------------------------------------------------------------
template <typename T>
typename Vector<T>::Iterator Vector<T>::rbegin() 
{ 
    return mySize > 0 ? Iterator{myData + mySize - 1} : Iterator{nullptr}; 
}

// -----------------------------------------------------------------------------
template <typename T>
typename Vector<T>::ConstIterator Vector<T>::rbegin() const 
{ 
    return mySize > 0 ? ConstIterator{myData + mySize - 1} : ConstIterator{nullptr}; 
}

// -----------------------------------------------------------------------------
template <typename T>
typename Vector<T>::Iterator Vector<T>::rend() 
{ 
    return mySize > 0 ? Iterator{myData - 1} : Iterator{nullptr};
}

// -----------------------------------------------------------------------------
template <typename T>
typename Vector<T>::ConstIterator Vector<T>::rend() const 
{ 
    return mySize > 0 ? ConstIterator{myData - 1} : ConstIterator{nullptr};
}

// -----------------------------------------------------------------------------
template <typename T>
T* Vector<T>::last() { return mySize > 0 ? end() - 1 : nullptr; }

// -----------------------------------------------------------------------------
template <typename T>
const T* Vector<T>::last() const { return mySize > 0 ? end() - 1 : nullptr; }

// -----------------------------------------------------------------------------
template <typename T>
void Vector<T>::clear() 
{
    utils::deleteMemory<T>(myData);
    myData = nullptr;
    mySize = 0;
}

// -----------------------------------------------------------------------------
template <typename T>
bool Vector<T>::resize(const size_t newSize) 
{
    auto copy{utils::reallocMemory<T>(myData, newSize)};
    if (copy == nullptr) { return false; }
    myData = copy;
    mySize = newSize;
    return true;
}

// -----------------------------------------------------------------------------
template <typename T>
bool Vector<T>::pushBack(const T& value) 
{
    if (!resize(mySize + 1)) { return false; }
    myData[mySize - 1] = value;
    return true;
}

// -----------------------------------------------------------------------------
template <typename T>
bool Vector<T>::popBack() 
{
    if (mySize <= 1) 
    {
        clear();
        return true;
    } 
    else 
    {
        return resize(mySize - 1);
    }
}

// -----------------------------------------------------------------------------
template <typename T>
bool Vector<T>::copy(const Vector<T>& source) 
{
    if (!resize(source.mySize)) { return false; }
    assign(source);
    return true;
}

// -----------------------------------------------------------------------------
template <typename T>
void Vector<T>::assign(const Vector<T>& source, const size_t offset) 
{
    for (size_t i{}; offset + i < mySize && i < source.mySize; ++i) 
    {
        myData[offset + i] = source.myData[i];
    }
}

// -----------------------------------------------------------------------------
template <typename T>
template <size_t NumValues>
void Vector<T>::assign(const T (&values)[NumValues], const size_t offset) 
{
    for (size_t i{}; i < NumValues && offset + i < mySize; ++i) 
    {
        myData[offset + i] = values[i];
    }
}

// -----------------------------------------------------------------------------
template <typename T>
bool Vector<T>::addValues(const Vector<T>& source) 
{
    const auto offset{mySize};
    if (!resize(mySize + source.mySize)) { return false; }
    assign(source, offset);
    return true;
}

// -----------------------------------------------------------------------------
template <typename T>
template <size_t NumValues>
bool Vector<T>::addValues(const T (&values)[NumValues]) 
{
    const auto offset{mySize};
    if (!resize(mySize + NumValues)) { return false; }
    assign(values, offset);
    return true;
}

// -----------------------------------------------------------------------------
template <typename T>
Vector<T>::Iterator::Iterator() = default;

// -----------------------------------------------------------------------------
template <typename T>
Vector<T>::Iterator::Iterator(T& data) : myData{&data} {}

// -----------------------------------------------------------------------------
template <typename T>
Vector<T>::Iterator::Iterator(T* data) : myData{data} {}

// -----------------------------------------------------------------------------
template <typename T>
void Vector<T>::Iterator::operator++() { myData++; }

// -----------------------------------------------------------------------------
template <typename T>
void Vector<T>::Iterator::operator--() { myData--; }

// -----------------------------------------------------------------------------
template <typename T>
void Vector<T>::Iterator::operator++(int) { myData++; }

// -----------------------------------------------------------------------------
template <typename T>
void Vector<T>::Iterator::operator--(int) { myData--; }

// -----------------------------------------------------------------------------
template <typename T>
void Vector<T>::Iterator::operator+=(const size_t numIncrements)
{
    for (size_t i{}; i < numIncrements; ++i) { myData++; }
}

// -----------------------------------------------------------------------------
template <typename T>
void Vector<T>::Iterator::operator-=(const size_t numIncrements)
{
    for (size_t i{}; i < numIncrements; ++i) { myData--; }
}

// -----------------------------------------------------------------------------
template <typename T>
bool Vector<T>::Iterator::operator==(const Iterator& other) const
{ 
    return myData == other.myData; 
}

// -----------------------------------------------------------------------------
template <typename T>
bool Vector<T>::Iterator::operator!=(const Iterator& other) const
{ 
    return myData != other.myData; 
}

// -----------------------------------------------------------------------------
template <typename T>
bool Vector<T>::Iterator::operator>(const Iterator& other) const
{ 
    return myData > other.myData; 
}

// -----------------------------------------------------------------------------
template <typename T>
bool Vector<T>::Iterator::operator<(const Iterator& other) const
{ 
    return myData < other.myData; 
}

// -----------------------------------------------------------------------------
template <typename T>
bool Vector<T>::Iterator::operator>=(const Iterator& other) const
{ 
    return myData >= other.myData; 
}

// -----------------------------------------------------------------------------
template <typename T>
bool Vector<T>::Iterator::operator<=(const Iterator& other) const
{ 
    return myData >= other.myData; 
}

// -----------------------------------------------------------------------------
template <typename T>
T& Vector<T>::Iterator::operator*() { return *myData; }

// -----------------------------------------------------------------------------
template <typename T>
const T& Vector<T>::Iterator::operator*() const { return *myData; }

// -----------------------------------------------------------------------------
template <typename T>
T* Vector<T>::Iterator::operator=(Iterator& iterator) { return myData; }

// -----------------------------------------------------------------------------
template <typename T>
const T* Vector<T>::Iterator::operator=(Iterator& iterator) const { return myData; }

// -----------------------------------------------------------------------------
template <typename T>
Vector<T>::ConstIterator::ConstIterator() = default;

// -----------------------------------------------------------------------------
template <typename T>
Vector<T>::ConstIterator::ConstIterator(const T& data) : myData{&data} {}

// -----------------------------------------------------------------------------
template <typename T>
Vector<T>::ConstIterator::ConstIterator(const T* data) : myData{data} {}

// -----------------------------------------------------------------------------
template <typename T>
void Vector<T>::ConstIterator::operator++() { myData++; }

// -----------------------------------------------------------------------------
template <typename T>
void Vector<T>::ConstIterator::operator--() { myData--; }

// -----------------------------------------------------------------------------
template <typename T>
void Vector<T>::ConstIterator::operator++(int) { myData++; }

// -----------------------------------------------------------------------------
template <typename T>
void Vector<T>::ConstIterator::operator--(int) { myData--; }

// -----------------------------------------------------------------------------
template <typename T>
void Vector<T>::ConstIterator::operator+=(const size_t numIncrements)
{
    for (size_t i{}; i < numIncrements; ++i) { myData++; }
}

// -----------------------------------------------------------------------------
template <typename T>
void Vector<T>::ConstIterator::operator-=(const size_t numIncrements)
{
    for (size_t i{}; i < numIncrements; ++i) { myData--; }
}

// -----------------------------------------------------------------------------
template <typename T>
bool Vector<T>::ConstIterator::operator==(const ConstIterator& other) const
{ 
    return myData == other.myData; 
}

// -----------------------------------------------------------------------------
template <typename T>
bool Vector<T>::ConstIterator::operator!=(const ConstIterator& other) const
{ 
    return myData != other.myData; 
}

// -----------------------------------------------------------------------------
template <typename T>
bool Vector<T>::ConstIterator::operator>(const ConstIterator& other) const
{ 
    return myData > other.myData; 
}

// -----------------------------------------------------------------------------
template <typename T>
bool Vector<T>::ConstIterator::operator<(const ConstIterator& other) const
{ 
    return myData < other.myData; 
}

// -----------------------------------------------------------------------------
template <typename T>
bool Vector<T>::ConstIterator::operator>=(const ConstIterator& other) const
{ 
    return myData >= other.myData; 
}

// -----------------------------------------------------------------------------
template <typename T>
bool Vector<T>::ConstIterator::operator<=(const ConstIterator& other) const
{ 
    return myData >= other.myData; 
}

// -----------------------------------------------------------------------------
template <typename T>
const T& Vector<T>::ConstIterator::operator*() const { return *myData; }

// -----------------------------------------------------------------------------
template <typename T>
const T* Vector<T>::ConstIterator::operator=(ConstIterator& iterator) const 
{ 
    return myData; 
}

} // namespace container