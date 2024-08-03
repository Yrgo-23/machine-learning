/********************************************************************************
 * @brief Implementation of static arrays of any data type.
 ********************************************************************************/
#pragma once

#include <stddef.h>

namespace container 
{
/********************************************************************************
 * @brief Class for implementation of static arrays.
 * 
 * @tparam T    The array type.
 * @tparam Size The array size.
 * 
 * @note The array size must exceed 0, else a compilation error will be generated.
 ********************************************************************************/
template <typename T, size_t Size>
class Array 
{
public:
    class Iterator;
    class ConstIterator;

    /********************************************************************************
     * @brief Creates empty array of specified size.
     ********************************************************************************/
    Array();

    /********************************************************************************
     * @brief Creates array containing referenced values.
     *
     * @tparam Values Parameter pack holding values.
     * 
     * @param values Reference to values to store in the newly created array.
     ********************************************************************************/
    template <typename... Values>
    Array(const Values&&... values);

    /********************************************************************************
     * @brief Creates array containing referenced values.
     *
     * @param values Reference to values to store in the newly created array.
     ********************************************************************************/
    Array(const T (&values)[Size]);

    /********************************************************************************
     * @brief Creates array as a copy of referenced source.
     *
     * @tparam NumValues The number of values in the source array.
     * 
     * @param source Reference to array whose content is copied to the new array.
     ********************************************************************************/
    template <size_t NumValues>
    Array(const Array<T, NumValues>& source);

    /********************************************************************************
     * @brief Deletes array.
     ********************************************************************************/
    ~Array();

    /********************************************************************************
     * @brief Returns reference to the element at specified index in the array.
     *
     * @param index Index of the requested element.
     * 
     * @return A reference to the element at specified index.
     ********************************************************************************/
    T& operator[](const size_t index);

    /********************************************************************************
     * @brief Returns reference to the element at specified index in the array.
     *
     * @param index Index of the requested element.
     * 
     * @return A reference to the element at specified index.
     ********************************************************************************/
    const T& operator[](const size_t index) const;

     /********************************************************************************
     * @brief Copies referenced values to assigned array. 
     *
     * @tparam NumValues The number of values to copy.
     * 
     * @param values Reference to array holding the values to copy.
     * 
     * @return A reference to the assigned array.     
     ********************************************************************************/
    template <size_t NumValues>
    Array& operator=(const T (&values)[NumValues]);

    /********************************************************************************
     * @brief Copies the content of referenced array to assigned array. 
     *
     * @tparam NumValues The number of values in the source array.
     * 
     * @param source Reference to array holding the values to copy.
     * 
     * @return A reference to the assigned array.     
     ********************************************************************************/
    template <size_t NumValues>
    Array& operator=(const Array<T, NumValues>& source);

    /********************************************************************************
     * @brief Adds values to the back of assigned array.
     *
     * @tparam NumValues The number of values to copy.
     * 
     * @param values Reference to array holding the values to copy.
     * 
     * @return A reference to the assigned array.     
     ********************************************************************************/
    template <size_t NumValues>
    Array& operator+=(const T (&values)[NumValues]);

    /********************************************************************************
     * @brief Adds values from referenced array to the back of assigned array.
     *
     * @tparam NumValues The number of values in the source array.
     * 
     * @param source Reference to array containing the the values to add.
     * 
     * @return A reference to assigned array.     
     ********************************************************************************/
    template <size_t NumValues>
    Array& operator+=(const Array<T, NumValues>& source);

    /********************************************************************************
     * @brief Provides the data held by the array.
     *
     * @return Pointer to the start address of the array.
     ********************************************************************************/
    T* data();

    /********************************************************************************
     * @brief Provides the data held by the array.
     *
     * @return Pointer to the start address of the array.
     ********************************************************************************/
    T* data() const;

    /********************************************************************************
     * @brief Returns the size of the array in the number of elements it can hold.
     *
     * @return The size of the array as an unsigned integer.
     ********************************************************************************/
    size_t size() const;

     /********************************************************************************
     * @brief Provides the start address of the vector.
     *
     * @return Iterator pointing at the start address of the the vector.
     ********************************************************************************/
    Iterator begin();

    /********************************************************************************
     * @brief Provides the start address of the vector.
     *
     * @return Iterator pointing at the start address of the the vector.
     ********************************************************************************/
    ConstIterator begin() const;

    /********************************************************************************
     * @brief Provides the end address of the vector.
     *
     * @return Iterator pointing at the end address of the the vector.
     ********************************************************************************/
    Iterator end();

    /********************************************************************************
     * @brief Provides the end address of the vector.
     *
     * @return Iterator pointing at the end address of the the vector.
     ********************************************************************************/
    ConstIterator end() const;

    /********************************************************************************
     * @brief Provides the reverse start address of the the vector.
     *
     * @return Iterator pointing at the reverse start address of the the vector.
     ********************************************************************************/
    Iterator rbegin();

    /********************************************************************************
     * @brief Provides the reverse start address of the the vector.
     *
     * @return Iterator pointing at the reverse start address of the the vector.
     ********************************************************************************/
    ConstIterator rbegin() const;

