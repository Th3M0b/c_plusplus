#ifndef BST_H // Header guard (protection against double inclusion)
#define BST_H

#include <memory> // For std::unique_ptr (PImpl idiom later)
#include <stdexcept> // For standart exceptions
#include <string>

// Project namespace
namespace BSTProject {

    class BSTException : public std::runtime_error{
        public:
            explicit BSTException(const std::string& msg) : std::runtime_error(msg){}
    };
    class BST {
        public:
            BST(); // Constructor
            ~BST(); // Destructor

            // Basic operations
            void insert(int value); // Adds a new element
            bool contains(int value) const; // Checks if value exists (read)
            bool modify(int oldValue, int newValue); // Modifies an element
            void remove(int value); // Deletes an element
            void clear(); // Deletes all elements (reset)

            BST(const BST& other); // Copy constructor
            BST& operator=(const BST& other); // Copy assignment

            // Additional helper methods (for demostration)
            bool empty() const; // Checks if tree is empty
            int size() const; // Returns number of nodes

        private:
            // Forward declaration of the implementation class (PImpl idiom)
            struct Node; // Node structure (will be defined in .cpp)
            struct Impl; // Implementation class (hidden details)

            std::unique_ptr<Impl> pImpl; // Pointer to the implementation
};
}

#endif // BST_H