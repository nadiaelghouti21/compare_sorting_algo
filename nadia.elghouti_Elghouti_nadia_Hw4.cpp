//nadia elghouti
//30466
//HW 4
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cctype>
#include "BST.h"
#include "Hash.h"
#include "strutils.h"
#include <time.h>
#include <chrono>
#include "sorting.h"


using namespace std;


struct file { //STRUCT USED TO PRINT THE FILES
    string filename;
    vector<WordItem*> wrds;
};
int found_in_vector(vector<DocumentItem> x, string name) { // the functtion checks if the document is found in the vector of documentitems
    for (int i = 0; i < x.size(); i++) {
        if (x[i].documentName == name) {
            return i;
        }
    }
    return -1;
}


/* the function will look for  a word in the vector and return the worditem pointer of it*/
WordItem* return_v(vector<WordItem*> a, string& name) {
    for (int i = 0; i < a.size(); i++) {
        if (a[i]->word == name) {
            return a[i];
        }
    }

    throw std::runtime_error("Word not found");
}
/*a function to check if a word is found in the vector or not*/
bool find_w(vector<WordItem*> a, string& name) {
    for (int i = 0; i < a.size(); i++) {
        if (a[i]->word == name) {
            return true;
        }
    }
    return false;
}


vector<string> allwords(string w, vector<string> all_w) {// the function checks the word and removes all speacial characetrs in the middle of the word
    string word = "";

    for (int i = 0; i < w.length(); i++) {
        if (w[i] >= 'a' && w[i] <= 'z') {
            word += w[i];
        }
        else {
            all_w.push_back(word);
            word = "";

        }
    }
    if (word != "") {
        all_w.push_back(word);
    }//return a vector of words 
    return all_w;
}
//a function to find the quried word in a hash table.
void find_hash(HashTable<string, WordItem*>& table, vector<string> w, vector<string> chosenFiles, bool p) {
    bool words_found = true;
    vector <file>found;
    vector<string> query_words_b;

    for (int i = 0; i < w.size(); i++) {
        if (table.find(w[i])) {
            query_words_b.push_back(w[i]); // preserve the words in a vector

        }
        else {
            words_found = false; //no such word in the table.

            break;
        }
    }


    if (words_found) {

        for (int i = 0; i < chosenFiles.size(); i++) {
            bool documentHasWords = false;
            vector <WordItem*>wrds;
            file newfile;
            for (int j = 0; j < query_words_b.size(); j++) {
                WordItem* search_word = table.return_v(query_words_b[j]);

                for (int k = 0; k < search_word->documents.size(); k++) {
                    if (chosenFiles[i] == search_word->documents[k].documentName) {

                        newfile.wrds.push_back(search_word);
                        newfile.filename = chosenFiles[i];



                    }
                }
            }
            if (newfile.filename != "") {
                found.push_back(newfile);
            }
        }
        //printing all the words found.
        if (p) {
            for (int o = 0; o < found.size(); o++) {
                vector <WordItem*> list = found[o].wrds;
                if (list.size() == query_words_b.size()) {
                    cout << "In Document " << found[o].filename << ", ";
                    for (int i = 0; i < list.size(); i++) {

                        for (int j = 0; j < query_words_b.size(); j++) {
                            if (query_words_b[j] == list[i]->word) {
                                cout << list[i]->word << " found ";
                            }
                        }
                        for (int k = 0; k < list[i]->documents.size(); k++) {
                            if (found[o].filename == list[i]->documents[k].documentName) {
                                cout << list[i]->documents[k].count << " times";
                            }

                        }
                        if (i != list.size() - 1) {
                            cout << " ,";

                        }


                    }
                    cout << ".";
                    cout << endl;

                }
            }

        }
    }

    if (p && !words_found) {
        //the case wrds_found is false
        cout << "No document contains the given query" << endl;


    }
}

