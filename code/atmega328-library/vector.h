/********************************************************************************
 * @brief Implementation of dynamic vectors of any data type.
 ********************************************************************************/
#pragma once

#include <stddef.h>

namespace container 
{
/********************************************************************************
 * @brief Class for implementation of dynamic vectors.
 * 
 * @tparam T The data type of the vector.
 ********************************************************************************/
template <typename T>
class Vector 
{
public:
    class Iterator;
    class ConstIterator;

    /********************************************************************************
     * @brief Creates empty vector.
     ********************************************************************************/
    Vector();

    /********************************************************************************
     * @brief Creates vector of specified size.
     *
     * @param size The size of the vector, i.e. the number of elements it can hold.
     ********************************************************************************/
    Vector(const size_t size);

    /********************************************************************************
     * @brief Creates vector containing specified values.
     *
     * @tparam Values Parameter pack containing values.
     * 
     * @param values The values to add to the vector.
     ********************************************************************************/
    template <typename... Values>
    Vector(const Values&&... values);

    /********************************************************************************
     * @brief Creates vector as a copy of referenced source.
     *
     * @param source Reference to vector whose content is copied to the new vector.
     ********************************************************************************/
    Vector(const Vector<T>& source);

    /********************************************************************************
     * @brief Moves memory from referenced source to assigned vector. The source
     *        vector is emptied after the move operation is performed.
     *
     * @param source Reference to vector whose content is moved to assigned vector.
     ********************************************************************************/
    Vector(Vector&& source);

    /********************************************************************************
     * @brief Empties vector before deletion.
     ********************************************************************************/
    ~Vector();

    /********************************************************************************
     * @brief Returns reference to the element at specified index in the vector.
     *
     * @param index Index of the requested element.
     * 
     * @return A reference to the element at specified index.
     ********************************************************************************/
    T& operator[](const size_t index);

    /********************************************************************************
     * @brief Returns reference to the element at specified index in the vector.
     *
     * @param index Index of the requested element.
     * 
     * @return A reference to the element at specified index.
     ********************************************************************************/
    const T& operator[](const size_t index) const;

    /********************************************************************************
     * @brief Copies the content of the vector to assigned vector. Previous values 
     *        are cleared before copying.
     *
     * @tparam Values Parameter pack holding values.
     * 
     * @param values Reference to the values to add.
     ********************************************************************************/
    template <typename... Values>
    void operator=(const Values&&... values);

    /********************************************************************************
     * @brief Copies the content of the vector to assigned vector. Previous values 
     *        are cleared before copying.
     *
     * @param source Reference to vector containing the the values to add.    
     ********************************************************************************/
    void operator=(const Vector<T>& source);

    /********************************************************************************
     * @brief Pushes referenced values to the back of the vector.
     *
     * @tparam NumValues The number of values to add.
     * 
     * @param values Reference to the values to add.
     ********************************************************************************/
    template <size_t NumValues>
    void operator+=(const T (&values)[NumValues]);

    /********************************************************************************
     * @brief Adds values from the vector to the back of assigned vector.
     *
     * @param source Reference to vector containing the the values to add.
     ********************************************************************************/
    void operator+=(const Vector<T>& source);

    /********************************************************************************
     * @brief Provides the data held by the vector.
     *
     * @return Pointer to the start address of the vector.
     ********************************************************************************/
    const T* data() const;

    /********************************************************************************
     * @brief Returns the size of the vector in the number of elements it can hold.
     *
     * @return The size of the vector as an unsigned integer.
     ********************************************************************************/
    size_t size() const;

    /********************************************************************************
     * @brief Indicates if the vector is empty.
     *
     * @return True if the vector vector is empty, else false.
     ********************************************************************************/
    bool empty() const;

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
     * @brief Returns the address of the last element of the vector.
     *
     * @return Pointer to the last element of the vector.
     ********************************************************************************/
    T* last();
   
    /********************************************************************************
     * @brief Returns the address of the last element of the vector.
     *
     * @return Pointer to the last element of the vector.
     ********************************************************************************/
    const T* last() const;

    /********************************************************************************
     * @brief Clears content of the vector.
     ********************************************************************************/
    void clear();

    /********************************************************************************
     * @brief Resizes the vector to specified new size.
     *
     * @param newSize The new size of the vector.
     * 
     * @return True if the vector was resized, else false.
     ********************************************************************************/
    bool resize(const size_t newSize);

    /********************************************************************************
     * @brief Pushes new value to the back of the vector.
     *
     * @param value Reference to the new value to push to the vector.
     * 
     * @return True if the value was pushed to the back of the vector, else false.
     ********************************************************************************/
    bool pushBack(const T& value);

    /******************************************************************************** 
     * @brief Pops value at the back of the vector.
     *
     * @return True if the last value of the vector was popped, else false.
     ********************************************************************************/
    bool popBack();

protected:
    bool copy(const Vector<T>& source);
    void assign(const Vector<T>& source, const size_t offset = 0);
    template <size_t NumValues>
    void assign(const T (&values)[NumValues], const size_t offset = 0);
    bool addValues(const Vector<T>& source);
    template <size_t NumValues>
    bool addValues(const T (&values)[NumValues]);
    T* realloc(const size_t newSize);

    T* myData{nullptr}; 
    size_t mySize{};  
};

/********************************************************************************
 * @brief Implementation of mutable vector iterators.
 *
 * @tparam T The data type of the vector.
 ********************************************************************************/
template <typename T>
class Vector<T>::Iterator
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
    T* myData{nullptr};
};

/********************************************************************************
 * @brief Implementation of constant vector iterators.
 *
 * @tparam T The data type of the vector.
 ********************************************************************************/
template <typename T>
class Vector<T>::ConstIterator
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
    const T* myData{nullptr};
};

} // namespace container

#include "vector_impl.h"