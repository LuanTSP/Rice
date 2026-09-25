#include "Rice/core/application.hpp"
#include <iostream>
#include <Rice.hpp>


int main() {
    std::cout << "Hello World!\n";
    auto app = Rice::Application();
    app.Run();
}