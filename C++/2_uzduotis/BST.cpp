#include <memory>
#include <stdexcept>
#include "BST.h"

namespace BSTProject{

// Node structure (hidden in implementation)
struct BST::Node {

        int value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Implementation class (hidden details)
struct BST::Impl {

        std::unique_ptr<Node> root;
        int nodeCount = 0;

        Impl() : root(nullptr), nodeCount(0) {}
};

// Deep Copy Helper

namespace{
    std::unique_ptr<BST::Node> cloneTree(const std::unique_ptr<BST::Node>&node){
        if (!node.get()){
            return std::unique_ptr<BST::Node>();
        }

        std::unique_ptr<BST::Node> newNode(new BST::Node(node->value));
        newNode->left = cloneTree(node->left);
        newNode->right = cloneTree(node->right);
        return newNode;
    }
}

// Constructor
BST::BST() : pImpl(new Impl()) {}

// Copy constructor
BST::BST(const BST& other) : pImpl(new Impl()){
    pImpl -> root = cloneTree(other.pImpl -> root);
    pImpl -> nodeCount = other.pImpl -> nodeCount;
}

// Copy assignment
BST& BST::operator=(const BST& other){
    if (this != &other){
        std::unique_ptr<Impl> newImpl(new Impl());
        newImpl -> root = cloneTree(other.pImpl -> root);
        newImpl -> nodeCount = other.pImpl -> nodeCount;
        pImpl = std::move(newImpl);
    }
    return *this;
}

// Destructor (needed for PImpl)
BST::~BST() {}

// Basic operations
void BST::insert(int value){
    if(contains(value)){
        throw std::invalid_argument("Duplicate value " + std::to_string(value));
    }

    std::unique_ptr<Node> newNode(new Node(value));
    if(!pImpl -> root){
        pImpl -> root = std::move(newNode);
    } else {
        Node* current = pImpl -> root.get();
        while (true) {
            if(value < current -> value){
                if(!current->left){
                    current -> left = std::move(newNode);
                    break;
                }
                current = current -> left.get();
            } else if (value > current -> value){
                if(!current -> right){
                    current -> right = std::move(newNode);
                    break;
                }
                current = current -> right.get();
            } else {
                // Value already exists (optional: throw exception)
                throw std::logic_error("Duplicate check failed");
            }
        }
    }
    pImpl -> nodeCount++;
}

bool BST::contains(int value) const{
    Node* current = pImpl -> root.get();
    while (current != nullptr) {
        if(value == current -> value){
            return true;
        } else if (value < current -> value){
            current = current -> left.get();
        } else {
            current = current -> right.get();
        }
    }
    return false;
}

bool BST::modify(int oldValue, int newValue){
    if(!contains(oldValue)){
        throw BSTException("Modification failed - source value " + 
            std::to_string(newValue) + " not found");
    }
    if(contains(newValue)){
        throw BSTException("Cannot modify - target value " +
            std::to_string(newValue) + " already exists");
    }

    if(oldValue == newValue) return true;
    
    try{
        remove(oldValue);
        insert(newValue);
        pImpl -> nodeCount--;

        return true;
    } catch (const std::exception& e){
        insert(oldValue);
        throw BSTException("Modification failed: " + std::string(e.what()));
    }
}

void BST::remove(int value){
    if(empty()){
        throw BSTException("Cannot remove from empty tree");
    }

    struct RemoveHelper {
        bool operator()(std::unique_ptr<Node>& node, int value, int& nodeCount){
            if(!node){
                throw BSTException("Value " + std::to_string(value) + " not found");
            }
            if(value < node -> value){
                return (*this)(node -> left, value, nodeCount);
            }
            else if(value > node -> value){
                return (*this)(node -> right, value, nodeCount);
            }
            else {
                if(!node -> left && !node -> right){
                    node.reset();
                    nodeCount--;
                    return true;
                }
                else if (!node -> left){
                    node = std::move(node -> right);
                    nodeCount--;
                    return true;
                }
                else if(!node -> right){
                    node = std::move(node -> left);
                    nodeCount--;
                    return true;
                }
                else{
                    Node* successor = node -> right.get();
                    while(successor -> left){
                        successor = successor -> left.get();
                    }
                    int successorValue = successor->value;
                    if ((*this)(node -> right, successorValue, nodeCount)){
                        node -> value = successorValue;
                        return true;
                    }
                    return false;
                }
            }
        }
    };
    RemoveHelper helper;
    helper(pImpl -> root, value, pImpl -> nodeCount);
}

void BST::clear() {
    if (empty()){
        throw BSTException("Cannot clear an already empty tree");
    }
    pImpl -> root.reset();
    pImpl -> nodeCount = 0;
}

bool BST::empty() const {
    return pImpl -> nodeCount == 0;
}

int BST::size() const {
    return pImpl -> nodeCount;
}

}