//a function to  find the quired word in a tree
void find_binary(BSTSearchTree<string, WordItem*>& tree, vector<string> w, vector<string> chosenFiles, bool p) {
    bool words_found = true;
    vector <file> found;
    vector<string> query_words_b;

    for (int i = 0; i < w.size(); i++) {
        if (tree.find(w[i])) {
            query_words_b.push_back(w[i]); // preserve the words in a vector

        }
        else {
            words_found = false; //no such word in the tree.

            break;
        }
    }


    if (words_found) {

        for (int i = 0; i < chosenFiles.size(); i++) {  //look in al the files chosen 
            bool documentHasWords = false;
            vector <WordItem*>wrds;
            file newfile;
            for (int j = 0; j < query_words_b.size(); j++) { //for all the words quired 
                WordItem* search_word = tree.return_w(query_words_b[j]);

                for (int k = 0; k < search_word->documents.size(); k++) {
                    if (chosenFiles[i] == search_word->documents[k].documentName) {  //if filename id found in the document list of the specific word

                        newfile.wrds.push_back(search_word);
                        newfile.filename = chosenFiles[i];



                    }
                }
            }
            if (newfile.filename != "") {
                found.push_back(newfile);
            }
        }
        //printing the found words
        if (p) {
            for (int o = 0; o < found.size(); o++) {
                vector <WordItem*> list = found[o].wrds;
                if (list.size() == query_words_b.size()) {
                    cout << "In Document " << found[o].filename << ", ";
                    for (int i = 0; i < list.size(); i++) {

                        for (int j = 0; j < query_words_b.size(); j++) {
                            if (query_words_b[j] == list[i]->word) {
                                cout << list[i]->word << " found ";
                            }
                        }
                        for (int k = 0; k < list[i]->documents.size(); k++) {
                            if (found[o].filename == list[i]->documents[k].documentName) {
                                cout << list[i]->documents[k].count << " times";
                            }

                        }
                        if (i != list.size() - 1) {
                            cout << " ,";

                        }


                    }
                    cout << ".";
                    cout << endl;

                }
            }
        }

    }


    if (p && !words_found) {
        cout << "No document contains the given query" << endl;

    }

}

//a function to insert into a binary tree
BSTSearchTree<string, WordItem*>& insert_Tree(vector<string> chosenFiles, BSTSearchTree<string, WordItem*>& tree) {
    for (int i = 0; i < chosenFiles.size(); i++) {
        ifstream inputfile(chosenFiles[i].c_str());
        if (!inputfile.is_open()) {
            cerr << "Error opening file: " << chosenFiles[i] << endl;
            continue;  // Move to the next file if opening fails
        }

        string words;
        DocumentItem details;
        while (inputfile >> words) { // reading the words in the file
            StripPunc(words);
            ToLower(words); // for case insensitivity turn all words to lowercase
            vector<string> w = allwords(words, {});
            for (int j = 0; j < w.size(); j++) {
                details.documentName = chosenFiles[i];
                details.count = 1;
                WordItem* new_word = new WordItem(w[j], details);

                if (tree.isEmpty() || !tree.find(w[j])) {
                    //incase tree is empty or the word does not already exists in tree.
                    tree.insert(new_word, w[j]);
                }
                else {
                    //in case the word already exists in tree
                    vector<DocumentItem>& docs = tree.return_w(w[j])->documents;
                    int idx = found_in_vector(docs, chosenFiles[i]);
                    if (idx == -1) {  //check if the document already exists in vector
                        DocumentItem new_doc;
                        new_doc.documentName = chosenFiles[i];
                        new_doc.count = 1;
                        docs.push_back(new_doc);
                    }
                    else {
                        docs[idx].count++;
                    }

                    delete new_word;  //dlete the node
                }
            }
        }

        inputfile.close(); // close file
    }
    return tree;
}


HashTable<string, WordItem*>& insert_Table(vector<string> chosenFiles, HashTable<string, WordItem*>& table) {
    int word_count = 0;
    for (int i = 0; i < chosenFiles.size(); i++) {
        ifstream inputfile(chosenFiles[i].c_str());
        if (!inputfile.is_open()) {
            cerr << "Error opening file: " << chosenFiles[i] << endl;
            continue;  // Move to the next file if opening fails
        }

        string words;
        DocumentItem details;
        while (inputfile >> words) { // reading the words in the file
            StripPunc(words);
            ToLower(words); // for case insensitivity turn all words to lowercase
            vector<string> w = allwords(words, {});
            for (int j = 0; j < w.size(); j++) {
                details.documentName = chosenFiles[i];
                details.count = 1;
                WordItem* new_word = new WordItem(w[j], details);

                if (table.isEmpty() || !table.find(w[j])) {
                    word_count++;
                    table.insert(w[j], new_word, word_count);
                }
                else {
                    vector<DocumentItem>& docs = table.return_v(w[j])->documents;
                    int idx = found_in_vector(docs, chosenFiles[i]);
                    if (idx == -1) {
                        DocumentItem new_doc;
                        new_doc.documentName = chosenFiles[i];
                        new_doc.count = 1;
                        docs.push_back(new_doc);
                    }
                    else {
                        docs[idx].count++;
                    }

                    delete new_word;  // delete node
                }
            }
        }

        inputfile.close(); // close file
    }

    int size = table.getsize();
    double l = static_cast<double>(word_count) / size;
    cout << endl;
    cout << "After preprocessing, the unique word count is " << word_count - 1 << ". Current load ratio is " << l << endl;
    return table;


}


