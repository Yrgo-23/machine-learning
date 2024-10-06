/*******************************************************************************
 * @brief Implementation details of the neural_network struct.
 ******************************************************************************/
#include <stdlib.h>

#include "dense_layer.h"
#include "neural_network.h"
#include "vector.h"
#include "vector_2d.h"

/********************************************************************************
 * @brief Structure holding implementation details of the neural_network struct.
 *******************************************************************************/
struct neural_network_impl
{
    struct dense_layer* hidden_layer;   /* Pointer to the network's hidden layer. */
    struct dense_layer* output_layer;   /* Pointer to the network's output layer. */
    struct vector_2d** training_input;  /* Pointer to vector holding training input. */ 
    struct vector_2d** training_output; /* Pointer to vector holding training output. */ 
    struct vector* training_order;      /* Pointer to vector holding the training order via index.*/
};

// -----------------------------------------------------------------------------
static inline struct vector** vector_2d_data(const struct vector_2d** vector)
{
    return (struct vector**)((*vector)->vptr->data(*vector));
}

// -----------------------------------------------------------------------------
static inline const struct vector** vector_2d_data_const(struct vector_2d** vector)
{
    return (const struct vector**)((*vector)->vptr->data(*vector));
}

// -----------------------------------------------------------------------------
static inline double absolute_value(const double value)
{
    return value >= 0.0 ? value : -value;
}

// -----------------------------------------------------------------------------
static double average_error(const struct vector* v1, const struct vector* v2)
{
    const size_t value_count = v1->vptr->size(v1);

    if (value_count == 0U || (v1->vptr->size(v1) != value_count)) 
    { 
        return -0.0; 
    }
    
    const double* x = (const double*)(v1->vptr->data(v1));
    const double* y = (const double*)(v2->vptr->data(v2));
    double error    = 0.0;

    for (size_t i = 0U; i < value_count; ++i)
    {
        error += absolute_value(x[i] - y[i]);
    }
    return error / value_count;
}

// -----------------------------------------------------------------------------
static bool neural_network_training_sets_match(const struct neural_network* self,
                                               struct vector_2d** input, 
                                               struct vector_2d** output)
{
    if (input && output && *input && *output)
    {
        if ((*input)->vptr->size(*input) == (*output)->vptr->size(*output))
        {
            const struct vector** x = (const struct vector**)((*input)->vptr->data(*input));
            const struct vector** y = (const struct vector**)((*output)->vptr->data(*output));

            for (size_t i = 0U; i < (*input)->vptr->size(*input); ++i)
            {
                if (!x[i] || !y[i] || 
                    (x[i]->vptr->size(x[i]) != self->vptr->input_count(self)) ||
                    (y[i]->vptr->size(y[i]) != self->vptr->output_count(self))) 
                { 
                    return false; 
                } 
            }
            return true;
        }
    }
    return false;
}

// -----------------------------------------------------------------------------
static void neural_network_update_training_sets(struct neural_network* self,
                                                struct vector_2d** input,
                                                struct vector_2d** output)
{
    if (self->impl->training_input && self->impl->training_output)
    {
        vector_2d_delete(self->impl->training_input);
        vector_2d_delete(self->impl->training_output);
    }
    self->impl->training_input  = input;
    self->impl->training_output = output;
}

// -----------------------------------------------------------------------------
static bool neural_network_init_training_order(struct neural_network* self,
                                               const size_t size)
{
    if (self->impl->training_order) 
    { 
        vector_delete(&self->impl->training_order); 
    }

    struct vector* order = vector_new(VECTOR_TYPE_INT, 0, 0);

    if (!order || !order->vptr->resize(order, size)) 
    { 
        return false;
    }

    int* data = (int*)(order->vptr->data(order));
    for (size_t i = 0U; i < size; ++i) { data[i] = i; }
    self->impl->training_order = order;
    return true;
}

// -----------------------------------------------------------------------------
static void neural_network_randomize_training_order(struct neural_network* self)
{
    struct vector* order = self->impl->training_order;
    int* data            = (int*)(order->vptr->data(order));
    const size_t size    = order->vptr->size(order);

    for (size_t i = 0U; i < size; ++i)
    {
        const int temp = data[i];
        const int r    = rand() % size;
        data[i]        = data[r];
        data[r]        = temp;
    }
}

// -----------------------------------------------------------------------------
static bool neural_network_feedforward(struct neural_network* self, const struct vector* input)
{
    if (!input) { return false; }
    struct dense_layer* hidden = self->impl->hidden_layer;
    struct dense_layer* output = self->impl->output_layer;
    return hidden->vptr->feedforward(hidden, input) &&
        output->vptr->feedforward(output, hidden->vptr->output(hidden));
}

