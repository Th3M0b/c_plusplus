#include <iostream>
#include <cassert>

class Country {
public:
    Country(const std::string& name, int population)
        : name(name), population(population) {}

    std::string getName() const {
        return name;
    }

    int getPopulation() const {
        return population;
    }

    void setName(const std::string& newName) {
        name = newName;
    }

    void setPopulation(int newPopulation) {
        population = newPopulation;
    }
};

int main() {
    // Test 1: Creating a country and getting its name and population
    Country country1("USA", 328200000);
    assert(country1.getName() == "USA");
    assert(country1.getPopulation() == 328200000);

    // Test 2: Setting a new name for the country
    country1.setName("United States of America");
    assert(country1.getName() == "United States of America");

    // Test 3: Setting a new population for the country
    country1.setPopulation(330000000);
    assert(country1.getPopulation() == 330000000);

    std::cout << "All tests passed!" << std::endl;

    return 0;
}