/*******************************************************************************
 * @brief Implementation of regression model for prediction of linear patterns.
 * 
 *        This file defines a linear regression structure that contains the
 *        core functionality of a linear regression model, including training
 *        and prediction.
 ******************************************************************************/
#ifndef LIN_REG_INCLUDED
#define LIN_REG_INCLUDED

#include <stdio.h>

/*******************************************************************************
 * @brief Forward declarations.
 ******************************************************************************/
struct lin_reg; /* Structure definition of a linear regression model. */

/*******************************************************************************
 * @brief Creates new linear regression model.
 * 
 * @param training_input     Pointer to array holding training input.
 * @param training_output    Pointer to array holding training output.
 * @param training_set_count The number of training sets.
 * 
 * @return Pointer to the linear regression model. If the model couldn't
 *         be created due to lack of memory, NULL is returned.
 ******************************************************************************/
struct lin_reg* lin_reg_new(const double* training_input, 
                            const double* training_output, 
                            const size_t training_set_count);

/*******************************************************************************
 * @brief Frees memory allocated for linear regression model.
 * 
 * @param self Double pointer to the linear regression model.
 ******************************************************************************/
void lin_reg_delete(struct lin_reg** self);

/*******************************************************************************
 * @brief Performs prediction with given input.
 * 
 * @param self  Pointer to the linear regression model.
 * @param input The input to predict with.
 * 
 * @return The predicted output as a double.
 ******************************************************************************/
double lin_reg_predict(const struct lin_reg* self, const double input);

/*******************************************************************************
 * @brief Trains the model with available training data.
 * 
 * @param self          Pointer to the linear regression model.
 * @param epoch_count   The number of epochs to train the model.
 * @param learning_rate The learning rate to train with (default = 1 %).
 * 
 * @return The model's accuracy post training as a double between 0 - 1.
 *         If an error occurs due to invalid parameters (epoch_count == 0 
 *         or learning_rate <= 0.0), -1.0 is returned.
 ******************************************************************************/
double lin_reg_train(struct lin_reg* self, const size_t epoch_count, 
                     const double learning_rate);

/*******************************************************************************
 * @brief Provides the accuracy of the model based on available training data.
 * 
 * @param self Pointer to the linear regression model.
 * 
 * @return The accuracy as a floating point number between 0 - 1.
 ******************************************************************************/
double lin_reg_accuracy(const struct lin_reg* self);

/*******************************************************************************
 * @brief Prints results post training by using input values from stored
 *        training sets.
 * 
 * @param self    Pointer to the linear regression model.
 * @param ostream Pointer to output stream (default = terminal print).
 ******************************************************************************/
void lin_reg_print_results(const struct lin_reg* self, FILE* ostream);

#endif /* LIN_REG_INCLUDED */