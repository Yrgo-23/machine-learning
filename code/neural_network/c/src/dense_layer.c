/*******************************************************************************
 * @brief Implementation details of the dense_layer struct.
 ******************************************************************************/
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "dense_layer.h"
#include "vector.h"
#include "vector_2d.h"

/********************************************************************************
 * @brief Structure holding implementation details of the dense_layer struct.
 *******************************************************************************/
struct dense_layer_impl
{
    struct vector* output;     /* Pointer to vector holding the output of each node. */
    struct vector* error;      /* Pointer to vector holding the calculated error for each node. */
    struct vector* bias;       /* Pointer to vector holding the bias for each node. */
    struct vector_2d* weights; /* Pointer to vector holding the weights for each node. */
    enum act_func act_func;    /* Activation function used for the dense layer. */
};

// -----------------------------------------------------------------------------
static inline void init_random_generator(void)
{
    static bool random_generator_initialized = false;
    if (!random_generator_initialized)
    {
        srand(time(NULL));
        random_generator_initialized = true;
    }
}

// -----------------------------------------------------------------------------
static inline double random_start_value(void) 
{
    return rand() / (double)(RAND_MAX);
}

// -----------------------------------------------------------------------------
static inline double* vector_data(struct vector* self)
{
    return (double*)(self->vptr->data(self));
}

// -----------------------------------------------------------------------------
static inline const double* vector_data_const(const struct vector* self)
{
    return (const double*)(self->vptr->data(self));
}

// -----------------------------------------------------------------------------
static inline struct vector** vector_2d_data(struct vector_2d* self)
{
    return self->vptr->data(self);
}

// -----------------------------------------------------------------------------
static inline const struct vector** vector_2d_data_const(const struct vector_2d* self)
{
    return (const struct vector**)(self->vptr->data(self));
}

// -----------------------------------------------------------------------------
static inline size_t vector_size(const struct vector* self)
{
    return self->vptr->size(self);
}

// -----------------------------------------------------------------------------
static inline size_t vector_2d_row_count(const struct vector_2d* self)
{
    return self->vptr->size(self);
}

// -----------------------------------------------------------------------------
static inline size_t vector_2d_column_count(const struct vector_2d* self)
{
    return vector_2d_row_count(self) > 0U ? 
        vector_size(vector_2d_data_const(self)[0U]) : 0U;
}

// -----------------------------------------------------------------------------
static const vector* dense_layer_output(const struct dense_layer* self)
{
    return self->impl->output;
}

// -----------------------------------------------------------------------------
static const vector* dense_layer_error(const struct dense_layer* self)
{
    return self->impl->error;
}

// -----------------------------------------------------------------------------
static const vector* dense_layer_bias(const struct dense_layer* self)
{
    return self->impl->bias;
}

// -----------------------------------------------------------------------------
static const vector_2d* dense_layer_weights(const struct dense_layer* self)
{
    return self->impl->weights;
}

// -----------------------------------------------------------------------------
static enum act_func dense_layer_act_func(const struct dense_layer* self)
{
    return self->impl->act_func;
}

// -----------------------------------------------------------------------------
static size_t dense_layer_node_count(const struct dense_layer* self)
{
    return self->impl->output->vptr->size(self->impl->output);
}

// -----------------------------------------------------------------------------
static size_t dense_layer_weight_count(const struct dense_layer* self)
{
    return vector_2d_column_count(self->impl->weights);
}

// -----------------------------------------------------------------------------
static bool dense_layer_feedforward(struct dense_layer* self, 
                                    const struct vector* input)
{
    if (!input || !input->vptr->is_arithmetic(input) || 
        (vector_size(input) != self->vptr->weight_count(self))) 
    { 
        return false; 
    }

    for (size_t i = 0U; i < self->vptr->node_count(self); ++i)
    {
        const struct vector* weights = vector_2d_data_const(self->impl->weights)[i];
        double sum                   = vector_data(self->impl->bias)[i];

        for (size_t j = 0U; j < self->vptr->weight_count(self); ++j)
        {
            sum += vector_data_const(weights)[j] * vector_data_const(input)[j];
        }
        vector_data(self->impl->output)[i] = act_func_output(sum, self->impl->act_func);
    }
    return true;
}