    /********************************************************************************
     * @brief Provides the reverse end address of the the vector.
     *
     * @return Iterator pointing at the reverse end address of the the vector.
     ********************************************************************************/
    Iterator rend();

    /********************************************************************************
     * @brief Provides the reverse end address of the the vector.
     *
     * @return Iterator pointing at the reverse end address of the the vector.
     ********************************************************************************/
    ConstIterator rend() const;

    /********************************************************************************
     * @brief Clears array content.
     ********************************************************************************/
    void clear();

protected:
    static_assert(Size > 0, "Static array size cannot be set to 0!");
    template <size_t NumValues>
    void copy(const T (&values)[NumValues], const size_t offset = 0);
    template <size_t NumValues>
    void copy(const Array<T, NumValues>& source, const size_t offset = 0);

    T myData[Size]{}; 
};

/********************************************************************************
 * @brief Implementation of mutable array iterators.
 *
 * @tparam T    The data type of the array.
 * @tparam Size The array size.
 *  
 * @note The array size must exceed 0, else a compilation error will be generated.
 ********************************************************************************/
template <typename T, size_t Size>
class Array<T, Size>::Iterator
{
public:
    /********************************************************************************
     * @brief Creates empty iterator.
     ********************************************************************************/
    Iterator();

    /********************************************************************************
     * @brief Creates iterator pointing at referenced data.
     *
     * @param data Reference to data the iterator is set to point at.
     ********************************************************************************/
    Iterator(T& data);

    /********************************************************************************
     * @brief Creates iterator pointing at referenced data.
     *
     * @param data Reference to data the iterator is set to point at.
     ********************************************************************************/
    Iterator(T* data);

    /********************************************************************************
     * @brief Increments the address the iterator is pointing at (prefix operator).
     ********************************************************************************/
    void operator++();

    /********************************************************************************
     * @brief Decrements the address the iterator is pointing at (prefix operator).
     ********************************************************************************/
    void operator--();

    /********************************************************************************
     * @brief Increments the address the iterator is pointing at (postfix operator).
     ********************************************************************************/
    void operator++(int);

    /********************************************************************************
     * @brief Decrements the address the iterator is pointing at (postfix operator).
     ********************************************************************************/
    void operator--(int);

    /********************************************************************************
     * @brief Increments the iterator specified number of times.
     *
     * @param numIncrements The number of times the iterator will be incremented.
     ********************************************************************************/
    void operator+=(const size_t numIncrements);

    /********************************************************************************
     * @brief Decrements the iterator specified number of times.
     *
     * @param numIncrements The number of times the iterator will be decremented.
     ********************************************************************************/
    void operator-=(const size_t numIncrements);

    /********************************************************************************
     * @brief Indicates if the iterator and referenced other iterator point at the
     *        same address.
     *
     * @param other Reference to other iterator.
     * 
     * @return True if the iterators point at the same address, else false.
     ********************************************************************************/
    bool operator==(const Iterator& other) const;

    /********************************************************************************
     * @brief Indicates if the iterator and referenced other iterator point at
     *        different addresses.
     *
     * @param other Reference to other iterator.
     * 
     * @return True if the iterators point at the different addresses, else false.
     ********************************************************************************/
    bool operator!=(const Iterator& other) const;

    /********************************************************************************
     * @brief Indicates if the iterator points at an address that's higher than
     *        the address pointed to by referenced other iterator.
     *
     * @param other Reference to other iterator.
     * 
     * @return True if iterator points at an address that's higher than the address
     *         pointed to by referenced other iterator, else false.
     ********************************************************************************/
    bool operator>(const Iterator& other) const;

    /********************************************************************************
     * @brief Indicates if the iterator points at an address that's lower than
     *        the address pointed to by referenced other iterator.
     *
     * @param other Reference to other iterator.
     * 
     * @return True if iterator points at an address that's lower than the address
     *         pointed to by referenced other iterator, else false.
     ********************************************************************************/
    bool operator<(const Iterator& other) const;

    /********************************************************************************
     * @brief Indicates if the iterator points at an address that's higher or equal
     *        to the address pointed to by referenced other iterator.
     *
     * @param other Reference to other iterator.
     * 
     * @return True if iterator points at an address that's higher or equal to the
     *         address pointed to by referenced other iterator, else false.
     ********************************************************************************/
    bool operator>=(const Iterator& other) const;

    /********************************************************************************
     * @brief Indicates if the iterator points at an address that's lower or equal
     *        to the address pointed to by referenced other iterator.
     *
     * @param other Reference to other iterator.
     * 
     * @return True if iterator points at an address that's lower or equal to the
     *         address pointed to by referenced other iterator, else false.
     ********************************************************************************/
    bool operator<=(const Iterator& other) const;

    /********************************************************************************
     * @brief Provides the value stored at the address the iterator is pointing at.
     *
     * @return Reference to the value at the address the iterator is pointing at.
     ********************************************************************************/
    T& operator*();

    /********************************************************************************
     * @brief Provides the value stored at the address the iterator is pointing at.
     *
     * @return Reference to the value at the address the iterator is pointing at.
     ********************************************************************************/
    const T& operator*() const;

