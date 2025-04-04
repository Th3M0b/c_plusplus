// Author: Mantas Majauskas VU MIF student 1-st year group 4

#include <memory>
#include <stdexcept>
#include "BST.h"

namespace BSTProject{

    // Node structure
    struct BST::Node {

            ValueType value;
            std::unique_ptr<Node> left;
            std::unique_ptr<Node> right;

            Node(ValueType val) : value(val), left(nullptr), right(nullptr) {}
    };

    // Implementation class
    struct BST::Impl {

            std::unique_ptr<Node> root;
            ValueType nodeCount = 0;

            Impl() : root(nullptr), nodeCount(0) {}
    };

    // Constructor
    BST::BST() : pImpl(new Impl()) {}

    // Destructor 
    BST::~BST() {}

    // Copy constructor
    std::unique_ptr<BST::Node> BST::copyTree(const std::unique_ptr<Node>& source) {
        if (!source) return nullptr;
        std::unique_ptr<Node> newNode = std::unique_ptr<Node>(new Node(source->value));
        newNode->left = copyTree(source->left);
        newNode->right = copyTree(source->right);
        return newNode;
    }

    BST::BST(const BST& other) : pImpl(new Impl()) {
        if (!other.empty()) {
            pImpl->root = copyTree(other.pImpl->root);
            pImpl->nodeCount = other.pImpl->nodeCount;
        }
    }

    // Copy assignment operator
    BST& BST::operator=(const BST& other) {
        if (this != &other) {
            BST temp(other);
            std::swap(pImpl, temp.pImpl);
        }
        return *this;
    }

    // Basic operations
    void BST::insert(ValueType value){
        if(contains(value)){
            throw BSTException("Duplicate value " + std::to_string(value));
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

    bool BST::contains(ValueType value) const{
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

    bool BST::modify(ValueType oldValue, ValueType newValue){
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

    void BST::remove(ValueType value){
        if(empty()){
            throw BSTException("Cannot remove from empty tree");
        }

        struct RemoveHelper {
            bool operator()(std::unique_ptr<Node>& node, ValueType value, ValueType& nodeCount){
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
                        ValueType successorValue = successor->value;
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

    //
    // Operators
    //

    // Comparison operators
    bool BST::operator==(const BST& other) const {
        if(size() != other.size()) return false;

        struct CompareHelper{
            static bool compare(const std::unique_ptr<Node>& a, const std::unique_ptr<Node>& b){
                if (!a && !b) return true;
                if (!a || !b) return false;
                return compare(a -> left, b -> left) &&
                        (a -> value == b -> value) &&
                        compare(a -> right, b -> right);
            }
        };

        return CompareHelper::compare(pImpl -> root, other.pImpl -> root);
    }

    bool BST::operator!=(const BST& other) const {
        return !(*this == other);
    }

    BST& BST::operator+=(ValueType value) {
        insert(value);
        return *this;
    }

    BST& BST::operator-=(ValueType value){
        remove(value);
        return *this;
    }

    BST BST::operator+(ValueType value) const {
        BST result(*this);
        result += value;
        return result;
    }

    BST BST::operator-(ValueType value) const {
        BST result(*this);
        result -= value;
        return result;
    }

    BST& BST::operator!(){
        clear();
        return *this;
    }

    bool BST::operator~() const {
        return !empty();
    }

    bool BST::operator[](ValueType value) const {
        return contains(value);
    }

}