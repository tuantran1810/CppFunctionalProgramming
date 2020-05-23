#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <boost/phoenix/phoenix.hpp>

int main(void) {
    using namespace boost::phoenix::arg_names;
    std::vector<int> collection = {1, 32, 12, 75, 54, 44, 81, 43, 78};
    std::vector<int>::const_iterator iter = std::partition(collection.begin(), collection.end(), arg1 <= 42);
    std::accumulate(collection.cbegin(), iter, std::ref(std::cout),
        [] (std::ostream& os, const auto& item) -> std::ostream& {
            os << item << " ";
            return os;
        });
    std::cout << std::endl;
    return 0;
}

