//
// Created by Jiawen Liu on 1/23/20.
//

#ifndef ASSIGNMENT1_PART2_STRING_H
#define ASSIGNMENT1_PART2_STRING_H

#endif //ASSIGNMENT1_PART2_STRING_H

#pragma once;
#include "object.h"
#include <stdio.h>
#include <string.h>

#ifndef STRING_H
#define STRING_H

class String: public Object
{
public :
    int length;
    char* data;
public:

    String() {
        length = 0;
        data = nullptr;
    }

    String(int capacity);

    String(char* s) {
        length = strlen(s) + 1; 
        data = new char[length];
        for (int i = 0; i < length; i++) {
        data[i] = s[i];
        }
        data[length - 1] = '\0';
    }
    ~String() {
        delete[] data;
    }

public:
    size_t hash() {
        size_t v = 0;
        for (int i = 0; i < strlen(this->data); i++) {
            v = data[i] + (7 * v); 
        }
        return v;
    }

    bool equals(Object* object) {
        if (object == nullptr) {
        return false;
        }

        String *s = dynamic_cast<String*>(object);

        if (s == nullptr) {
        return false;
        }
        return strcmp(data, s->data) == 0;
    }

    String* concat(String* s) {
        size_t t_size = length + s->length - 1;
        char* t_val = new char[t_size];
        for (size_t i = 0; i < length - 1; i++) {
            t_val[i] = data[i];
        }
        for (size_t i = 0; i < s->length - 1; i++) {
            t_val[i + length - 1] = s->data[i]; 
        }
        t_val[t_size - 1] = '\0';
        return new String(t_val);
    }

    int compareTo(String* s) {
        return strcmp(this->data, s->data);
    }
};
#endif
