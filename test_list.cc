#include <iostream>

#include "list.hpp"

//using namespace std;

#define SOLUTION 1  // Change to 1 when completely done

int main() {
#if SOLUTION == 0

    // Minimal code to use the list

    // You are recommended to start with your template implementation
    // and convert this code to instantiate it.
    // Move on to the iterator once it compiles.

    List list;
    decltype(list)::value_type number;

    cout << "Enter numbers, finish by Ctrl-D " << endl;
    while (cin >> number) {
        list.insert(number);
    }

#else
    // example of using the list with integers
    {
        List<int> list;
        decltype(list)::value_type number;

        std::cout << "Enter numbers, finish by Ctrl-D " << std::endl;
        while (std::cin >> number) {
            list.insert(number);
        }

        std::cout << std::endl;

        for (decltype(list)::Iterator it{list.begin()};
             it != list.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        for (auto i : list) {
            std::cout << i << " ";
        }
        std::cout << std::endl;

        std::cout << list << std::endl;
    }

    std::cin.clear();

    // example of using the list with std::string
    // ( notice the overwhelming similarity to above code? )
    {
        List<std::string> list;
        decltype(list)::value_type word;

        std::cout << "Enter words, finish by Ctrl-D " << std::endl;
        while (std::cin >> word) {
            list.insert(word);
        }

        std::cout << std::endl;

        for (decltype(list)::Iterator it{list.begin()};
             it != list.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        for (auto w : list) {
            std::cout << w << " ";
        }
        std::cout << std::endl;

        std::cout << list << std::endl;
    }
#endif

    return 0;
}