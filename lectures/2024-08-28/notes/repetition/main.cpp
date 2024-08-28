/*******************************************************************************
 * @brief Repetition exercise containing vectors, type traits, prints etc.
 ******************************************************************************/
#include <fstream>

#include "vector.h"

/*******************************************************************************
 * @brief Assigns numbers to different vectors and prints the content to
 *        the terminal and a file named "data.txt".
 * 
 * @return Success code 0 upon termination of the program.
 ******************************************************************************/
int main()
{   
    std::ofstream ostream{"data.txt"}; /** Opens file "data.txt" for writing. */
    std::vector<int> v1{};             /** Creates empty int vector v1. */
    vector::assign(v1, 20);            /** Assigns {0, 1, 2, 3... 19} to v1. */
    vector::print(v1);                 /** Prints content of v1 in the terminal. */
    vector::print(v1, ostream);        /** Prints content of v1 to file "data.txt". */

    std::vector<double> v2{};          /** Creates empty double vector v2. */
    vector::assign(v2, 10, 0.0, 0.5);  /** Assigns {0, 0.5, 1.0... 4.5} to v2. */
    vector::print(v2);                 /** Prints content of v2 in the terminal. */
    vector::print(v2, ostream);        /** Prints content of v2 to file "data.txt". */

    /** Creates string vector v3 holding two strings. */
    const std::vector<const char*> v3{"Hello there", "how are you?"}; 
    vector::print(v3);                 /** Prints content of v3 in the terminal. */
    vector::print(v3, ostream);        /** Prints content of v3 to file "data.txt". */
    return 0;                          /** Returns success code 0 upon termination of the program. */
}