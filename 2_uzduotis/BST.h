// Author: Mantas Majauskas VU MIF student 1-st year group 4

/**
 * BINARY SEARCH TREE (BST) CLASS
 * =============================
 * 
 * A balanced binary search tree implementation with the following features:
 * - Stores unique integer values in sorted order
 * - Provides standard CRUD operations (Create, Read, Update, Delete)
 * - Supports deep copying and value semantics
 * - Throws BSTException for invalid operations
 * 
 * BASIC USAGE:
 * -----------
 * BST tree;               // Create empty tree
 * tree.insert(10);        // Add value
 * if (tree.contains(5))   // Check existence
 * tree.remove(10);        // Remove value
 * tree.clear();           // Remove all values
 * 
 * OPERATORS:
 * ---------
 * tree += 5;             // Insert operator
 * tree -= 5;             // Remove operator
 * tree[0]                // Get smallest value (by in-order index)
 * tree == otherTree      // Equality comparison
 * 
 * SIZE MANAGEMENT:
 * --------------
 * tree.size()            // Get element count
 * tree.empty()           // Check if empty
 * 
 * EXCEPTIONS:
 * ----------
 * All methods throw BSTException with descriptive messages for:
 * - Duplicate values
 * - Missing values
 * - Invalid operations
 * - Out-of-bounds access
 * 
 * COPY SEMANTICS:
 * -------------
 * BST tree2(tree1);      // Deep copy constructor
 * tree3 = tree1;         // Deep copy assignment
 * 
 */

#ifndef BST_H // Header guard (protection against double inclusion)
#define BST_H

#include <memory> // For std::unique_ptr (PImpl idiom later)
#include <stdexcept> // For standart exceptions
#include <string>

//
// Project namespace
//

namespace BSTProject {

    //
    // Binary Search Tree Exception class
    //

    class BSTException : public std::runtime_error{
        public:
            explicit BSTException(const std::string& msg);
    };

    //
    // Binary Search Tree class
    //

    class BST {
        public:
            // Type synonyms
            using ValueType = int;

            BST(); // Constructor
            ~BST(); // Destructor

            // Basic operations
            void insert(ValueType value); // Adds a new element
            bool contains(ValueType value) const; // Checks if value exists (read)
            bool modify(ValueType oldValue, int newValue); // Modifies an element
            void remove(ValueType value); // Deletes an element
            void clear(); // Deletes all elements (reset)

            BST(const BST& other); // Copy constructor
            BST& operator=(const BST& other); // Copy assignment

            // Comparison operators
            bool operator==(const BST& other) const;
            bool operator!=(const BST& other) const;

            // Arithmetic operators
            BST& operator+=(ValueType value);  // Insert
            BST& operator-=(ValueType value);  // Remove
            BST operator+(ValueType value) const;  // Returns new tree with value added
            BST operator-(ValueType value) const;  // Returns new tree with value removed

            // Unary operators
            BST& operator!();  // Clear tree
            bool operator~() const;  // Check if value exists (like contains)

            // Subscript operator
            bool operator[](ValueType value) const;  // Search by value
            
            // Additional helper methods (for demostration)
            bool empty() const; // Checks if tree is empty
            int size() const; // Returns number of nodes

        private:
            // Forward declaration of the implementation class
            struct Impl; // Implementation class
            std::unique_ptr<Impl> pImpl; // Pointer to the implementation
};
}

#endif // BST_H
