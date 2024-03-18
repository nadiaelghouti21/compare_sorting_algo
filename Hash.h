#pragma once
#ifndef HASH_H_
#define HASH_H_
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <functional>
#include "List.h"

using namespace std;
















template <class Key, class Value>
class HashTable
{

    int hash(string word, int tableSize) const {

        int sum = 0;
        for (int i = 0; i < word.length(); i++) {
            char w = word[i];
            int aski = w;
            sum = w + sum;

        }
        return sum % tableSize;



    }


public:
    HashTable(const List <Key, Value>& notFound,
        int size) : ITEM_NOT_FOUND(notFound), theLists(size) {}

    HashTable(const HashTable& rhs)
        : ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND),
        theLists(rhs.theLists) { }

    bool find(const Key& x) const {
        ListItr<Key, Value> itr;
        // locate the approriate list and search there
        itr = theLists[hash(x, theLists.size())].find(x);
        // retrieve from the located position
        if (itr.isPastEnd())
            return false;

        return true;
    }
    Value return_v(Key& x) {
        ListItr<Key, Value> itr;
        // locate the approriate list and search there
        itr = theLists[hash(x, theLists.size())].find(x);
        return itr.retrieve_v();

    }
    const HashTable& operator=(const HashTable& rhs) {
        if (this != &rhs) {  // Check for self-assignment
            // Clear the current contents of the hash table
            //makeEmpty();
            int w = 0;
            // Copy the ITEM_NOT_FOUND value
            ITEM_NOT_FOUND = rhs.ITEM_NOT_FOUND;

            // Resize theLists to match the size of rhs.theLists
            theLists.resize(rhs.theLists.size());

            // Iterate over the old vector
            for (int i = 0; i < rhs.theLists.size(); i++) {
                // Create a new list for each element in the rhs
                ListItr<Key, Value> itr = rhs.theLists[i].first();
                while (!itr.isPastEnd()) {
                    w++;
                    insert(itr.retrieve_k(), itr.retrieve_v(), w);
                    itr.advance();
                }
            }
        }
        return *this;
    }


    void makeEmpty() {
        for (int i = 0; i < theLists.size(); i++)
            theLists[i].makeEmpty();
        // destroy the lists but not the vector!
    }
    void insert(const Key& x, const Value& w, int word_count) {
        double load = static_cast<double>(word_count) / theLists.size();
        if (load > 0.7) {
            rehash(word_count);
        }

        // hash the given object and locate the list it should be on 
        List<Key, Value>& whichList = theLists[hash(x, theLists.size())];
        // locate the object in the list (using List’s find)
        ListItr<Key, Value> itr = whichList.find(x);
        // insert the new item at the head of the list if not found!
        if (itr.isPastEnd()) {
            whichList.insert(x, w, whichList.zeroth());
        }
    }
    bool isEmpty() const {
        for (int i = 0; i < theLists.size(); ++i) {
            if (!theLists[i].isEmpty()) {
                return false;  // At least one non-empty list found
            }
        }
        return true;  // All lists are empty
    }
    void remove(const Key& x) {
        // remove from the appropriate list
        theLists[hash(x, theLists.size())].remove(x);
    }





    int getsize() {
        return theLists.size();
    }

    ~HashTable() {
        // Make sure to clean up the memory used by each list in theLists
        /*for (int i = 0; i < theLists.size(); ++i) {
            theLists[i].makeEmpty(); // Assuming you have a makeEmpty function in List class
        }

        // Clear theLists vector
        theLists.clear();*/
    }


private:
    vector<List<Key, Value> > theLists;
    // The array of Lists
    mutable List<Key, Value> ITEM_NOT_FOUND;
    /**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
    bool isPrime(int n)
    {
        if (n == 2 || n == 3)
            return true;

        if (n == 1 || n % 2 == 0)
            return false;

        for (int i = 3; i * i <= n; i += 2)
            if (n % i == 0)
                return false;

        return true;

    }



    void rehash(int w) {
        int oldsize = theLists.size();
        int newsize = nextPrime(2 * theLists.size());

        // Create a new double-sized, empty table
        vector<List<Key, Value>> newTable(newsize);

        // Iterate over the old vector
        for (int i = 0; i < oldsize; i++) {
            ListItr<Key, Value> itr = theLists[i].first();

            // Check if the current list is not empty
            while (!itr.isPastEnd()) {
                Key key = itr.retrieve_k();
                Value val = itr.retrieve_v();
                List<Key, Value>& whichList = newTable[hash(key, newTable.size())];
                whichList.insert(key, val, whichList.zeroth());
                itr.advance();
            }
        }

        // theLists is a vector, so its destructor will be automatically called when it goes out of scope
        // Assign the newTable to theLists
        theLists = std::move(newTable);

    }





    int nextPrime(int n)
    {
        if (n % 2 == 0)
            n++;

        for (; !isPrime(n); n += 2)
            ;

        return n;
    }
};























#endif
