/*******************************************************************************
 * @brief Implementation details of struct dense_layer.
 ******************************************************************************/
#include <stdlib.h>
#include <time.h>

#include "dense_layer.h"

/*******************************************************************************
 * @brief Dense layer structure for neural networks.
 ******************************************************************************/
struct dense_layer
{
    double* output;         /* Pointer to field holding outputs. */
    double* error;          /* Pointer to field holding error values. */
    double* bias;           /* Pointer to field holding the bias of each node. */
    double** weights;       /* Pointer to field holding the weights for each node. */
    size_t node_count;      /* The number of nodes in the layer. */
    size_t weight_count;    /* The number of weights per node in the layer. */
    enum act_func act_func; /* Activation function to use. */
};

// -----------------------------------------------------------------------------
static void init_random(void)
{
    static bool initialized = false;
    if (initialized) { return; }
    srand(time(NULL));
    initialized = true;
}

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
static void double_vector_print(const double* data, const size_t size, 
                                FILE* ostream, const char* end)
{
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
static void double_vector_2d_print(const double** data, const size_t row_count,
                                   const size_t column_count, FILE* ostream,
                                   const char* end)
{
    if (!end) { end = "\n"; }
    fprintf(ostream, "[");

    for (const double** it = data; it < data + row_count; ++it)
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

// -----------------------------------------------------------------------------
static inline double get_random() { return (double)(rand()) / RAND_MAX; }

// -----------------------------------------------------------------------------
static inline struct dense_layer* dense_layer_alloc(void)
{
    return (struct dense_layer*)(malloc(sizeof(struct dense_layer)));
}

// -----------------------------------------------------------------------------
static inline double* double_vector_alloc(const size_t size)
{
    return (double*)(malloc(sizeof(double) * size));
}

// -----------------------------------------------------------------------------
static void double_vector_2d_free(double** self, const size_t row_count)
{
    for (size_t i = 0U; i < row_count; ++i) { free(self[i]); }
    free(self);
}

// -----------------------------------------------------------------------------
static double** double_vector_2d_alloc(const size_t row_count, const size_t column_count)
{
    double** self = (double**)(malloc(sizeof(double*) * row_count));
    if (!self) { return NULL; }

    for (size_t i = 0U; i < row_count; ++i)
    {
        double* column = double_vector_alloc(column_count);

        if (!column) 
        { 
            double_vector_2d_free(self, i); 
            return NULL;
        }

        self[i] = column;
    }
    return self;
}

// -----------------------------------------------------------------------------
static inline bool dense_layer_alloc_success(const struct dense_layer* self)
{
    return self->output && self->error && self->bias && self->weights;
}

// -----------------------------------------------------------------------------
static void dense_layer_clear_parameters(struct dense_layer* self)
{
    free(self->output);
    free(self->error);
    free(self->bias);
    double_vector_2d_free(self->weights, self->node_count);
}

// -----------------------------------------------------------------------------
static void dense_layer_init_parameters(struct dense_layer* self)
{
    init_random();

    for (size_t i = 0U; i < self->node_count; ++i)
    {
        self->output[i] = 0.0;
        self->error[i]  = 0.0;
        self->bias[i]   = get_random();

        for (size_t j = 0U; j < self->weight_count; ++j)
        {
            self->weights[i][j] = get_random();
        }
    }
}

// -----------------------------------------------------------------------------
struct dense_layer* dense_layer_new(const size_t node_count, const size_t weight_count,
                                    const enum act_func act_func)
{
    struct dense_layer* self = dense_layer_alloc();
    if (!self) { return NULL; }
    self->output       = double_vector_alloc(node_count);
    self->error        = double_vector_alloc(node_count);
    self->bias         = double_vector_alloc(node_count);
    self->weights      = double_vector_2d_alloc(node_count, weight_count);
    self->node_count   = node_count;
    self->weight_count = weight_count;

    if (!dense_layer_alloc_success(self)) 
    { 
        dense_layer_delete(&self);
        return NULL;
    }

    dense_layer_init_parameters(self);
    return self;
}

// -----------------------------------------------------------------------------
void dense_layer_delete(struct dense_layer** self)
{
    if (self && *self)
    {
        dense_layer_clear_parameters(*self);
        free(*self);
        *self = NULL;
    }
}

// -----------------------------------------------------------------------------
const double* dense_layer_output(const struct dense_layer* self)
{
    return self->output;
}

// -----------------------------------------------------------------------------
const double* dense_layer_error(const struct dense_layer* self)
{
    return self->error;
}

// -----------------------------------------------------------------------------
const double* dense_layer_bias(const struct dense_layer* self)
{
    return self->bias;
}

// -----------------------------------------------------------------------------
const double** dense_layer_weights(const struct dense_layer* self)
{
    return (const double**)(self->weights);
}

// -----------------------------------------------------------------------------
enum act_func dense_layer_act_func(const struct dense_layer* self)
{
    return self->act_func;
}

// -----------------------------------------------------------------------------
size_t dense_layer_node_count(const struct dense_layer* self)
{
    return self->node_count;
}

// -----------------------------------------------------------------------------
size_t dense_layer_weight_count(const struct dense_layer* self)
{
    return self->weight_count;
}

// -----------------------------------------------------------------------------
bool dense_layer_feedforward(struct dense_layer* self, const double* input, 
                             const size_t input_count)
{
    if (input_count != self->weight_count) { return false; }

    for (size_t i = 0U; i < self->node_count; ++i)
    {
        double sum = self->bias[i];

        for (size_t j = 0U; j < self->weight_count; ++j)
        {
            sum += self->weights[i][j] * input[j];
        }
        self->output[i] = act_func_output(sum, self->act_func);
    }
    return true;
}

// -----------------------------------------------------------------------------
bool dense_layer_backpropagate_output(struct dense_layer* self, const double* reference,
                                      const size_t reference_count)
{
    if (reference_count != self->node_count) { return false; }

    for (size_t i = 0U; i < self->node_count; ++i)
    {
        const double error = reference[i] - self->output[i];
        self->error[i] = error * act_func_gradient(self->output[i], self->act_func);
    }
    return true;
}

// -----------------------------------------------------------------------------
bool dense_layer_backpropagate_hidden(struct dense_layer* self,
                                      const struct dense_layer* next_layer)
{
    if (next_layer->weight_count != self->node_count) { return false; }

    for (size_t i = 0U; i < self->node_count; ++i)
    {
        double error = 0.0;

        for (size_t j = 0U; j < next_layer->node_count; ++j)
        {
            error += next_layer->error[j] * next_layer->weights[j][i];
        }
        self->error[i] = error * act_func_gradient(self->output[i], self->act_func);
    }
    return true;
}

// -----------------------------------------------------------------------------
bool dense_layer_optimize(struct dense_layer* self, const double* input,
                          const size_t input_count, const double learning_rate)
{
    if ((input_count != self->node_count) && (learning_rate <= 0.0)) { return false; }
    
    for (size_t i = 0U; i < self->node_count; ++i)
    {
        self->bias[i] += self->error[i] * learning_rate;

        for (size_t j = 0U; j < self->weight_count; ++j)
        {
            self->weights[i][j] += self->error[i] * learning_rate * input[j];
        }
    }
    return true;
}

// -----------------------------------------------------------------------------
void dense_layer_print(const struct dense_layer* self, FILE* ostream)
{
    if (!ostream) { ostream = stdout; }
    fprintf(ostream, "--------------------------------------------------------------------------------\n");
    fprintf(ostream, "Output: ");
    double_vector_print(self->output, self->node_count, ostream, 0);
    fprintf(ostream, "Error: ");
    double_vector_print(self->error, self->node_count, ostream, 0);
    fprintf(ostream, "Bias: ");
    double_vector_print(self->bias, self->node_count, ostream, 0);
    fprintf(ostream, "Weights: ");
    double_vector_2d_print((const double**)(self->weights), self->node_count, self->weight_count, ostream, 0);
    fprintf(ostream, "--------------------------------------------------------------------------------\n\n");
}
