// tet.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <vector>
#include <algorithm>
#include "boost/asio.hpp"
/*
auto tet_fun(int a, int b) -> void { std::cout << a + b << std::endl; }
class MyClass {
public:
    MyClass(int, int);
    ~MyClass();

private:
    int a;
    int b;
};

MyClass::MyClass(int a, int b) {
    a = a;
    b = b;
};

MyClass::~MyClass() {}
int main() {
    int a { 5 };
    int b {};
    int c {};
    std::cout << "Hello World!\n";
    tet_fun(4, 5);
    auto io_contet = new boost::asio::io_context {};
    auto timer     = new boost::asio::steady_timer { *io_contet, boost::asio::chrono::seconds(5) };
    //timer->expires_from_now(boost::asio::chrono::seconds(5));
    timer->async_wait([](auto err) {
        if (!err) {
            std::cout << "time_out";
        }
    });
    io_contet->run();
    // Initialization ith curly brace
    MyClass          d { 3, 4 };
    std::vector<int> myvector;
    myvector.push_back(1);
    myvector.push_back(2);
    myvector.push_back(3);
    for_each(myvector.begin(), myvector.end(), [](int x) { std::cout << x * x << std::endl; });

    std::cout << "a=" << a << "b=" << b << "c=" << c;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
*/
/*
#include <boost/process.hpp>

#include <string>
#include <iostream>

using namespace boost::process;

int main() {
    ipstream pipe_stream;
    child    c("gcc --version", std_out > pipe_stream);

    std::string line;

    while (pipe_stream && std::getline(pipe_stream, line) && !line.empty())
        std::cerr << line << std::endl;

    c.wait();
}
*/

/*
* 
* The implementation of the shared pointer 
#include "Shared.hpp"
template <class T>
int multiplyby2(T a) {
    return 2 * a.getdata();
}
template <class T>
int multiplyby3(T a) {
    return 3 * a.getdata();
}
template <typename T>
T multall(T a, T b, T c) {
    return a * b * c;
}
auto main() -> int {

    Shared<int> a { new int { 5 } };
    int         a1 = 2, a2 = 3;
    auto        f1 = std::bind(multall, a1, a2);
    auto        b  = multiplyby2(a);
    auto        c  = multiplyby3(a);
    return 0;
}
*/

#include <random>
#include <iostream>
#include <memory>
#include <functional>
//template <typename T>
//void f(T n1, T n2, T n3, const T &n4, T n5) {
//    std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
//}
void f(int n1, int n2, int n3, const int &n4, int n5) { //
    std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}

template <class T>
T multall(T a, T b, T c) { //
    return a * b * c;
}
int g(int n1) { return n1; }

struct Foo {
    void print_sum(int n1, int n2) { std::cout << n1 + n2 << '\n'; }
    int  data = 10;
};

int main() {
    using namespace std::placeholders; // for _1, _2, _3...
    auto f2 = std::bind(multall<int>, 2, 3, std::placeholders::_1);
    std::cout << f2(9) << std::endl;

    std::cout << "1) argument reordering and pass-by-reference: ";
    int n = 7;
    // (_1 and _2 are from std::placeholders, and represent future
    // arguments that will be passed to f1)
    auto f1 = std::bind(f, _2, 42, _1, std::cref(n), n);
    n       = 10;
    f1(1, 2, 1001); // 1 is bound by _1, 2 is bound by _2, 1001 is unused
                    // makes a call to f(2, 42, 1, n, 7)

    std::cout << "2) achieving the same effect using a lambda: ";
    n           = 7;
    auto lambda = [ncref = std::cref(n), n = n](auto a, auto b, auto /*unused*/) { f(b, 42, a, ncref, n); };
    n           = 10;
    lambda(1, 2, 1001); // same as a call to f1(1, 2, 1001)

    std::cout << "3) nested bind subexpressions share the placeholders: ";
    auto f2 = std::bind(f, _3, std::bind(g, _3), _3, 4, 5);
    f2(10, 11, 12); // makes a call to f(12, g(12), 12, 4, 5);

    std::cout << "4) bind a RNG with a distribution: ";
    std::default_random_engine      e;
    std::uniform_int_distribution<> d(0, 10);
    auto                            rnd = std::bind(d, e); // a copy of e is stored in rnd
    for (int n = 0; n < 10; ++n)
        std::cout << rnd() << ' ';
    std::cout << '\n';

    std::cout << "5) bind to a pointer to member function: ";
    Foo  foo;
    auto f3 = std::bind(&Foo::print_sum, &foo, 95, _1);
    f3(5);

    std::cout << "6) bind to a mem_fn that is a pointer to member function: ";
    auto ptr_to_print_sum = std::mem_fn(&Foo::print_sum);
    auto f4               = std::bind(ptr_to_print_sum, &foo, 95, _1);
    f4(5);

    std::cout << "7) bind to a pointer to data member: ";
    auto f5 = std::bind(&Foo::data, _1);
    std::cout << f5(foo) << '\n';

    std::cout << "8) bind to a mem_fn that is a pointer to data member: ";
    auto ptr_to_data = std::mem_fn(&Foo::data);
    auto f6          = std::bind(ptr_to_data, _1);
    std::cout << f6(foo) << '\n';

    std::cout << "9) use smart pointers to call members of the referenced objects: ";
    std::cout << f6(std::make_shared<Foo>(foo)) << ' ' << f6(std::make_unique<Foo>(foo)) << '\n';
}