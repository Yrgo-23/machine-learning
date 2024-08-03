/********************************************************************************
 * @brief Implementation details for the container::List class.
 * 
 * @note Don't include this file directly.
 ********************************************************************************/
#pragma once

#include "utils.h"

namespace container
{

template <typename T>
struct List<T>::Node 
{
    Node* previous; 
    Node* next;     
    T data;         

    static Node* create(const T& data);
    static void destroy(Node* self);
    static Node* get(Iterator& iterator);
    static const Node* get(ConstIterator& iterator);
};

// -----------------------------------------------------------------------------
template <typename T>
List<T>::List() = default;

// -----------------------------------------------------------------------------
template <typename T>
List<T>::List(const size_t size, const T& startValue) 
{
    resize(size, startValue);
}

// -----------------------------------------------------------------------------
template <typename T>
template <typename... Values> 
List<T>::List(const Values&&... values) 
{ 
    const T array[sizeof...(values)]{(values)...};
    addValues(array);
}

// -----------------------------------------------------------------------------
template <typename T>
List<T>::List(List<T>& source) { copy(source); }

// -----------------------------------------------------------------------------
template <typename T>
List<T>::~List() { clear(); }

// -----------------------------------------------------------------------------
template <typename T>
T& List<T>::operator[](Iterator& iterator) { return *iterator; }

// -----------------------------------------------------------------------------
template <typename T>
const T& List<T>::operator[] (ConstIterator& iterator) const { return *iterator; }

// -----------------------------------------------------------------------------
template <typename T>
template <size_t NumValues>
bool List<T>::operator+=(const T (&values)[NumValues]) { return addValues(values); }

// -----------------------------------------------------------------------------
template <typename T>
size_t List<T>::size() const { return mySize; }

// -----------------------------------------------------------------------------
template <typename T>
void List<T>::clear() 
{
    removeAllNodes();
    myFirst = nullptr;
    myLast = nullptr;
    mySize = 0;
}

// -----------------------------------------------------------------------------
template <typename T>
bool List<T>::empty() const { return mySize == 0; }

// -----------------------------------------------------------------------------
template <typename T>
typename List<T>::Iterator List<T>::begin() 
{ 
    return mySize > 0 ? Iterator{myFirst} : Iterator{nullptr};
}

// -----------------------------------------------------------------------------
template <typename T>
typename List<T>::ConstIterator List<T>::begin() const 
{ 
    return mySize > 0 ? ConstIterator{myFirst} : ConstIterator{nullptr};
}

// -----------------------------------------------------------------------------
template <typename T>
typename List<T>::Iterator List<T>::end() { return Iterator{nullptr}; }

// -----------------------------------------------------------------------------
template <typename T>
typename List<T>::ConstIterator List<T>::end() const 
{ 
    return ConstIterator{nullptr}; 
}

// -----------------------------------------------------------------------------
template <typename T>
typename List<T>::Iterator List<T>::rbegin() 
{ 
    return mySize > 0 ? Iterator{myLast} : Iterator{nullptr};
}

// -----------------------------------------------------------------------------
template <typename T>
typename List<T>::ConstIterator List<T>::rbegin() const 
{ 
    return mySize > 0 ? ConstIterator{myLast} : ConstIterator{nullptr};
}

// -----------------------------------------------------------------------------
template <typename T>
typename List<T>::Iterator List<T>::rend() { return Iterator{nullptr}; }

// -----------------------------------------------------------------------------
template <typename T>
typename List<T>::ConstIterator List<T>::rend() const 
{ 
    return ConstIterator{nullptr}; 
}

// -----------------------------------------------------------------------------
template <typename T>
bool List<T>::resize(const size_t newSize, const T& startValue) 
{
    while (mySize < newSize) 
    {
        if (!pushBack(startValue)) { return false; }
    }
    while (mySize > newSize) { popFront(); }
    return true;
}

// -----------------------------------------------------------------------------
template <typename T>
bool List<T>::pushFront(const T& value) 
{
    auto node1{Node::create(value)};
    if (node1 == nullptr) { return false; }

    if (mySize++ == 0) 
    {
        myFirst = node1;
        myLast = node1;
    } 
    else 
    {
        auto node2{myFirst};
        node1->next = node2;
        node2->previous = node1;
        myFirst = node1;
    }
    return true;
}

// -----------------------------------------------------------------------------
template <typename T>
bool List<T>::pushBack(const T& value) 
{
    auto node2{Node::create(value)};
    if (node2 == nullptr) { return false; }  

    if (mySize++ == 0) 
    {
        myFirst = node2;
        myLast = node2;
    } 
    else 
    {
        auto node1{myLast};
        node1->next = node2;
        node2->previous = node1;
        myLast = node2;
    }
    return true;
}

// -----------------------------------------------------------------------------
template <typename T>
bool List<T>::insert(Iterator& iterator, const T& value)
{
    if (iterator == nullptr) {  return false; }
    auto node2{Node::create(value)};
    if (node2 == nullptr) return false;            
    auto node1{Node::get(iterator)->previous};
    auto node3{node1->next};

    node1->next = node2;
    node2->previous = node1;
    node2->next = node3;
    node3->previous = node2;
    mySize++;
    return true;      
}

// -----------------------------------------------------------------------------
template <typename T>
void List<T>::popFront() 
{
    if (mySize <= 1) 
    {
        clear();
        return;
    } 
    auto node1{myFirst};
    auto node2{node1->next};
    node2->previous = nullptr;
    
    Node::destroy(node1);
    myFirst = node2;
    mySize--;
}

// -----------------------------------------------------------------------------
template <typename T>
void List<T>::popBack() 
{
    if (mySize <= 1) 
    {
        clear();
        return;
    } 
    auto node2{myLast};
    auto node1{node2->previous};
    node1->next = nullptr;     
    Node::destroy(node2);
    myLast = node1;
    mySize--;
}

// -----------------------------------------------------------------------------
template <typename T>
bool List<T>::remove(Iterator& iterator) 
{
    if (iterator == nullptr) 
    {
        return false;
    } 
    else 
    {
        auto node2{iterator.get()};
        auto node1{node2->previous};
        auto node3{node2->next};

        node1->next = node3;
        node3->previous = node1;
        Node::destroy(node2);
        mySize--;
        return true;
    }
}

// -----------------------------------------------------------------------------
template <typename T>
bool List<T>::copy(List& source) 
{
    clear();
    for (size_t i{}; i < source.Size(); ++i) 
    {
        if (!pushBack(source[i])) { return false; }
    }
    return true;
}

// -----------------------------------------------------------------------------
template <typename T>
template <size_t NumValues>
void List<T>::assign(const T (&values)[NumValues], const size_t offset)
{
    for (size_t i{}; i < NumValues && offset + i < mySize; ++i)
    {
        (*this)[offset + i] = values[i];
    }
}

// -----------------------------------------------------------------------------
template <typename T>
template <size_t NumValues>
bool List<T>::addValues(const T (&values)[NumValues])
{
    if (NumValues == 0) { return false; }
    for (size_t i{}; i < NumValues; ++i)
    {
        if (!pushBack(values[i])) { return false; }
    }
    return true;
}

// -----------------------------------------------------------------------------
template <typename T>
void List<T>::removeAllNodes() 
{
    for (auto i{begin()}; i != end();) 
    {
        auto next{Node::get(i)->next};
        Node::destroy(Node::get(i));
        i = next;
    }
}

// -----------------------------------------------------------------------------
template <typename T>
List<T>::Iterator::Iterator() = default;

// -----------------------------------------------------------------------------
template <typename T>
List<T>::Iterator::Iterator(Node* node) : myNode{node} {}

// -----------------------------------------------------------------------------
template <typename T>
void List<T>::Iterator::operator++() { myNode = myNode->next; }

// -----------------------------------------------------------------------------
template <typename T>
void List<T>::Iterator::operator++(int) { myNode = myNode->next; }

// -----------------------------------------------------------------------------
template <typename T>
void List<T>::Iterator::operator--() { myNode = myNode->previous; }

// -----------------------------------------------------------------------------
template <typename T>
void List<T>::Iterator::operator--(int) { myNode = myNode->previous; }

// -----------------------------------------------------------------------------
template <typename T>
void List<T>::Iterator::operator+= (const size_t numIncrements) 
{
    for (size_t i{}; i < numIncrements; ++i) 
    {
        myNode = myNode->next;
    }
}

// -----------------------------------------------------------------------------
template <typename T>
void List<T>::Iterator::operator-=(const size_t numIncrements) 
{
    for (size_t i{}; i < numIncrements; ++i) 
    {
        myNode = myNode->previous;
    }
}

// -----------------------------------------------------------------------------
template <typename T>
bool List<T>::Iterator::operator==(const Iterator& other) { return myNode == other.myNode; }

// -----------------------------------------------------------------------------
template <typename T>
bool List<T>::Iterator::operator!=(const Iterator& other) { return myNode != other.myNode; }

// -----------------------------------------------------------------------------
template <typename T>
T& List<T>::Iterator::operator*() { return myNode->data; }

// -----------------------------------------------------------------------------
template <typename T>
void* List<T>::Iterator::address() { return myNode; }

// -----------------------------------------------------------------------------
template <typename T>
List<T>::ConstIterator::ConstIterator(const Node* node) : myNode{node} {}

// -----------------------------------------------------------------------------
template <typename T>
void List<T>::ConstIterator::operator++() { myNode = myNode->next; }

// -----------------------------------------------------------------------------
template <typename T>
void List<T>::ConstIterator::operator++(int) { myNode = myNode->next; }

// -----------------------------------------------------------------------------
template <typename T>
void List<T>::ConstIterator::operator--() {  myNode = myNode->previous; }

// -----------------------------------------------------------------------------
template <typename T>
void List<T>::ConstIterator::operator--(int) { myNode = myNode->previous; }

// -----------------------------------------------------------------------------
template <typename T>
void List<T>::ConstIterator::operator+=(const size_t numIncrements) 
{
    for (size_t i{}; i < numIncrements; ++i) 
    {
        myNode = myNode->next;
    }
}

// -----------------------------------------------------------------------------
template <typename T>
void List<T>::ConstIterator::operator-=(const size_t numIncrements) 
{
    for (size_t i{}; i < numIncrements; ++i) 
    {
        myNode = myNode->previous;
    }
}

// -----------------------------------------------------------------------------
template <typename T>
bool List<T>::ConstIterator::operator==(ConstIterator& other) const { return myNode == other.myNode; }

// -----------------------------------------------------------------------------
template <typename T>
bool List<T>::ConstIterator::operator!=(ConstIterator& other) const { return myNode != other.myNode; }

// -----------------------------------------------------------------------------
template <typename T>
const T& List<T>::ConstIterator::operator*() const { return myNode->data; }

// -----------------------------------------------------------------------------
template <typename T>
const void* List<T>::ConstIterator::address() const { return myNode; }

// -----------------------------------------------------------------------------
template <typename T>
typename List<T>::Node* List<T>::Node::create(const T& data) 
{
    auto self{utils::newMemory<Node>()};
    if (self == nullptr) { return nullptr; }
    self->data = data;
    self->previous = nullptr;
    self->next = nullptr;
    return self;
}

// -----------------------------------------------------------------------------
template <typename T>
void List<T>::Node::destroy(Node* self) { utils::deleteMemory(self); }

// -----------------------------------------------------------------------------
template <typename T>
typename List<T>::Node* List<T>::Node::get(Iterator& iterator) 
{ 
    return static_cast<Node*>(iterator.address()); 
}

// -----------------------------------------------------------------------------
template <typename T>
const typename List<T>::Node* List<T>::Node::get(ConstIterator& iterator) 
{
    return static_cast<Node*>(iterator.address());
}

} // namespace container