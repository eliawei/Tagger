//
// Created by Gchiko on 28-Nov-18.
//

#ifndef MWET1_LIST_H
#define MWET1_LIST_H

#include <iostream>
#include "exceptions.h"

template <class K, class D>
class List {
    class Node {
        K key; // the key of the node.
        D data; // the data that the node contains.
        Node* next; // the next node in the list.
        Node* prev; // the previous node in the list.

        friend class List; // now class List can access private members of Node

    public:
        /**
         * the basic c'tor, constructs a node with given data and key.
         * @param data - the data that the link contains.
         * @param key - the key that the link contains.
         */
        Node(const K& key, const D& data) :
                    key(key),
                    data(data),
                    next(NULL),
                    prev(NULL) {};


        /**
         * node d'tor - deletes the given node.
         */
        ~Node()= default;
    };

    int size; // indicates the amount of nodes in the list.
    Node* head; // pointer for the first node in the list.

public:

    /**
     * list c'tor' - construct an empty list.
     */
    List(): size(0), head(NULL){}

    /**
     * list d'tor - deletes the given list and all of it's nodes.
     */
    ~List() {
        Node* node = this->head;
        Node* next;
        while (node != NULL) {
            next = node->next;
            delete node; //does it work?!
            this->size--;
            node = next;
        }
    }

    /**
     * indicates the amount of nodes in the list.
     * @return size field of the list.
     */
    int getSize() const {
        return this->size;
    }

    /**
     * inserting a new data with it's key to the start of the list.
     * @param key - key of the new node.
     * @param data - data of the new node.
     * @param node - a pointer to a variable which will contain the value of the element.
     */
    void insert(const K& key, const D& data, void** node) {
        Node* new_node = new Node(key, data);

        if (this->size != 0) {
            new_node->next = this->head;
            this->head->prev = new_node;
        }
        this->head = new_node;
        this->size++;
        *node = new_node;
    }

    /**
     * search for the node that match a given key.
     * @param key - key of the wanted node.
     * @return true if the node was found, false otherwise.
     */
    void search(const K& key, void** value) {
        Node* wanted_node = this->head;
        while (wanted_node != NULL && wanted_node->key != key) {
            wanted_node = wanted_node->next;
        }
            if (wanted_node == NULL) {
                throw not_found();
            }

            *value = wanted_node->data;
    }

    /**
     * removes a node from the list that match the given key.
     * @param key - key of the node to be deleted.
     * @return false if the key does not exists, true if it was removed.
     */
    void remove(const K& key) {
        Node* node_to_delete = this->head;
        while (node_to_delete != NULL && node_to_delete->key != key) {
            node_to_delete = node_to_delete->next;
        }
        if (node_to_delete == NULL) {
            throw not_found();
        }

        removeByPointer(node_to_delete);
    }

    /**
     * removes a node from the list that the given pointer points at.
     * @param node_to_delete - pointer for the node to be deleted.
     */
    void removeByPointer(void* node_to_delete) {
        Node* node = (Node*)node_to_delete;
        if (node == this->head) {
            this->head = this->head->next;
        }

        if (node->prev != NULL) {
            node->prev->next = node->next;
        }

        if (node->next != NULL) {
            node->next->prev = node->prev;
        }

        delete node;
        this->size--;
    }

};




#endif //MWET1_LIST_H