// -----------------------------------------------------------------------------
static bool dense_layer_backpropagate_output(struct dense_layer* self, 
                                             const struct vector* reference)
{
    if (!reference || !reference->vptr->is_arithmetic(reference) ||
        vector_size(reference) != self->vptr->node_count(self)) 
    { 
        return false; 
    }

    for (size_t i = 0U; i < self->vptr->node_count(self); ++i)
    {
        const double output               = vector_data_const(self->impl->output)[i];
        const double gradient             = act_func_gradient(output, self->impl->act_func);
        const double error                = vector_data_const(reference)[i] - output;
        vector_data(self->impl->error)[i] = error * gradient;
    }
    return true;
}

// -----------------------------------------------------------------------------
static bool dense_layer_backpropagate_hidden(struct dense_layer* self, 
                                             const struct dense_layer* next_layer)
{
    if (!next_layer || (next_layer->vptr->weight_count(next_layer) != self->vptr->node_count(self))) 
    { 
        return false; 
    }

    const struct vector** next_weights = vector_2d_data_const(next_layer->vptr->weights(next_layer));
    const double* next_error           = vector_data_const(next_layer->vptr->error(next_layer));

    for (size_t i = 0U; i < self->vptr->node_count(self); ++i)
    {
        const double output   = vector_data(self->impl->output)[i];
        const double gradient = act_func_gradient(output, self->impl->act_func);
        double sum            = 0.0;

        for (size_t j = 0U; j < next_layer->vptr->node_count(next_layer); ++j)
        {
            const double* weights = vector_data_const(next_weights[j]);
            sum                   += next_error[j] * weights[i];
        }
        vector_data(self->impl->error)[i] = sum * gradient;
    }
    return true;
}

// -----------------------------------------------------------------------------
static bool dense_layer_optimize(struct dense_layer* self, const struct vector* input,
                                 const double learning_rate)
{
    if (!input || !input->vptr->is_arithmetic(input) || learning_rate <= 0.0 ||
        (vector_size(input) != self->vptr->weight_count(self))) 
    { 
        return false; 
    }

    for (size_t i = 0U; i < self->vptr->node_count(self); ++i)
    {
        const double adjustment = vector_data(self->impl->error)[i] * learning_rate;
        struct vector* weights  = vector_2d_data(self->impl->weights)[i];

        vector_data(self->impl->bias)[i] += adjustment;
        
        for (size_t j = 0U; j < self->vptr->weight_count(self); ++j)
        {
            vector_data(weights)[j] += adjustment * vector_data_const(input)[j];
        }
    }
    return true;
}

// -----------------------------------------------------------------------------
static void dense_layer_print(const struct dense_layer* self, FILE* ostream)
{
    if (!ostream) { ostream = stdout; }
    fprintf(ostream, "--------------------------------------------------------------------------------\n");
    fprintf(ostream, "Output:\t\t\t");
    self->impl->output->vptr->print(self->impl->output, ostream, "\n");
    fprintf(ostream, "Error:\t\t\t");
    self->impl->error->vptr->print(self->impl->error, ostream, "\n");
    fprintf(ostream, "Bias:\t\t\t");
    self->impl->bias->vptr->print(self->impl->bias, ostream, "\n");
    fprintf(ostream, "Weights:\t\t");
    self->impl->weights->vptr->print(self->impl->weights, ostream, "\n");
    fprintf(ostream, "Activation function:\t%s\n", act_func_string(self->impl->act_func));
    fprintf(ostream, "--------------------------------------------------------------------------------\n\n");
}

