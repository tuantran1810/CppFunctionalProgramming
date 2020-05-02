#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::vector<int>
count_lines_in_files1(const std::vector<std::string>& files) {
    std::vector<int> result;
    char c = 0;
    for (const auto& file : files) {
        int line_count = 0;
        std::ifstream in(file);
        while (in.get(c))
            if (c == '\n') line_count++;
        result.push_back(line_count);
    }
    return result;
}

int
count_lines(const std::string& filename) {
    std::ifstream in(filename);
    return std::count(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>(), '\n');
}

std::vector<int>
count_lines_in_files2(const std::vector<std::string>& files) {
    std::vector<int> result;
    for (const auto& file : files) {
        result.push_back(count_lines(file));
    }
    return result;
}

std::vector<int>
count_lines_in_files3(const std::vector<std::string>& files) {
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
    execute(files, count_lines_in_files1);
    execute(files, count_lines_in_files2);
    execute(files, count_lines_in_files3);
    return 0;
}
