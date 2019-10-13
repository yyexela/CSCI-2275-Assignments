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

//Book class, base abstract class that all genre's will use
class Book{
	protected:
	//These members are used in all of the sub classes
	int rating;
	string title;
	string genre;
	//ID is implemented in each genre
	//Base constructor
	public:
	Book(){
		this->title = "";
		this->genre = "";
		this->rating = 0;
	}
	//Parameter constructor
	Book(string title, string genre, int rating){
		this->title = title;
		this->genre = genre;
		this->rating = rating;
	}
	//Rating getter
	int getRating(){
		return rating;
	}
	//toString method returns string form of the object
	string toString(){
		stringstream ss;
		ss<<title<<","<<genre<<","<<rating;
		return ss.str();
	}
};

class Fiction : public Book{
	//ID members unique to Fiction
	string ID;
	public:
	//Base constructor with initializer list of Book
	Fiction() : Book(){
		this->ID = "";
	}
	//Parameter constructor with initializer list of Book
	Fiction(string title, string ID, string genre, int rating)
		: Book(title, genre, rating){
		this->ID = ID;
	}
	//toString method returns string form of the object
	string toString(){
		stringstream ss;
		ss<<title<<","<<ID<<","<<genre<<","<<rating;
		return ss.str();
	}
};

class Poetry : public Book{
	//ID members unique to Poetry
	int ID;
	public:
	//Base constructor with initializer list of Book
	Poetry() : Book(){
		this->ID = 0;
	}
	//Parameter constructor with initializer list of Book
	Poetry(string title, int ID, string genre, int rating)
		: Book(title, genre, rating){
		this->ID = ID;
	}
	//toString method returns string form of the object
	string toString(){
		stringstream ss;
		ss<<title<<","<<ID<<","<<genre<<","<<rating;
		return ss.str();
	}
};

class Horror : public Book{
	//ID members unique to Horror
	float ID;
	public:
	//Base constructor with initializer list of Book
	Horror() : Book(){
		this->ID = 0;
	}
	//Parameter constructor with initializer list of Book
	Horror(string title, float ID, string genre, int rating)
		: Book(title, genre, rating){
		this->ID = ID;
	}
	//toString method returns string form of the object
	string toString(){
		stringstream ss;
		ss<<title<<","<<ID<<","<<genre<<","<<rating;
		return ss.str();
	}
};

//Print top books according to rating
void sortFicArr(Fiction arr[]){
	if(DEBUG) cout<<"Sorting Fiction: "<<endl;
	Fiction sorted[SIZE];
	//Sorting algorithm, sort from highest rating to lowest rating
	//Selection sort
	for(int i = 0; i < SIZE; i++){
		int maxRating = arr[i].getRating();//Set max rating to the first book
		int maxIndex = i;//Set the max index to i
		for(int j = i; j < SIZE; j++){ //Find max rating in the remaining array
			//Update index and max rating
			if(arr[j].getRating() > maxRating){
				maxIndex = j;
				maxRating = arr[j].getRating();
			}
		}
		//Swap the pointer index with the max index
		Fiction temp = arr[i];
		arr[i] = arr[maxIndex];
		arr[maxIndex] = temp;
	}
	//Print sorted array
	if(DEBUG){
		for(int i = 0; i < SIZE; i++){
			cout<<arr[i].toString()<<endl;
		}
		cout<<endl;
	}	
}

void sortPoeArr(Poetry arr[]){
	if(DEBUG) cout<<"Sorting Poetry: "<<endl;
	Poetry sorted[SIZE];
	//Sorting algorithm, sort from highest rating to lowest rating
	//Selection sort
	for(int i = 0; i < SIZE; i++){
		int maxRating = arr[i].getRating();//Set max rating to the first book
		int maxIndex = i;//Set the max index to i
		for(int j = i; j < SIZE; j++){ //Find max rating in the remaining array
			//Update index and max rating
			if(arr[j].getRating() > maxRating){
				maxIndex = j;
				maxRating = arr[j].getRating();
			}
		}
		//Swap the pointer index with the max index
		Poetry temp = arr[i];
		arr[i] = arr[maxIndex];
		arr[maxIndex] = temp;
	}
	//Print sorted array
	if(DEBUG){
		for(int i = 0; i < SIZE; i++){
			cout<<arr[i].toString()<<endl;
		}
		cout<<endl;
	}
}

