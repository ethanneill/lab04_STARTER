// intbst.cpp
// Implements class IntBST
// Ethan Neill  Perm #: 4178315
// Omar Sanchez Perm #: 

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() : root(0) { }

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    // handle special case of empty tree first
    if (!root) {
	root = new Node(value);
	return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->info)
	return false;
    if (value < n->info) {
	if (n->left)
	    return insert(value, n->left);
	else {
	    n->left = new Node(value);
	    n->left->parent = n;
	    return true;
	}
    }
    else {
	if (n->right)
	    return insert(value, n->right);
	else {
	    n->right = new Node(value);
	    n->right->parent = n;
	    return true;
	}
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n) {
	cout << n->info << " ";
	printPreOrder(n->left);
	printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if(n){
        printInOrder(n->left);
        cout<<n->info<<" ";
        printInOrder(n->right);
    }
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if(n){
        printPostOrder(n->right);
        cout<<n->info<<" ";
        printPostOrder(n->left);
    }
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if(n){
        return n->info + sum(n->left) + sum(n->right);
    }
    else{
        return 0;
    }
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if(n){
        return 1 + count(n->left) + count(n->right);
    }
    else{
        return 0;
    }
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if(n){
        if(n->info == value){
            return n;
        }
        else if(n->info >= value){
            getNodeFor(value, n->left);
        }
        else if(n->info <= value){
            getNodeFor(value, n->right);
        }
    }
    else{
        return NULL;
    }
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    if(getNodeFor(value, root) != NULL){
        return true;
    }
    else{
        return false;
    }
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* current = getNodeFor(value, root);
    Node* pred = nullptr;
    Node* n = root;
    while(n->left){
        n = n->left;
    }
    if(n->info == value){
        return pred;
    }
    if(current->left){
        current = current->left;
        pred = current;
        while(current->right){
            current = current->right;
            pred = current;
        }
    }
    else if(current->parent){
        while(current->info < current->parent->info && current->parent){
            current = current->parent;
            pred = current;
        }
        pred = current->parent;
    }
    return pred;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    if(getPredecessorNode(value)){
        return getPredecessorNode(value)->info;
    }
    else{
        return 0;
    }
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* current = getNodeFor(value, root);
    Node* succ = nullptr;
    Node* n = root;
    while(n->right){
        n = n->right;
    }
    if(n->info == value){
        return succ;
    }
    if(current->right){
        current = current->right;
        succ = current;
        while(current->left){
            current = current->left;
            succ = current;
        }
    }
    else if(current->parent){
        while(current->info > current->parent->info && current->parent){
            current = current->parent;
            succ = current;
        }
        succ = current->parent;
    }
    return succ;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    if(getSuccessorNode(value)){
        return getSuccessorNode(value)->info;
    }
    else{
        return 0;
    }
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    if(contains(value)){
        Node* current = getNodeFor(value, root);
        Node* succ = nullptr;
        if(current->left == nullptr && current->right == nullptr){
            if(current == root){
                delete root;
                root = nullptr;
            }
            else{
                if(current->info < current->parent->info){
                    current->parent->left = nullptr;
                }
                else{
                    current->parent->right = nullptr;
                }
                delete current;
            }
        }
        else if(current->left && current->right){
            succ = getSuccessorNode(current->info);
            int succValue = succ->info;
            remove(succ->info);
            current->info = succValue;
        }
        else if(current->left || current->right){
            Node* child = current->left;
            if(current->right != nullptr){
                child = current->right;
            }
            if(current->parent->left == current){
                current->parent->left = child;
            }
            if(current->parent->right == current){
                current->parent->right = child;
            }
            delete current;
        }
        return true;
    }
    else{
        return false;
    }
}
