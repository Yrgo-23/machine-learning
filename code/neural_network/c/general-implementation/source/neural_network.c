/*******************************************************************************
 * @brief Implementation details of struct neural_network.
 ******************************************************************************/
#include <stdlib.h>

#include "act_func.h"
#include "dense_layer.h"
#include "double_vector.h"
#include "neural_network.h"

/*******************************************************************************
 * @brief Neural network structure.
 ******************************************************************************/
struct neural_network
{
    struct dense_layer* hidden_layer; /* Pointer to the network's hidden layer. */
    struct dense_layer* output_layer; /* Pointer to the network's output layer. */
    double** training_input;          /* Pointer to field holding training inputs. */
    double** training_output;         /* Pointer to field holding training outputs. */
    size_t* training_order;           /* Pointer to field holding training order via index. */
    size_t training_set_count;        /* The number of stored training sets. */
};

// -----------------------------------------------------------------------------
static inline double absolute_value(const double value)
{
    return value >= 0.0 ? value : -value;
}

// -----------------------------------------------------------------------------
static double average_error(const double* v1, const double* v2, const size_t size)
{
    if (!v1 || !v2 || (size == 0U)) { return 0.0; }
    double error = 0.0;

    for (size_t i = 0U; i < size; ++i)
    {
        error += absolute_value(v1[i] - v2[i]);
    }
    return error / size;
}

// -----------------------------------------------------------------------------
static size_t* training_order_vector_new(const size_t size)
{
    size_t* order = (size_t*)(malloc(sizeof(size_t) * size));
    if (!order) { return NULL; }
    for (size_t i = 0U; i < size; ++i) { order[i] = i; }
    return order;
}

// -----------------------------------------------------------------------------
static bool verify_training_sets(double** input, double** output, const size_t set_count)
{
    if (!input || !output || (set_count == 0U)) { return false; }

    for (size_t i = 0U; i < set_count; ++i)
    {
        if (!input[i] || !output[i]) { return false; }
    }
    return true;
}

// -----------------------------------------------------------------------------
static void neural_network_delete_training_sets(struct neural_network* self)
{
    double_vector_2d_delete(&self->training_input, self->training_set_count);
    double_vector_2d_delete(&self->training_output, self->training_set_count);
    free(self->training_order);
}

// -----------------------------------------------------------------------------
static inline struct neural_network* neural_network_alloc(void)
{
    return (struct neural_network*)(malloc(sizeof(struct neural_network)));
}

// -----------------------------------------------------------------------------
static void neural_network_dealloc(struct neural_network* self)
{
    dense_layer_delete(&(self->hidden_layer));
    dense_layer_delete(&(self->output_layer));
    neural_network_delete_training_sets(self);
    free(self);
}

// -----------------------------------------------------------------------------
static void neural_network_randomize_training_order(struct neural_network* self)
{
    for (size_t i = 0U; i < self->training_set_count; ++i)
    {
        const size_t r          = rand() % self->training_set_count;
        const size_t temp       = self->training_order[i];
        self->training_order[i] = self->training_order[r];
        self->training_order[r] = temp;
    }
}

// -----------------------------------------------------------------------------
static bool neural_network_feedforward(struct neural_network* self, const double* input,
                                       const size_t input_count)
{
    const double* hidden_output    = dense_layer_output(self->hidden_layer);
    const size_t hidden_node_count =  dense_layer_node_count(self->hidden_layer);

    return dense_layer_feedforward(self->hidden_layer, input, input_count) &&
        dense_layer_feedforward(self->output_layer, hidden_output, hidden_node_count);
}


// -----------------------------------------------------------------------------
static bool neural_network_backpropagate(struct neural_network* self, const double* output,
                                         const size_t output_count)
{
    return dense_layer_backpropagate_output(self->output_layer, output, output_count) &&
        dense_layer_backpropagate_hidden(self->hidden_layer, self->output_layer);
}


// -----------------------------------------------------------------------------
static bool neural_network_optimize(struct neural_network* self, const double* input,
                                       const size_t input_count, const double learning_rate)
{
    const double* hidden_output    = dense_layer_output(self->hidden_layer);
    const size_t hidden_node_count =  dense_layer_node_count(self->hidden_layer);

    return dense_layer_optimize(self->hidden_layer, input, input_count, learning_rate) &&
        dense_layer_optimize(self->output_layer, hidden_output, hidden_node_count, learning_rate);
}

// -----------------------------------------------------------------------------
struct neural_network* neural_network_new(const size_t input_count, 
                                          const size_t hidden_count,
                                          const size_t output_count, 
                                          const enum act_func act_func_hidden,
                                          const enum act_func act_func_output)
{
    struct neural_network* self = neural_network_alloc();
    if (!self) { return NULL; }

    self->hidden_layer = dense_layer_new(hidden_count, input_count, act_func_hidden);
    self->output_layer = dense_layer_new(output_count, hidden_count, act_func_output);

    if (!self->hidden_layer || !self->output_layer) 
    { 
        neural_network_delete(&self); 
        return NULL;
    }

    self->training_input     = NULL;
    self->training_output    = NULL;
    self->training_order     = NULL;
    self->training_set_count = 0U;
    return self;
}

