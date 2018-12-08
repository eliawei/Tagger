//
// Created by Gchiko on 04-Dec-18.
//

#ifndef MWET1_AVL_TREE_H
#define MWET1_AVL_TREE_H

#include <stdio.h>
#include <iostream>
#include "exceptions.h"

using namespace std;
#include "exceptions.h"


template<class S, class T>
class AVL_Tree {
    class Node {
        S key;
        T data;
        int height; //AVL patch
        Node *left = nullptr;
        Node *right = nullptr;
        Node *parent = nullptr;
    public:
        Node(const S &key, const T &data) : key(key), data(data) {}

        bool is_right_son() {
            return parent->key < key;
        }

        void print_node() {
            int left_key;
            if (left) {
                left_key = left->key;
            } else {
                left_key = -1;
            }
            int right_key;
            if (right) {
                right_key = right->key;
            } else {
                right_key = -1;
            }

            int parent_key;
            if (parent) {
                parent_key = parent->key;
            } else {
                parent_key = -1;
            }

            cout << " key: " << key << " parent: " << parent_key <<
            //" Data: " << data  <<
            " left: " << left_key << " right: " << right_key << " height: " << height << endl;
        }

        Node *next_inorder() {
            Node *t = right;
            while (t->left) {
                t = t->left;
            }
            return t;
        }

        //AVL patch
        void update_height() {
            int right_h = -1, left_h = -1;
            if (right) {
                right_h = right->height;
            }
            if (left) {
                left_h = left->height;
            }
            height = max(right_h, left_h) + 1;
        }

        int BF() {
            int right_h = -1, left_h = -1;
            if (right) {
                right_h = right->height;
            }
            if (left) {
                left_h = left->height;
            }
            return ((left_h) - (right_h));
        }
// continue cheking
        void roll_right() {
            Node *left_son = left;
            Node *left_right_son = nullptr;
            if (left_son->right) {
                left_right_son = left_son->right;
            }
            left_son->right = this;
            left = left_right_son;
            if (left_right_son) {
                left_right_son->parent = this;
            }

            left_son->parent = this->parent;
            if (left_son->parent != NULL) {
                if (left_son->is_right_son()) {
                    left_son->parent->right = left_son;
                } else {
                    left_son->parent->left = left_son;
                }
            }
            this->parent = left_son;

            this->update_height();
            left_son->update_height();
        }

        void roll_left() {
            Node *right_son = right;
            Node *right_left_son = nullptr;
            if (right_son->left) {
                right_left_son = right_son->left;
            }
            right_son->left = this;
            right = right_left_son;
            if (right_left_son) {
                right_left_son->parent = this;
            }

            right_son->parent = this->parent;
            if (right_son->parent != NULL) {
                if (right_son->is_right_son()) {
                    right_son->parent->right = right_son;// for normal RR - if it's part of LR need to do something else
                } else {
                    right_son->parent->left = right_son;
                }
            }
            this->parent = right_son;


            this->update_height();
            right_son->update_height();
        }

        void LR() {
            this->left->roll_left();
            roll_right();
        }

        void RL() {
            this->right->roll_right();
            roll_left();
        }

        void roll() {
            int BF_Self = BF();
            int BFL = -2, BFR = 2;
            if (left) {
                BFL = (left->BF());
            }
            if (right) {
                BFR = (right->BF());
            }
            if (BF_Self == 2) {
                if (BFL >= 0) {
                    roll_right();
                }
                if (BFL == -1) {
                    LR();
                }
            } else if (BF_Self == -2) {
                if (BFR == 1) {
                    RL();
                }
                if (BFR <= 0) {
                    roll_left();
                }
            }

        }

        friend class AVL_Tree;
    };

private:
    Node *root = nullptr;
    int size = 0;

    void destroy_tree(Node *node) {
        if (node == nullptr) {
            return;
        }
        destroy_tree(node->left);
        destroy_tree(node->right);
        delete node;
    }

    Node *find_free_space(Node *node, const S &key) {
        if (node->key == key) {
            return nullptr;
        } else if (node->key > key) {
            if (node->left == nullptr) {
                return node;
            }
            find_free_space(node->left, key);
        } else if (node->key < key) {
            if (node->right == nullptr) {
                return node;
            }
            find_free_space(node->right, key);
        }
    }

    /**
     * Prints out the tree in an in order method.
     * @param root: starts from given root.
     */
    void print_in_order(Node *root) {

        if (root == nullptr) {
            return;
        }
        print_in_order(root->left);
        root->print_node();
        print_in_order(root->right);
    }

