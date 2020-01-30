//lang::CwC
#pragma once

#include "object.h"
#include <cstdlib>
#include <cstring>
#include <cstdio> 
#include <stddef.h>

/**
 * An immutable String class representing a char*
 * author: chasebish */
class String : public Object {
    public:
        char* data;
        size_t length;
        size_t hashCode;
    /** CONSTRUCTORS & DESTRUCTORS **/

    /* Creates a String copying s */
    String(const char* s) {
        this->data = strdup(s);
        this->length = strlen(s);
        this->hashCode = this->hash();
    }

    /* Copies a String copying the value from s */
    String(String* const s) {
        this->data = strdup(s->data);
        this->length = s->length;
        this->hashCode = this->hash();   
    }

    /* Clears String from memory */
    ~String() {
        delete this->data;
    }


    /** INHERITED METHODS **/

    /* Inherited from Object, generates a hash for a String */
    size_t hash() {
            if (this->hashCode != 0) {
                return this->hashCode;
            }
            size_t hashValue = 0;
            size_t prime = 43;
            size_t mod = 17;
            size_t primeToPower = 1;
            for (size_t i = 0; i < this->length; i++) {
                size_t charVal = static_cast<size_t>(*(this->data + i));
                hashValue += charVal * primeToPower % mod;
                primeToPower = (primeToPower * prime) % mod;
            }

            return hashValue;
    }

    /* Inherited from Object, checks equality between an String and an Object */
    bool equals(Object* const obj) {
        String* s = dynamic_cast<String*>(obj);
        if (s == nullptr) return false;
        return this->cmp(s) == 0;
    }


    /** STRING METHODS **/
  
    /** Compares strings based on alphabetical order
     * < 0 -> this String is less than String s
     * = 0 -> this String is equal to String s
     * > 0 -> this String is greater than String s
     */
    int cmp(String* const s) {
        return strcmp(this->data, s->data);
    }

    /* Creates a new String by combining two existing Strings */
    String* concat(String* const s) {
        char* compoundString = new char[this->length + s->length];
        strncpy(compoundString, this->data, this->length);
        strncpy(compoundString + this->length, s->data, s->length);
        String* newString = new String(compoundString);
        delete[] compoundString;
        return newString;
    }

    /* Returns the current length of the String */
    size_t size() {
        return this->length;
    }
};