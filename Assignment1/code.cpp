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
bool DEBUG = false; //Used to print diagnostic information
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
		//Check if 'item' is wanted, i is the index of the buyer
		if(board[i].isWanted){
			//Loop through the rest of the array
			int buyerIndex = i;
			int minDiff = -1;//Updated when there is a possible transaction
			int sellerIndex = -1;//Only updated if minDiff becomes positive
			for(int j = 0; j < arrSize; j++){
				//Look for seller of 'item', j is the index of the seller
				if(board[j].type == board[buyerIndex].type && !board[j].isWanted){
					//See if 'item' from seller is the highest price closest to wanted
					int priceDiff = board[buyerIndex].price - board[j].price;
					if(DEBUG) cout<<"diff of buyer "<<board[buyerIndex].type<<":"<<board[buyerIndex].price<<" and seller "<<board[j].type<<":"<<board[j].price<<" is "<<priceDiff<<endl;
					if(minDiff < 0 || (priceDiff >= 0 && priceDiff < minDiff)){
						//Update sellerIndex and minDiff
						minDiff = priceDiff;
						sellerIndex = j;
						if(DEBUG) cout<<"new lowest diff: "<<minDiff<<endl;
					}
				}
			}
			//All values have been checked
			//See if seller accepts buyer by price
			if(minDiff >= 0){
				int profit = board[sellerIndex].price;
				if(DEBUG) totalProfit += profit;
				if(DEBUG){
					cout<<"Buying "<<board[sellerIndex].type<<": Seller: "<<board[sellerIndex].price<<" Buyer: "<<board[buyerIndex].price<<endl<<endl;
				} else {
					cout<<board[sellerIndex].type<<" "<<board[sellerIndex].price<<endl;
				}
				//Remove seller and buyer
				if(buyerIndex < sellerIndex){
					removeIndex(board, sellerIndex, arrSize);
					removeIndex(board, buyerIndex, arrSize);
				} else {
					removeIndex(board, buyerIndex, arrSize);
					removeIndex(board, sellerIndex, arrSize);
				}
				//If a match is found, change i to next element not checked
				if(sellerIndex < i) i = i-2; //if buyer index is less than i, set i back 2 since 2 were removed from arr from i to 0
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
	ifs.close();
	if(DEBUG) cout<<"End of program"<<endl;
}
