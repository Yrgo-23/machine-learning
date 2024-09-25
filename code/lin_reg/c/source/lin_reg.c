/*******************************************************************************
 * @brief Implementation details of struct lin_reg.
 ******************************************************************************/
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "lin_reg.h"

/*******************************************************************************
 * @brief Structure definition of a linear regression model.
 ******************************************************************************/
struct lin_reg
{
    const double* training_input;  /* Pointer to array holding training input. */
    const double* training_output; /* Pointer to array holding training output */
    size_t* training_order;        /* Pointer to field holding the training order via index. */
    size_t training_set_count;     /* The number of stored training sets. */
    double bias;                   /* The model's bias. */
    double weight;                 /* The model's weight. */
};

// -----------------------------------------------------------------------------
static void init_random_generator()
{
    static bool generator_initialized = false;

    if (!generator_initialized)
    {
        srand((unsigned)(time(NULL)));
        generator_initialized = true;
    }
}

// -----------------------------------------------------------------------------
static double get_random_start_value()
{
    init_random_generator();
    return (double)(rand()) / RAND_MAX;
}

// -----------------------------------------------------------------------------
static inline double absolute_value(const double number)
{
    return number >= 0 ? number : -number;
}

// -----------------------------------------------------------------------------
static size_t* new_training_order_vec(const size_t size)
{
    size_t* training_order = (size_t*)(malloc(sizeof(size_t) * size));
    if (!training_order) { return NULL; }

    for (size_t i = 0U; i < size; ++i)
    {
        training_order[i] = i;
    }
    return training_order;
}

// -----------------------------------------------------------------------------
static inline double round_to_zero(const double number)
{
    return absolute_value(number) < 0.001 ? 0.0 : number;
}

// -----------------------------------------------------------------------------
static void lin_reg_randomize_training_order(struct lin_reg* self)
{
    if (!self->training_order) { return; }

    for (size_t i = 0U; i < self->training_set_count; ++i)
    {
        const size_t r          = rand() % self->training_set_count;
        const size_t temp       = self->training_order[i];
        self->training_order[i] = self->training_order[r];
        self->training_order[r] = temp;
    }
}

// -----------------------------------------------------------------------------
static void lin_reg_optimize(struct lin_reg* self, const double input,
                             const double reference, const double learning_rate)
{
    if (input == 0.0)
    {
        self->bias = reference; 
    }
    else
    {
        const double prediction = lin_reg_predict(self, input);
        const double error      = reference - prediction;
        self->bias              += error * learning_rate;
        self->weight            += error * learning_rate * input;
    }
}

// -----------------------------------------------------------------------------
struct lin_reg* lin_reg_new(const double* training_input, 
                            const double* training_output, 
                            const size_t training_set_count)
{
    struct lin_reg* self = (struct lin_reg*)(malloc(sizeof(struct lin_reg)));
    if (!self) { return NULL; }

    self->training_input     = training_input;
    self->training_output    = training_output;
    self->training_order     = new_training_order_vec(training_set_count);
    self->training_set_count = training_set_count;
    self->bias               = get_random_start_value();
    self->weight             = get_random_start_value();
    return self;
}

// -----------------------------------------------------------------------------
void lin_reg_delete(struct lin_reg** self)
{
    if (self && *self)
    {
        free((*self)->training_order);
        free(*self);
        *self = NULL;
    }
}

// -----------------------------------------------------------------------------
double lin_reg_predict(const struct lin_reg* self, const double input)
{
    return self->weight * input + self->bias;
}

// -----------------------------------------------------------------------------
double lin_reg_train(struct lin_reg* self, const size_t epoch_count, 
                     const double learning_rate)
{
    if ((epoch_count == 0U) || (learning_rate <= 0.0)) { return -1.0; }

    for (size_t epoch = 0U; epoch < epoch_count; ++epoch)
    {
        lin_reg_randomize_training_order(self);

        for (size_t i = 0U; i < self->training_set_count; ++i)
        {
            const double input     = self->training_input[i];
            const double reference = self->training_output[i];
            lin_reg_optimize(self, input, reference, learning_rate);
        }
    }

    return lin_reg_accuracy(self);
}

// -----------------------------------------------------------------------------
double lin_reg_accuracy(const struct lin_reg* self)
{
    if (self->training_set_count == 0U) { return 0.0; }
    double error = 0.0;

    for (size_t i = 0U; i < self->training_set_count; ++i)
    {
        const double input      = self->training_input[i];
        const double reference  = self->training_output[i];
        const double prediction = lin_reg_predict(self, input);
        error += absolute_value(reference - prediction);
    }
    return 1.0 - error / self->training_set_count;
    
}

// -----------------------------------------------------------------------------
void lin_reg_print_results(const struct lin_reg* self, FILE* ostream)
{
    if (self->training_set_count == 0U) { return; }
    if (!ostream) { ostream = stdout; }
    fprintf(ostream, "--------------------------------------------------------------------------------\n");

    for (size_t i = 0U; i < self->training_set_count; ++i)
    {
        const double input      = self->training_input[i];
        const double prediction = lin_reg_predict(self, input);
        const double reference  = self->training_output[i];
        const double error      = round_to_zero(reference - prediction);

        fprintf(ostream, "Input: %.1f, ", input);
        fprintf(ostream, "prediction: %.1f, ", prediction);
        fprintf(ostream, "reference: %.1f, ", reference);
        fprintf(ostream, "error: %.1f\n", error);
    }
    fprintf(ostream, "--------------------------------------------------------------------------------\n\n");
}
