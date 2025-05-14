#include <iostream>
#include "validator.h"

/*
Trečiasis neįgyvendintas validavimo variantas: PasswordValidator

Šis validatorius turėtų tikrinti slaptažodžio stiprumą pagal šias taisykles:
1. Bent 8 simbolių ilgio
2. Bent vienas didžioji raidė
3. Bent vienas skaičius
4. Bent vienas specialus simbolis (!@#$%^&*)

Metodai, kuriuos turėtų įgyvendinti:
- validate(const std::string& password) - patikrina ar slaptažodis atitinka taisykles
- getErrorMessage() - grąžina klaidos pranešimą, kuris nurodo, kurios taisyklės nesilaikoma
*/

class PasswordValidatorTest {
public:
    void runTests() {
        testLengthRequirement();
        testUpperCaseRequirement();
        testNumberRequirement();
        testSpecialCharRequirement();
        testValidPassword();
    }
    
private:
    void testLengthRequirement() {
        // TURI feilinti, kol nebus įgyvendinta
        std::cout << "PasswordValidator length test... FAILED (not implemented)" << std::endl;
    }
    
    void testUpperCaseRequirement() {
        // TURI feilinti, kol nebus įgyvendinta
        std::cout << "PasswordValidator upper case test... FAILED (not implemented)" << std::endl;
    }
    
    void testNumberRequirement() {
        // TURI feilinti, kol nebus įgyvendinta
        std::cout << "PasswordValidator number test... FAILED (not implemented)" << std::endl;
    }
    
    void testSpecialCharRequirement() {
        // TURI feilinti, kol nebus įgyvendinta
        std::cout << "PasswordValidator special char test... FAILED (not implemented)" << std::endl;
    }
    
    void testValidPassword() {
        // TURI feilinti, kol nebus įgyvendinta
        std::cout << "PasswordValidator valid password test... FAILED (not implemented)" << std::endl;
    }
};

int main() {
    PasswordValidatorTest tester;
    tester.runTests();
    return 0;
}