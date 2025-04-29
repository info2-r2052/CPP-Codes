#include <iostream>
#include <vector> // header for vector+
#include <string>

int main()
{
    std::vector<std::string> vec; //vector container for integer elements

    for (int i = 1 ; i <= 6 ; ++i)
    {
        vec.push_back(std::to_string(i));
    }

    //print all elements followed by a space
    for (int i = 0 ; i <= vec.size() ; ++i)
    {
        std::cout << vec.at(i);
    }

    for (const auto &ele : vec)
    {
        std::cout << ele << ' ';
    }

    std::cout << std::endl;
}


