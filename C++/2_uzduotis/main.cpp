#include <iostream>
#include "BST.h"

int main() {
    try {
        BSTProject::BST tree1;
        tree1.insert(50);
        tree1.insert(30);
        tree1.insert(70);

        // Test copy constructor
        BSTProject::BST tree2(tree1);
        std::cout << "Copy test - size: " << tree2.size() 
                  << " (expected 3)" << std::endl;

        // Test assignment
        BSTProject::BST tree3;
        tree3 = tree1;
        std::cout << "Assignment test - contains 50: " 
                  << (tree3.contains(50) ? "true" : "false")
                  << " (expected true)" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}