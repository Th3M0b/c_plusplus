#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cassert>

#define countAfterDelete "New count after deleting objects: "


class Country {
public:
    std::string countryName;
    std::string capitalName;
    int yearsSinceFound;
    static int objectCount;
    int id;

public:
    // Default constructor
    Country(const std::string& cName, const std::string& capName, int* years = nullptr) : yearsSinceFound(0) {
        setCountryName(cName);
        setCapitalName(capName);
    
        if (years != nullptr) 
            setYearsSinceFound(*years);  // Validate years before updating objectCount
        
        id = ++objectCount;  // Increment object count after validation
    }


    // Parameterized constructor
    Country(const std::string& cName, const std::string& capName, int years) {
        setCountryName(cName);
        setCapitalName(capName);
        setYearsSinceFound(years);
        id = ++objectCount;  // Increment object count after validation
    }

    // Destructor
    ~Country() {
        --objectCount; // Decrement object count when an object is destroyed
    }

    // Setters with validation
    void setCountryName(const std::string& cName) {
        countryName = cName;
    }

    void setCapitalName(const std::string& capName) {
        capitalName = capName;
    }

    void setYearsSinceFound(int years) {
        if (years < 0) 
            throw std::invalid_argument("Years since found cannot be negative.");
        
        yearsSinceFound = years;
    }

    // Function to add a country (takes vector as argument)
    static void addCountry(std::vector<Country*>& countryList, const std::string& name, const std::string& capital, int* years = nullptr) {
        countryList.push_back(new Country(name, capital, years));
    }

    static void deleteAllCountries(std::vector<Country*>& countryList) {
        for (size_t i = 0; i < countryList.size(); ++i) {
            delete countryList[i];   // Deletes each country object
        }
        countryList.clear();  // Removes all pointers from the vector
    }

    // toString method for diagnostic information
    std::string toString() const {
        std::stringstream ss;
        ss << id << ". " << countryName << ", " << capitalName << ", " << yearsSinceFound;
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
    // Define the country list inside main()
    std::vector<Country*> countryList;

    // Create objects using different constructors
    Country::addCountry(countryList, "USA", "Washington D.C.", new int(1776));
    Country::addCountry(countryList, "Lithuania", "Vilnius", new int(1991));
    Country::addCountry(countryList, "Japan", "Tokyo"); // Without years

    // Display all countries
    for (std::vector<Country*>::iterator it = countryList.begin(); it != countryList.end(); ++it) {
        Country* c = *it;
        std::cout << c->toString() << std::endl;
    }

    std::cout << "Initial object count: " << Country::getObjectCount() << std::endl;


    try {
        Country::addCountry(countryList, "InvalidCountry", "Nowhere", new int(-100)); // Invalid year
        assert(false);  // This line should not be reached
    } catch (const std::invalid_argument& e) {
        // Expected exception for negative years
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }

    // Delete all objects at once
    Country::deleteAllCountries(countryList);
    std::cout << countAfterDelete << Country::getObjectCount() << std::endl;

    assert(Country::getObjectCount() == 0); // Should be 0 after deletion

    return 0;
}
