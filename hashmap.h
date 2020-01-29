//
// Created by Jiawen Liu on 1/24/20.
//

#ifndef PART2_HASHMAP_H
#define PART2_HASHMAP_H

#endif //PART2_HASHMAP_H

#pragma once;
#include "object.h"
#include "hashnode.h"

class Hashmap : public Object {

public:
    Hashnode** table;
    int size;
    int capacity;
    int hash_code;


public:
    /**
     * Default constructor that constructs an empty HashMap with
     * the default initial capacity 16
    */
    Hashmap() {
        this->table = new Hashnode*[16]();
        this->capacity = 16;
        this->size = 0;
        this->hash_code = 0;
    }

    /**
     * Destructor that delete Hashmap object
     */
    ~Hashmap() {
        if (this->table != nullptr) delete[] this->table;
    }

public:
    /**
     * Returns the number of key-value (Hashnode) mappings in this map.
     */
    int get_size() {
        return this->size;
    }

    /**
     * Returns the capacity of key-value (Hashnode) mappings in this map.
     */
    int get_capacity() {
        return this->capacity;
    }

    /**
     * return index for hashcode of key
     * @param key       the key that used to be hashed and get location of an object that needs to be stored
     * @return index    index of the inner array
     */
    int index_for(Object* key) {
        return key->hash() & (this->capacity - 1);
    }

    // Private helper for resize
    int index_for(Object* key, size_t new_capacity) {
        return key->hash() & (new_capacity - 1);
    }

    /**
     * resize of inner array when size hits its threshold(capacity)
     */
    void resize() {
        Hashnode** nodes = this->nodes();
        this->capacity *= 2;
        Hashnode** new_table = new Hashnode*[this->capacity]();
        int old_size = this->size;
        this->size = 0;
        this->hash_code = 0;
        this->table = new_table;
        for (int i = 0; i < old_size; i++) {
            Hashnode * node = nodes[i];
            this->put(node->_key, node->_value);
        }
    }


    /**
     * Associates the specified value with the specified key in this map.
     * If the map previously contained a mapping for the key, the old value is replaced.
     * @param key   key with which the specified value is to be associated
     * @param val   value to be associated with the specified key
     * @return  the previous value associated with key, or null if there was no mapping for key.
     */
    Object* put(Object* key, Object* val) {
        if (!this->contains_key(key) && size == capacity) {
            this->resize();
        }
        int index = index_for(key);
        Hashnode* prev = nullptr;
        Hashnode* node = *(this->table + index);
        Hashnode * new_node = new Hashnode(key, val);
        if (node == nullptr) {
            *(this->table + index) = new_node;
            this->size++;
            this->hash_code += new_node->hash();
            return val;
        }
        while (node != nullptr && !node->_key->equals(key)) {
            prev = node;
            node = node->next;
        }

        // Replacement
        if (node != nullptr) {
            this->hash_code -= node->hash();
            this->size--;
            *node = *new_node;
        }
        if (prev != nullptr) {
            new_node->next = prev->next;
            prev->next = new_node;
        }
        this->hash_code += new_node->hash();
        this->size++;
        return val;
    }


    /**
     * Returns the value to which the specified key is mapped, or null if this map contains no mapping for the key.
     * @param key   the key whose associated value is to be returned
     * @return  the value to which the specified key is mapped, or null if this map contains no mapping for the key
     */
    Object* get(Object* key) {
        return getHashnode(key)->_value;
    }


    /**
     * Returns true if this map contains a mapping for the specified key.
     * @param key   The key whose presence in this map is to be tested
     * @return  true if this map contains a mapping for the specified key, otherwise false
     */
    bool contains_key(Object* key) {
        return getHashnode(key) != nullptr;
    }


    /**
     * Removes the mapping for the specified key from this map if present.
     * @param key   key whose mapping is to be removed from the map
     * @return  the previous value associated with key, or null if there was no mapping for key.
     */
    Object* remove(Object* key) {
        int index = index_for(key);
        Hashnode* prev = nullptr;
        Hashnode* node = *(this->table + index);
        while (node != nullptr && node->_key != nullptr && !node->_key->equals(key)) {
            prev = node;
            node = node->next;
        }
        if (node == nullptr) {
            return NULL;
        }
        this->hash_code -= node->hash();
        Object* value = node->_value;
        if (prev != nullptr) {
            prev->next = node->next;
        } else {
            *(this->table + index) = node->next; // this is always the first element in the linked list
            // delete node TODO
        }
        return value;
    }

    // Private helper to get every Hashnode
    Hashnode** nodes() {
        Hashnode** nodes = new Hashnode*[this->size];
        int counter = 0;
        for (int i = 0; i < this->capacity; i++) {
            Hashnode* node = *(this->table + i);
            while (node != nullptr) {
                *(nodes + counter) = node;
                node = node->next;
                counter++;
            }
        }
        return nodes;
    }


    /**
     * @return  a list of the keys contained in this map
     */
    Object** key_set() {
        Hashnode** nodes = this->nodes();
        Object** keys = new Object*[this->size];
        for (int i = 0; i < this->size; i++) {
            keys[i] = nodes[i]->_key;
        }
        return keys;
    }


    /**
     * @return  a list of values contained in this map
     */
    Object** values() {
        Hashnode** nodes = this->nodes();
        Object** vals_ = new Object*[this->size];
        for (int i = 0; i < this->size; i++) {
            vals_[i] = nodes[i]->_value;
        }
        return vals_;
    }

    size_t hash() {
        return this->hash_code;
    }

    bool equals(Object* object) {
        if (this->hash_code != object->hash()) return false;
        Hashmap* other_map = dynamic_cast<Hashmap*>(object);
        if (other_map == nullptr) return false;

        Object** keys = this->key_set();
        for (int i = 0; i < this->size; i++) {
            if (!(this->get(keys[i])->equals(other_map->get(keys[i])))) {
                return false;
            }
        }
        return true;
    }

    /**
     * @return the Hashnode for the given key, or nullptr if it doesn't exist 
     */
     Hashnode* getHashnode(Object* key) {
        int index = index_for(key);
        Hashnode* node = this->table[index];
        while (node != nullptr && !node->_key->equals(key)) {
            node = node->next;
        }
        return node;
     }
};