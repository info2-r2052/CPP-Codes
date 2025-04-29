#include <iostream>
#include <map>
#include <string>

int main()
{
    std::map<std::string, std::string> mp; //set container for int/string values

    //insert some elements in arbitrary order
    // a value with key 1 gets inserted twice
    mp.insert(std::make_pair("5", "map")); 

    /** 
     *  The  elements are key/value pairs, so you must create such a pair to insert it into the
     *  collection. The auxiliary function make_pair() is provided for this purpose.
     */
    mp.insert(std::make_pair("2", "is a"));
    mp.insert(std::make_pair("1", "sorted"));
    mp.insert(std::make_pair("4", "associative"));
    mp.insert(std::make_pair("6", "container"));
    mp.insert(std::make_pair("1", "key"));
    mp.insert(std::make_pair("3", "value"));

    // print key value pairs
    for (const auto &ele : mp)
    {
        /**
         * you must access the members of the pair structure, which are called first and second
         */
        std::cout << ele.first << " : " << ele.second << std::endl;  
    }
}


