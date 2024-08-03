/********************************************************************************
 * @brief Implementation of doubly linked lists of any data type.
 ********************************************************************************/
#pragma once

#include <stddef.h>

namespace container 
{
/********************************************************************************
 * @brief Class for implementation of doubly linked lists.
 * 
 * @tparam T The list type.
 ********************************************************************************/
template <typename T>
class List 
{        
public:
    class Iterator;      
    class ConstIterator; 

    /********************************************************************************
     * @brief Creates empty list.
     ********************************************************************************/
    List();

    /********************************************************************************
     * @brief Creates list of specified size initialized with specified start value.
     *
     * @param size The starting size of the list.
     * @param startValue The starting value for each element (default = 0).
     ********************************************************************************/
     List(const size_t size, const T& startValue = static_cast<T>(0));

    /********************************************************************************
     * @brief Creates list initialized with values passed as input arguments.
     *
     * @tparam Values... Parameter pack holding input arguments.
     * 
     * @param values The arguments to store in newly created list.
     ********************************************************************************/
    template <typename... Values> 
    List(const Values&&... values);

    /********************************************************************************
     * @brief Creates new list as a copy of referenced source.
     *
     * @param source Reference to list whose content is copied to the new list.
     ********************************************************************************/
    List(List& source);

    /********************************************************************************
     * @brief Deletes list.
     ********************************************************************************/
    ~List();

    /********************************************************************************
     * @brief Returns reference to the value at specified position in the list.
     *
     * @param iterator Reference to iterator pointing at the value to read.
     * 
     * @return A reference to the element at specified position.
     ********************************************************************************/
    T& operator[](Iterator& iterator);

    /********************************************************************************
     * @brief Returns a reference to the element at specified index in the list.
     *
     * @param iterator Reference to iterator pointing at the value to read.
     * 
     * @return A reference to the element at specified position.
     ********************************************************************************/
    const T& operator[] (ConstIterator& iterator) const;

     /********************************************************************************
     * @brief Pushes values to the back of the list.
     *
     * @tparam NumValues The number of values to add.
     * 
     * @param values Reference to the values to add.
     ********************************************************************************/
    template <size_t NumValues>
    bool operator+=(const T (&values)[NumValues]);

    /********************************************************************************
     * @brief Returns the size of the list.
     *
     * @return The size of the list in the number of element it holds.
     ********************************************************************************/
    size_t size() const;

    /********************************************************************************
     * @brief Clears the list.
     ********************************************************************************/
    void clear();

    /********************************************************************************
     * @brief Indicates if the list is empty.
     *
     * @return True if the list is empty, else false.
     ********************************************************************************/
    bool empty() const;

    /********************************************************************************
     * @brief Provides the start address of the list.
     *
     * @return Iterator pointing at the start address of the list.
     ********************************************************************************/
    Iterator begin();

    /********************************************************************************
     * @brief Provides the start address of the list.
     *
     * @return Iterator pointing at the start address of the list.
     ********************************************************************************/
    ConstIterator begin() const;

    /********************************************************************************
     * @brief Provides the end address of the list.
     *
     * @return Iterator pointing at the end address of the list.
     ********************************************************************************/
    Iterator end();

     /********************************************************************************
     * @brief Provides the end address of the list.
     *
     * @return Iterator pointing at the end address of the list.
     ********************************************************************************/
    ConstIterator end() const;

    /********************************************************************************
     * @brief Provides the reverse start address of the list.
     *
     * @return Iterator pointing at the reverse start address of the list.
     ********************************************************************************/
    Iterator rbegin();

    /********************************************************************************
     * @brief Provides the reverse start address of the list.
     *
     * @return Iterator pointing at the reverse start address of the list.
     ********************************************************************************/
    ConstIterator rbegin() const;

    /********************************************************************************
     * @brief Provides the reverse end address of the list.
     *
     * @return Iterator pointing at the reverse end address of the list.
     ********************************************************************************/
    Iterator rend();

    /********************************************************************************
     * @brief Provides the reverse end address of the list.
     *
     * @return Iterator pointing at the reverse end address of the list.
     ********************************************************************************/
    ConstIterator rend() const;

    /********************************************************************************
     * @brief resizes the list to specified new size.
     *
     * @param newSize The new size of the list.
     * @param startValue The starting value for each new element (default = 0).
     * 
     * @return True if the list was resized, else false.
     ********************************************************************************/
    bool resize(const size_t newSize, const T& startValue = static_cast<T>(0));

    /********************************************************************************
     * @brief Inserts value at the front of the list.
     *
     * @param value Reference to the value to add.
     * 
     * @return True if the value was added, else false.
     ********************************************************************************/
    bool pushFront(const T& value);

    /********************************************************************************
     * @brief Inserts value at the back of the list.
     *
     * @param value Reference to the value to add.
     * 
     * @return True if the value was added, else false.
     ********************************************************************************/
    bool pushBack(const T& value);

    /********************************************************************************
     * @brief Inserts value at specified position in the list.
     *
     * @param iterator Reference to iterator pointing at the location to place
     *                 the new value.
     * @param value Reference to the value to add.
     * 
     * @return True if the value was added, else false.
     ********************************************************************************/
    bool insert(Iterator& iterator, const T& value);

    /********************************************************************************
     * @brief Removes value at the front of the list.
     ********************************************************************************/
    void popFront();

    /********************************************************************************
     * @brief Removes value at the back of the list.
     ********************************************************************************/
    void popBack();
    
    /********************************************************************************
     * @brief Removes value at specified position in the list.
     *
     * @param iterator Reference to iterator pointing at the value to remove.
     *
     * @return True if the value was removed, else false.
     ********************************************************************************/
    bool remove(Iterator& iterator);

protected:
    struct Node;
    bool copy(List& source);
    template <size_t NumValues>
    void assign(const T (&values)[NumValues], const size_t offset = 0);
    template <size_t NumValues>
    bool addValues(const T (&values)[NumValues]);
    void removeAllNodes();

