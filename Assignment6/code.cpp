/* Alexey Yermakov
 * CSCI 2275
 * October 29, 2019
 * Assignment 6
 */

#include<iostream>
#include<string>
#include<fstream>

using namespace std;

//prints additional statements when true
const bool DEBUG = false;

//node for the linked-list in each BST node
struct MovieLLNode{
	//member variables
	int imdb_ranking;
	string title;
	int year_released;
	int quantity;
	MovieLLNode *next;

	//constructors
	MovieLLNode(){};
	MovieLLNode(int ranking, string title, int year_released, int quantity){
		this->imdb_ranking = ranking;
		this->title = title;
		this->year_released = year_released;
		this->quantity = quantity;
		this->next = NULL;
	}

	//functions
	//prints the information of the current node
	void printInfo(){
		cout<<"Movie Info:"<<endl;
		cout<<"==========="<<endl;
		cout<<"Ranking: "<<imdb_ranking<<endl;
		cout<<"Title: "<<title<<endl;
		cout<<"Released: "<<year_released<<endl;
		cout<<"Quantity: "<<quantity<<endl<<endl;
	}
};

//node for the BST
struct MovieBSTNode{
	//member variables
	char letter;
	MovieBSTNode *parent;
	MovieBSTNode *left;
	MovieBSTNode *right;
	MovieLLNode *head; //head points to the first node in the linkedk list

	//constructors
	MovieBSTNode(){};
	MovieBSTNode(char letter){
		this->letter = letter;
		this->parent = NULL;
		this->left = NULL;
		this->right = NULL;
		this->head = NULL;
	}

	//functions
	//prints the linked list starting from head by calling the LLNode print() function
	void printLL(){
		MovieLLNode *tmp = head;
		if(DEBUG) cout<<"LL for BST \'"<<letter<<"\'"<<endl<<endl;
		if(tmp == NULL){
			cout<<"Empty LL"<<endl;
		} else while(tmp != NULL) {
			tmp->printInfo();
			cout<<endl;
			tmp = tmp->next;
		}
	}

	//prints the linked list node movie title and quantities only
	void printLLSimplified(){
		MovieLLNode *tmp = head;
		if(DEBUG) cout<<"Simplified LL for BST \'"<<letter<<"\'"<<endl<<endl;
		if(tmp == NULL){
			cout<<"Empty LL"<<endl;
		} else while(tmp != NULL) {
			cout<<"Movie: "<<tmp->title<<" "<<tmp->quantity<<endl<<endl;
			tmp = tmp->next;
		}
	}
};

//class for the movie tree containing BST nodes which contains LL nodes
class MovieTree {
	private:
	//member variables
	MovieBSTNode* treeMinimum(MovieBSTNode *node); //use this to find the left most(or minimum) leaf node of the BST, you'll need this in the delete function
	MovieBSTNode* root;

	//functions
	//recursively deletes the nodes of the tree bottom up
	//by deleting the entirity of the LL, deleteMovie() also removes the BST node
	void deleteAll(MovieBSTNode* node){
		if(node->left != NULL) deleteAll(node->left);
		if(node->right != NULL) deleteAll(node->right);
		if(node->left == NULL && node->right == NULL){
			while(node->head->next != NULL){
				cout<<"Deleting "<<node->head->title<<endl;
				deleteMovie(node->head->title);
			}
			cout<<"Deleting "<<node->head->title<<endl;
			deleteMovie(node->head->title);
		}
	}

	//prints every linked list in the BST, recursive and in-order traversal
	void printMovieInventory(MovieBSTNode* node){
		if(node->left != NULL) printMovieInventory(node->left);
		if(node != NULL) node->printLL();
		if(node->right != NULL) printMovieInventory(node->right);
	}

	//prints the letters of the BST nodes in order recursively
	//includes the parent letter, left child, and right child
	void printLettersInOrder(MovieBSTNode* node){
		if(node->left != NULL) printLettersInOrder(node->left);
		if(node != NULL){
			cout<<node->letter<<": ";
			if(node->parent != NULL)
				cout<<"p:"<<node->parent->letter<<" ";
			else
				cout<<"p:  ";
			if(node->left != NULL)
				cout<<"l:"<<node->left->letter<<" ";
			else
				cout<<"l:  ";
			if(node->right != NULL)
				cout<<"r:"<<node->right->letter<<" ";
			else
				cout<<"r:  ";
			cout<<endl;
		}
		if(node->right != NULL) printLettersInOrder(node->right);
	}

