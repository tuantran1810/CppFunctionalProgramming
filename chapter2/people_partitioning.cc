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
        std::for_each(lst.begin(), lst.end(), [this] (const Person& p) -> bool {
            this->push_back(p);
            return true;
        });
    }

    People::iterator partition_female() {
        return std::partition(this->begin(), this->end(), [] (const Person& p) -> bool {
            return !p.isMale;
        });
    }

    People::iterator stable_partition_female() {
        return std::stable_partition(this->begin(), this->end(), [] (const Person& p) -> bool {
            return !p.isMale;
        });
    }

    std::vector<std::string> female_names() {
        std::vector<Person> females;
        std::copy_if(this->cbegin(), this->cend(), std::back_inserter(females), [] (const Person& p) -> bool {
            return !p.isMale;
        });

        std::vector<std::string> result(females.size());
        std::transform(females.cbegin(), females.cend(), result.begin(), [] (const Person& p) -> std::string {
            return p.name;
        });
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const People& p);
};

std::ostream& operator<<(std::ostream& os, const People& p) {
    return std::accumulate(p.cbegin(), p.cend(), std::ref(os),
        [] (std::ostream& os_, const Person& person) -> std::ostream& {
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
    people.partition_female();
    std::cout << people << std::endl;
    std::cout << "======================" << std::endl;

    People people2 = { Person("Peter", true), Person("Martha", false), Person("Jane", false),
                        Person("David", true), Person("Rose", false), Person("Tom", true) };
    people2.stable_partition_female();
    std::cout << people2 << std::endl;
    std::cout << "======================" << std::endl;

    People people3 = { Person("Peter", true), Person("Martha", false), Person("Jane", false),
                        Person("David", true), Person("Rose", false), Person("Tom", true) };
    std::vector<std::string> names = people3.female_names();
    std::accumulate(names.cbegin(),
        names.cend(),
        std::ref(std::cout),
        [] (std::ostream& os, const std::string& name) -> std::ostream& {
        os << name << " ";
        return os;
    });
    return 0;
}
