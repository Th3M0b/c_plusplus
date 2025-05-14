#include <iostream>
#include <string>
#include <cassert>
#include "validator.h"

/*
Trečiasis validavimo variantas: PasswordValidator

Šis validatorius turi tikrinti slaptažodžio stiprumą pagal šias taisykles:
1. Bent 8 simbolių ilgio
2. Bent vienas didžioji raidė
3. Bent vienas skaičius
4. Bent vienas specialus simbolis (!@#$%^&*)

Kolegos užduotis - sukurti PasswordValidator klasę, kuri paveldi Validator
ir įgyvendina šiuos metodus:
- validate(const std::string& password) - patikrina ar slaptažodis atitinka taisykles
- getErrorMessage() - grąžina klaidos pranešimą, kuris nurodo, kurios taisyklės nesilaikoma
*/

// Testų funkcijos
void test_password_validator() {
    // Šie testai turi feilinti, kol PasswordValidator nebus įgyvendintas
    // Testai pradės veikti, kai kolega įgyvendins PasswordValidator klasę
    
    std::cout << "Testing PasswordValidator...\n";
    
    // TODO: Kolega turi atkomentuoti šią eilutę, kai sukurs PasswordValidator
    // class PasswordValidator : public Validator {
    // public:
    //     bool validate(const std::string& password) const override {
    //         // Implementation here
    //     }
    //     
    //     std::string getErrorMessage() const override {
    //         // Implementation here
    //     }
    // };
    
    // Šiuo metu testai neturi kompiliuotis, nes PasswordValidator neegzistuoja
    // Kolega turės sukurti šią klasę ir atkomentuoti testus
    
    #ifdef PASSWORD_VALIDATOR_IMPLEMENTED
    PasswordValidator validator;
    
    // Testas 1: Per trumpas slaptažodis
    try {
        assert(!validator.validate("Short1!"));
        std::cout << "Test 1 (short password) passed\n";
    } catch (...) {
        std::cout << "Test 1 (short password) failed\n";
    }
    
    // Testas 2: Trūksta didžiosios raidės
    try {
        assert(!validator.validate("longpassword1!"));
        std::cout << "Test 2 (missing uppercase) passed\n";
    } catch (...) {
        std::cout << "Test 2 (missing uppercase) failed\n";
    }
    
    // Testas 3: Trūksta skaičiaus
    try {
        assert(!validator.validate("Longpassword!"));
        std::cout << "Test 3 (missing number) passed\n";
    } catch (...) {
        std::cout << "Test 3 (missing number) failed\n";
    }
    
    // Testas 4: Trūksta specialaus simbolio
    try {
        assert(!validator.validate("Longpassword1"));
        std::cout << "Test 4 (missing special char) passed\n";
    } catch (...) {
        std::cout << "Test 4 (missing special char) failed\n";
    }
    
    // Testas 5: Teisingas slaptažodis
    try {
        assert(validator.validate("StrongPass1!"));
        std::cout << "Test 5 (valid password) passed\n";
    } catch (...) {
        std::cout << "Test 5 (valid password) failed\n";
    }
    
    // Testas 6: Klaidos pranešimas
    try {
        validator.validate("weak");
        std::string error = validator.getErrorMessage();
        assert(!error.empty());
        std::cout << "Test 6 (error message) passed\n";
    } catch (...) {
        std::cout << "Test 6 (error message) failed\n";
    }
    #else
    std::cout << "PasswordValidator not implemented yet - tests skipped\n";
    std::cout << "To implement, create PasswordValidator class and define PASSWORD_VALIDATOR_IMPLEMENTED\n";
    #endif
}

int main() {
    test_password_validator();
    return 0;
}
