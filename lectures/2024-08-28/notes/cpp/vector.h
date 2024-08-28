/*******************************************************************************
 * @brief Vector implementation for holding data of an arbitrary type.
 ******************************************************************************/
#pragma once

#include <iostream>
#include <cstdlib>

namespace yrgo
{

/*******************************************************************************
 * @brief Vector implementation for holding data of an arbitrary type.
 * 
 * @tparam T The type of the vector.
 ******************************************************************************/
template <typename T>
class vector
{
public:

    /*******************************************************************************
     *  @brief Creates empty vector. 
     ******************************************************************************/
    vector() = default;

    /*******************************************************************************
     * @brief Creates vector holding values stored in passed value pack.
     * 
     * @tparam Values Type for passed value pack.
     * 
     * @param value Reference to value pack holding values.
     ******************************************************************************/
    template <typename... Values>
    vector(const Values&... values)
    {
        for (const auto& i : {values...}) { push_back(i); }
    }

    /*******************************************************************************
     * @brief Releases allocated memory automatically before the vector is deleted.
     ******************************************************************************/
    ~vector() { clear(); }

    /*******************************************************************************
     * @brief Overload of operator [] for accessing elements by index.
     * 
     * @param index The index of the searched element.
     * 
     * @return Reference to element held at specified index.
     ******************************************************************************/
    T& operator[](const std::size_t index) { return myData[index]; }
    const T& operator[](const std::size_t index) const { return myData[index]; }

    /*******************************************************************************
     * @brief Overload of operator = for assigning new values to the vector.
     * 
     * @tparam ValueCount The number of values to add.
     * 
     * @param param values Reference to array holding the values to add.
     ******************************************************************************/
    template <std::size_t ValueCount>
    void operator=(const T (&values)[ValueCount])
    {
        clear();
        for (std::size_t i{}; i < ValueCount; ++i) { push_back(values[i]); }
    }

    /*******************************************************************************
     * @brief Provides the start address of the vector.
     * 
     * @return Pointer to the start address of the vector.
     ******************************************************************************/
    T* begin() { return myData; }
    const T* begin() const { return myData; }

    /*******************************************************************************
     * @brief Provides the end address of the vector.
     * 
     * @return Pointer to the end address of the vector.
     ******************************************************************************/
    T* end() { return myData + mySize; }
    const T* end() const { return myData + mySize; }

    /*******************************************************************************
     * @brief Provides the data held by the vector.
     * 
     * @return Pointer to data held by the vector.
     ******************************************************************************/
    const T* data() const { return myData; }

    /*******************************************************************************
     * @brief Provides the size of the vector.
     * 
     * @return The size of the vector in number of held values.
     ******************************************************************************/
    std::size_t size() const { return mySize; }

    /*******************************************************************************
     * @brief Pushes value to the back of vector.
     * 
     * @param value The value to add.
     * 
     * @return True if the operation succeeded, else false.
     ******************************************************************************/
    bool push_back(const T& value)
    {
        auto copy{static_cast<T*>(std::realloc(myData, sizeof(T) * (mySize + 1U)))};
        if (copy == nullptr) { return false; }
        copy[mySize++] = value;
        myData = copy;
        return true;
    }
   
    /*******************************************************************************
     * @brief Prints content held by vector in a bracket.
     * 
     * @param ostream Reference to output stream (default = terminal print).
     ******************************************************************************/
    void print(std::ostream& ostream = std::cout) const
    {
        ostream << "[";
        for (std::size_t i{}; i < mySize; ++i)
        {
            ostream << myData[i];
            if (i != mySize - 1U) { ostream << ", "; }
        }
        ostream << "]\n";
    }

    /*******************************************************************************
     * @brief Clears vector.
     ******************************************************************************/
    void clear()
    {
        std::free(myData);
        myData = nullptr;
        mySize = 0;
    }

private:
    T* myData{nullptr}; /** Pointer to dynamically allocated field. */
    size_t mySize{};    /** The size of the vector in number of elements. */
};

} // namespace yrgo


