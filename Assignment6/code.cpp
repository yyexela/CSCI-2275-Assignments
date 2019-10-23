#include<iostream>
#include<string>
#include<fstream>

using namespace std;

const bool DEBUG = true;

struct MovieLLNode{
	int imdb_ranking;
	string title;
	int year_released;
	int quantity;
	MovieLLNode *next;
	//this is constructor
	MovieLLNode(){};
	MovieLLNode(int ranking, string title, int year_released, int quantity){
	this->imdb_ranking = ranking;
	this->title = title;
	this->year_released = year_released;
	this->quantity = quantity;
	this->next = NULL;
	}
};

struct MovieBSTNode{
	char letter;
	MovieBSTNode *parent;
	MovieBSTNode *left;
	MovieBSTNode *right;
	//pointer to the head of the list of the movies starting with letter MovieFirstLetter
	MovieLLNode *head;
	//constructor 
	MovieBSTNode(){};
	MovieBSTNode(char letter){
		this->letter = letter;
		this->parent = NULL;
		this->left = NULL;
		this->head = NULL;
	}
};

class MovieTree {
	MovieBSTNode* treeMinimum(MovieBSTNode *node); //use this to find the left most(or minimum) leaf node of the BST, you'll need this in the delete function
	MovieBSTNode* root;

	private:
	void DeleteAll(MovieBSTNode *node){
    //recursive function to delete all nodes
		//same as in-order traversal
		//instead of printing, you go through the LL pointed by tree node and delete it
	}  //use this for the post-order traversal deletion of the tree
	void printMovieInventory(MovieBSTNode * node){
		//this is a recursive function to print in-order
		//you need to print entire LL attached to a particular node
	}
	void countMovieNodes(MovieBSTNode *node, int &count){
		//write recursive function
		//recurstion is same as in-order traversal, 
		//instead of printing value you have to increase count by traversing the LL attached to the node
	}
	//parent if node is not found, or the node if the letter is found
	MovieBSTNode* searchBST(MovieBSTNode *node, char letter){
		if((node->left == NULL && letter < node->letter)
			|| (node->right == NULL && node->letter < letter)
			|| node->letter == letter) 
				return node;
		if(letter < node->letter) return(searchBST(node->left, letter));
		else return(searchBST(node->right, letter));
		//this is used by findMovie, deleteMovieNode, rentMovie so that you do not have to repeat this function
		//use this recursive function to find a pointer to a node in the BST, given a MOVIE TITLE first letter
	}
	//return the node containing title, or return tail if not found, NULL if head is NULL
	MovieLLNode* searchLL(MovieLLNode* head, string title){
		//this is used by findMovie, deleteMovieNode, rentMovie so that you do not have to repeat this function
		//use this to return a pointer to a node in a linked list, given a MOVIE TITLE and the head of the linked list
		MovieLLNode *tmp = head;
		while(tmp != NULL && tmp->next != NULL){
			if(tmp->title == title) return tmp;
			tmp = tmp->next;
		}
		return tmp;
	}

