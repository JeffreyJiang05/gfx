#include <iostream>

#include "rflt/rflt.hpp"

struct foo
{
    int i;
    std::string lol;
};

struct test
{
    int i;
    char j;
    foo f;
    std::size_t k;
    std::string test;
    std::string hello;
    foo _;
};

int main()
{
    foo f{ -1, "ello maties" };

    std::cout << rflt::get<0>(f) << "\n";
    rflt::get<0>(f) = 12;
    std::cout << rflt::to_string(f) << "\n";

    test t{ 23, 'c', { 23, "aaa" }, 233, "test", "hello", { 122, "bbb" } };
    std::cout << rflt::to_string(t) << "\n";
}