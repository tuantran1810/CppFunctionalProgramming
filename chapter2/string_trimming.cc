#include <iostream>
#include <execution>
#include <vector>
#include <algorithm>
#include <string>

std::string trim_left(std::string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [] (char c) -> bool {
        return c != ' ';
    }));
    return s;
}

std::string trim_right(std::string s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [] (char c) -> bool {
        return c != ' ';
    }).base(), s.end());
    return s;
}

std::string trim(std::string s) {
    return trim_right(trim_left(std::move(s)));
}

int main(void) {
    std::cout << trim("     ahihi     bla bla   ") << std::endl;
}

