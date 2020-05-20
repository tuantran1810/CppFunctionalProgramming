#include <iostream>

int ask() { return 42; }

typedef decltype(ask)* function_ptr;

class convertible_to_function_ptr {
public:
    operator function_ptr() const {
        return ask;
    }
};

int main() {
    auto* ask_ptr = &ask;
    auto& ask_ref = ask;
    convertible_to_function_ptr ask_wrapper;

    std::cout << "ask_ptr: " << ask_ptr() << std::endl;
    std::cout << "ask_ref: " << ask_ref() << std::endl;
    std::cout << "ask_wrapper: " << ask_wrapper() << std::endl;
    return 0;
}

