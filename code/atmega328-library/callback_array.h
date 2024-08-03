/********************************************************************************
 * @brief Implementation of callback arrays of arbitrary size.
 ********************************************************************************/
#pragma once

#include "array.h"

namespace container
{
namespace 
{

/********************************************************************************
 * @brief Class for implementation of callback arrays.
 * 
 * @tparam Size The array size.
 * 
 * @note The array size must exceed 0, else a compilation error will be generated.
 ********************************************************************************/
template <size_t Size>
class CallbackArray : public Array<void (*)(), Size>
{
public:
    /********************************************************************************
     * @brief Creates empty callback array of specified size.
     ********************************************************************************/
    CallbackArray();

    /********************************************************************************
     * @brief Deletes callback array.
     ********************************************************************************/
    ~CallbackArray();

    /********************************************************************************
     * @brief Adds new callback routine at specified index of the callback array.
     *
     * @param callback Reference to the callback routine to add.
     * @param index    Storage index of the callback routine.
     *
     * @return True if the callback routine was added, else false.
     ********************************************************************************/
    bool add(void (*callback)(), const size_t index);

     /********************************************************************************
     * @brief Removes callback routine at specified index of the callback array.
     *
     * @param index Storage index of the callback routine.
     *
     * @return True if the callback routine was removed, else false.
     ********************************************************************************/
    bool remove(const size_t index);

     /********************************************************************************
     * @brief Removes specified callback routine from the callback array.
     *
     * @param callback Reference to the callback routine to remove.
     *
     * @return True if the callback routine was removed, else false.
     ********************************************************************************/
    bool remove(void (*callback)(), const size_t index);

     /********************************************************************************
     * @brief Performs function call of callback routine at specified index of the 
     *        callback array, if it exists.
     *
     * @param index Storage index of the callback routine to call.
     *
     * @return True if the callback routine was called, else false.
     ********************************************************************************/
    bool call(const size_t index);

private:
    constexpr bool isIndexValid(const size_t index) const;
    bool isCallbackDefined(const size_t index) const;
};

} // namespace
} // namespace container

#include "callback_array_impl.h"