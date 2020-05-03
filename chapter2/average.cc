#include <iostream>
#include <execution>
#include <vector>
#include <algorithm>
#include <numeric>

double average1(const std::vector<int>& scores) {
    int sum = 0;
    for (auto score : scores) {
        sum += score;
    }
    return sum/(double)scores.size();
}

double average2(const std::vector<int>& scores) {
    return std::accumulate(scores.cbegin(), scores.cend(), 0)/(double)scores.size();
}

double average3(const std::vector<int>& scores) {
    return std::reduce(std::execution::par, scores.cbegin(), scores.cend(), 0)/(double)scores.size();
}

int main(void) {
    std::vector<int> scores = {9, 7, 10, 5, 8, 8, 6};
    std::cout << average1(scores) << std::endl;
    std::cout << average2(scores) << std::endl;
    std::cout << average3(scores) << std::endl;
}
