//
// Created by Jiawen Liu on 1/21/20.
//
#pragma once;
#ifndef ASSIGNMENT1_PART2_OBJECT_H
#define ASSIGNMENT1_PART2_OBJECT_H

#endif //ASSIGNMENT1_PART2_OBJECT_H


class Object {

public:
    virtual size_t hash() {
        size_t hash_ = reinterpret_cast<size_t>(this);
        size_t x = 3145889 & 15;
        return hash_;
    }

    virtual bool equals(Object* object) {
        return this == object;
    }
};
