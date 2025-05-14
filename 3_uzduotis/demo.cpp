#include <iostream>
#include <memory>
#include "validator.h"

// Helper funkcija demonstracijai
void testValidation(ValidationContext& context, const std::string& data) {
    try {
        bool isValid = context.validate(data);
        std::cout << "Data '" << data << "' is " 
                  << (isValid ? "valid" : "invalid") << std::endl;
        
        if (!isValid) {
            std::cout << "Error: " << context.getErrorMessage() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Validation error: " << e.what() << std::endl;
    }
}

int main() {
    ValidationContext context;
    
    // Email validavimo demonstracija
    context.setStrategy(createEmailValidator());
    testValidation(context, "user@example.com");  // Validus
    testValidation(context, "invalid-email");     // Nevalidus
    
    // Phone validavimo demonstracija
    context.setStrategy(createPhoneValidator());
    testValidation(context, "+37061234567");     // Validus
    testValidation(context, "861234567");        // Nevalidus
    
    // Polimorfizmo demonstracija
    std::unique_ptr<Validator> validators[] = {
        createEmailValidator(),
        createPhoneValidator()
    };
    
    const std::string testData = "test@example.com";
    
    for (const auto& validator : validators) {
        // polimorfizmas
        bool result = validator->validate(testData);
        std::cout << "Validation result for " << testData << ": " 
                  << (result ? "valid" : "invalid") << std::endl;
    }
    
    return 0;
}