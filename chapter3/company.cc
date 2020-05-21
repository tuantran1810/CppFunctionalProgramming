#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

struct Person {
    std::string name;
    std::string teamName;

    Person(std::string name, std::string teamName): name(name), teamName(teamName) {}
    friend std::ostream& operator<<(std::ostream& os, const Person& p);
};

std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << "Name: " << p.name << ", Team: " << p.teamName;
    return os;
}

struct Company {
    Company(std::initializer_list<Person>&& lst) {
        std::for_each(lst.begin(), lst.end(), [this] (const Person& p) -> bool {
            this->employees.push_back(p);
            return true;
        });
    }

    std::string teamNameFor(const Person& p) const {
        return p.teamName;
    }

    int countTeamMember(const std::string& name) const {
        return std::count_if(employees.cbegin(), employees.cend(), [&name, this] (const Person& p) -> bool {
            return name == teamNameFor(p);
        });
    }

private:
    std::vector<Person> employees;
};

void mutableLambda() {
    int count = 0;
    std::vector<std::string> words{"An", "ancient", "pond"};
    std::for_each(words.cbegin(), words.cend(),
        [count] (const std::string& word) mutable {
        if (isupper(word[0])) {
            std::cout << "word: " << word << " count: " << count << std::endl;
            count++;
        }
    });
}

int main() {
    Company company = {
        Person("Jane", "Mars"), Person("David", "Earth"), Person("Tom", "Mars"),
        Person("Peter", "Mars"), Person("Martha", "Moon"), Person("Rose", "Moon"),
        Person("Jon", "Earth"), Person("Colin", "Moon"), Person("Clara", "Moon")
    };

    std::cout << "Company has " << company.countTeamMember("Mars") << " members in team Mars\n";
    std::cout << "Company has " << company.countTeamMember("Earth") << " members in team Earth\n";
    std::cout << "Company has " << company.countTeamMember("Moon") << " members in team Moon\n";

    mutableLambda();
    return 0;
}

