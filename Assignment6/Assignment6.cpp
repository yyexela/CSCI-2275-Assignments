#include<iostream>

using namespace std;

struct MovieLLNode
{
 int imdb_ranking;
 string title;
 int year_released;
 int quantity;
 MovieLLNode *next;
 //this is constructor
 MovieLLNode(){};
 MovieLLNode(int ranking, string title, int year_released, int quantity)
 {
 this->imdb_ranking = ranking;
 this->title = title;
 this->year_released = year_released;
 this->quantity = quantity;
 this->next = NULL;
 }
}

struct MovieBSTNode
{
char MovieFirstLetter;
MovieBSTNode *parent;
MovieBSTNode *left;
MovieBSTNode *right;
//pointer to the head of the list of the movies starting with letter MovieFirstLetter
MovieLLNode *head;
//constructor 
MovieBSTNode(){};
MovieBSTNode(char first_letter)
{
  //
	this->MovieFirstLetter = first_letter;
	this->parent = NULL;
	this->left = NULL;
	this->head = NULL;
}

}

class MovieTree {
    
public:
    MovieTree(char* argv[])
    {
    	readFile(argv[1]);
    	//print menu
    	//call appropriate function depending on menu printed
    }
    ~MovieTree();
    void printMovieInventory()
    {
    	//call private function printMovieInventory() with root of the node as parameter and do in-order traversal
    };
    int countMovieNodes()
    {
    	//call private function countMovieNodes() with root and variable count=0
    	//(count is passed by refference see the private function definition)
    };
    void deleteMovieNode(std::string title)
    {
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
    };
    void addMovieNode(int ranking, std::string title, int releaseYear, int quantity)
    {
    	//    Create MovieNodeLL called newMovie to be added to its LL

    	//    Create a BST called newIndex node to be added

    	//    If BST is empty, set newIndex as root and set newMovie as head

    	//    Find if newIndex is already in BST, add newMovie to the LL pointed by newIndex alphabetically

    	//    if newIndex is not already present, add it in appropriate postition and set newMovie as head

    	//    remeber you are given a parent pointer too, so you need to set parent too


    };
    void findMovie(std::string title)
    {
    	//BST search to find the node starting from the first letter of title
    	//then once you find BST node, traverse to the LL attached to it to find the node with title and display information 
    	//if nothign is found print "Movie not found"
    };
    void rentMovie(std::string title)
    {
    	//Find node in BST for the first letter of title

    	//If no node found in BST print "Movie Not Found."

    	//if BST index is found, search for the movie title in the LL pointed by BST node

    	//Print the LL node information and decrease its quantity

    	//if quantity is 0, call deleteMovieNode() to delete a LL node with the title
    }
    void printMenu()
    {
    	//just prints the menu
    };
    void readFile(std::string filename)
    {
    	//read file 
    	//and call addMovieNode(stoi(rank), title, stoi(year), stoi(quantity));
    };

private:
    void DeleteAll(MovieNodeBST *node)
    {
    	//recursive function to delete all nodes
    	//same as in-order traversal
    	//instead of printing, you go through the LL pointed by tree node and delete it
    }; //use this for the post-order traversal deletion of the tree
    void printMovieInventory(MovieNodeBST * node)
    {
    	//this is a recursive function to print in-order

    	//you need to print entire LL attached to a particular node
    };
    void countMovieNodes(MovieNodeBST *node, int &count)
    {
    	//write recursive function
    	//recurstion is same as in-order traversal, 
    	//instead of printing value you have to increase count by traversing the LL attached to the node
    };
    MovieNodeBST* searchBST(MovieNodeBST *node, std::string title)
    {
    	//this is used by findMovie, deleteMovieNode, rentMovie so that you do not have to repeat this function

    }; //use this recursive function to find a pointer to a node in the BST, given a MOVIE TITLE first letter
    MovieNodeLL* searchLL(MovieNodeLL* head, std::string title)
    {
    	////this is used by findMovie, deleteMovieNode, rentMovie so that you do not have to repeat this function
    }; //use this to return a pointer to a node in a linked list, given a MOVIE TITLE and the head of the linked list
    MovieNodeBST* treeMinimum(MovieNodeBST *node); //use this to find the left most(or minimum) leaf node of the BST, you'll need this in the delete function
    MovieNodeBST* root;
};

int main(int argc, char* argv[]) {
    MovieTree mt(argv);
    return 0;
}