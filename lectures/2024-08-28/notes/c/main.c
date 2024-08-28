#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct int_vector
{
    int* data; 
    size_t size;
};

/**
 * @brief Adds value to the back of vector.
 * 
 * @param self  Reference to the vector in question.
 * @param value The value to add.
 * 
 * @return True if the value was added, else false.
 */
bool int_vector_push_back(struct int_vector* self, const int value)
{
    int* copy = (int*)realloc(self->data, sizeof(int) * (self->size + 1));
    if (!copy) { return false; }
    copy[self->size++] = value;
    self->data = copy;
    return true;
}

void int_vector_clear(struct int_vector* self)
{
    free(self->data);
    self->data = NULL;
    self->size = 0;
}

int main(void)
{
    struct int_vector v1 = {0, 0};
    for (int i = 0; i < 10; ++i)
    {
        int_vector_push_back(&v1, i);
    }

    v1.size = 1;

    for (int i = 0; i < v1.size; ++i)
    {
        printf("%d\n", v1.data[i]);
    }

    int_vector_clear(&v1);
    return 0;
}