	//prints the letters of the BST nodes pre order recursively
	//includes the parent letter, left child, and right child
	void printLettersPreOrder(MovieBSTNode* node){
		if(node != NULL){
			cout<<node->letter<<": ";
			if(node->parent != NULL)
				cout<<"p:"<<node->parent->letter<<" ";
			else
				cout<<"p:  ";
			if(node->left != NULL)
				cout<<"l:"<<node->left->letter<<" ";
			else
				cout<<"l:  ";
			if(node->right != NULL)
				cout<<"r:"<<node->right->letter<<" ";
			else
				cout<<"r:  ";
			cout<<endl;
		}
		if(node->left != NULL) printLettersPreOrder(node->left);
		if(node->right != NULL) printLettersPreOrder(node->right);
	}

	//counts the number of movies by traversing the BST and then each LL
	//adding to the count variable passed in by reference recursively pre-order
	void countMovieNodes(MovieBSTNode *node, int &count){
		MovieLLNode *tmp = node->head;
		while(tmp != NULL){
			count += tmp->quantity;
			tmp = tmp->next;
		}
		if(node->left != NULL)
			countMovieNodes(node->left, count);
		if(node->right != NULL)
			countMovieNodes(node->right, count);
	}

	//returns the parent node of the BST if the passed in letter were to be added
	//or the node itself if the letter is found (ie. it already exists)
	MovieBSTNode* searchBST(MovieBSTNode *node, char letter){
		if((node->left == NULL && letter < node->letter)
			|| (node->right == NULL && node->letter < letter)
			|| node->letter == letter) 
				return node;
		else if(letter < node->letter) return(searchBST(node->left, letter));
		else return(searchBST(node->right, letter));
	}
	
	//return the LL node containing title in the given LL, or NULL if title is not found
	//assumes that the head of the LL given will contain the title (same first letter)
	//same as findMovie
	MovieLLNode* searchLL(MovieLLNode* head, string title){
		MovieLLNode *tmp = head;
		while(tmp != NULL){
			if(tmp->title == title) return tmp;
			tmp = tmp->next;
		}
		return tmp;
	}

	public:
	//constructor, requires file name to build the tree
	MovieTree(string file){
		root = NULL;
		if(DEBUG) cout<<"Root set to NULL"<<endl;
		readFile(file);
	}

	//destructor, removes all of the nodes in the tree
	~MovieTree(){
		deleteAll(root);
	}

	//calls the recursive deleteAll function from root
	void deleteAll(){
		deleteAll(root);
	}

	//deletes a movie from the BST tree by searchingn by the first letter
	//and then through the linked list of the BST node
	void deleteMovie(string movie){
		if(movie.size() <= 0){
			cout<<"No movie entered, exiting"<<endl;
			return;
		}
		MovieBSTNode* search = searchBST(root, movie[0]);
		if(search->letter == movie[0]){
			MovieLLNode* tmp = search->head;
			if(tmp->title == movie){
				if(DEBUG) cout<<"Deleting head of "<<search->letter<<endl;
				search->head = tmp->next;
				delete tmp;
			} else {
				while(tmp->next->title != movie && tmp->next != NULL){
					tmp = tmp->next;
				}
				if(tmp->next != NULL && tmp->next->title == movie){
					if(DEBUG) cout<<"Removing movie "<<movie<<endl;
					MovieLLNode* tmpDel = tmp->next;
					tmp->next = tmp->next->next;
					delete tmpDel;
				}
			}
			if(search->head == NULL)
					deleteBSTNode(movie[0]);
			}else{
				cout<<"Movie not found"<<endl;
			}
	}

	//calls the recursive function printLettersInOrder()
	//checks if root is NULL first
	void printLettersInOrder(){
		if(root != NULL){
			printLettersInOrder(root);
		} else {
			cout<<"Root is NULL"<<endl;
		}
	}

	//used to call the recursive printLettersPreOrder()
	//checks if root is NULL first
	void printLettersPreOrder(){
		if(root != NULL){
			printLettersPreOrder(root);
		} else {
			cout<<"Root is NULL"<<endl;
		}
	}
	
	//calls the printMovieInventory() recursive function with root
	//as the starting BST node
	void printMovieInventory(){
		if(root != NULL){
			printMovieInventory(root);
		} else {
			cout<<"Root is NULL"<<endl;
		}
	}

