/* 
 * File:   main.cpp
 * Author: mendart
 *
 * Created on July 2, 2013, 3:13 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>

#include "hashtable.h"

using namespace std;

HashTable H;

/*Check the input string by English*/

//// NOT FINISHED YET //////////////
string engCheck(string Word) 
{
    int Length = Word.length();
    
    for (int i = 0; i < Length; i++) 
    {
        if((int)Word[i] >= (int)'a' && (int)Word[i] <= (int)'z') {
            continue;}
        
        else if((int)Word[i] >= (int)'A' && (int)Word[i] <= (int)'Z') {
            Word[i] = Word[i] + 32;} 
        
        else {
            cout << "incorrect value" << endl;
            return "0";
        }
        return Word;
    }
}
////////////////////////////////

/*-----------------------------------------*/


/*Clear screen function*/

void Clear() 
{
    system("clear");
}


/*Add word if not found in Table*/

void if_word_not_found (string Word) 
{
    string Russian;
    char Confirm;
    char AddConfirm;
    Clear();
    cout << "Do you want to add \"" << Word << "\" to the Table? (y/n)"; cin >> Confirm;

    if(Confirm == 'y' || Confirm == 'Y') {

        cout << Word << " - "; cin >> Russian;
        //add word to the Table
        AddConfirm = H.AddWord(Word, Russian);
        //add word to the file
        H.FileWordAdd(Word);
        H.FileWordAdd(Russian);
        /*------------------------------------------*/
        if(AddConfirm == true) {
            Clear();
            cout << "\"" << Word << "\" was successfuly added to the Table" << endl;
        }
    } else {
        return;}
}

/*-----------------------------------------*/


/*search Word in the Table*/

void Search() 
{
    string Word;
    string English;
    Item* ptr;
    
    Clear();
    cout << "search for: "; cin >> Word;
    
    ptr = H.SearchWord(Word);
    
    if (ptr != NULL) {
        Clear();
        cout << ptr->English << " - " << ptr->Russian << endl;
    } else {
        if_word_not_found(Word);
    }
    
}

/*-----------------------------------------*/

/*Add Word to the Table*/

void Add() 
{
    string English;
    string Russian;
    Item* ptr;
    
    cout << "English: "; cin >> English;
    Clear();
    ptr = H.SearchWord(English);
    
    if(ptr == NULL) {
    
        cout << English << " - "; cin >> Russian;
        H.AddWord(English, Russian);
        //add word to the file
        H.FileWordAdd(English);
        H.FileWordAdd(Russian);
        /*------------------------------------------*/
    } else {
        Clear();
        cout << English << " already exist in the table" << endl;
    }
    
}

/*-----------------------------------------*/

/*Remove Word from Table*/

void Remove()
{
    string Word;
    Clear();
    cout << "remove: "; cin >> Word;
    H.RemoveWord(Word);
}

/*-----------------------------------------*/

/*Edit Word*/

void Edit()
{
    string Word;
    string Confirm;
    string Russian;
    string English;
    bool RemoveConfirm;
    bool AddConfirm;
    Clear();
    cout << "edit: "; cin >> Word;
    Clear();
    
    Item* ptr;
    ptr = H.SearchWord(Word);
    
    if(ptr != NULL) {
        cout << "English /> "; cin >> English;
        if(English == "q") {
            return;}
        cout << "Russian /> "; cin >> Russian;
        if(Russian == "q") {
            return;}
    } else {
        if_word_not_found(Word);
        return;
    }
    
    RemoveConfirm = H.RemoveWord(Word);
    AddConfirm = H.AddWord(English, Russian);
    
    if(RemoveConfirm == true && AddConfirm == true) { 
        Clear();
        cout << "\"" << Word << "\" successfuly changed to \"" << English << "\"" << endl;}
}

/*-----------------------------------------*/

/*Print whole table*/

void Print()
{
    Clear();
    H.PrintTable();
}
/*-----------------------------------------*/

/*How to use program*/

void Help() 
{
    Clear();
    cout << "Command List: "
            "\n[search] - seek Word in the Table"
            "\n[add] - add new Word"
            "\n[edit] - change Word that already exist in the Table"
            "\n[remove] - erase Word from Table"
            "\n[print] - print the whole Table"
            "\n\nWARNING! Type lowercase symbols only!\n";
}

/*-----------------------------------------*/

/*About*/

void About() 
{
    Clear();
    cout << "English-Russian Dictionary v.0.0.1a" << endl;
}

/*-----------------------------------------*/

void Options(string input) 
{
    /*clear*/
    if(input == "clear") {    
        Clear();}
    /*search*/
    else if(input == "search") {        
        Search();}
    /*add new word*/
    else if(input == "add") {    
        Add();}
    /*edit*/
    else if(input == "edit") {    
        Edit();}
    /*remove*/
    else if(input == "remove") {    
        Remove();}
    /*print*/
    else if(input == "print") {    
        Print();}
    /*help*/
    else if(input == "help") {    
        Help();}
    /*about*/
    else if(input == "about") {    
        About();}
    /*save edited data to file*/
    else if(input == "save") {
        H.FileSave();
        Clear();
        cout << "Successfully saved to file" << endl;}
    /*exit program*/
    else if(input == "quit") {
        return;}
    /*if incorrect command*/
    else {    
        cout << "command: " << input << " not found" << endl;}
    
}

void Load() 
{
    H.FileRead();
}

void Display() 
{
    string input;
    
    while(input != "quit") 
    {
        if(input != "quit") {
        
            cout << "cmd /> "; cin >> input;
            Options(input);
        }
    }
}


int main(int argc, char** argv) {   


    Load();
    Display();
    H.FileSave();

    return 0;
}