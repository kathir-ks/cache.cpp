#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <vector>

class KeyValuePair
{
    public:
        void * Key;
        void * Value;
        KeyValuePair * Next = NULL;

        KeyValuePair(void * Key, void * Value);
};

class HashTable
{
    public:
        void (*HashFunction)(void* Key);
        void **Slots;
        void InitializeHashTable(const int &SlotSize = 1024);
        void DeleteHashTable();
        void ResizeHashTable(const int &NewslotSize);
};

#endif