	public:
	MovieTree(string file){
		root = NULL;
		if(DEBUG) cout<<"Root set to NULL"<<endl;
		readFile(file);
	}
	~MovieTree(){
	}
	void printMovieInventory(){
		//call private function printMovieInventory() with root of the node as parameter and do in-order traversal
	}
	int countMovieNodes(){
		//call private function countMovieNodes() with root and variable count=0
		//(count is passed by refference see the private function definition)
	}
	void deleteMovieNode(string title){
		//search the node starting with first letter of title
		//call the private function searchBST that returns the BST node

		//call the private function searchLL to search in the LL attached to BST node found above
		//delete this LL node searched above

		//if movie to be deleted is head of the LL, Delete BST node as well
		//NOTE: you are given nodes parent pointer too
		//Depending on 3 conditions:
		//when node has no child
		//when node has just 1 child
		//when node has two children: you need to find in-order successor. Use function treeMinimum by passing node's right child
	}
	void addMovieNode(int ranking, string title, int releaseYear, int quantity){
		//    Create MovieLLNode called newMovie to be added to its LL
		//    Create a BST called newIndex node to be added
		//    If BST is empty, set newIndex as root and set newMovie as head
		//    Find if newIndex is already in BST, add newMovie to the LL pointed by newIndex alphabetically
		//    if newIndex is not already present, add it in appropriate postition and set newMovie as head
		//    remeber you are given a parent pointer too, so you need to set parent too
		if(DEBUG) cout<<"Calling addMovieNode"<<endl;
		if(title.size() <= 0){
			cout<<"Attempting to add movie with no title, exiting addMovieNode()"<<endl;
			return;
		}

		MovieLLNode *llNode = new MovieLLNode(ranking, title, releaseYear, quantity);
		
		if(root == NULL){
			if(DEBUG) cout<<"Root is null, adding "<<title<<endl;
			MovieBSTNode *bstNode = new MovieBSTNode(title[0]);
			root = bstNode;
			bstNode->head = llNode;
			if(DEBUG) cout<<endl;
			return;
		}

		if(DEBUG) cout<<"root isn't null"<<endl;

		MovieBSTNode *search = searchBST(root, title[0]);
		if(search->letter == title[0]){
			if(DEBUG) cout<<"Node found, adding "<<title<<" to LL"<<endl;
			if(search->head == NULL){
				if(DEBUG) cout<<"Head is null, setting "<<title<<" to head"<<endl;
				search->head = llNode;
			}
			else{
				if(DEBUG) cout<<"Head isn't NULL, adding "<<title<<" to LL"<<endl;
				MovieLLNode *tmp = searchLL(search->head, title);
				if(tmp->title == title) tmp->quantity += quantity;
				else tmp->next = llNode;
			}
		}else{
			if(DEBUG) cout<<"Node not found, making bstNode for "<<title<<endl;
			MovieBSTNode *bstNode = new MovieBSTNode(title[0]);
			if(title[0] < search->letter){
				search->left = bstNode;
			} else {
				search->right = bstNode;
			}
			if(DEBUG) cout<<"Adding llNode as head"<<endl;
			bstNode->head = llNode;
		}
		if(DEBUG) cout<<endl;
	}
	void findMovie(string title){
		//BST search to find the node starting from the first letter of title
		//then once you find BST node, traverse to the LL attached to it to find the node with title and display information 
		//if nothign is found print "Movie not found"
	}
	void rentMovie(string title){
		//Find node in BST for the first letter of title
		//If no node found in BST print "Movie Not Found."
		//if BST index is found, search for the movie title in the LL pointed by BST node
		//Print the LL node information and decrease its quantity
		//if quantity is 0, call deleteMovieNode() to delete a LL node with the title
	}
	void printMenu(){
		//just prints the menu
	}
	void readFile(string file){
		//read file 
		//and call addMovieNode(stoi(rank), title, stoi(year), stoi(quantity));
		ifstream ifs;
		ifs.open(file);
		string ranking, title, releaseYear, quantity;
		while(ifs.good()){
			getline(ifs, ranking, ',');
			if(DEBUG) cout<<"Ranking: "<<ranking<<endl;
			getline(ifs, title, ',');
			if(DEBUG) cout<<"Title: "<<title<<endl;
			getline(ifs, releaseYear, ',');
			if(DEBUG) cout<<"Year: "<<releaseYear<<endl;
			getline(ifs, quantity);
			if(DEBUG) cout<<"Quantity: "<<quantity<<endl<<endl;
			addMovieNode(stoi(ranking), title, stoi(releaseYear), stoi(quantity));
		}
	}
};

bool getNum(string &option){
        getline(cin, option);
        try{
                stoi(option);
        }catch(...){
                cout<<"Invalid input"<<endl;
                return false;
        };
        return true;
}

void printMenu(){
	cout<<"====Main Menu===="<<endl;
	cout<<"1. Find a movie"<<endl;
	cout<<"2. Rent a movie"<<endl;
	cout<<"3. Print the inventory"<<endl;
	cout<<"4. Delete a movie"<<endl;
	cout<<"5. Count the movies"<<endl;
	cout<<"6. Quit"<<endl;
}

int main(int argc, char* argv[]) {
	const string FILE = "Assignment6Movies.txt";
	MovieTree mt(FILE);
	string option = "";
	do{
		option = "";
		printMenu();
		while(!getNum(option));
		switch(stoi(option)){
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				cout<<"Exiting program"<<endl;
				break;
			default:
				cout<<"Invalid option"<<endl<<endl;
		}
	} while (stoi(option) != 6);
	return 0;
}
