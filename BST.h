#pragma once
#ifndef BST_H_
#define BST_H_
#include <vector>
#include <iostream>
#include <string>
//THE FOLLOWING CODE IS MAINLY COPIED FROM THE LECTURE SLIDES WITH SLIGHT MODIFICATIONS
using namespace std;



template <class Key, class Value>
class BSTNode;

template <class Key, class Value>
class BSTSearchTree;


template <class Key, class Value>
class BSTNode {
public:
    Value element;
    Key key;
    BSTNode* left;
    BSTNode* right;
    int height;

    BSTNode(Value theElement, Key word, BSTNode* l, BSTNode* r)
        : element(theElement), key(word), left(l), right(r), height(1) {}

    friend class BSTSearchTree<Key, Value>;
};


// value is WordItem struct AKA comperable
// key is the word. 
//AVL- node.


template <class Key, class Value>
class BSTSearchTree {

private:
    BSTNode< Key, Value>* root;

    const bool& elementAt(BSTNode< Key, Value>* t) const {
        if (t == NULL) {
            return false;
        }
        return true;
    }


    int getHeight(BSTNode< Key, Value>* node) {
        return (node == nullptr) ? 0 : node->height;
    }

    void insert(const Value word, Key key, BSTNode< Key, Value>*& t) const {
        {
            if (t == NULL)
                t = new BSTNode< Key, Value>(word, key, NULL, NULL);

            else  if (key < t->key) {
                //word should be inserted to the left tree!
                insert(word, key, t->left);


            }
            else if (t->key < key)
            {    // Otherwise word is inserted to the right subtree
                insert(word, key, t->right);

            }
            else
                ;  // Duplicate; do nothing



        }


    }
    void remove(const Key& x, BSTNode< Key, Value>*& t) const {
        if (t == NULL)
            return;   // Item not found; do nothing
        if (x < t->key)
            remove(x, t->left);
        else if (t->key < x)
            remove(x, t->right);
        else if (t->left != NULL && t->right != NULL) // Two children
        {
            t->key = findMin(t->right)->key;
            remove(t->key, t->right);
        }
        else // one or no children
        {
            BSTNode<Key, Value>* oldNode = t;
            t = (t->left != NULL) ? t->left : t->right;
            delete oldNode;
        }
    }


    BSTNode< Key, Value>* findMin(BSTNode< Key, Value>* t) const {
        if (t == NULL)
            return NULL;
        if (t->left == NULL)
            return t;
        return findMin(t->left);

    }
    BSTNode< Key, Value>* findMax(BSTNode< Key, Value>* t) const {
        if (t != NULL)
            while (t->right != NULL)
                t = t->right;
        return t;

    }
    BSTNode< Key, Value>* find(const Key& x, BSTNode< Key, Value>* t)const {
        while (t != NULL) {
            if (x < t->key) {
                t = t->left;
            }
            else if (t->key < x) {
                t = t->right;
            }
            else {
                return t;    // Match
            }
            // No match
        }
        return NULL;

    }

    void makeEmpty(BSTNode< Key, Value>*& t) const {
        if (t != NULL)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = NULL;

    }
    void printTree(BSTNode< Key, Value>* t) const {
        if (t != NULL)
        {
            printTree(t->left);
            cout << t->element << endl;
            printTree(t->right);
        }

    }
    BSTNode< Key, Value>* clone(BSTNode< Key, Value>* t) const {
        if (t == NULL)
            return NULL;
        else
            return new BSTSearchTree<Key, Value>
            (t->element,
                clone(t->left),
                clone(t->right));

    }


    int height(BSTNode< Key, Value>* t) const {
        if (t == NULL)
            return -1;

        return t->height;
    }


    int max(int lhs, int rhs) const {
        if (lhs > rhs)
            return lhs;

        return rhs;

    }


public:


    explicit BSTSearchTree() { root = nullptr; }



    BSTSearchTree(const BSTNode<Key, Value>& rhs) {
        *this = rhs;

    }
    ~BSTSearchTree() {
        makeEmpty();
    }

    const Value& findMin() const {
        return elementAt(findMin(root));
    }
    const Value& findMax() const {
        return elementAt(findMax(root));
    }
    const bool& find(const Key& x) const {

        return elementAt(find(x, root));


    }
    bool isEmpty() const {
        if (root == nullptr) {
            return true;
        }
        return false;
    }
    void printTree() const {
        if (isEmpty())
            cout << "Empty tree" << endl;
        else
            printTree(root);

    }

    void makeEmpty() {
        makeEmpty(root);
    }
    void insert(const Value x, Key w)
    {
        if (root == NULL) {
            root = new BSTNode< Key, Value>(x, w, NULL, NULL);
        }
        else {
            insert(x, w, root);

        }

    }

    void remove(const Key& x) {
        remove(x, root);
    }

    Value return_w(const Key& w) {
        BSTNode< Key, Value>* x = find(w, root);
        return x->element;
    }




};

#endif 