// -----------------------------------------------------------------------------
void neural_network_delete(struct neural_network** self)
{
    if (self && *self)
    {
        neural_network_dealloc(*self);
        *self = NULL;
    }
}

// -----------------------------------------------------------------------------
size_t neural_network_input_count(const struct neural_network* self)
{
    return dense_layer_weight_count(self->hidden_layer);
}

// -----------------------------------------------------------------------------
size_t neural_network_hidden_nodes_count(const struct neural_network* self)
{
    return dense_layer_node_count(self->hidden_layer);
}

// -----------------------------------------------------------------------------
size_t neural_network_output_count(const struct neural_network* self)
{
    return dense_layer_node_count(self->output_layer);
}

// -----------------------------------------------------------------------------
const double* neural_network_output(const struct neural_network* self)
{
    return dense_layer_output(self->output_layer);
}

// -----------------------------------------------------------------------------
size_t neural_network_training_set_count(const struct neural_network* self)
{
    return self->training_set_count;
}

// -----------------------------------------------------------------------------
const double* neural_network_predict(struct neural_network* self, const double* input,
                                     const size_t input_count)
{
    return neural_network_feedforward(self, input, input_count) ?
        neural_network_output(self) : NULL;
}

// -----------------------------------------------------------------------------
bool neural_network_add_training_sets(struct neural_network* self, double** input,
                                      double** output, const size_t set_count)
{
    if (!verify_training_sets(input, output, set_count)) { return false; }
    self->training_order = training_order_vector_new(set_count);
    if (!self->training_order) { return false; }

    self->training_input     = input;
    self->training_output    = output;
    self->training_set_count = set_count;
    return true;
}

// -----------------------------------------------------------------------------
double neural_network_train(struct neural_network* self, const size_t epoch_count,
                            const double learning_rate)
{
    if ((epoch_count == 0U) || (learning_rate <= 0.0) || (self->training_set_count == 0U))
    {
        return -1.0;
    }

    const size_t input_count  = neural_network_input_count(self);
    const size_t output_count = neural_network_output_count(self);

    for (size_t epoch = 0U; epoch < epoch_count; ++epoch)
    {
        neural_network_randomize_training_order(self);

        for (size_t* i = self->training_order; i < self->training_order + self->training_set_count; ++i)
        {
            const double* input  = self->training_input[*i];
            const double* output = self->training_output[*i];

             if (!neural_network_feedforward(self, input, input_count) ||
                !neural_network_backpropagate(self, output, output_count) ||
                !neural_network_optimize(self, input, input_count, learning_rate))
            {
                return false;
            }
        }
    }
    
    return neural_network_accuracy(self);
}

// -----------------------------------------------------------------------------
double neural_network_accuracy(struct neural_network* self)
{
    if (self->training_set_count == 0U) { return 0.0; }
    const size_t input_count  = neural_network_input_count(self);
    const size_t output_count = neural_network_output_count(self);
    double error              = 0.0;

    for (size_t i = 0U; i < self->training_set_count; ++i)
    {
        const double* input       = self->training_input[i];
        const double* reference   = self->training_output[i];
        const double* prediction  = neural_network_predict(self, input, input_count);
        error                     += average_error(reference, prediction, output_count);
    }

    return 1.0 - error / self->training_set_count;
}

// -----------------------------------------------------------------------------
void neural_network_print_results(struct neural_network* self, FILE* ostream)
{
    if (self->training_set_count == 0U)
    {
        fprintf(stderr, "Cannot print training results without training data!\n");
        return;
    }

    const size_t input_count  = neural_network_input_count(self);
    const size_t output_count = neural_network_output_count(self);

    if (!ostream) { ostream = stdout; }
    fprintf(ostream, "--------------------------------------------------------------------------------\n");

    for (size_t i = 0U; i < self->training_set_count; ++i)
    {
        const double* input      = self->training_input[i];
        const double* reference  = self->training_output[i];
        const double* prediction = neural_network_predict(self, input, input_count);

        fprintf(ostream, "Input: ");
        double_vector_print(input, input_count, ostream, ", ");
        fprintf(ostream, "prediction: ");
        double_vector_print(prediction, output_count, ostream, ", ");
        fprintf(ostream, "reference: ");
        double_vector_print(reference, output_count, ostream, ", ");
        fprintf(ostream, "error: %.2f %%\n", average_error(reference, prediction, output_count) * 100.0);
    }
    fprintf(ostream, "--------------------------------------------------------------------------------\n\n");
}