vector <WordItem*> push_in(vector<string> chosenfiles, vector< WordItem*> final_vector) {

    for (int i = 0; i < chosenfiles.size(); i++) {
        ifstream inputfile(chosenfiles[i].c_str());
        if (!inputfile.is_open()) {
            cerr << "Error opening file: " << chosenfiles[i] << endl;
            continue;  // Move to the next file if opening fails
        }

        string words;
        DocumentItem details;
        while (inputfile >> words) { // reading the words in the file
            StripPunc(words);
            ToLower(words); // for case insensitivity turn all words to lowercase
            vector<string> w = allwords(words, {});
            for (int j = 0; j < w.size(); j++) {
                details.documentName = chosenfiles[i];
                details.count = 1;
                WordItem* new_word = new WordItem(w[j], details);

                if (final_vector.empty() || !find_w(final_vector, w[j])) {
                    //incase vector is empty or the word does not already exists in vector .
                    final_vector.push_back(new_word);
                }
                else {
                    //in case the word already exists in vector
                    vector<DocumentItem>& docs = return_v(final_vector, w[j])->documents;
                    int idx = found_in_vector(docs, chosenfiles[i]);
                    if (idx == -1) {  //check if the document already exists in vector
                        DocumentItem new_doc;
                        new_doc.documentName = chosenfiles[i];
                        new_doc.count = 1;
                        docs.push_back(new_doc);
                    }
                    else {
                        docs[idx].count++;
                    }

                    delete new_word;  //dlete the node
                }
            }
        }

        inputfile.close(); // close file
    }
    return final_vector;

}


void binarySearch(const vector<WordItem*>& sortedArray, const vector<string>& chosenFiles, const vector<string>& w, bool print) {
    vector<string> query_words_b;
    vector<file> found;

    for (const string& query : w) {
        int low = 0;
        int high = sortedArray.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (sortedArray[mid]->word == query) {
                query_words_b.push_back(query);
                break;  // Word found, exit the loop
            }
            else if (sortedArray[mid]->word < query) {
                low = mid + 1;  // Search in the right half
            }
            else {
                high = mid - 1;  // Search in the left half
            }
        }
    }

    if (query_words_b.size() == w.size()) {
        for (int i = 0; i < chosenFiles.size(); i++) {
            vector<WordItem*> wrds;
            file newfile;

            for (int j = 0; j < query_words_b.size(); j++) {
                WordItem* search_word = return_v(sortedArray, query_words_b[j]);

                for (int k = 0; k < search_word->documents.size(); k++) {
                    if (chosenFiles[i] == search_word->documents[k].documentName) {

                        newfile.wrds.push_back(search_word);
                        newfile.filename = chosenFiles[i];

                    }
                }
            }

            if (!newfile.filename.empty()) {
                found.push_back(newfile);
            }
        }

        if (print) {
            for (const file& f : found) {
                vector<WordItem*> list = f.wrds;

                if (list.size() == query_words_b.size()) {
                    cout << "In Document " << f.filename << ", ";
                    for (size_t i = 0; i < list.size(); i++) {
                        for (size_t j = 0; j < query_words_b.size(); j++) {
                            if (query_words_b[j] == list[i]->word) {
                                cout << list[i]->word << " found ";
                            }
                        }
                        for (const DocumentItem& doc : list[i]->documents) {
                            if (f.filename == doc.documentName) {
                                cout << doc.count << " times";
                            }
                        }
                        if (i != list.size() - 1) {
                            cout << " ,";
                        }
                    }
                    cout << "." << endl;
                }
            }
        }
    }

    if (print && query_words_b.size() != w.size()) {
        cout << "No document contains the given query" << endl;
    }
}

