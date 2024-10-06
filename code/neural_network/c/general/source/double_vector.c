/********************************************************************************
 * @brief Implementation details of double vector functions.
 *******************************************************************************/
#include <stdlib.h>

#include "double_vector.h"

// -----------------------------------------------------------------------------
static inline double absolute_value(const double value)
{
    return value >= 0.0 ? value : -value;
}

// -----------------------------------------------------------------------------
static inline double round_near_zero_value(const double value)
{
    return absolute_value(value) < 0.001 ? 0.0: value;
}

// -----------------------------------------------------------------------------
double* double_vector_new(const size_t size)
{
    return (double*)(malloc(sizeof(double) * size));
}

// -----------------------------------------------------------------------------
void double_vector_delete(double** self)
{
    if (self && *self)
    {
        free(*self);
        *self = NULL;
    }
}

// -----------------------------------------------------------------------------
double** double_vector_2d_new(const size_t row_count, const size_t column_count)
{
    double** self = (double**)(malloc(sizeof(double*) * row_count));
    if (!self) { return NULL; }

    for (size_t i = 0U; i < row_count; ++i)
    {
        double* column = double_vector_new(column_count);

        if (!column) 
        { 
            double_vector_2d_delete(&self, i); 
            return NULL;
        }

        self[i] = column;
    }
    return self;
}

// -----------------------------------------------------------------------------
void double_vector_2d_delete(double*** self, const size_t row_count)
{
    if (self && *self)
    {
        double** vector = *self;

        for (size_t i = 0U; i < row_count; ++i) 
        { 
            double_vector_delete(&(vector[i]));
        }

        free(vector);
        *self = NULL;
    }
}

// -----------------------------------------------------------------------------
void double_vector_print(const double* data, const size_t size, FILE* ostream, const char* end)
{
    if (!data || (size == 0U)) { return; }
    if (!ostream) { ostream = stdout; }
    if (!end) { end = "\n"; }
    fprintf(ostream, "[");

    for (const double* it = data; it < data + size; ++it)
    {
        const double number = round_near_zero_value(*it);

        if (it < (data + size - 1U)) 
        { 
            fprintf(ostream, "%.2f, ", number); 
        }
        else 
        { 
            fprintf(ostream, "%.2f", number); 
        }
    }
    fprintf(ostream, "]%s", end);
}

// -----------------------------------------------------------------------------
void double_vector_2d_print(double** data, const size_t row_count,
                            const size_t column_count, FILE* ostream,
                            const char* end)
{
    if (!data || (row_count == 0U) || (column_count == 0U)) { return; }
    if (!ostream) { ostream = stdout; }
    if (!end) { end = "\n"; }
    fprintf(ostream, "[");
    
    for (double** it = data; it < data + row_count; ++it)
    {
        if (it < data + row_count - 1U)
        {
            double_vector_print(*it, column_count, ostream, ", ");
        }
        else
        {
            double_vector_print(*it, column_count, ostream, "");
        }
    }
    fprintf(ostream, "]%s", end);
}