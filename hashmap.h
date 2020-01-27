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
        this->table = new Hashnode*[16];
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

    /**
     * resize of inner array when size hits its threshold(capacity)
     */
    void resize() {
    
    }


    /**
     * Associates the specified value with the specified key in this map.
     * If the map previously contained a mapping for the key, the old value is replaced.
     * @param key   key with which the specified value is to be associated
     * @param val   value to be associated with the specified key
     * @return  the previous value associated with key, or null if there was no mapping for key.
     */
    Object* put(Object* key, Object* val) {
        int index = index_for(key);
        Hashnode* prev = nullptr;
        Hashnode* node = *(this->table + index);
        while (node->next != nullptr) {
            prev = node;
            node = node->next;
        }
        prev->next = new Hashnode(key, val);
        this->hash_code += prev->hash();
        this->size++;
    }


    /**
     * Returns the value to which the specified key is mapped, or null if this map contains no mapping for the key.
     * @param key   the key whose associated value is to be returned
     * @return  the value to which the specified key is mapped, or null if this map contains no mapping for the key
     */
    Object* get(Object* key) {
        return getHashnode(key);
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
        while (node != nullptr && !node->_key->equals(key)) {
            prev = node;
            node = node->next;
        }
        this->hash_code -= node->hash();
        Object* value = node->_value;
        if (prev != nullptr) {
            prev->next = node->next;
        } else {
            delete node;
            *node = node->next; 
        }

        return value;
    }


    /**
     * @return  a list of the keys contained in this map
     */
    Object** key_set() {
        Object** keys = new Object*[this->size];
        int counter = 0;
        for (int i = 0; i < this->capacity; i++) {
            Hashnode* node = *(this->table + i);
            while (node != nullptr) {
                *(keys + counter) = node->_key;
                node = node->next;
                counter++;
            }
        }

        return keys;
    }


    /**
     * @return  a list of values contained in this map
     */
    Object** values() {
        Object** value_list = new Object*[this->size];
        int counter = 0;
        for (int i = 0; i < this->capacity; i++) {
            Hashnode* node = *(this->table + i);
            while (node != nullptr) {
                *(value_list + counter) = node->_value;
                node = node->next;
                counter++;
            }
        }

        return value_list; 
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
        Hashnode* node = *(this->table + index);
        while (node != nullptr && !node->_key->equals(key)) {
            node = node->next;
        }
        return node;
     }
};