	//call the recursive function countMovieNodes() with 
	//root as the starting BST node and variable count=0 (passed by reference)
	int countMovieNodes(){
		if(root != NULL){
			int count = 0;
			countMovieNodes(root, count);
			return count;
		} else {
			cout<<"Root is NULL"<<endl;
		}
	}

	//by passing in the right child of a BST node, return the left-most child
	MovieBSTNode* findLeftMostBSTNode(MovieBSTNode* node){
		MovieBSTNode* tmp = node;
		while(tmp->left != NULL){
			tmp = tmp->left;
		}
		return tmp;
	}

	//deletes a BST node from a tree and updates it
	void deleteBSTNode(char letter){
		if(DEBUG) cout<<"Called deleteBSTNode"<<endl;
		if(root == NULL){
			cout<<"Root is NULL, exiting"<<endl;
			return;
		}
		MovieBSTNode *search = searchBST(root, letter);
		//see if the BSTNode was found given root != NULL
		if(search->letter != letter){
			cout<<"BSTNode not found"<<endl;
			return;
		}
		//check if node is root
		if(search == root){
			if(DEBUG) cout<<"Deleting root"<<endl;
			//delete root
			if(search->left == NULL && search->right == NULL){
				if(DEBUG) cout<<"Root has no children"<<endl;
				//root has no children
				root = NULL;
			} else if (search->left != NULL && search->right != NULL){
				if(DEBUG) cout<<"Root two children"<<endl;
				MovieBSTNode* min = findLeftMostBSTNode(search->right);
				if(min == search->right){
					if(DEBUG) cout<<"min is right child of root"<<endl;
					//min is right child of search, left child won't be an option ever
					//remember, search is root so don't need to check if it's
					//right or left of parent
					min->left = root->left;
					min->left->parent = min;
					min->parent = NULL;
					root = min;
				}
				//min is NOT child of parent
				else{
					if(DEBUG) cout<<"deleteNode is not child of root"<<endl;
					min->parent->left = min->right;
					if(min->right != NULL)
						min->right->parent = min->parent;
					min->parent = NULL;
					min->left = search->left;
					min->right = search->right;
					search->right->parent = min;
					search->left->parent = min;
					root = min;
				}
			}
			else {
				if(DEBUG) cout<<"Root has 1 child"<<endl;
				if(search->right != NULL){
					if(DEBUG) cout<<"root left is NULL"<<endl;
					root = root->right;
				} else {
					if(DEBUG) cout<<"root right is NULL"<<endl;
					root = root->left;
				}
				root->parent = NULL;
			}
			delete search;
			return;
		}
		//see if the node to be delete is one of its kind
		if(search->left == NULL && search->right == NULL){
			if(DEBUG) cout<<"Deleting node with no children"<<endl;
			//update parent pointer and delete node
			if(search->letter < search->parent->letter){
				//search is left child of parent
				search->parent->left = NULL;
			} else {
				//search is right child of parent
				search->parent->right = NULL;
			}
		}else if (search->left != NULL && search->right != NULL){
			if(DEBUG) cout<<"Deleting node with 2 children"<<endl;
			MovieBSTNode* min = findLeftMostBSTNode(search->right);
			MovieBSTNode* minParent = min->parent;
			//update parent pointer and delete node
			if(min == search->right){
				if(DEBUG) cout<<"min is right child of what to delete"<<endl;
				//min is right child of search, left child won't be an option ever
				if(search->letter < search->parent->letter){
					//search is left child of parent
					search->parent->left = min;
				}else{
					//search is right child of parent
					search->parent->right = min;
				}
				min->parent = search->parent;
				min->left = search->left;
				if(min->left != NULL)
					min->left->parent = min;
			}
			//min is NOT child of parent
			else{
				if(search->letter < search->parent->letter){
					if(DEBUG) cout<<"deleteNode is left of parent"<<endl;
					search->parent->left = min;
				}else{
					if(DEBUG) cout<<"deleteNode is right of parent"<<endl;
					search->parent->right = min;
				}
				//search is left child of parent
				min->parent->left = min->right;
				if(min->right != NULL)
					min->right->parent = min->parent;
				min->parent = search->parent;
				min->left = search->left;
				min->right = search->right;
				search->right->parent = min;
				search->left->parent = min;
			}
		} else {
			if(DEBUG) cout<<"Deleting node with 1 child"<<endl;
			if(search->right != NULL){
				if(DEBUG) cout<<"search left is NULL"<<endl;
				MovieBSTNode* tmp = search->right;
				if(search->letter < search->parent->letter){
					if(DEBUG) cout<<"letter is left of parent"<<endl;
					search->parent->left = tmp;
				} else {
					if(DEBUG) cout<<"letter is right of parent"<<endl;
					search->parent->right = tmp;
				}
				tmp->parent = search->parent;
			} else {
				if(DEBUG) cout<<"search right is NULL"<<endl;
				MovieBSTNode* tmp = search->left;
				if(search->letter < search->parent->letter)
					search->parent->left = tmp;
				else
					search->parent->right = tmp;
				tmp->parent = search->parent;
			}
		}
		//free memory
		delete search;
	}