// -----------------------------------------------------------------------------
static const struct dense_layer_vtable* dense_layer_vptr_new(void)
{
    static const struct dense_layer_vtable vtable =
    {
        .output               = dense_layer_output,
        .error                = dense_layer_error,
        .bias                 = dense_layer_bias,
        .weights              = dense_layer_weights,
        .act_func             = dense_layer_act_func,
        .node_count           = dense_layer_node_count,
        .weight_count         = dense_layer_weight_count,
        .feedforward          = dense_layer_feedforward,
        .backpropagate_output = dense_layer_backpropagate_output,
        .backpropagate_hidden = dense_layer_backpropagate_hidden,
        .optimize             = dense_layer_optimize,
        .print                = dense_layer_print
    };
    return &vtable;
}

// -----------------------------------------------------------------------------
static struct vector* create_node_weights(const size_t weight_count)
{
    struct vector* weights = vector_new(VECTOR_TYPE_DOUBLE, 0, 0);

    if (!weights || !weights->vptr->resize(weights, weight_count))
    { 
        return NULL; 
    }

    for (size_t i = 0U; i < weight_count; ++i) 
    { 
        vector_data(weights)[i] = random_start_value(); 
    }
    return weights;
}

// -----------------------------------------------------------------------------
static bool dense_layer_impl_init_values(struct dense_layer_impl* self, const size_t node_count, 
                                         const size_t weight_count)
{
    for (size_t i = 0U; i < node_count; ++i)
    {
        vector_data(self->output)[i]     = 0.0;
        vector_data(self->error)[i]      = 0.0;
        vector_data(self->bias)[i]       = random_start_value();
        vector_2d_data(self->weights)[i] = create_node_weights(weight_count);
        
        if (!vector_2d_data(self->weights)[i]) 
        { 
            return false; 
        }
    }
    return true;
}

// -----------------------------------------------------------------------------
static bool dense_layer_impl_init(struct dense_layer_impl* self,
                                     const size_t node_count, 
                                     const size_t weight_count)
{
    init_random_generator();

    if (!self->output->vptr->resize(self->output, node_count) ||
        !self->error->vptr->resize(self->error, node_count) ||
        !self->bias->vptr->resize(self->bias, node_count) ||
        !self->weights->vptr->resize(self->weights, node_count)) 
    { 
        return false;
    }
    return dense_layer_impl_init_values(self, node_count, weight_count);
}

// -----------------------------------------------------------------------------
static void dense_layer_impl_delete(struct dense_layer_impl* self)
{
    vector_delete(&self->output);
    vector_delete(&self->error);
    vector_delete(&self->bias);
    vector_2d_delete(&self->weights);
    free(self);
}

// -----------------------------------------------------------------------------
static struct dense_layer_impl* dense_layer_impl_new(const size_t node_count, const size_t weight_count,
                                                     const enum act_func act_func)
{
    struct dense_layer_impl* self = (struct dense_layer_impl*)(malloc(sizeof(struct dense_layer_impl)));
    if (!self) { return NULL; }

    self->output   = vector_new(VECTOR_TYPE_DOUBLE, 0, 0);
    self->error    = vector_new(VECTOR_TYPE_DOUBLE, 0, 0);
    self->bias     = vector_new(VECTOR_TYPE_DOUBLE, 0, 0);
    self->weights  = vector_2d_new(0, 0);
    self->act_func = act_func;

    if (!self->output || !self->error || !self->bias || !self->weights ||
        !dense_layer_impl_init(self, node_count, weight_count))
    {
        dense_layer_impl_delete(self);
        return NULL;
    }
    return self;
}

// -----------------------------------------------------------------------------
struct dense_layer* dense_layer_new(const size_t node_count, 
                                    const size_t weight_count,
                                    const enum act_func act_func)
{
    struct dense_layer* self = (struct dense_layer*)(malloc(sizeof(struct dense_layer)));
    if (!self) { return NULL; }

    self->vptr = dense_layer_vptr_new();
    self->impl = dense_layer_impl_new(node_count, weight_count, act_func);
    
    if (!self->impl)
    {
        free(self);
        return NULL;
    }
    return self;
}

// -----------------------------------------------------------------------------
void dense_layer_delete(struct dense_layer** self)
{
    if (self && *self)
    {
        dense_layer_impl_delete((*self)->impl);
        free(*self);
        *self = NULL;
    }
}
