#include<iostream>
#include<string>
#include<fstream>

using namespace std;

const bool DEBUG = false;

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
	//prints the information of the LLNode
	void printInfo(){
		cout<<"Movie Info:"<<endl;
		cout<<"==========="<<endl;
		cout<<"Ranking: "<<imdb_ranking<<endl;
		cout<<"Title: "<<title<<endl;
		cout<<"Released: "<<year_released<<endl;
		cout<<"Quantity: "<<quantity<<endl<<endl;
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
		this->right = NULL;
		this->head = NULL;
	}
	//prints the LL starting from head
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
	//prints the LL starting from head, simplified
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

class MovieTree {
	MovieBSTNode* treeMinimum(MovieBSTNode *node); //use this to find the left most(or minimum) leaf node of the BST, you'll need this in the delete function
	MovieBSTNode* root;
	private:
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
		//recursive function to delete all nodes
		//same as in-order traversal
		//instead of printing, you go through the LL pointed by tree node and delete it
	}	//use this for the post-order traversal deletion of the tree
	void printMovieInventory(MovieBSTNode* node){
		//this is a recursive function to print in-order
		//you need to print entire LL attached to a particular node
		if(node->left != NULL) printMovieInventory(node->left);
		if(node != NULL) node->printLL();
		if(node->right != NULL) printMovieInventory(node->right);
	}
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
		else if(letter < node->letter) return(searchBST(node->left, letter));
		else return(searchBST(node->right, letter));
		//this is used by findMovie, deleteMovieNode, rentMovie so that you do not have to repeat this function
		//use this recursive function to find a pointer to a node in the BST, given a MOVIE TITLE first letter
	}void printLettersPreOrder(){
		if(root != NULL){
			printLettersPreOrder(root);
		} else {
			cout<<"Root is NULL"<<endl;
		}
	}
	//return the node containing title, or NULL if title is not found is NULL
	MovieLLNode* searchLL(MovieLLNode* head, string title){
		//this is used by findMovie, deleteMovieNode, rentMovie so that you do not have to repeat this function
		//use this to return a pointer to a node in a linked list, given a MOVIE TITLE and the head of the linked list
		MovieLLNode *tmp = head;
		while(tmp != NULL){
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
		deleteAll(root);
	}
	void deleteAll(){
		deleteAll(root);
	}
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
	void printLettersInOrder(){
		if(root != NULL){
			printLettersInOrder(root);
		} else {
			cout<<"Root is NULL"<<endl;
		}
	}
	void printMovieInventory(){
		//call private function printMovieInventory() with root of the node as parameter and do in-order traversal
		if(root != NULL){
			printMovieInventory(root);
		} else {
			cout<<"Root is NULL"<<endl;
		}
	}
	int countMovieNodes(){
		//call private function countMovieNodes() with root and variable count=0
		if(root != NULL){
			int count = 0;
			countMovieNodes(root, count);
			return count;
		} else {
			cout<<"Root is NULL"<<endl;
		}
		//(count is passed by refference see the private function definition)
	}
	MovieBSTNode* findLeftMostBSTNode(MovieBSTNode* node){
		MovieBSTNode* tmp = node;
		while(tmp->left != NULL){
			tmp = tmp->left;
		}
		return tmp;
	}
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
					//Remember, search is root so don't need to check if it's
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
	
	void addMovieNode(int ranking, string title, int releaseYear, int quantity){
		//    Create MovieLLNode called newMovie to be added to its LL
		//    Create a BST called newIndex node to be added
		//    If BST is empty, set newIndex as root and set newMovie as head
		//    Find if newIndex is already in BST, add newMovie to the LL pointed by newIndex alphabetically
		//    if newIndex is not already present, add it in appropriate postition and set newMovie as head
		//    remeber you are given a parent pointer too, so you need to set parent too

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
	void addToLL(MovieLLNode* head, MovieLLNode* node){
		if(DEBUG) cout<<"adding to LL"<<endl;
		MovieLLNode* tmp = head;
		if(head == NULL){
			if(DEBUG) cout<<"LL head is NULL, setting node as head"<<endl;
			head = node;
			if(DEBUG){
				cout<<"count: "<<1<<endl;
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
	void findMovie(string title){
		//BST search to find the node starting from the first letter of title
		//then once you find BST node, traverse to the LL attached to it to find the node with title and display information 
		//if nothign is found print "Movie not found"
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
	void rentMovie(string title){
		//Find node in BST for the first letter of title
		//If no node found in BST print "Movie Not Found."
		//if BST index is found, search for the movie title in the LL pointed by BST node
		//Print the LL node information and decrease its quantity
		//if quantity is 0, call deleteMovieNode() to delete a LL node with the title
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
	/*
	cout<<"7. Delete All"<<endl;
	cout<<"8. Print Pre Order"<<endl;
	cout<<"9. Print LL of char"<<endl;
	cout<<"10. Delete Movie"<<endl;
	*/
}

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
			case 7:
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
				cout<<"Invalid option"<<endl<<endl;
		}
	} while (stoi(option) != 6);
	cout<<"Goodbye!"<<endl;
	return 0;
}