	//creates a BST node for the first letter of the movie if it doesn't exist,
	//else it finds the BST node
	//in both situations it adds a new LL node to a BST node to the back of the LL
	void addMovieNode(int ranking, string title, int releaseYear, int quantity){
		if(DEBUG) cout<<"Calling addMovieNode"<<endl;

		//return if title size doesn't exist
		if(title.size() <= 0){
			cout<<"Attempting to add movie with no title, exiting addMovieNode()"<<endl;
			return;
		}

		MovieLLNode *llNode = new MovieLLNode(ranking, title, releaseYear, quantity);

		//see if BST is empty		
		if(root == NULL){
			if(DEBUG) cout<<"Root is null, adding "<<title<<endl;
			MovieBSTNode *bstNode = new MovieBSTNode(title[0]);
			root = bstNode;
			//since BST is empty, so is its LL
			bstNode->head = llNode;
			if(DEBUG) cout<<endl;
			return;
		}

		if(DEBUG) cout<<"root isn't null"<<endl;

		//search for BSTNode, returning the node if it's found, the parent of where it should be added if not
		MovieBSTNode *search = searchBST(root, title[0]);
		if(search->letter == title[0]){
			//letter is found
			if(DEBUG) cout<<"Node found, adding "<<title<<" to LL"<<endl;
			addToLL(search->head, llNode);
		}else{
			if(DEBUG) cout<<"Node not found, making bstNode for "<<title<<endl;
			MovieBSTNode *bstNode = new MovieBSTNode(title[0]);
			//swap out null of BST for the parent found in search
			if(title[0] < search->letter){
				if(DEBUG) cout<<"Adding letter to left"<<endl;
				search->left = bstNode;
			} else {
				if(DEBUG) cout<<"Adding letter to right"<<endl;
				search->right = bstNode;
			}

			//setting bstNode parent to search result
			bstNode->parent = search;
			if(DEBUG) cout<<"Setting bstNode parent to "<<search->letter<<endl;
			if(DEBUG) cout<<"Adding llNode as head"<<endl;
			//since bstNode is added, head is NULL
			bstNode->head = llNode;
		}
		if(DEBUG) cout<<endl;
	}

	//add an LL node in order of addition, new nodes pushed to back
	void addToLL(MovieLLNode* head, MovieLLNode* node){
		if(DEBUG) cout<<"adding to LL"<<endl;
		MovieLLNode* tmp = head;
		if(head == NULL){
			if(DEBUG) cout<<"LL head is NULL, setting node as head"<<endl;
			head = node;
			if(DEBUG){
				cout<<"count: 1"<<endl;
			}
			return;
		}
		while(tmp != NULL){
			if(tmp->title == node->title){
				if(DEBUG) cout<<"title already exists, adding to quantity"<<endl;
				tmp->quantity += node->quantity;
				return;
			}
			if(tmp->next == NULL){
				if(DEBUG) cout<<"title not found, adding to end"<<endl;
				tmp->next = node;
				return;
			}
			tmp = tmp->next;
		}
	}

	//searches through LL given head for a movie by an input string and returns the LL node
	//same as searchLL
	MovieLLNode* findMovie(MovieLLNode* head, string title){
		MovieLLNode* tmp = head;
		while(tmp != NULL){
			if(tmp->title == title){
				return tmp;
			}
			tmp = tmp->next;
		}
		return tmp;
	}

