/*******************************************************************************
 * @brief Implementation details of the ml::Node class.
 ********************************************************************************/
#include <cstdlib>
#include <ctime>

#include "node.h"

namespace
{

// -----------------------------------------------------------------------------
constexpr double relu(const double x) { return x > 0 ? x : 0; }

// -----------------------------------------------------------------------------
constexpr double reluDelta(const double y) { return y > 0 ? 1 : 0; }

// -----------------------------------------------------------------------------
void initRandomGenerator() 
{ 
    static auto generatorInitialized{false};

    if (!generatorInitialized) 
    {
        std::srand(std::time(nullptr));
        generatorInitialized = true;
    }
}

// -----------------------------------------------------------------------------
static double getRandom(const double min = 0, const double max = 1)
{ 
    return (std::rand() / static_cast<double>(RAND_MAX)) * (max - min) + min; 
}

} // namespace