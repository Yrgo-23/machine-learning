#include <iostream>
#include <cstdlib>

template <typename T>
class vector
{
public:
    std::size_t size() const { return mySize; }

    vector()
    {
        std::cout << "Created vector!\n";
    }

    template <typename... Values>
    vector(const Values&... values)
    {
        for (const auto& i : {values...})
        {
            push_back(i);
        }
    }

    ~vector() { clear(); }

    bool push_back(const T& value)
    {
        T* copy = (T*)realloc(myData, sizeof(T) * (mySize + 1));
        if (!copy) { return false; }
        copy[mySize++] = value;
        myData = copy;
        return true;
    }

    void print(std::ostream& ostream = std::cout) const
    {
        ostream << "[";
        for (std::size_t i{}; i < mySize; ++i)
        {
            ostream << myData[i];
            if (i != mySize - 1U) { ostream << ", "; }
        }
        ostream << "]\n";
    }

    void clear()
    {
        std::cout << "Vector cleared!\n";
        free(myData);
        myData = nullptr;
        mySize = 0;
    }

private:
    T* myData{nullptr};
    size_t mySize{};
};

int main()
{
    vector<int> v1{1, 2, 3, 4, 5};
    v1.print();
    return 0;
}