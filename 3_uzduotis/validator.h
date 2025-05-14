/*
 * Autorius: Mantas Majauskas VU MIF group 4
 *
 * Projekto pavadinimas: DataValidation - Strategy Šablonas
 * 
 * Projekto esmė:
 * Šis modulis suteikia lankstų duomenų validavimo mechanizmą, kuris leidžia
 * keisti validavimo algoritmus nekeičiant pagrindinės programos logikos.
 * 
 * Stabilus aspektas:
 * - Validavimo konteksto klasė (ValidationContext) ir jos sąsaja
 * - Bazinės validavimo strategijos interfeisas (Validator)
 * - Validavimo proceso struktūra ir naudojimo būdas
 * 
 * Kintamas aspektas:
 * - Konkretūs validavimo algoritmai (strategijos)
 * - Validavimo taisyklės ir jų implementacija
 * - Klaidų pranešimų formatas ir turinys
 * 
 * Įgyvendintas projektavimo šablonas: Strategy
 * Strategy šablonas buvo pasirinktas, nes:
 * 1. Leidžia atskirti validavimo algoritmus nuo jų naudojimo konteksto
 * 2. Lengvai pridedami nauji validavimo algoritmai
 * 3. Galima keisti validavimo elgseną vykdymo metu
 * 4. Užtikrina, kad visi validavimo algoritmai laikysis to paties interfeiso
 */

#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <memory>

// Bazinė validavimo strategijos klasė
class Validator {
public:
    virtual ~Validator() = default;
    virtual bool validate(const std::string& data) const = 0;
    virtual std::string getErrorMessage() const = 0;
    
};

// Validavimo kontekstas, naudojantis strategiją
class ValidationContext {
private:
    std::unique_ptr<Validator> strategy;
    
public:
    explicit ValidationContext(std::unique_ptr<Validator> validator = nullptr)
        : strategy(std::move(validator)) {}
    
    void setStrategy(std::unique_ptr<Validator> validator) {
        strategy = std::move(validator);
    }
    
    bool validate(const std::string& data) const {
        if (!strategy) {
            throw std::runtime_error("Validation strategy not set");
        }
        return strategy->validate(data);
    }
    
    std::string getErrorMessage() const {
        if (!strategy) {
            throw std::runtime_error("Validation strategy not set");
        }
        return strategy->getErrorMessage();
    }
};

std::unique_ptr<Validator> createEmailValidator();
std::unique_ptr<Validator> createPhoneValidator();

#endif // VALIDATOR_H