// -----------------------------------------------------------------------------
static bool neural_network_backpropagate(struct neural_network* self, const struct vector* reference)
{
    if (!reference) { return false; }
    struct dense_layer* hidden = self->impl->hidden_layer;
    struct dense_layer* output = self->impl->output_layer;
    return output->vptr->backpropagate_output(output, reference) &&
        hidden->vptr->backpropagate_hidden(hidden, output);
}

// -----------------------------------------------------------------------------
static bool neural_network_optimize(struct neural_network* self, const struct vector* input,
                                    const double learning_rate)
{
    if (!input) { return false; }
    struct dense_layer* hidden = self->impl->hidden_layer;
    struct dense_layer* output = self->impl->output_layer;
    return hidden->vptr->optimize(hidden, input, learning_rate) &&
        output->vptr->optimize(output, hidden->vptr->output(hidden), learning_rate);
}

// -----------------------------------------------------------------------------
static bool neural_network_run_epoch(struct neural_network* self, const double learning_rate)
{
    const size_t set_count     = self->vptr->training_set_count(self);
    const struct vector* order = (const struct vector*)(self->impl->training_order);
    const int* indexes         = (const int*)(order->vptr->data(order));

    const struct vector** input     = vector_2d_data_const(self->impl->training_input);
    const struct vector** reference = vector_2d_data_const(self->impl->training_output);

    for (const int* i = indexes; i < indexes + set_count; ++i)
    {
        if (!neural_network_feedforward(self, input[*i]) ||
            !neural_network_backpropagate(self, reference[*i]) ||
            !neural_network_optimize(self, input[*i], learning_rate)) 
            { 
                return false; 
            }
    }
    return true;
}

// -----------------------------------------------------------------------------
static size_t neural_network_input_count(const struct neural_network* self)
{
    return self->impl->hidden_layer->vptr->weight_count(self->impl->hidden_layer);
}

// -----------------------------------------------------------------------------
static size_t neural_network_hidden_nodes_count(const struct neural_network* self)
{
    return self->impl->hidden_layer->vptr->node_count(self->impl->hidden_layer);
}

// -----------------------------------------------------------------------------
static size_t neural_network_output_count(const struct neural_network* self)
{
    return self->impl->output_layer->vptr->node_count(self->impl->output_layer);
}

// -----------------------------------------------------------------------------
static const struct vector* neural_network_output(const struct neural_network* self)
{
    return self->impl->output_layer->vptr->output(self->impl->output_layer);
}

// -----------------------------------------------------------------------------
static size_t neural_network_training_set_count(const struct neural_network* self)
{
    const struct vector* order = (const struct vector*)(self->impl->training_order);
    return order ? order->vptr->size(order) : 0U;
}

// -----------------------------------------------------------------------------
static const struct vector* neural_network_predict(struct neural_network* self, const struct vector* input)
{
    return neural_network_feedforward(self, input) ? self->vptr->output(self) : NULL;
}

// -----------------------------------------------------------------------------
static bool neural_network_add_training_sets(struct neural_network* self, struct vector_2d** training_input,
                                             struct vector_2d** training_output)
{
    if (!neural_network_training_sets_match(self, training_input, training_output)) 
    { 
        return false; 
    }

    const size_t set_count = (*training_input)->vptr->size(*training_input);
    
    if (set_count > 0U && neural_network_init_training_order(self, set_count))
    {
        neural_network_update_training_sets(self, training_input, training_output);
        return true;
    }
    return false;
}

// -----------------------------------------------------------------------------
static double neural_network_train(struct neural_network* self, const size_t epoch_count,
                                   const double learning_rate)
{
    if (epoch_count == 0U || learning_rate <= 0.0 || self->vptr->training_set_count(self) == 0U) 
    { 
        return -1.0; 
    }
    
    for (size_t epoch = 0U; epoch < epoch_count; ++epoch)
    {
        neural_network_randomize_training_order(self);
        
        if (!neural_network_run_epoch(self, learning_rate)) 
        { 
            return -1.0; 
        }
    }
    return self->vptr->accuracy(self);
}

