// Author: Mantas Majauskas VU MIF student 1-st year group 4

#include "BST.h"
#include <iostream>

void demonstrateBasicOperations() {
    std::cout << "\n=== Basic Operations Demo ===\n";
    BSTProject::BST tree;
    
    // Insertion
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    std::cout << "Inserted values: 50, 30, 70, 20, 40\n";
    std::cout << "Tree size: " << tree.size() << "\n";
    
    // Contains check
    std::cout << "Contains 30? " << (tree.contains(30) ? "Yes" : "No") << "\n";
    std::cout << "Contains 99? " << (tree.contains(99) ? "Yes" : "No") << "\n";
    
    // Modification
    tree.modify(30, 35);
    std::cout << "Modified 30 to 35\n";
    std::cout << "Now contains 30? " << (tree.contains(30) ? "Yes" : "No") << "\n";
    std::cout << "Now contains 35? " << (tree.contains(35) ? "Yes" : "No") << "\n";
}

void demonstrateCopyOperations() {
    std::cout << "\n=== Copy Operations Demo ===\n";
    BSTProject::BST original;
    original.insert(100);
    original.insert(50);
    original.insert(150);
    
    // Copy constructor
    BSTProject::BST copy1(original);
    std::cout << "Original size: " << original.size() 
              << " | Copy size: " << copy1.size() << "\n";
    std::cout << "Copy contains 150? " << (copy1.contains(150) ? "Yes" : "No") << "\n";
    
    // Assignment operator
    BSTProject::BST copy2;
    copy2 = original;
    std::cout << "After assignment, copy2 contains 50? " 
              << (copy2.contains(50) ? "Yes" : "No") << "\n";
    
    // Verify independence
    copy2.insert(75);
    std::cout << "Added 75 to copy2\n";
    std::cout << "Original contains 75? " << (original.contains(75) ? "Yes" : "No") << "\n";
    std::cout << "copy2 contains 75? " << (copy2.contains(75) ? "Yes" : "No") << "\n";
}

void demonstrateExceptionHandling() {
    std::cout << "\n=== Exception Handling Demo ===\n";
    try {
        BSTProject::BST tree;
        tree.insert(10);
        tree.insert(10); // Duplicate insert
    } catch (const BSTProject::BSTException& e) {
        std::cout << "Caught BSTException: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cout << "Caught standard exception: " << e.what() << "\n";
    }
    
    try {
        BSTProject::BST tree;
        tree.remove(99); // Remove from empty
    } catch (const BSTProject::BSTException& e) {
        std::cout << "Caught BSTException: " << e.what() << "\n";
    }
}
void demonstrateOperators() {
    std::cout << "\n=== Operator Demonstrations ===\n";
    
    BSTProject::BST tree;
    tree += 50;
    tree += 30;
    tree += 70;
    
    // Test += and ==
    BSTProject::BST tree2;
    tree2 += 50;
    tree2 += 30;
    tree2 += 70;
    std::cout << "Trees equal? " << (tree == tree2 ? "Yes" : "No") << "\n";
    
    // Test -= and []
    tree -= 30;
    std::cout << "Contains 30? " << (tree[30] ? "Yes" : "No") << "\n";
    
    // Test + operator
    BSTProject::BST tree3 = tree2 + 25;
    std::cout << "New tree contains 25? " << (tree3[25] ? "Yes" : "No") << "\n";
    
    // Test - operator
    BSTProject::BST tree4 = tree3 - 25;
    std::cout << "New tree contains 25? " << (tree4[25] ? "Yes" : "No") << "\n";

    // Test ! operator
    !tree3;
    std::cout << "Tree cleared? " << (~tree3 ? "No" : "Yes") << "\n";
}

int main() {
    try {
        std::cout << "=== Binary Search Tree Demonstration ===\n";
        
        demonstrateBasicOperations();
        demonstrateCopyOperations();
        demonstrateExceptionHandling();
        demonstrateOperators();
        
        std::cout << "\nAll demonstrations completed successfully!\n";
        return 0;
    } 
    catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown exception occurred!" << std::endl;
        return 2;
    }
}