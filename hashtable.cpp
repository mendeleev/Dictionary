#include <cstdlib>
#include <iostream>
#include <string>

#include "hashtable.h"

using namespace std;


/*Create the Hash Table*/

HashTable::HashTable() 
{
    for (int i = 0; i < HashTableSize; i++) 
    {
        Table[i] = new Item;
        Table[i]->English = "empty";
        Table[i]->Russian = "empty";
        Table[i]->next = NULL;
    }
}
/*------------------------------------------*/


/*Get hash key*/

int HashTable::Hash(string key) 
{

    int hash = 0;
    int index;
    
    for (int i = 0; i < key.length(); i++) 
    {
        hash += (int)key[i];
    }
    
    index = hash % HashTableSize;
   
    return index;
}
/*------------------------------------------*/


/*Add word to the hash table*/

bool HashTable::AddWord(string English, string Russian) 
{
    int index = Hash(English);
    
    if(SearchWord(English) != NULL) {
        return false;
    }
    
    if (Table[index]->English == "empty") {
        
        Table[index]->English = English;
        Table[index]->Russian = Russian;
    
    } else {
    
        Item* ptr = Table[index];
        Item* next = new Item;
        next->English = English;
        next->Russian = Russian;
        next->next = NULL;
        
        while (ptr->next != NULL) {
        
            ptr = ptr->next;
        }
        
        ptr->next = next;
    }
    return true;    
}
/*------------------------------------------*/


/*Get the number of elements in hash*/

int HashTable::NumberOfItemsInIndex(int index) 
{
    int counter = 0;
    
    if (Table[index]->English == "empty") {
    
        return counter;
    } else {
    
        counter++;
        Item* ptr = Table[index];
        
        while (ptr->next != NULL) {
            
            counter++;
            ptr = ptr->next;
        }
    }
    
    return counter;
}
/*------------------------------------------*/


/*Print Content by Index*/

void HashTable::PrintItemsInIndex(int index) 
{
    Item* ptr = Table[index];
    
    if (ptr->English != "empty") {
        while(ptr != NULL) {
            cout << ptr->English << " - " << ptr->Russian << endl;
            ptr = ptr->next;}
    }
}
/*------------------------------------------*/


/*Print Hash Table*/

void HashTable::PrintTable() 
{
    int number;
    for (int i = 0; i < HashTableSize; i++) 
    {
        PrintItemsInIndex(i);
    }
}
/*------------------------------------------*/


/*Search the Word*/

Item* HashTable::SearchWord(string English) 
{
    int index = Hash(English);
    bool is_found = false;
    
    string Russian;
    Item* ptr = Table[index];
    
    while(ptr != NULL) 
    {
        if (ptr->English == English) {
        
            is_found = true;
            Russian = ptr->Russian;
            break;
        }
        
        ptr = ptr->next;
    }
    
    if(is_found == true) {    
        return ptr;
    } else {
        return NULL;}
}

/*----------------------------------*/

/*Remove Word*/

bool HashTable::RemoveWord(string English) 
{
    int index = Hash(English);
    
    Item* pDel;
    Item* p1;
    Item* p2;
    
    if (Table[index]->English == "empty" && Table[index]->Russian == "empty") {
    
        return true;
    }
    
    else if (Table[index]->English == English && Table[index]->next == NULL) {
    
        Table[index]->English = "empty";
        Table[index]->Russian = "empty";
        
        return true;
    }
    
    else if (Table[index]->English == English) {
    
        pDel = Table[index];
        Table[index] = Table[index]->next;
        delete pDel;
        
        return true;
    }
    
    else {
    
        p1 = Table[index]->next;
        p2 = Table[index];
        
        while(p1 != NULL && p1->English != English) {
        
            p2 = p1;
            p1 = p1->next;
        }
        
        if(p1 == NULL) {
        
            return false;
        } 
        else {
        
            pDel = p1;
            p1 = p1->next;
            p2->next = p1;
            
            delete pDel;
            return true;
        }
    }
}

/*----------------------------------*/


/*Add Word to the file*/

void HashTable::FileWordAdd(string Word) 
{
    FILE* pFile;
    pFile = fopen(filename.c_str(), "a");
    fputs(Word.c_str(), pFile);
    fputs("\n", pFile);
    fclose(pFile);
}

/*----------------------------------*/


/*Read file and load data to the Hash Table*/

void HashTable::FileRead() 
{
    char line[100];
    string English;
    string Russian;
    int last;
    FILE* pFile;
    pFile = fopen(filename.c_str(), "r");
    
    while (true) 
    {
        fgets(line, 100, pFile);
        if(feof(pFile)) {
                break;}
        English = line;
        last = English.length()-1;
        
        if(English[last] == '\n') {
            English.erase(last);
        }
        
        fgets(line, 100, pFile);
        if(feof(pFile)) {
                break;}
        Russian = line;
        last = Russian.length()-1;
        
        if(Russian[last] == '\n') {
            Russian.erase(last);
        }        
        
        AddWord(English, Russian);
    }
    
    fclose(pFile);
}

/*----------------------------------*/


void HashTable::FileSave() 
{
    FILE* pFile;
    pFile = fopen(filename.c_str(), "w");
    for (int i = 0; i < HashTableSize; i++) 
    {
        Item* ptr = Table[i];

        if (ptr->English == "empty") {
            continue;
        } else {
            while(ptr != NULL) {
                fputs(ptr->English.c_str(), pFile);
                fputs("\n", pFile);
                fputs(ptr->Russian.c_str(), pFile);
                fputs("\n", pFile);
                ptr = ptr->next;}
        }
    }
    
    fclose(pFile);
}

