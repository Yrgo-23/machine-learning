/********************************************************************************
 * @brief Implementation details for the container::ContainerArray class.
 * 
 * @note Don't include this file directly.
 ********************************************************************************/
#pragma once

namespace container
{
namespace
{

// -----------------------------------------------------------------------------
template <size_t Size>
CallbackArray<Size>::CallbackArray() = default;

// -----------------------------------------------------------------------------
template <size_t Size>
CallbackArray<Size>::~CallbackArray() = default;

// -----------------------------------------------------------------------------
template <size_t Size>
bool CallbackArray<Size>::add(void (*callback)(), const size_t index)
{
    if (index < Size && callback != nullptr)
    {
        Array<void (*)(), Size>::myData[index] = callback;
        return true;
    }
    else
    {
        return false;
    }
}

// -----------------------------------------------------------------------------
template <size_t Size>
bool CallbackArray<Size>::remove(const size_t index)
{
    if (index < Size)
    {
        Array<void (*)(), Size>::myData[index] = nullptr;
        return true;
    }
    else
    {
        return false;
    }
}

// -----------------------------------------------------------------------------
template <size_t Size>
bool CallbackArray<Size>::remove(void (*callback)(), const size_t index)
{
    for (auto& myCallback : *this)
    {
        if (myCallback == callback) 
        { 
            myCallback = nullptr; 
            return true;
        }
    }
    return false;
}

// -----------------------------------------------------------------------------
template <size_t Size>
bool CallbackArray<Size>::call(const size_t index)
{
    if (isIndexValid(index) && isCallbackDefined(index))
    {
        Array<void (*)(), Size>::myData[index]();
        return true;
    }
    else
    {
        return false;
    }
}

// -----------------------------------------------------------------------------
template <size_t Size>
constexpr bool CallbackArray<Size>::isIndexValid(const size_t index) const
{
    return index < Size;
}

// -----------------------------------------------------------------------------
template <size_t Size>
bool CallbackArray<Size>::isCallbackDefined(const size_t index) const
{
    return this->myData[index] != nullptr;
}

} // namespace
} // namespace container