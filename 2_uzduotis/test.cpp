#include "BST.h"
#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>

namespace BSTTest {

void testEmptyTree() {
    BSTProject::BST tree;
    assert(tree.empty());
    assert(tree.size() == 0);
    assert(!tree.contains(10));
    std::cout << "Empty tree tests passed.\n";
}

void testInsertAndContains() {
    BSTProject::BST tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);

    assert(!tree.empty());
    assert(tree.size() == 3);
    assert(tree.contains(50));
    assert(tree.contains(30));
    assert(tree.contains(70));
    assert(!tree.contains(99));
    std::cout << "Insert and contains tests passed.\n";
}

void testRemove() {
    BSTProject::BST tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    
    tree.remove(30);
    assert(tree.size() == 2);
    assert(!tree.contains(30));
    
    tree.remove(50);
    assert(tree.size() == 1);
    assert(!tree.contains(50));
    std::cout << "Remove tests passed.\n";

}

void testCopyOperations() {
    BSTProject::BST original;
    original.insert(40);
    original.insert(20);
    original.insert(60);

    // Test copy constructor
    BSTProject::BST copy1(original);
    assert(copy1.size() == 3);
    assert(copy1.contains(40));
    assert(copy1.contains(20));
    assert(copy1.contains(60));

    // Test assignment operator
    BSTProject::BST copy2;
    copy2 = original;
    assert(copy2.size() == 3);
    assert(copy2.contains(40));

    // Verify independence
    copy2.insert(35);
    assert(copy2.size() == 4);
    assert(original.size() == 3);
    std::cout << "Copy operations tests passed.\n";
}

void testOperators() {
    BSTProject::BST tree;
    tree += 50;
    tree += 30;
    tree += 70;

    // Test += and size
    assert(tree.size() == 3);

    // Test -= 
    tree -= 30;
    assert(tree.size() == 2);
    assert(!tree.contains(30));

    // Test []
    assert(tree[50]);  // First in-order value
    assert(tree[70]);  // Second in-order value

    // Test ==
    BSTProject::BST tree2;
    tree2 += 50;
    tree2 += 70;
    assert(tree == tree2);

    // Test clear operator
    !tree;
    assert(tree.empty());
    std::cout << "Operators tests passed.\n";
}

void testExceptionHandling() {
    BSTProject::BST tree;

    // Test empty tree operations
    try {
        tree.remove(10);
        assert(false); // Shouldn't reach here
    } catch (const BSTProject::BSTException&) {
        assert(true);
    }

    // Test duplicate insert
    tree.insert(10);
    try {
        tree.insert(10);
        assert(false); // Shouldn't reach here
    } catch (const BSTProject::BSTException&) {
        assert(true);
    }
    std::cout << "Exception handling tests passed.\n";
}

void testInOrderBehavior() {
    BSTProject::BST tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);

    // Verify in-order traversal using []
    assert(tree[20]);
    assert(tree[30]);
    assert(tree[40]);
    assert(tree[50]);
    assert(tree[70]);
    std::cout << "In-order behavior tests passed.\n";
}



void runAllTests() {
    testEmptyTree();
    testInsertAndContains();
    testRemove();
    testCopyOperations();
    testOperators();
    testExceptionHandling();
    testInOrderBehavior();
    
    std::cout << "All tests passed successfully!\n";
}

} // namespace BSTTest

int main() {
    try {
        BSTTest::runAllTests();
        return 0;
    } catch (...) {
        std::cerr << "Some tests failed!" << std::endl;
        return 1;
    }
}