    Node* myFirst{nullptr}; 
    Node* myLast{nullptr};  
    size_t mySize{}; 
};

/********************************************************************************
 * @brief Implementation of mutable list iterators.
 *
 * @tparam T The data type of the list.
 ********************************************************************************/
template <typename T>
class List<T>::Iterator 
{
public:
    /********************************************************************************
     * @brief Creates empty iterator.
     ********************************************************************************/
    Iterator();

    /********************************************************************************
     * @brief Creates iterator pointing at referenced node.
     *
     * @param node Reference to node the iterator is to point at.
     ********************************************************************************/
    Iterator(Node* node);

    /********************************************************************************
     * @brief Prefix increment operator, sets the iterator to point at next node.
     ********************************************************************************/
    void operator++();

    /********************************************************************************
     * @brief Postfix increment operator, sets the iterator to point at next node.
     ********************************************************************************/
    void operator++(int);

    /********************************************************************************
     * @brief Prefix decrement operator, sets the iterator to point at previous node.
     ********************************************************************************/
    void operator--();

    /********************************************************************************
     * @brief Postfix decrement operator, sets the iterator to point at previous node.
     ********************************************************************************/
    void operator--(int);

    /********************************************************************************
     * @brief Addition operator, increments the iterator specified number of times.
     *
     * @param numIncrements The number of times the iterator will be incremented.
     ********************************************************************************/
    void operator+= (const size_t numIncrements);

    /********************************************************************************
     * @brief Subtraction operator, decrements the iterator specified number of times.
     *
     * @param numIncrements The number of times the iterator will be decremented.
     ********************************************************************************/
    void operator-=(const size_t numIncrements);

    /********************************************************************************
     * @brief Equality operator, checks if the iterator points at the same node as
     *        referenced other iterator.
     *
     * @param other Reference to other iterator.
     * 
     * @return True if the iterators point at the same node, else false.
     ********************************************************************************/
    bool operator==(const Iterator& other);

    /********************************************************************************
     * @brief Inequality operator, checks if the iterator and referenced other
     *        iterator points at different nodes.
     *
     * @param other Reference to other iterator.
     * 
     * @return True if the iterators point at different nodes, else false.
     ********************************************************************************/
    bool operator!=(const Iterator& other);

    /********************************************************************************
     * @brief Dereference operator, provides a reference to the value stored by the
     *        node the iterator is pointing at.
     *
     * @return Reference to the value stored by the node the iterator is pointing at.
     ********************************************************************************/
    T& operator*();

    /********************************************************************************
     * @brief Returns the address of the node the iterator points at. A void pointer
     *        is returned to keep information about nodes private within the List 
     *        class.
     *
     * @return Pointer to the node the iterator is pointing at.
     ********************************************************************************/
    void* address();

private:
    Node* myNode{nullptr};
};

/********************************************************************************
 * @brief Implementation of constant list iterators.
 *
 * @tparam T The data type of the list.
 ********************************************************************************/
template <typename T>
class List<T>::ConstIterator 
{
public:
    /********************************************************************************
     * @brief Creates iterator pointing at referenced node.
     *
     * @param node Pointer to node that the iterator is set to point at.
     ********************************************************************************/
    ConstIterator(const Node* node);

    /********************************************************************************
     * @brief Prefix increment operator, sets the iterator to point at next node.
     ********************************************************************************/
    void operator++();

    /********************************************************************************
     * @brief Postfix increment operator, sets the iterator to point at next node.
     ********************************************************************************/
    void operator++(int);

    /********************************************************************************
     * @brief Prefix decrement operator, sets the iterator to point at previous node.
     ********************************************************************************/
    void operator--();

    /********************************************************************************
     * @brief Postfix decrement operator, sets the iterator to point at previous node.
     ********************************************************************************/
    void operator--(int);

    /********************************************************************************
     * @brief Addition operator, increments the iterator specified number of times.
     *
     * @param numIncrements The number of times the iterator will be incremented.
     ********************************************************************************/
    void operator+=(const size_t numIncrements);

    /********************************************************************************
     * @brief Subtraction operator, decrements the iterator specified number of 
     *        times.
     *
     * @param numIncrements The number of times the iterator will be decremented.
     ********************************************************************************/
    void operator-=(const size_t numIncrements);

    /********************************************************************************
     * @brief Equality operator, checks if the iterator points at the same node as
     *        referenced other iterator.
     *
     * @param other Reference to other iterator.
     *
     * @return True if the iterators point at the same node, else false.
     ********************************************************************************/
    bool operator==(ConstIterator& other) const;

    /********************************************************************************
     * @brief Inequality operator, checks if the iterator and referenced other
     *        iterator points at different nodes.
     *
     * @param other Reference to other iterator.
     *
     * @return True if the iterators point at different nodes, else false.
     ********************************************************************************/
    bool operator!=(ConstIterator& other) const;

    /********************************************************************************
     * @brief Dereference operator, provides a reference to the value stored by the
     *        node the iterator is pointing at. Not
     *
     * @return Reference to the value stored by the node the iterator is pointing at.
     ********************************************************************************/
    const T& operator*() const;
    
    /********************************************************************************
     * @brief Returns the address of the node the iterator points at. 
     * 
     * @note A void pointer is provided to keep information about nodes private.
     *
     * @return Pointer to the node the iterator is pointing at.
     ********************************************************************************/
    const void* address() const;

private:
    const Node* myNode{nullptr}; 
};

} // namespace container

#include "list_impl.h"