    /********************************************************************************
     * @brief Provides the address the iterator is pointing at.
     *
     * @return A pointer to the address the iterator is pointing at.
     ********************************************************************************/
    T* operator=(Iterator& iterator);

    /********************************************************************************
     * @brief Provides the address the iterator is pointing at.
     *
     * @return A pointer to the address the iterator is pointing at.
     ********************************************************************************/
    const T* operator=(Iterator& iterator) const;

private:
    static_assert(Size > 0, "Static array size cannot be set to 0!");
    T* myData{nullptr};
};

/********************************************************************************
 * @brief Implementation of constant array iterators.
 *
 * @tparam T    The data type of the array.
 * @tparam Size The array size.
 *  
 * @note The array size must exceed 0, else a compilation error will be generated.
 ********************************************************************************/
template <typename T, size_t Size>
class Array<T, Size>::ConstIterator
{
public:
    /********************************************************************************
     * @brief Creates empty iterator.
     ********************************************************************************/
    ConstIterator();

    /********************************************************************************
     * @brief Creates iterator pointing at referenced data.
     *
     * @param data Reference to data the iterator is set to point at.
     ********************************************************************************/
    ConstIterator(const T& data);

    /********************************************************************************
     * @brief Creates iterator pointing at referenced data.
     *
     * @param data Reference to data the iterator is set to point at.
     ********************************************************************************/
    ConstIterator(const T* data);

    /********************************************************************************
     * @brief Increments the address the iterator is pointing at (prefix operator).
     ********************************************************************************/
    void operator++();

    /********************************************************************************
     * @brief Decrements the address the iterator is pointing at (prefix operator).
     ********************************************************************************/
    void operator--();

    /********************************************************************************
     * @brief Increments the address the iterator is pointing at (postfix operator).
     ********************************************************************************/
    void operator++(int);

    /********************************************************************************
     * @brief Decrements the address the iterator is pointing at (postfix operator).
     ********************************************************************************/
    void operator--(int);

    /********************************************************************************
     * @brief Increments the iterator specified number of times.
     *
     * @param numIncrements The number of times the iterator will be incremented.
     ********************************************************************************/
    void operator+=(const size_t numIncrements);

    /********************************************************************************
     * @brief Decrements the iterator specified number of times.
     *
     * @param numIncrements The number of times the iterator will be decremented.
     ********************************************************************************/
    void operator-=(const size_t numIncrements);

    /********************************************************************************
     * @brief Indicates if the iterator and referenced other iterator point at the
     *        same address.
     *
     * @param other Reference to other iterator.
     * 
     * @return True if the iterators point at the same address, else false.
     ********************************************************************************/
    bool operator==(const ConstIterator& other) const;

    /********************************************************************************
     * @brief Indicates if the iterator and referenced other iterator point at
     *        different addresses.
     *
     * @param other Reference to other iterator.
     * 
     * @return True if the iterators point at the different addresses, else false.
     ********************************************************************************/
    bool operator!=(const ConstIterator& other) const;

    /********************************************************************************
     * @brief Indicates if the iterator points at an address that's higher than
     *        the address pointed to by referenced other iterator.
     *
     * @param other Reference to other iterator.
     * 
     * @return True if iterator points at an address that's higher than the address
     *         pointed to by referenced other iterator, else false.
     ********************************************************************************/
    bool operator>(const ConstIterator& other) const;

    /********************************************************************************
     * @brief Indicates if the iterator points at an address that's lower than
     *        the address pointed to by referenced other iterator.
     *
     * @param other Reference to other iterator.
     * 
     * @return True if iterator points at an address that's lower than the address
     *         pointed to by referenced other iterator, else false.
     ********************************************************************************/
    bool operator<(const ConstIterator& other) const;

    /********************************************************************************
     * @brief Indicates if the iterator points at an address that's higher or equal
     *        to the address pointed to by referenced other iterator.
     *
     * @param other Reference to other iterator.
     * 
     * @return True if iterator points at an address that's higher or equal to the
     *         address pointed to by referenced other iterator, else false.
     ********************************************************************************/
    bool operator>=(const ConstIterator& other) const;

    /********************************************************************************
     * @brief Indicates if the iterator points at an address that's lower or equal
     *        to the address pointed to by referenced other iterator.
     *
     * @param other Reference to other iterator.
     * 
     * @return True if iterator points at an address that's lower or equal to the
     *         address pointed to by referenced other iterator, else false.
     ********************************************************************************/
    bool operator<=(const ConstIterator& other) const;

    /********************************************************************************
     * @brief Provides the value stored at the address the iterator is pointing at.
     *
     * @return Reference to the value at the address the iterator is pointing at.
     ********************************************************************************/
    const T& operator*() const;

    /********************************************************************************
     * @brief Provides the address the iterator is pointing at.
     *
     * @return A pointer to the address the iterator is pointing at.
     ********************************************************************************/
    const T* operator=(ConstIterator& iterator) const;

private:
    static_assert(Size > 0, "Static array size cannot be set to 0!");
    const T* myData{nullptr};
};

} // namespace container

#include "array_impl.h"