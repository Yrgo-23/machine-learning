/********************************************************************************
 * @brief Implementation details of the vector_2d struct.
 *******************************************************************************/
#include <stdlib.h>

#include "vector_2d.h"

/********************************************************************************
 * @brief Structure holding implementation details of the vector_2d struct.
 *******************************************************************************/
struct vector_2d_impl
{
    struct vector** data; /* Pointer to field holding pointers to vectors. */
    size_t size;          /* The size of the vector. */
};

// -----------------------------------------------------------------------------
static struct vector** vector_2d_data(const struct vector_2d* self)
{
    return self->impl->data;
}

// -----------------------------------------------------------------------------
static size_t vector_2d_size(const struct vector_2d* self)
{
    return self->impl->size;
}

// -----------------------------------------------------------------------------
static struct vector** vector_2d_begin(const struct vector_2d* self)
{
    return self->impl->data;
}

// -----------------------------------------------------------------------------
static struct vector** vector_2d_end(const struct vector_2d* self)
{
    return self->impl->data ? self->impl->data + self->impl->size : NULL;
}

// -----------------------------------------------------------------------------
static void vector_2d_clear(struct vector_2d* self)
{
    free(self->impl->data);
    self->impl->data = NULL;
    self->impl->size = 0U;
}

// -----------------------------------------------------------------------------
static bool vector_2d_resize(struct vector_2d* self, const size_t new_size)
{
    struct vector** copy = (struct vector**)(realloc(self->impl->data, sizeof(struct vector*) * new_size));
    if (!copy) { return false; }
    self->impl->data = copy;
    self->impl->size = new_size;
    return true;
}

// -----------------------------------------------------------------------------
static bool vector_2d_push_back(struct vector_2d* self, const struct vector** vector)
{
    struct vector** copy = (struct vector**)(
        realloc(self->impl->data, sizeof(struct vector*) * (self->impl->size + 1U)));
    if (!copy) { return false; }
    copy[self->impl->size++] = *(struct vector**)(vector);
    self->impl->data         = copy;
    return true;
}

// -----------------------------------------------------------------------------
static bool vector_2d_push_back_multiple(struct vector_2d* self, 
                                         const vector** vectors, 
                                         const size_t size)
{
    if (!vectors || size == 0U) { return false; }
    const size_t old_size = self->impl->size;

    for (size_t i = 0U; i < size; ++i)
    {
        if (vectors[i]) { self->vptr->push_back(self, &vectors[i]); }
    }
    return self->impl->size == old_size + size;
}

// -----------------------------------------------------------------------------
static void vector_2d_print(const struct vector_2d* self, FILE* ostream, 
                            const char* end)
{
    const struct vector** data = (const struct vector**)(self->impl->data);
    if (!end) { end = "\n"; }
    fprintf(ostream, "[");

    for (size_t i = 0U; i < self->impl->size; ++i)
    {
        if (i < self->impl->size - 1U)
        {
            data[i]->vptr->print(data[i], ostream, ", ");
        }
        else
        {
            data[i]->vptr->print(data[i], ostream, "");
        }
    }
    fprintf(ostream, "]%s", end);
}

// -----------------------------------------------------------------------------
static const struct vector_2d_vtable* vector_2d_vptr_new(void)
{
    static const struct vector_2d_vtable vtable = 
    {
        .data               = vector_2d_data,
        .size               = vector_2d_size,
        .begin              = vector_2d_begin,
        .end                = vector_2d_end,
        .clear              = vector_2d_clear,
        .resize             = vector_2d_resize,
        .push_back          = vector_2d_push_back,
        .push_back_multiple = vector_2d_push_back_multiple,
        .print              = vector_2d_print
    };
    return &vtable;
}

// -----------------------------------------------------------------------------
static struct vector_2d_impl* vector_2d_impl_new(void)
{
    struct vector_2d_impl* self = (struct vector_2d_impl*)(malloc(sizeof(struct vector_2d_impl)));
    if (!self) { return NULL; }
    self->data = NULL;
    self->size = 0U;
    return self;
}
// -----------------------------------------------------------------------------
static void vector_2d_impl_delete(struct vector_2d_impl* self)
{
    for (struct vector** it = self->data; it < self->data + self->size; ++it)
    {
        vector_delete(it);
    }

    free(self->data);
    free(self);
}

// -----------------------------------------------------------------------------
struct vector_2d* vector_2d_new(const struct vector** vectors, const size_t size)
{
    struct vector_2d* self = (struct vector_2d*)(malloc(sizeof(struct vector)));
    if (!self) { return NULL; }

    self->vptr = vector_2d_vptr_new();
    if (!self->vptr) { goto vector_2d_new_free_resources; }
    
    self->impl  = vector_2d_impl_new();
    if (!self->impl) { goto vector_2d_new_free_resources; }
    
    if (!vectors && size) { self->vptr->resize(self, size); }
    else { self->vptr->push_back_multiple(self, vectors, size); }
    return self;

vector_2d_new_free_resources:
    free(self->impl);
    free(self);
    return NULL;
}

// -----------------------------------------------------------------------------
void vector_2d_delete(struct vector_2d** self)
{
    if (self && *self)
    {
        vector_2d_impl_delete((*self)->impl);
        free(*self);
        *self = NULL;
    }
}