	//prints all of the movie info of a given title string
	//searches for a BST node given the first character of the title
	//then searches through the LL
	void findMovie(string title){
		if(root == NULL){
			cout<<"Root is null, exiting"<<endl;
			return;
		}
		MovieBSTNode *search = searchBST(root, title[0]);
		if(title[0] == search->letter){
			//title letter is found
			MovieLLNode* tmp = findMovie(search->head, title);
			if(tmp != NULL){
				tmp->printInfo();
				return;
			}
		}
		cout<<"Movie not found"<<endl<<endl;
	}

	//find node in BST for the first letter of title
	//if no node found in BST print "Movie Not Found."
	//if BST index is found, search for the movie title in the LL pointed by BST node
	//print the LL node information and decrease its quantity
	//if quantity is 0, call deleteMovieNode() to delete a LL node with the title
	void rentMovie(string title){
		if(root == NULL){
			cout<<"Root is NULL, exiting"<<endl;
			return;
		}
		MovieBSTNode *search = searchBST(root, title[0]);
		if(title[0] == search->letter){
			//movie letter is found
			MovieLLNode* tmp = findMovie(search->head, title);
			if(tmp != NULL){
				--(tmp->quantity);
				tmp->printInfo();
				//check if quantity is 0, if it is, deleteNode()
				if(tmp->quantity <= 0){
					deleteMovie(title);
				}
				if(search->head == NULL)
					deleteBSTNode(search->letter);
				return;
			}
		}
		cout<<"Movie not found"<<endl<<endl;
	}

	//prints user menu
	void printMenu(){
	}


	//read file 
	//and call addMovieNode(stoi(rank), title, stoi(year), stoi(quantity))
	//which adds a BST node to the tree with the first character
	//and adds an LL node to the BST node
	void readFile(string file){
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

//used to filter user input to just numbers
bool getNum(string &option){
        getline(cin, option);
        try{
                stoi(option);
        }catch(...){
                cout<<"Invalid input, enter a number"<<endl;
                return false;
        };
        return true;
}

//prints the menu for user selection
void printMenu(){
	cout<<"====Main Menu===="<<endl;
	cout<<"1. Find a movie"<<endl;
	cout<<"2. Rent a movie"<<endl;
	cout<<"3. Print the inventory"<<endl;
	cout<<"4. Delete a movie"<<endl;
	cout<<"5. Count the movies"<<endl;
	cout<<"6. Quit"<<endl;
	/* //additional menu options
	cout<<"7. Delete All"<<endl;
	cout<<"8. Print Pre Order"<<endl;
	cout<<"9. Print LL of char"<<endl;
	cout<<"10. Delete Movie"<<endl;
	*/
}

//main function which is run at the start of the program
//creates a MovieTree object from a file and takes in user commands
//which perform functions on the tree
int main(int argc, char* argv[]) {
	const string FILE = "Assignment6Movies.txt";
	MovieTree mt(FILE);
	string option = "", str1 = "";
	do{
		option = str1 = "";
		printMenu();
		while(!getNum(option));
		switch(stoi(option)){
			case 1:
				cout<<endl<<"Enter a title to search for:"<<endl;
				getline(cin, str1);
				cout<<endl;
				mt.findMovie(str1);
				break;
			case 2:
				cout<<endl<<"Enter a title to rent:"<<endl;
				getline(cin, str1);
				cout<<endl;
				mt.rentMovie(str1);
				break;
			case 3:
				mt.printMovieInventory();
				break;
			case 4:
				cout<<"Enter name of a movie to delete:"<<endl;
				getline(cin, str1);
				mt.deleteMovie(str1);
				cout<<endl;
				break;
			case 5:
				cout<<endl<<"Tree contains: "<<mt.countMovieNodes()<<" movies"<<endl<<endl;
				break;
			case 6:
				cout<<"Exiting program"<<endl;
				break;
				/*
			case 7: //additional secret user options
				cout<<"Delete All"<<endl;
				mt.deleteAll();
				break;
			case 8:
				mt.printLettersPreOrder();
				break;
			case 9:
				cout<<"Print which LL?"<<endl;
				getline(cin, str1);
				if(mt.searchBST(mt.root, str1[0])->letter == str1[0]){
					mt.searchBST(mt.root, str1[0])->printLL();
				}
				*/
				break;
			default:
				cout<<"Invalid menu option"<<endl<<endl;
		}
	} while (stoi(option) != 6);
	cout<<"Goodbye!"<<endl;
	return 0;
}
