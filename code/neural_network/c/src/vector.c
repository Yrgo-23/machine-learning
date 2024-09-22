/********************************************************************************
 * @brief Implementation details of the vector struct.
 *******************************************************************************/
#include <stdlib.h>

#include "vector.h"

/********************************************************************************
 * @brief Structure holding implementation details of the vector struct.
 *******************************************************************************/
struct vector_impl
{
    void* data;            /* Pointer to field holding data. */
    size_t size;           /* The size of the vector. */
    enum vector_type type; /* The vector type. */
};

// -----------------------------------------------------------------------------
static inline bool vector_type_is_valid(const enum vector_type type)
{
    return (type >= VECTOR_TYPE_INT) && (type < VECTOR_TYPE_COUNT);
}

// -----------------------------------------------------------------------------
static void* vector_data(const struct vector* self)
{
    return self->impl->data;
}

// -----------------------------------------------------------------------------
static size_t vector_size(const struct vector* self)
{
    return self->impl->size;
}

// -----------------------------------------------------------------------------
static enum vector_type vector_type(const struct vector* self)
{
    return self->impl->type;
}

// -----------------------------------------------------------------------------
static bool vector_is_arithmetic(const struct vector* self)
{
    return true;
}

// -----------------------------------------------------------------------------
static bool vector_is_not_arithmetic(const struct vector* self)
{
    return false;
}

// -----------------------------------------------------------------------------
static void* vector_begin(const struct vector* self)
{
    return self->impl->data;
}

// -----------------------------------------------------------------------------
static void* vector_end(const struct vector* self)
{
    return self->impl->data ? (int*)(self->impl->data) + self->impl->size : NULL;
}

// -----------------------------------------------------------------------------
static void vector_clear(struct vector* self)
{
    free(self->impl->data);
    self->impl->data = NULL;
    self->impl->size = 0U;
}

// -----------------------------------------------------------------------------
static bool vector_int_resize(struct vector* self, const size_t new_size)
{
    int* copy = (int*)(realloc(self->impl->data, sizeof(int) * new_size));
    if (!copy) { return false; }
    self->impl->data = copy;
    self->impl->size = new_size;
    return true;
}

// -----------------------------------------------------------------------------
static bool vector_int_push_back(struct vector* self, const void* value)
{
    if (!value) { return false; }
    int* copy = (int*)(realloc(self->impl->data, sizeof(int) * (self->impl->size + 1U)));
    if (!copy) { return false; }
    copy[self->impl->size++] = *((int*)(value));
    self->impl->data         = copy;
    return true;
}

// -----------------------------------------------------------------------------
static bool vector_int_push_back_multiple(struct vector* self, const void* data, 
                                          const size_t size)
{
    if (!data || size == 0U) { return false; }
    const size_t old_size = self->impl->size;
    
    if (self->vptr->resize(self, size))
    {
        const int* new_values = (const int*)(data);
        int* field            = (int*)(self->impl->data);

        for (size_t i = old_size; i < self->impl->size; ++i)
        {
            field[old_size + i] = new_values[i]; 
        }
        return true;
    }
    return false;
}

// -----------------------------------------------------------------------------
static void vector_int_print(const struct vector* self, FILE* ostream, const char* end)
{
    const int* data = (const int*)(self->impl->data);

    if (!ostream) { ostream = stdout; }
    if (!end) { end = "\n"; }
    fprintf(ostream, "[");

    for (size_t i = 0U; i < self->impl->size; ++i)
    {
        if (i < self->impl->size - 1U) 
        { 
            fprintf(ostream, "%d, ", data[i]); 
        }
        else 
        { 
            fprintf(ostream, "%d", data[i]); 
        }
    }
    fprintf(ostream, "]%s", end);
}

// -----------------------------------------------------------------------------
static bool vector_double_resize(struct vector* self, const size_t new_size)
{
    double* copy = (double*)(realloc(self->impl->data, sizeof(double) * new_size));
    if (!copy) { return false; }
    self->impl->data = copy;
    self->impl->size = new_size;
    return true;
}

// -----------------------------------------------------------------------------
static bool vector_double_push_back(struct vector* self, const void* value)
{
    if (!value) { return false; }
    double* copy = (double*)(realloc(self->impl->data, sizeof(double) * (self->impl->size + 1U)));
    if (!copy) { return false; }
    copy[self->impl->size++] = *((double*)(value));
    self->impl->data         = copy;
    return true;
}

// -----------------------------------------------------------------------------
static bool vector_double_push_back_multiple(struct vector* self, const void* data, 
                                             const size_t size)
{
    if (!data || size == 0U) { return false; }
    const size_t old_size = self->impl->size;
    
    if (self->vptr->resize(self, size))
    {
        const double* new_values = (const double*)(data);
        double* field            = (double*)(self->impl->data);

        for (size_t i = old_size; i < self->impl->size; ++i)
        {
            field[old_size + i] = new_values[i]; 
        }
    }
    return self->impl->size == old_size + size;
}

// -----------------------------------------------------------------------------
static void vector_double_print(const struct vector* self, FILE* ostream, const char* end)
{   
    const double* data = (const double*)(self->impl->data);

    if (!ostream) { ostream = stdout; }
    if (!end) { end = "\n"; }
    fprintf(ostream, "[");

    for (size_t i = 0U; i < self->impl->size; ++i)
    {
        if (i < self->impl->size - 1U) 
        { 
            fprintf(ostream, "%.2f, ", data[i]); 
        }
        else 
        { 
            fprintf(ostream, "%.2f", data[i]); 
        }
    }
    fprintf(ostream, "]%s", end);
}

