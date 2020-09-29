#include <iostream>
#include "SenderApp/SenderApp.hpp"

int main(int argc, const char **argv) {
    std::cout << "aaaa" << std::endl;
    app::sender::SenderApp app(&argc, &argv);
    return 0;
}
