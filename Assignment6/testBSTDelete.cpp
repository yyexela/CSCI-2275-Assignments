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
	//prints the information of the LLNode
	void printInfo(){
		cout<<"Ranking: "<<imdb_ranking<<endl;
		cout<<"Title: "<<title<<endl;
		cout<<"Released: "<<year_released<<endl;
		cout<<"Quantity: "<<quantity<<endl;
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
		cout<<"LL for BST \'"<<letter<<"\'"<<endl<<endl;
		if(tmp == NULL){
			cout<<"Empty LL"<<endl;
		} else while(tmp != NULL) {
			tmp->printInfo();
			cout<<endl;
			tmp = tmp->next;
		}
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
	}
	public:
	MovieTree(string file){
		root = NULL;
		if(DEBUG) cout<<"Root set to NULL"<<endl;
	}
	~MovieTree(){
	}
	void printLettersInOrder(){
		if(root != NULL){
			printLettersInOrder(root);
		} else {
			cout<<"Root is NULL"<<endl;
		}
	}
	void printLettersPreOrder(){
		if(root != NULL){
			printLettersPreOrder(root);
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
		MovieBSTNode *search = searchBST(root, title[0]);
		if(title[0] == search->letter){
			MovieLLNode* tmp = findMovie(search->head, title);
			if(tmp != NULL){
				tmp->printInfo();
			} else {
				cout<<"Movie not found"<<endl;
				if(DEBUG) cout<<"in LL"<<endl;
			}
		} else {
			cout<<"Movie not found"<<endl;
			if(DEBUG) cout<<"in BST"<<endl;
		}
		cout<<endl;
	}
	void printMenu(){
		//just prints the menu
	}
	void addLetter(string str){
		addMovieNode(0, str, 0, 0);
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
	cout<<"2. XXX"<<endl;
	cout<<"3. Print the inventory"<<endl;
	cout<<"4. Delete a movie"<<endl;
	cout<<"5. Count the movies"<<endl;
	cout<<"6. Quit"<<endl;
	cout<<"7. Delete Letter"<<endl;
	cout<<"8. Print Letters"<<endl;
	cout<<"9. Add Letters"<<endl;
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
				break;
			case 3:
				mt.printMovieInventory();
				break;
			case 4:
				break;
			case 5:
				cout<<endl<<"Movies: "<<mt.countMovieNodes()<<endl<<endl;
				break;
			case 6:
				cout<<"Exiting program"<<endl;
				break;
			case 7:
				cout<<"Enter char"<<endl;
				getline(cin, str1);
				mt.deleteBSTNode(str1[0]);
				cout<<"InOrder:"<<endl;
				mt.printLettersInOrder();
				cout<<"PreOrder:"<<endl;
				mt.printLettersPreOrder();
				cout<<endl;
				break;
			case 8:
				cout<<"InOrder:"<<endl;
				mt.printLettersInOrder();
				cout<<"PreOrder:"<<endl;
				mt.printLettersPreOrder();
				cout<<endl;
				break;
			case 9:
				cout<<"Add letter:"<<endl;
				getline(cin, str1);
				mt.addLetter(str1);
			default:
				cout<<"Invalid option"<<endl<<endl;
		}
	} while (stoi(option) != 6);
	return 0;
}
