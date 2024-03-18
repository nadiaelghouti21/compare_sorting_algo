#pragma once
#ifndef SORTING_H
#define SORTING_H

#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <stack>
#include <algorithm>
using namespace std;

struct DocumentItem {
    string documentName;
    int count;
};

struct WordItem {
    string word;
    vector<DocumentItem> documents;
    WordItem() : word(""), documents() {}
    WordItem(const string& w, const DocumentItem& doc) : word(w) {
        documents.push_back(doc);
    };
};

template <class Key, class Value>
class sorting_Algo {
public:


    /**
  * Quicksort algorithm (driver).
 */

    vector<Value> m_quicksort(vector<Value>& input, bool r, bool m)
    {
        vector <Value> a = input;
        median_quicksort(a, 0, a.size() - 1, r, m);
        return a;
    }




    vector<Value> insertionSort(const vector<Value>& input) {
        vector<Value> a = input;
        for (int i = 1; i < a.size(); ++i) {
            Value key = a[i];
            int j = i - 1;

            while (j >= 0 && key->word < a[j]->word) {
                a[j + 1] = a[j];
                j = j - 1;
            }
            a[j + 1] = key;
        }
        return a;
    }

    vector<Value> heapsort(const vector<Value>& input) {
        vector<Value> a = input;
        for (int i = a.size() / 2 - 1; i >= 0; i--) {
            percDown(a, i, a.size());
        }
        for (int i = a.size() - 1; i > 0; i--) {
            swap(a[0], a[i]);
            percDown(a, 0, i);
        }
        return a;
    }

    const Value& median3(vector<Value>& a, int left, int right)
    {
        int center = (left + right) / 2;
        if (a[center] < a[left])
            swap(a[left], a[center]);
        if (a[right] < a[left])
            swap(a[left], a[right]);
        if (a[right] < a[center])
            swap(a[center], a[right]);

        // Place pivot at position right - 1
        swap(a[center], a[right - 1]);
        return a[right - 1];
    }



    vector< Value> mergeSort(vector<Value>& a)
    {
        vector<Value> tmpArray(a.size());

        mergeSort(a, tmpArray, 0, a.size() - 1);
        return a;
    }



private:
    int generateRandomInteger(int start, int end) {
        // Seed the random number generator with the current time
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // Generate a random number in the specified range
        return std::rand() % (end - start + 1) + start;
    }


    /**
    * Internal insertion sort routine for subarrays
    * that is used by quicksort.
    * a is an array of Comparable items.
    * left is the left-most index of the subarray.
    * right is the right-most index of the subarray.
    */

    void insertionSort(vector<Value>& a, int left, int right)
    {
        for (int p = left + 1; p <= right; p++)
        {
            Value tmp = a[p];
            int j;

            for (j = p; j > left && tmp < a[j - 1]; j--)
                a[j] = a[j - 1];
            a[j] = tmp;
        }
    }




    /**
        * Internal quicksort method that makes recursive calls.
        * Uses median-of-three partitioning and a cutoff of 10.
        * a is an array of Comparable items.
        * left is the left-most index of the subarray.
        * right is the right-most index of the subarray.
        */



    bool isSorted(const vector<Value>& vec) {
        for (size_t i = 1; i < vec.size(); ++i) {
            if (vec[i - 1] > vec[i]) {
                return false;  // If any element is greater than its next element, the vector is not sorted.
            }
        }
        return true;
    }
    void median_quicksort(vector<Value>& a, int left, int right, bool r, bool m) {
        if (left + 10 <= right)
        {
            Value pivot;
            if (r) {
                int idx = generateRandomInteger(0, a.size() - 1);
                pivot = a[idx];
            }
            else if (m) {
                pivot = median3(a, left, right);
            }
            else {
                pivot = a[0];
            }
            // Begin partitioning
            int i = left, j = right - 1;
            for (; ; )
            {
                while (a[++i] < pivot) {}

                while (pivot < a[--j]) {}

                if (i < j)
                    swap(a[i], a[j]);
                else
                    break;
            }
            swap(a[i], a[right - 1]);   // Restore pivot

            median_quicksort(a, left, i - 1, r, m);       // Sort small elements
            median_quicksort(a, i + 1, right, r, m);    // Sort large elements
        }
        else  // Do an insertion sort on the subarray
            insertionSort(a, left, right);
    }








    void mergeSort(vector<Value>& a, vector<Value>& tmpArray, int left, int right)
    {
        if (left < right)
        {
            int center = (left + right) / 2;
            mergeSort(a, tmpArray, left, center);
            mergeSort(a, tmpArray, center + 1, right);
            merge(a, tmpArray, left, center + 1, right);
        }
    }
    /**
         * Internal method that merges two sorted halves of a subarray.
         * a is an array of Comparable items.
         * tmpArray is an array to place the merged result.
         * leftPos is the left-most index of the subarray.
         * rightPos is the index of the start of the second half.
         * rightEnd is the right-most index of the subarray.
    */

    void merge(vector<Value>& a, vector<Value>& tmpArray, int leftPos, int rightPos, int rightEnd)
    {
        int leftEnd = rightPos - 1;
        int tmpPos = leftPos;
        int numElements = rightEnd - leftPos + 1;
        // Main loop
        while (leftPos <= leftEnd && rightPos <= rightEnd)
            if (a[leftPos] <= a[rightPos])
                tmpArray[tmpPos++] = a[leftPos++];
            else
                tmpArray[tmpPos++] = a[rightPos++];

        while (leftPos <= leftEnd)    // Copy rest of first half
            tmpArray[tmpPos++] = a[leftPos++];

        while (rightPos <= rightEnd)  // Copy rest of right half
            tmpArray[tmpPos++] = a[rightPos++];

        // Copy tmpArray back
        for (int i = 0; i < numElements; i++, rightEnd--)
            a[rightEnd] = tmpArray[rightEnd];
    }



    void percDown(vector<Value>& a, int i, int n) {
        int child;
        Value tmp = a[i];

        for (; leftChild(i) < n; i = child) {
            child = leftChild(i);
            if (child != n - 1 && a[child]->word < a[child + 1]->word) {
                child++;
            }
            if (a[child]->word > tmp->word) {
                a[i] = a[child];
            }
            else {
                break;
            }
        }
        a[i] = tmp;
    }

    int leftChild(int i) {
        return 2 * i + 1;
    }

    void swap(Value& obj1, Value& obj2) {
        Value tmp = obj1;
        obj1 = obj2;
        obj2 = tmp;
    }
};

#endif  // SORTING_H