int main() {
    List<string, WordItem*> x;
    int num_files;
    cout << "Enter number of input files: ";
    cin >> num_files;
    vector<string> chosenFiles; // to store the filenames
    vector <DocumentItem> docs;
    BSTSearchTree<string, WordItem*> tree;  // the main tree
    HashTable<string, WordItem*> table(x, 53); //main hash tbale 
    vector<WordItem*> arrayw;
    sorting_Algo<string, WordItem*> vector_w;
    string filename;
    int word_count = 0;

    for (int i = 0; i < num_files; i++) {  //for the chosen number of files


        cout << "Enter " << i + 1 << ". file name : ";
        cin >> filename;
        chosenFiles.push_back(filename);
    }
    tree = insert_Tree(chosenFiles, tree);
    table = insert_Table(chosenFiles, table);
    arrayw = push_in(chosenFiles, arrayw);

    bool words_found = true;
    vector<string> query_words_h;
    vector<string> query_words_b;
    string input_line, queried_word;


    cout << "Enter queried words in one line: ";
    cin.ignore();
    getline(cin, input_line); //take all the line inputed
    istringstream iss(input_line);// cut the line into words.
    vector<string> w;
    while (iss >> queried_word) {  // while reading each word in the line.
        ToLower(queried_word); // for case insensitivity turn all words to lowercase

        w = allwords(queried_word, w);
        // make sure all characters are alphabetical

    }
    vector<WordItem*> insertionSorted = vector_w.insertionSort(arrayw);
    bool print = true;

    find_binary(tree, w, chosenFiles, print);
    find_hash(table, w, chosenFiles, print);
    binarySearch(insertionSorted, chosenFiles, w, print);











    int k = 100;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        // QueryDocuments(with BST);
        print = false;
        find_binary(tree, w, chosenFiles, print);
    }
    auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
        (std::chrono::high_resolution_clock::now() - start);
    cout << "\nBinary Search Tree Time: " << BSTTime.count() / k << "\n";
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        // QueryDocuments (with hashtable);
        print = false;
        find_hash(table, w, chosenFiles, print);
    }
    auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
        (std::chrono::high_resolution_clock::now() - start);
    cout << "Hash Table Time: " << HTTime.count() / k << "\n";
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        // QueryDocuments (with hashtable);
        print = false;
        binarySearch(insertionSorted, chosenFiles, w, print);
    }
    auto BTime = std::chrono::duration_cast<std::chrono::nanoseconds>
        (std::chrono::high_resolution_clock::now() - start);
    cout << "Binary Search Time: " << BTime.count() / k << "\n";
    bool random = true;
    bool middle = false;
    start = std::chrono::high_resolution_clock::now();
    vector<WordItem*> random_sort = vector_w.m_quicksort(arrayw, random, middle);
    auto randomTime = std::chrono::duration_cast<std::chrono::nanoseconds>
        (std::chrono::high_resolution_clock::now() - start);
    cout << "\nQuick Sort(random) Time: " << randomTime.count() << "\n";

    random = false;
    middle = true;
    start = std::chrono::high_resolution_clock::now();
    vector<WordItem*> median_sort = vector_w.m_quicksort(arrayw, random, middle);
    auto medianTime = std::chrono::duration_cast<std::chrono::nanoseconds>
        (std::chrono::high_resolution_clock::now() - start);
    cout << "Quick Sort(median) Time: " << medianTime.count() << "\n";
    random = false;
    middle = false;
    start = std::chrono::high_resolution_clock::now();
    vector<WordItem*> first_sort = vector_w.m_quicksort(arrayw, random, middle);
    auto firstTime = std::chrono::duration_cast<std::chrono::nanoseconds>
        (std::chrono::high_resolution_clock::now() - start);
    cout << "Quick Sort(first) Time: " << firstTime.count() << "\n";

    start = std::chrono::high_resolution_clock::now();
    vector<WordItem*> mergesort = vector_w.mergeSort(arrayw);
    auto mergeTime = std::chrono::duration_cast<std::chrono::nanoseconds>
        (std::chrono::high_resolution_clock::now() - start);
    cout << "Merge Sort Time: " << mergeTime.count() << "\n";



    start = std::chrono::high_resolution_clock::now();
    vector<WordItem*> HeapSorted = vector_w.heapsort(arrayw);
    auto HTime = std::chrono::duration_cast<std::chrono::nanoseconds>
        (std::chrono::high_resolution_clock::now() - start);
    cout << "Heap Sort Time: " << HTime.count() << "\n";


    start = std::chrono::high_resolution_clock::now();
    vector<WordItem*> new_insertionSorted = vector_w.insertionSort(arrayw);
    auto ITime = std::chrono::duration_cast<std::chrono::nanoseconds>
        (std::chrono::high_resolution_clock::now() - start);
    cout << "Insertion Sort Time: " << ITime.count() << "\n";
    cout << "\nSpeed Up BST/HST:" << double((BSTTime.count() / k)) / (HTTime.count() / k) << "\n";
    cout << "Speed Up Merge Sort/Quick Sort(Median):" << double((mergeTime.count() / k)) / (medianTime.count() / k) << "\n";
    cout << "Speed Up Heap Sort/Quick Sort(Median):" << double((HTime.count() / k)) / (medianTime.count() / k) << "\n";
    cout << "Speed Up Insertion Sort/Quick Sort(Median):" << double((ITime.count() / k)) / (medianTime.count() / k) << "\n";
    cout << "\nSpeed Up Binary Search / Binary Search Tree Time: " << double((BTime.count() / k)) / (BSTTime.count() / k) << "\n";
    cout << "Speed Up Binary Search / Hash Table Time: " << double((BTime.count() / k)) / (HTTime.count() / k) << "\n";
    return 0;
}

