/** @brief Implementation details for the int_vector struct. */
#include "vector.h"

/**
 * 1. The current data field is copied, but with room for one more element.
 * 2. If insufficient memory is available (i.e. realloc returns NULL), false is returned.
 * 3. The new value is pushed to the back of the vector and the vector size is incremented.
 * 4. The data pointer is set to point at the new bigger field (pointer to by the copy).
 * 5. True is returned to indicate that the value has been added.
 */
bool int_vector_push_back(struct int_vector* self, const int value)
{
    int* copy = (int*)realloc(self->data, sizeof(int) * (self->size + 1U));
    if (!copy) { return false; } 
    copy[self->size++] = value; 
    self->data = copy;         
    return true;
}

/**
 * 1. Dynamic memory allocated for the vector (and pointed to by the data pointer) is cleared.
 * 2. The data pointer is set to point at NULL instead of where the field use to be.
 * 3. The vector size is set to 0, since it's now empty.
 */
void int_vector_clear(struct int_vector* self)
{
    free(self->data);
    self->data = NULL;
    self->size = 0;
}

/**
 * 1. If no output stream has been specified, terminal print is performed.
 * 2. Each number stored in the vector is printed one by one, separated by a comma.
 */
void int_vector_print(const struct int_vector* self, FILE* ostream)
{
    if (!ostream) { ostream = stdout; }
    fprintf(ostream, "[");
    for (size_t i = 0; i < self->size; ++i)
    {
        fprintf(ostream, "%d", self->data[i]);
        if (i != self->size - 1U) { fprintf(ostream, ", "); }
    }
    fprintf(ostream, "]\n");
}