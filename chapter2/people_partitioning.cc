#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

struct Person {
    std::string name;
    bool isMale;

    Person(std::string name, bool isMale): name(name), isMale(isMale) {}
    friend std::ostream& operator<<(std::ostream& os, const Person& p);
};

std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << "Name: " << p.name << ", Gender: " << (p.isMale? "Male":"Female");
    return os;
}

struct People: public std::vector<Person> {
    People(std::initializer_list<Person>&& lst) {
        std::for_each(lst.begin(), lst.end(), [this] (const Person& p) {
            this->push_back(p);
            return true;
        });
    }

    People::iterator partition() {
        return std::partition(this->begin(), this->end(), [] (const Person& p) {
            return !p.isMale;
        });
    }

    People::iterator stable_partition() {
        return std::stable_partition(this->begin(), this->end(), [] (const Person& p) {
            return !p.isMale;
        });
    }

    friend std::ostream& operator<<(std::ostream& os, const People& p);
};

std::ostream& operator<<(std::ostream& os, const People& p) {
    return std::accumulate(p.cbegin(), p.cend(), std::ref(os),
        [] (std::ostream& os_, Person person) -> std::ostream& {
            os_ << person << std::endl;
            return os_;
        }
    );
}

int main(void) {
    People people = { Person("Peter", true), Person("Martha", false), Person("Jane", false),
                        Person("David", true), Person("Rose", false), Person("Tom", true) };
    std::cout << people << std::endl;
    std::cout << "======================" << std::endl;
    people.partition();
    std::cout << people << std::endl;
    std::cout << "======================" << std::endl;

    People people2 = { Person("Peter", true), Person("Martha", false), Person("Jane", false),
                        Person("David", true), Person("Rose", false), Person("Tom", true) };
    people2.stable_partition();
    std::cout << people2 << std::endl;
    std::cout << "======================" << std::endl;
    return 0;
}
