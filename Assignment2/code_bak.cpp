/* Alexey Yermakov
 * CSCI 2275
 * September 20, 2019
 * Assignment 2
 */

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

bool DEBUG = false;
int SIZE = 50;

class Book{
	protected:
	int rating;
	string title;
	string genre;
	//ID is implemented in each genre
	public:
	Book(){
		this->title = "";
		this->genre = "";
		this->rating = 0;
	}
	Book(string title, string genre, int rating){
		this->title = title;
		this->genre = genre;
		this->rating = rating;
	}
	int getRating(){
		return rating;
	}
	string toString(){
		stringstream ss;
		ss<<title<<","<<genre<<","<<rating;
		return ss.str();
	}
};

class Fiction : public Book{
	string ID;
	public:
	Fiction() : Book(){
		this->ID = "";
	}
	Fiction(string title, string ID, string genre, int rating)
		: Book(title, genre, rating){
		this->ID = ID;
	}
	string toString(){
		stringstream ss;
		ss<<title<<","<<ID<<","<<genre<<","<<rating;
		return ss.str();
	}
};

void printFicArr(Fiction *arr[], int n){
	cout<<"Fiction:"<<endl;
	for(int i = 0; i < n; i++){
		cout<<arr[i]->toString()<<endl;
	}
	cout<<endl;
}

void printBookArr(Book *arr[], int n){
	cout<<"Book:"<<endl;
	for(int i = 0; i < n; i++){
		cout<<arr[i]->toString()<<endl;
	}
	cout<<endl;
}


//Function to make all arrays
void mkArr(Book *ficArr[], ifstream &ifs){
	if(DEBUG) cout<<"Making arrays:"<<endl;
	//Open the book file
	ifs.open("book.txt");
	//Index counters for filling the arrays
	int ficIndex = 0;
	while(ifs.good()){
		//Get all parts of a book in terms of string
		string title;
		getline(ifs, title, ',');
		string ID;
		getline(ifs, ID, ',');
		string genre;
		getline(ifs, genre, ',');
		string rating;
		getline(ifs, rating);
		
		//Differentiate into book types
		if(genre == "fiction"){
			//Create the Fiction book
			Fiction *book = new Fiction(title, ID, genre, stoi(rating));
			if(DEBUG) cout<<"Making Fiction: "<<book->toString()<<" | Index: "<<ficIndex<<endl;
			//Fill the array with the book in the next open slot
			ficArr[ficIndex] = book;
			//Shift index by one for the next book
			ficIndex++;
		}
	}
	if(DEBUG) cout<<endl;
}

main(){
	//Make file stream
	ifstream ifs;
	//Make arrays for genres
	Book** ficArr = new Book*[SIZE];
	//Fill the arrays with the books from the file
	mkArr(ficArr, ifs);
	cout<<"Test:"<<ficArr[0]->toString()<<endl<<endl;
	//Print the first 10 of each array
	//printFicArr(ficArr, 10);
	printBookArr(ficArr, 10);
}
//To print the ID make an abstract fuction called getString() in book and speccify it for each subclass
