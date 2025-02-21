#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cassert>

class Country {
private:
    std::string countryName;
    std::string capitalName;
    int yearsSinceFound;
    static int objectCount;
    int id;

public:
    // Default constructor
    Country() : countryName(""), capitalName(""), yearsSinceFound(0), id(++objectCount) {}

    // Parameterized constructor
    Country(const std::string& cName, const std::string& capName, int years) : id(++objectCount) {
        setCountryName(cName);
        setCapitalName(capName);
        setYearsSinceFound(years);
    }

    // Destructor
    ~Country() {
        // Empty destructor for now
    }

    // Setters with validation
    void setCountryName(const std::string& cName) {
        countryName = cName;
    }

    void setCapitalName(const std::string& capName) {
        capitalName = capName;
    }

    void setYearsSinceFound(int years) {
        if (years < 0) {
            throw std::invalid_argument("Years since found cannot be negative.");
        }
        yearsSinceFound = years;
    }

    // Getters
    std::string getCountryName() const {
        return countryName;
    }

    std::string getCapitalName() const {
        return capitalName;
    }

    int getYearsSinceFound() const {
        return yearsSinceFound;
    }

    int getId() const {
        return id;
    }

    // toString method for diagnostic information
    std::string toString() const {
        std::stringstream ss;
        ss << "Country[ID: " << id << ", Name: " << countryName << ", Capital: " << capitalName
           << ", Years Since Found: " << yearsSinceFound << "]";
        return ss.str();
    }

    // Static method to get the object count
    static int getObjectCount() {
        return objectCount;
    }
};

// Initialize static variable
int Country::objectCount = 0;

int main() {
    // Create a list of Country objects
    std::vector<Country> countryList;

    // Test 1: Creating objects and using Get and toString
    try {
        Country c1("Lithuania", "Vilnius", 1000);
        Country c2("Latvia", "Riga", 800);

        countryList.push_back(c1);
        countryList.push_back(c2);

        // Print diagnostic information
        std::cout << c1.toString() << std::endl;
        std::cout << c2.toString() << std::endl;

        // Check Get methods
        assert(c1.getCountryName() == "Lithuania");
        assert(c1.getCapitalName() == "Vilnius");
        assert(c1.getYearsSinceFound() == 1000);
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    // Test 2: Exception handling
    try {
        Country c3("InvalidCountry", "InvalidCapital", -50);
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught exception for invalid years: " << e.what() << std::endl;
    }

    // Test 3: Static object count
    std::cout << "Total countries created: " << Country::getObjectCount() << std::endl;

    return 0;
}
