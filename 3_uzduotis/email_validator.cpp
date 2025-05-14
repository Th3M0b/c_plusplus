#include "validator.h"
#include <regex>
#include <stdexcept>

class EmailValidator : public Validator {
public:
    bool validate(const std::string& email) const override {
        
        const std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        return std::regex_match(email, pattern);
    }
    
    std::string getErrorMessage() const override {
        return "Invalid email format. Expected format: user@example.com";
    }
};

// Factory funkcija
std::unique_ptr<Validator> createEmailValidator() {
    return std::make_unique<EmailValidator>();
}