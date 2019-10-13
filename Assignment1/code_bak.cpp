/* Alexey Yermakov
 * CSCI 2275
 * September 13, 2019
 * Assignment 1
 */


//Create an array of item structs for each item (type, price, for sale 0 or wanted 1)

#include<iostream>
#include<string>
#include<fstream>
using namespace std;

//Global variables
const bool DEBUG = false; //Used to print diagnostic information
const string FROMFILE = "Items.txt"; //File to read from
int totalProfit = 0; //Used only if DEBUG is true

//'item' struct containing string type, int price, and boolean isWanted
struct item{
	string type;
	int price;
	bool isWanted;
};

//PreCondition: board[] is an array of size arrSize or less, arrSize is greater than 0
//PostConditon: all the elements of board[] are printed to screen along with total profit and total items
void printArr(item board[], int arrSize){
	cout<<endl;
	for(int i = 0; i < arrSize; i++){
		cout<<board[i].type<<":"<<board[i].isWanted<<":"<<board[i].price<<endl;
	}
	cout<<endl;
	cout<<"Items left: "<<arrSize<<endl;
	cout<<"Total profit: $"<<totalProfit<<endl;
}

//PreCondition: board[] is an array of size arrSize, arrSize is greater than 0
//PostCondition: This function fills 'item' array board[] with 'item' structs from 0 to arrSize
void writeToItemArr(item board[], ifstream &ifs, int arrSize){
	string wrd;	
	for(int i = 0; i < arrSize && ifs.good(); i++){
		getline(ifs, wrd, ',');
		board[i].type = wrd;
		getline(ifs, wrd, ',');
		if(wrd == " wanted") board[i].isWanted = true;
		else board[i].isWanted = false;
		getline(ifs, wrd);
		board[i].price = stoi(wrd);
		
		if(DEBUG) cout<<board[i].type<<":"<<board[i].isWanted<<":"<<board[i].price<<endl;
	}
	if(DEBUG) cout<<endl;
}

//PreCondition: board[] contains elements of struct 'item' from 0 to arrSize
//PostCondition: board[] contains elements of struct 'item' from 0 to arrSize
void removeIndex(item board[], int index, int &arrSize){
	for(int i = index; i < arrSize - 1; i++){
		board[i] = board[i+1];
	}
	arrSize--;
}

//PreCondition: board[] is filled with 'item' structs from index 0 to arrSize, arrSize is greater than 0
//PostCondition: board[] is removed of matched elements after they are printed to the console
void findMatch(item board[], int &arrSize){
	//Loop through the entire array
	for(int i = 0; i < arrSize; i++){
		//Check if 'item' is for sale, if it's not wanted it's for sale
		if(!board[i].isWanted){
			//Loop through the rest of the array
			int maxPrice = -1;
			int buyerIndex = -1;
			for(int j = 0; j < arrSize; j++){
				//Look for buyer of 'item'
				if(board[j].type == board[i].type && board[j].isWanted){
					//See if 'item' at index j is the highest price
					if(board[j].price > maxPrice){
						//Set buyer index to j and update maxPrice
						maxPrice = board[j].price;
						buyerIndex = j;
					}
				}
			}
			//All values have been checked
			//See if seller accepts buyer by price
			if(maxPrice >= 0 && buyerIndex >= 0 && 
					board[i].price <= board[buyerIndex].price){
				int profit = board[buyerIndex].price - board[i].price;
				if(DEBUG) totalProfit += profit;
				if(DEBUG){
					cout<<board[i].type<<" for "<<board[buyerIndex].price<<" $"<<profit<<" profit"<<endl;
				} else {
					cout<<board[i].type<<" "<<board[i].price<<endl;
				}
				//Remove seller and buyer
				removeIndex(board, i, arrSize);
				removeIndex(board, buyerIndex, arrSize);
				//If a match is found, change i to next element not checked
				if(buyerIndex < i) i = i-2; //if buyer index is less than i, set i back 2 since 2 were removed from arr from i to 0
				else i--; //simply remove 1 because only 1 element was removed from i to 0
			} else {
				if(!DEBUG){
					//Seller DOES NOT accept the price, no sale made
					cout<<"Match not found"<<endl;
					cout<<board[i].type<<" "<<board[i].price<<endl;
				}
			}
		}
	}
}

//'main' method
int main(int argc, char *argv[]){
	//Array size
	//Creation of input stream from file "Items.txt"
	ifstream ifs;
	ifs.open(FROMFILE);
	if(ifs.is_open()){
	       	if(DEBUG) cout<<"File opened"<<endl;
	       	//Array 'board' used for storing of variables
		int arrSize = 100;
	       	item board[arrSize];
		//Copy file to array of struct 'item'
	       	writeToItemArr(board, ifs, arrSize);
		//Find matches of buyers and sellers in the array
		findMatch(board, arrSize);

		//Print final array
		if(DEBUG) printArr(board, arrSize);
	}else{
		cout<<"File failed to open"<<endl;
	}
	if(DEBUG) cout<<"End of program"<<endl;
}