    Node *internal_find(Node *node, const S &key) {
        if (!node) {
            return nullptr;
        }
        if (node->key == key) {
            return node;
        }
        if (node->key > key) {
            return internal_find(node->left, key);
        } else {
            return internal_find(node->right, key);
        }
    }

    //AVL patch

    void update_heights_insertion(Node *node) {
        node->height = 0;
        while (node != root) {
            Node *p = node->parent;
            //need to check//p->update_height();
            if (p->height >= (node->height + 1)) {
                break;
            }
            p->height = node->height + 1;
            if (abs(p->BF()) > 1) {
                p->roll();
                update_root(p);
                break;
            }
            node = p;
        }
    }

    void balance_fix(Node* node) {
        while (node) {
            int old_height = node->height;
            node->update_height();

            Node* parent = node->parent;// need to move to the original parent of the node (before the roll).
            if (abs(node->BF()) == 2) {
                node->roll();
                update_root(node);
            } else if (old_height == node->height) {
                break;
            }
            node = parent;
        }
    }

    void update_root(Node* node) {
        if (node->parent->parent == NULL) {
            this->root = node->parent;
        }
    }

    void tree_to_array_aux(T* arr,Node* node,int& i){
        if (node == nullptr) {
            return;
        }
        tree_to_array_aux(arr,node->left,i);
        arr[i++]=node->data;
        tree_to_array_aux(arr,node->right,i);
    }
public:
    virtual ~AVL_Tree() {
        destroy_tree(root);
    }

/**
 * gets data and key,makes a node and inserts it to tree
 */
    void insert(const S &key, const T &data, void** node) {
        Node* new_node = new Node(key, data);
        if (!root) {
            root = new_node;
        } else {
            Node *parent = find_free_space(root, key);
            new_node->parent = parent;
            if (new_node->is_right_son()) {
                parent->right = new_node;
            } else {
                parent->left = new_node;
            }
        }
        size++;
        update_heights_insertion(new_node);
        *node = new_node;
    }


    void search(const S &key, void** value) {
        Node* wanted_node = find(key);
        *value = wanted_node->data;
        return;
    }
    /**
     * With given key, return the node holds it.
     * @param key
     */
    Node *find(const S &key) {
        Node *found = internal_find(root, key);
        if (!found) {
            throw not_found();
        }
        return found;
    }

    /**
     * prints out the tree.
     */
    void print() {
        this->print_in_order(root);
    }

    /**
     *  if key is not in the tree- there is nothing to remove
     *  (exception would be thrown).
     * @param key
     */
    void remove_by_key(const S &key) {
        Node *node = find(key);
        remove_by_pointer(node);
    }

    void remove_by_pointer(void* p) {
        Node* node = (Node*)p;
        Node* parent;
        if (node->right && node->left) {
            parent = node->next_inorder()->parent;
        } else {
            parent = node->parent;
        }

        root = remove_by_pointer(root, node->key);
        size--;
        balance_fix(parent);
    }

/**
 * will delete the wanted node and return new root for handled tree
 */
    Node *remove_by_pointer(Node *node, const S &key) {
        //Step 1- find the wanted node,recursively (and fix the path)
        //stop condition-no node
        if (!node) {
            return node;
        }
        if (key < node->key) {
            node->left = remove_by_pointer(node->left, key);
        } else if (key > node->key) {
            node->right = remove_by_pointer(node->right, key);
        }
            //FOUND IT
        else {
            //Step 2- delete it
            //Case 1- no children/one child
            if (!node->right) {
                Node *temp = node->left;

                if (temp) {
                    temp->parent = node->parent;
                }
                delete node;
                return temp;
            }
            if (!node->left) {
                Node *temp = node->right;

                if (temp) {
                    temp->parent = node->parent;
                }

                temp->parent = node->parent;
                delete node;
                return temp;
            }
            //Case 2- has 2 children
            Node *temp = node->next_inorder();
            node->key = temp->key;
            node->data = temp->data;
            node->right = remove_by_pointer(node->right, temp->key);
        }
        return node;
    }

    int getSize() const {
        return size;
    }

    T* tree_to_array(){
        T* arr=new T[(this->size)* sizeof(T)];
        int i=0;
        tree_to_array_aux(arr,root,i);
        return arr;
    }


};

#endif //MWET1_AVL_TREE_H
