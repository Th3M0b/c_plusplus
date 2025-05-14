#include "validator.h"
#include <regex>
#include <stdexcept>

class PhoneValidator : public Validator {
public:
    bool validate(const std::string& phone) const override {
        // Validuoja tarptautinius telefonų numerius (su + ir 9-15 skaitmenų)
        const std::regex pattern(R"(\+\d{9,15})");
        return std::regex_match(phone, pattern);
    }
    
    std::string getErrorMessage() const override {
        return "Invalid phone number format. Expected format: +37012345678";
    }
};

// Factory funkcija
std::unique_ptr<Validator> createPhoneValidator() {
    return std::make_unique<PhoneValidator>();
}