// -----------------------------------------------------------------------------
static double neural_network_accuracy(struct neural_network* self)
{
    if (self->vptr->training_set_count(self) == 0U) { return 0.0; }

    const struct vector** input     = vector_2d_data_const(self->impl->training_input);
    const struct vector** reference = vector_2d_data_const(self->impl->training_output);
    double error                    = 0.0;

    for (size_t i = 0U; i < self->vptr->training_set_count(self); ++i)
    {
        error += average_error(reference[i], self->vptr->predict(self, input[i]));
    }

    return 1.0 - error / self->vptr->training_set_count(self);
}

// -----------------------------------------------------------------------------
static void neural_network_print_results(const struct neural_network* self, FILE* ostream)
{
    if (self->vptr->training_set_count(self) == 0U)
    {
        fprintf(stderr, "Cannot print training results without training data!\n");
        return;
    }

    const struct vector** inputs    = vector_2d_data_const(self->impl->training_input);
    const struct vector** reference = vector_2d_data_const((self->impl->training_output));

    if (!ostream) { ostream = stdout; }
    fprintf(ostream, "--------------------------------------------------------------------------------\n");

    for (size_t i = 0U; i < self->vptr->training_set_count(self); ++i)
    {
        const struct vector* prediction = self->vptr->predict((struct neural_network*)(self), inputs[i]);
        fprintf(ostream, "Input: ");
        inputs[i]->vptr->print(inputs[i], ostream, ", ");
        fprintf(ostream, "prediction: ");
        prediction->vptr->print(prediction, ostream, ", ");
        fprintf(ostream, "reference: ");
        reference[i]->vptr->print(reference[i], ostream, ", ");
        fprintf(ostream, "error: %.2f %%\n", average_error(reference[i], prediction) * 100.0);
    }
    fprintf(ostream, "--------------------------------------------------------------------------------\n\n");
}

// -----------------------------------------------------------------------------
static inline const struct neural_network_vtable* neural_network_vptr_new(void)
{
    static const struct neural_network_vtable vtable = 
    {
        .input_count        = neural_network_input_count,
        .hidden_nodes_count = neural_network_hidden_nodes_count,
        .output_count       = neural_network_output_count,
        .output             = neural_network_output,
        .training_set_count = neural_network_training_set_count,
        .predict            = neural_network_predict,
        .add_training_sets  = neural_network_add_training_sets,
        .train              = neural_network_train,
        .accuracy           = neural_network_accuracy,
        .print_results      = neural_network_print_results
    };
    return &vtable;
};

// -----------------------------------------------------------------------------
static struct neural_network_impl* neural_network_impl_new(
    const size_t input_count, const size_t hidden_nodes_count, const size_t output_count,
    const enum act_func act_func_hidden, const enum act_func act_func_output)
{
    struct neural_network_impl* self = (struct neural_network_impl*)(malloc(sizeof(struct neural_network_impl)));
    if (!self) { return NULL; }

    self->hidden_layer = dense_layer_new(hidden_nodes_count, input_count, act_func_hidden);
    self->output_layer = dense_layer_new(output_count, hidden_nodes_count, act_func_output);

    if (!self->hidden_layer || !self->output_layer)
    {
        free(self->hidden_layer);
        free(self->output_layer);
        free(self);
        return NULL;
    }

    self->training_input  = NULL;
    self->training_output = NULL;
    self->training_order  = NULL;
    return self;
}

// -----------------------------------------------------------------------------
static void neural_network_impl_delete(struct neural_network_impl* self)
{
    dense_layer_delete(&self->hidden_layer);
    dense_layer_delete(&self->output_layer);

    if (self->training_order) 
    { 
        vector_2d_delete((struct vector_2d**)(self->training_input));
        vector_2d_delete((struct vector_2d**)(self->training_output));
        vector_delete(&self->training_order);
    }

    free(self);
}

// -----------------------------------------------------------------------------
struct neural_network* neural_network_new(const size_t input_count, 
                                          const size_t hidden_nodes_count,
                                          const size_t output_count,
                                          const enum act_func act_func_hidden,
                                          const enum act_func act_func_output)
{
    struct neural_network* self = (struct neural_network*)(malloc(sizeof(struct neural_network)));
    if (!self) { return NULL; }

    self->vptr = neural_network_vptr_new();
    self->impl = neural_network_impl_new(input_count, hidden_nodes_count, output_count,
                                         act_func_hidden, act_func_output);
    if (!self->impl)
    {
        free(self);
        return NULL;
    }
    return self;
}

// -----------------------------------------------------------------------------
void neural_network_delete(struct neural_network** self)
{
    if (self && *self)
    {
        neural_network_impl_delete((*self)->impl);
        delete(*self);
        *self = NULL;
    }
}