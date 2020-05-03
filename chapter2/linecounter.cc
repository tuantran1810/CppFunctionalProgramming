#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

int count_lines(const std::string& file) {
    std::ifstream in(file);
    return std::accumulate(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>(),
        0, [] (int previousCount, char c) -> int {
            return (c != '\n') ? previousCount : previousCount + 1;
        });
}

std::vector<int> count_lines_in_files(const std::vector<std::string>& files) {
    std::vector<int> result(files.size());
    std::transform(files.cbegin(), files.cend(), result.begin(), count_lines);
    return result;
}

void print_vector(const std::vector<int>& v) {
    std::cout << "Result: " << std::endl;
    for (const auto& item : v) {
        std::cout << item << std::endl;
    }
    std::cout << "==================" << std::endl;
}

int main(void) {
    std::vector<std::string> files = {"./test_files/test1.txt", "./test_files/test2.txt", "./test_files/test3.txt"};
    auto execute = [] (const std::vector<std::string>& files, std::vector<int> func(const std::vector<std::string>&)) {
        std::vector<int> result1 = func(files);
        print_vector(result1);
    };
    execute(files, count_lines_in_files);
    return 0;
}

