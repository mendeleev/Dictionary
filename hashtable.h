/* 
 * File:   hashtable.h
 * Author: mendart
 *
 * Created on October 11, 2013, 3:50 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#ifndef HASHTABLE_H
#define	HASHTABLE_H

struct Item 
    {
        string English;
        string Russian;
        Item* next;
    };

class HashTable 
{
private:
    static const unsigned int HashTableSize = 4;
    string filename = "file.dat";
    /*
    struct Item 
    {
        string English;
        string Russian;
        Item* next;
    };*/
    
    Item* Table[HashTableSize];
    
public:
    HashTable();
    int Hash(string key);
    bool AddWord(string English, string Russian);
    int NumberOfItemsInIndex(int index);
    void PrintItemsInIndex(int index);
    void PrintTable();
    Item* SearchWord(string English);
    void EditWord(string English);
    bool RemoveWord(string English);
    
    void FileWordAdd(string Word);
    void FileRead();
    void FileSave();
    
};


#endif	/* HASHTABLE_H */

