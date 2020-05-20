#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

struct Person {
    std::string name;
    bool isMale;
    int age;

    Person(std::string name, bool isMale, int age): name(name), isMale(isMale), age(age) {}

    friend std::ostream& operator<<(std::ostream& os, const Person& p);
};

std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << "Name: " << p.name << ", Gender: " << (p.isMale? "Male":"Female") << ", age: " << p.age;
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

struct OlderThan {
    OlderThan(int age): limit(age) {}
    bool operator()(const Person& person) const { return person.age > limit; }
private:
    int limit;
};

int main() {
    People people = { Person("Peter", true, 19), Person("Martha", false, 35), Person("Jane", false, 44),
                        Person("David", true, 50), Person("Rose", false, 35), Person("Tom", true, 17) };
    auto olderThan42 = OlderThan(42);
    std::for_each(people.cbegin(), people.cend(), [olderThan42] (const auto& person) {
        if (olderThan42(person)) {
            std::cout << person << " older than 42" << std::endl;
        }
    });
    std::cout << "There are " << std::count_if(people.cbegin(), people.cend(), olderThan42) << " people older than 42" << std::endl;
    return 0;
}