void sortHorArr(Horror arr[]){
	if(DEBUG) cout<<"Sorting Horror: "<<endl;
	Horror sorted[SIZE];
	//Sorting algorithm, sort from highest rating to lowest rating
	//Selection sort
	for(int i = 0; i < SIZE; i++){
		int maxRating = arr[i].getRating();//Set max rating to the first book
		int maxIndex = i;//Set the max index to i
		for(int j = i; j < SIZE; j++){ //Find max rating in the remaining array
			//Update index and max rating
			if(arr[j].getRating() > maxRating){
				maxIndex = j;
				maxRating = arr[j].getRating();
			}
		}
		//Swap the pointer index with the max index
		Horror temp = arr[i];
		arr[i] = arr[maxIndex];
		arr[maxIndex] = temp;
	}
	//Print sorted array
	if(DEBUG){
		for(int i = 0; i < SIZE; i++){
			cout<<arr[i].toString()<<endl;
		}
		cout<<endl;
	}
}

//Print the first n elements of the array
void printFicArr(Fiction arr[], int n){
	cout<<"Top 10 for Genre Fiction are:"<<endl;
	for(int i = 0; i < n; i++){
		cout<<arr[i].toString()<<endl;
	}
	cout<<endl;
}

//Print the first n elements of the array
void printPoeArr(Poetry arr[], int n){
	cout<<"Top 10 for Genre Poetry are:"<<endl;
	for(int i = 0; i < n; i++){
		cout<<arr[i].toString()<<endl;
	}
	cout<<endl;
}

//Print the first n elements of the array
void printHorArr(Horror arr[], int n){
	cout<<"Top 10 for Genre Horror are:"<<endl;
	for(int i = 0; i < n; i++){
		cout<<arr[i].toString()<<endl;
	}
	cout<<endl;
}

//Print the first n elements of all the genres
void printTop(Fiction ficArr[], Poetry poeArr[], Horror horArr[], int n){
	cout<<"Top 10 for all Genres are:"<<endl;
	//counters seeing which books were printed in each array
	int ficIndex = 0;
	int poeIndex = 0;
	int horIndex = 0;
	for(int i = 0; i < 10; i++){
		//Find largest rating out of the three
		int max = (ficArr[ficIndex].getRating() > horArr[horIndex].getRating() ) ? ficArr[ficIndex].getRating() : horArr[horIndex].getRating();
		max = (max > poeArr[poeIndex].getRating()) ? max : poeArr[poeIndex].getRating();
		//print the largest and add an index to the one printed so it does't compare it again
		if(max == ficArr[ficIndex].getRating()){
			cout<<ficArr[ficIndex].toString()<<endl;
			ficIndex++;
		} else if (max == poeArr[poeIndex].getRating()){
			cout<<poeArr[poeIndex].toString()<<endl;
			poeIndex++;
		} else {
			cout<<horArr[horIndex].toString()<<endl;
			horIndex++;
		}
	}
	cout<<endl;
}

//Function to make all arrays
void mkArr(Fiction ficArr[], Poetry poeArr[], Horror horArr[], ifstream &ifs){
	if(DEBUG) cout<<"Making arrays:"<<endl;
	//Open the book file
	ifs.open("book.txt");
	//Index counters for filling the arrays
	int ficIndex = 0;
	int poeIndex = 0;
	int horIndex = 0;
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
			Fiction book(title, ID, genre, stoi(rating));
			if(DEBUG) cout<<"Making Fiction: "<<book.toString()<<" | Index: "<<ficIndex<<endl;
			//Fill the array with the book in the next open slot
			ficArr[ficIndex] = book;
			//Shift index by one for the next book
			ficIndex++;
		} else if(genre == "poetry"){
			//Create the Poetry book
			Poetry book(title, stoi(ID), genre, stoi(rating));
			if(DEBUG) cout<<"Making Poetry: "<<book.toString()<<" | Index: "<<poeIndex<<endl;
			//Fill the array with the book in the next open slot
			poeArr[poeIndex] = book;
			//Shift index by one for the next book
			poeIndex++;
		} else if(genre == "horror"){
			//Create the Horror book
			Horror book(title, stof(ID), genre, stoi(rating));
			if(DEBUG) cout<<"Making Horror: "<<book.toString()<<" | Index: "<<horIndex<<endl;
			//Fill the array with the book in the next open slot
			horArr[horIndex] = book;
			//Shift the index by one for the next book
			horIndex++;
		}
	}
	if(DEBUG) cout<<endl;
}

main(){
	//Make file stream
	ifstream ifs;
	//Make arrays for genres
	Fiction ficArr[SIZE];
	Poetry poeArr[SIZE];
	Horror horArr[SIZE];
	//Fill the arrays with the books from the file
	mkArr(ficArr, poeArr, horArr, ifs);
	//Sort the arrays
	sortFicArr(ficArr);
	sortPoeArr(poeArr);
	sortHorArr(horArr);
	//Print the first 10 of each array
	printFicArr(ficArr, 10);
	printPoeArr(poeArr, 10);
	printHorArr(horArr, 10);
	//Print the first 10 total
	printTop(ficArr, poeArr, horArr, 10);
}
