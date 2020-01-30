//
// Created by Jiawen Liu on 1/24/20.
//

#ifndef PART2_HASHNODE_H
#define PART2_HASHNODE_H

#endif //PART2_HASHNODE_H

#pragma once;
#include "object.h"
#include <stddef.h>

/**
 * Hashnode class is represent of key-value pairs
 * Hashmap objects are stored in each bucket in our Hashmap
 * The implementation of hashnode is using linked list
 */
class Hashnode : public Object{

public:
    Object* _key;
    Object* _value;
    Hashnode* next;

public:
    /**
     * Default constructor that construct an object of Hashnode
     * @param key       the key needs to be hased and specify where the value resides
     * @param val       the value needs to be stored in Hashmap
     * @param next      Hashnode pointer that points to the next Hashnode
     */
    Hashnode(Object* key, Object* val) {
        this->_key = key;
        this->_value = val;
        this->next = nullptr;
    }

    // /**
    //  * Hashnode constructor that make a copy of the given Hashnode
    //  * @param node      the node that needs to be copied
    //  */
    // Hashnode(Hashnode* node) {
    //     this->_key = node->_key;
    //     this->_value = node->_value;
    //     this->next = nullptr;
    // }

    /**
    * Hashnode destructor that delete Hashnode object
    */
    ~Hashnode() {

    }

    bool equals(Object* object) {
        if (object == nullptr) return false;
        Hashnode* other = dynamic_cast<Hashnode*>(object);
        if (other == nullptr) return false;
        return this->_key->equals(other->_key) 
            && this->_value->equals(other->_value);
    }

    size_t hash() {
        return this->_key->hash() + this->_value->hash();
    }
};