// -----------------------------------------------------------------------------
static bool vector_string_resize(struct vector* self, const size_t new_size)
{
    const char** copy = (const char**)(realloc(self->impl->data, sizeof(const char*) * new_size));
    if (!copy) { return false; }
    self->impl->data = copy;
    self->impl->size = new_size;
    return true;
}

// -----------------------------------------------------------------------------
static bool vector_string_push_back(struct vector* self, const void* value)
{
    if (!value) { return false; }
    const char** copy = (const char**)(realloc(self->impl->data, 
        sizeof(const char*) * (self->impl->size + 1U)));
    if (!copy) { return false; }
    copy[self->impl->size++] = (const char*)(value);
    self->impl->data         = copy;
    return true;
}

// -----------------------------------------------------------------------------
static bool vector_string_push_back_multiple(struct vector* self, const void* data, 
                                             const size_t size)
{
    if (!data || size == 0U) { return false; }
    const size_t old_size = self->impl->size;
    
    if (self->vptr->resize(self, size))
    {
        const char** new_values = (const char**)(data);
        const char** field      = (const char**)(self->impl->data);

        for (size_t i = old_size; i < self->impl->size; ++i)
        {
            field[old_size + i] = new_values[i]; 
        }
        return true;
    }
    return false;
}

// -----------------------------------------------------------------------------
static void vector_string_print(const struct vector* self, FILE* ostream, const char* end)
{
    const char** data = (const char**)(self->impl->data);

    if (!ostream) { ostream = stdout; }
    if (!end) { end = "\n"; }
    fprintf(ostream, "[");

    for (size_t i = 0U; i < self->impl->size; ++i)
    {
        if (!data[i]) { continue; }

        if (i < self->impl->size - 1U) 
        { 
            fprintf(ostream, "%s, ", data[i]);
        }
        else 
        { 
            fprintf(ostream, "%s", data[i]); 
        }
    }
    fprintf(ostream, "]%s", end);
}

// -----------------------------------------------------------------------------
static const struct vector_vtable* vector_vptr_int_new(void)
{
    static const struct vector_vtable vtable = 
    {
        .data               = vector_data,
        .size               = vector_size,
        .type               = vector_type,
        .is_arithmetic      = vector_is_arithmetic,
        .begin              = vector_begin,
        .end                = vector_end,
        .clear              = vector_clear,
        .resize             = vector_int_resize,
        .push_back          = vector_int_push_back,
        .push_back_multiple = vector_int_push_back_multiple,
        .print              = vector_int_print
    };
    return &vtable;
}

// -----------------------------------------------------------------------------
static const struct vector_vtable* vector_vptr_double_new(void)
{
    static const struct vector_vtable vtable = 
    {
        .data               = vector_data,
        .size               = vector_size,
        .type               = vector_type,
        .is_arithmetic      = vector_is_arithmetic,
        .begin              = vector_begin,
        .end                = vector_end,
        .clear              = vector_clear,
        .resize             = vector_double_resize,
        .push_back          = vector_double_push_back,
        .push_back_multiple = vector_double_push_back_multiple,
        .print              = vector_double_print
    };
    return &vtable;
}

// -----------------------------------------------------------------------------
static const struct vector_vtable* vector_vptr_string_new(void)
{
    static const struct vector_vtable vtable = 
    {
        .data               = vector_data,
        .size               = vector_size,
        .type               = vector_type,
        .is_arithmetic      = vector_is_not_arithmetic,
        .begin              = vector_begin,
        .end                = vector_end,
        .clear              = vector_clear,
        .resize             = vector_string_resize,
        .push_back          = vector_string_push_back,
        .push_back_multiple = vector_string_push_back_multiple,
        .print              = vector_string_print
    };
    return &vtable;
}

// -----------------------------------------------------------------------------
static const struct vector_vtable* vector_vptr_new(const enum vector_type type)
{
    switch (type)
    {
        case VECTOR_TYPE_INT:
            return vector_vptr_int_new();
        case VECTOR_TYPE_DOUBLE:
            return vector_vptr_double_new();
        case VECTOR_TYPE_STRING:
            return vector_vptr_string_new();
        default:
            return NULL;
    }
}

// -----------------------------------------------------------------------------
static struct vector_impl* vector_impl_new(const enum vector_type type)
{
    struct vector_impl* self = (struct vector_impl*)(malloc(sizeof(struct vector_impl)));
    if (!self) { return NULL; }
    self->data = NULL;
    self->size = 0U;
    self->type = type;
    return self;
}

// -----------------------------------------------------------------------------
static void vector_impl_delete(struct vector_impl* self)
{
    free(self->data);
    free(self);
}

// -----------------------------------------------------------------------------
bool vector_set_type(struct vector* self, const enum vector_type new_type)
{
    if (vector_type_is_valid(new_type) && (new_type != self->impl->type))
    {
        self->vptr->clear(self);
        self->impl->type = new_type;
        return true;
    }
    return false;
}

// -----------------------------------------------------------------------------
struct vector* vector_new(const enum vector_type type, const void* data, const size_t size)
{
    struct vector* self = (struct vector*)(malloc(sizeof(struct vector)));
    if (!self) { return NULL; }
    
    self->vptr  = vector_vptr_new(type);
    self->impl  = vector_impl_new(type);

    if (!self->impl)
    {
        free(self);
        return NULL;
    }

    if (!data && size) { self->vptr->resize(self, size); }
    else { self->vptr->push_back_multiple(self, data, size); }
    return self;
}

// -----------------------------------------------------------------------------
void vector_delete(struct vector** self)
{
    if (self && *self)
    {
        vector_impl_delete((*self)->impl);
        free(*self);
        *self = NULL;
    }
}
