#pragma once;
#include <iostream>
#include <string.h>
#include "object.h"
#include "hashmap.h"
#include "string.h"


void FAIL() {   exit(1);    }
void OK(const char* m) { std:: cout << "All test cases in test " << m << " are passed" << std:: endl;}
void t_true(bool p) { if (!p) FAIL(); }
void t_false(bool p) { if (p) FAIL(); }


/**
 * test cases for put() and get_size() methods
 * put an object(in this case we used string) will increase the size of hashmap
 */
void test1() {
    Hashmap* h1 = new Hashmap();
    String * key_1 = new String("Hello");
    String * val_1 = new String("1");
    String * key_2 = new String("World");
    String * val_2 = new String("2");
    h1->put(key_1, val_1);
    t_true(h1->get_size() == 1);
    h1->put(key_2, val_2);
    t_true(h1->get_size() == 2);
    OK("1");
}

/**
 * test cases for put() and get_size() method when using the same key
 * put an object(in this case we used string) with the same key will replace the associated value
 * the size of hashmap will not be increased
 */
void test2() {
    Hashmap* h1 = new Hashmap();
    String * key_1 = new String("Hello");
    String * val_1 = new String("1");
    String * val_2 = new String("2");
    h1->put(key_1, val_1);
    t_true(h1->get_size() == 1);
    h1->put(key_1, val_2);
    t_true(h1->get_size() == 1);
    OK("2");
}

/**
 * test cases for get() methods
 * comparing value extracting from hashmap with input value
 */
void test3() {
    Hashmap* h1 = new Hashmap();
    String * key_1 = new String("Hello");
    String * val_1 = new String("1");
    String * key_2 = new String("World");
    String * val_2 = new String("2");
    h1->put(key_1, val_1);
    h1->put(key_2, val_2);
    t_true(h1->get(key_1)->equals(val_1));
    t_true(h1->get(key_2)->equals(val_2));
    OK("3");
}

/**
 * test cases for get() methods when using the same key
 * comparing value extracting from hashmap with input value
 * associated value of the same key will be different since the original value have been replaced
 */
void test4() {
    Hashmap* h1 = new Hashmap();
    String * key_1 = new String("Hello");
    String * val_1 = new String("1");
    String * val_2 = new String("2");
    h1->put(key_1, val_1);
    t_true(h1->get(key_1)->equals(val_1));
    h1->put(key_1, val_2);
    t_true(h1->get(key_1)->equals(val_2));
    OK("4");

}

/**
 * test cases for remove() method
 * comparing value that removed from hashmap should be the same as associated value of input key
 */

void test5() {
    Hashmap* h1 = new Hashmap();
    String * key_1 = new String("Hello");
    String * val_1 = new String("1");
    String * key_2 = new String("World");
    String * val_2 = new String("2");
    h1->put(key_1, val_1);
    h1->put(key_2, val_2);
    t_true(h1->remove(key_1)->equals(val_1));
    t_false(h1->remove(key_2)->equals(val_1));
    t_true(h1->remove(key_1) == NULL);

    OK("5");
}

/**
 * test cases for containsKey() method
 * testing on if an associated value of input key is existed in the hashmap
 */
void test6() {
    Hashmap* h1 = new Hashmap();
    String * key_1 = new String("Hello");
    String * val_1 = new String("1");
    String * key_2 = new String("World");
    String * val_2 = new String("2");
    String * key_3 = new String("NEU");
    h1->put(key_1, val_1);
    h1->put(key_2, val_2);
    t_true(h1->contains_key(key_1));
    t_true(h1->contains_key(key_2));
    t_false(h1->contains_key(key_3));
    OK("6");
}


/**
 *
 * test cases for resize()
 * default capacity of hashmap is 16
 * when the number of elements hits the threshold of the hashmap, the capacity will be doubled
 */

void test7() {
    Hashmap* h1 = new Hashmap();
    String * key_1 = new String("A");
    String * val_1 = new String("1");
    String * key_2 = new String("B");
    String * val_2 = new String("2");
    String * key_3 = new String("C");
    String * val_3 = new String("3");
    String * key_4 = new String("D");
    String * val_4 = new String("4");
    String * key_5 = new String("E");
    String * val_5 = new String("5");
    String * key_6 = new String("F");
    String * val_6 = new String("6");
    String * key_7 = new String("G");
    String * val_7 = new String("7");
    String * key_8 = new String("H");
    String * val_8 = new String("8");
    String * key_9 = new String("I");
    String * val_9 = new String("9");
    String * key_10 = new String("J");
    String * val_10= new String("10");
    String * key_11 = new String("K");
    String * val_11 = new String("11");
    String * key_12 = new String("L");
    String * val_12 = new String("12");
    String * key_13 = new String("M");
    String * val_13 = new String("13");
    String * key_14 = new String("N");
    String * val_14 = new String("14");
    String * key_15 = new String("O");
    String * val_15 = new String("15");
    String * key_16 = new String("P");
    String * val_16 = new String("16");
    String * key_17 = new String("Q");
    String * val_17 = new String("17");


    h1->put(key_1, val_1);
    h1->put(key_2, val_2);
    h1->put(key_3, val_3);
    h1->put(key_4, val_4);
    h1->put(key_5, val_5);
    h1->put(key_6, val_6);
    t_true(h1->get_size() == 6);
    t_true(h1->get_capacity() == 16);
    h1->put(key_7, val_7);
    h1->put(key_8, val_8);
    h1->put(key_9, val_9);
    h1->put(key_10, val_10);
    h1->put(key_11, val_11);
    h1->put(key_12, val_12);
    h1->put(key_13, val_13);
    h1->put(key_14, val_14);
    t_true(h1->get_size() == 14);
    h1->put(key_15, val_15);
    h1->put(key_16, val_16);
    t_true(h1->get_size() == 16);
    h1->put(key_17, val_17);
    t_true(h1->get_size() == 17);
    t_true(h1->get_capacity() == 32);
    OK("7");
}

/**
 * test cases for keys() function
 * testing on keys() function that return all keys that exist in the hashmap
 */
void test8() {
    Hashmap* h1 = new Hashmap();
    String * key_1 = new String("A");
    String * val_1 = new String("1");
    String * key_2 = new String("B");
    String * val_2 = new String("2");
    String * key_3 = new String("C");
    String * val_3 = new String("3");
    h1->put(key_1, val_1);
    h1->put(key_2, val_2);
    h1->put(key_3, val_3);
    Object** keys_array;
    keys_array =  h1->key_set();
    t_true(keys_array[0]->equals(key_1));
    t_true(keys_array[1]->equals(key_2));
    t_true(keys_array[2]->equals(key_3));
    OK("8");
}


/**
 * test cases for values() function
 * testing on keys() function that return all values that exist in the hashmap
 */
void test9() {

    Hashmap* h1 = new Hashmap();
    String * key_1 = new String("A");
    String * val_1 = new String("1");
    String * key_2 = new String("B");
    String * val_2 = new String("2");
    String * key_3 = new String("C");
    String * val_3 = new String("3");
    h1->put(key_1, val_1);
    h1->put(key_2, val_2);
    h1->put(key_3, val_3);
    Object** values_array;
    values_array = h1->values();
    t_true(values_array[0]->equals(val_1));
    t_true(values_array[1]->equals(val_2));
    t_true(values_array[2]->equals(val_3));
    OK("9");
}





int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    return 0;
}
