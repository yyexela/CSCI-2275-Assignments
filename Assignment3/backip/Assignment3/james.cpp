

// Assignment3.cpp : This file contains the 'main' function. Program execution begins and ends there.

//

 

#include <iostream>

#include <string>

#include <algorithm>

#include <fstream>

#include <sstream>

using namespace std;

const int COMMON_WORD_LIST_SIZE = 50;

const int STARTING_UNIQUE_WORD_LIST_SIZE = 100;

 

struct wordItem {

        string word;

        int count = 0;

};

 

wordItem newWordItem(string word, int count) {

        wordItem i;

        i.word = word;

        i.count = count;

        return i;

}

 

void printWordItem(wordItem item) {

        cout << item.word << ", " << item.count << endl;

}

 

class WordAnalysis {

public:

 

        wordItem* wordItems = new wordItem[STARTING_UNIQUE_WORD_LIST_SIZE];

        wordItem* topWords;

        wordItem* bottomWords;

        string ignoredWords[COMMON_WORD_LIST_SIZE];

        string* choiceWords;

        int doublingCount = 0, totalWordCount = 0, uniqueWordCount = 0, endWordCount = 0;

public:

        WordAnalysis(int n, string words) {

               endWordCount = n;

               topWords = new wordItem[n];

               bottomWords = new wordItem[n];

                stringstream ss(words);

               int commas = 0, index = 0;

               for (char c : words) {

                       if (c == ',') ++commas;

               }

               choiceWords = new string[commas + 1];

               for (int i = 0; i < commas; ++i) {

                       getline(ss, choiceWords[i], ',');

               } getline(ss, choiceWords[commas]);

        }

 

        void printWordItems(wordItem* items, int startIndex, int endIndex) {

               for (int i = startIndex; i < endIndex; ++i) {

                       printWordItem(items[i]);

               } cout << endl;

        }

 

        void doubleArray() {

               int newSize = STARTING_UNIQUE_WORD_LIST_SIZE * pow(2, ++doublingCount);

               wordItem* temp = new wordItem[newSize];

               for (int i = 0; i < newSize / 2; ++i) {

                       temp[i] = wordItems[i];

               }

               delete[] wordItems;

               wordItems = temp;

        }

 

        void parseIgnoredWords(string fileName) {

               ifstream in;

               in.open(fileName);

               if (!in.is_open()) { cout << "File Failed to Open" << endl; return; }

               int inputIndex = 0;

               while (in.good()) {

                       getline(in, ignoredWords[inputIndex++]);

                       //cout << ignoredWords[inputIndex - 1] << endl;

               }

               in.close();

        }

 

        bool isIgnored(string word) {

               for (string w : ignoredWords) {

                       if (w == word) return true;

               } return false;

        }

 

        void addWord(string word) {

               for (int i = 0; i < uniqueWordCount; ++i) {

                       if (word == wordItems[i].word) {

                               ++wordItems[i].count;

                               for (int j = i - 1; wordItems[j].count < wordItems[j+1].count; --j) {

                                       wordItem temp = wordItems[j];

                                       wordItems[j] = wordItems[j + 1];

                                       wordItems[j + 1] = temp;

                               }

                               return;

                       }

               }

               if (uniqueWordCount == STARTING_UNIQUE_WORD_LIST_SIZE * pow(2, doublingCount)) doubleArray();

               wordItems[uniqueWordCount++] = newWordItem(word, 1);

        }

 

        int findCount(string word) {

               for (int i = 0; i < uniqueWordCount; ++i) {

                       if (word == wordItems[i].word) return wordItems[i].count;

               } return -1;

        }

 

        void build(string bookFileName, string ignoredFileName) {

               parseIgnoredWords(ignoredFileName);

               ifstream in;

               in.open(bookFileName);

               if (!in.is_open()) { cout << "File Failed to Open" << endl; return; }

               string temp;

               int count = 0;

               while (in >> temp) {

                       //cout << "Word Number " << ++count << ": " << temp << endl;

                       if (!isIgnored(temp)) addWord(temp);

               }

               //printWordItems();

        }

};

 

int main(int argc, char* argv[])

{

        /*WordAnalysis book;

        for (int i = 0; i < 10; ++i) {

               book.wordItems[i] = newWordItem(to_string(i));

        }

        cout << book.binarySearch(0, 9, "9.5",false);*/

 

        /*WordAnalysis book(stoi(argv[1]), argv[4]);

        book.addWord("d");

        book.printWordItems(book.wordItems, 0 ,book.uniqueWordCount);

        book.addWord("a");

        book.printWordItems(book.wordItems, 0, book.uniqueWordCount);

        book.addWord("d");

        book.printWordItems(book.wordItems, 0, book.uniqueWordCount);

        book.addWord("g");

        book.printWordItems(book.wordItems, 0, book.uniqueWordCount);

        book.addWord("b");

        book.printWordItems(book.wordItems, 0, book.uniqueWordCount);

        book.addWord("f");

        book.printWordItems(book.wordItems, 0, book.uniqueWordCount);

        book.addWord("c");

        book.printWordItems(book.wordItems, 0, book.uniqueWordCount);

        book.addWord("e");

        book.printWordItems(book.wordItems, 0, book.uniqueWordCount);

        book.addWord("g");

        book.printWordItems(book.wordItems, 0, book.uniqueWordCount);

        book.addWord("g");

        book.printWordItems(book.wordItems, 0, book.uniqueWordCount);

 

        cout << book.findCount("d") << endl;

        cout << book.findCount("a") << endl;*/

 

        /*WordAnalysis book;

        book.parseIgnoredWords(argv[1]);

        cout << book.isIgnored("the") << endl;

        cout << book.isIgnored("you") << endl;

        cout << book.isIgnored("me") << endl;

        cout << book.isIgnored("abc") << endl;*/

 

        WordAnalysis book(stoi(argv[1]), argv[4]);

        book.build(argv[2], argv[3]);

        printWordItem(book.wordItems[0]);

        ///*book.findTopWords();

        //book.printWordItems(book.topWords, book.endWordCount);

        //book.findBottomWords();

        //book.printWordItems(book.bottomWords, book.endWordCount);*/

        //for (int i = 0; i < 2; i++) {

        //    cout << book.findCount(book.choiceWords[i]) << endl;

        //}

}

