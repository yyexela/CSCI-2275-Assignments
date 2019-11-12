/* Alexey Yermakov
 * CSCI 2275
 * November 15, 2019
 * Assignment 7
 */

#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

//prints debug info when true
const bool DEBUG = false;

//struct holding a single person
struct vertex{
    string name;
    bool visited;
    int distance;
    string path;
    vector<vertex*> adjacency;
    vertex(string n){
        name = n;
        visited = false;
        distance = 0;
    }
};

class City{
    //Member variables
    vector<vertex*> people;

    public:
    //Constructor
    City(){
    }

    //Functions
    void buildGraph(string FILE){
        ifstream ifs(FILE);
        string line;
        int first, last;

        //add initial vectors to the people vector
        while(ifs.good()){
            //get the line as a string and the first and last index of commas
            ifs >> line;
            if(DEBUG) cout<<"Working with: "<<line<<" size: "<<line.size()<<endl;
            int first = line.find('-');
            if(DEBUG) cout<<"first: "<<first<<endl;

            //see if a heiphen exists in the line
            if(first == -1){
                //no heiphen means add the whole line
                if(DEBUG) cout<<"Adding: "<<line<<endl;
                vertex *v = new vertex(line);
                people.push_back(v);
            } else {
                //yes heiphen means add substring up to the heiphen
                if(DEBUG) cout<<"Adding: "<<line.substr(0, first)<<endl;
                vertex *v = new vertex(line.substr(0, first));
                people.push_back(v);
            }
            if(DEBUG) cout<<endl;
        }

        //reset ifs to read from the top
        ifs.close();
        ifs.open(FILE);

        //build the adjacency list
        while(ifs.good()){
            string name = "";

            //get the line as a string and the first and last index of heiphen and commas
            ifs >> line;
            if(DEBUG) cout<<"Working with: "<<line<<endl;
            int first = line.find('-');
            int last = line.rfind(',');
            if(DEBUG) cout<<"first: "<<first<<" last: "<<last<<endl;

            //find the vertex to build edges with
            vertex *v = find(line.substr(0, first));

            //see if neighbors exist
            if(first == -1){
                if(DEBUG) cout<<"Not doing anything"<<endl;
            } else if(last == -1){
                //see if there is only one neighbor (no commas but there is a hyphen)
                name = line.substr(first+1); 
                if(DEBUG) cout<<"Last = -1, Adding: "<<name<<endl;
                vertex *v2 = find(name);
                v->adjacency.push_back(v2);
            } else {
                //keep adding neighbors comma delimeted
                while(first != last){
                    int next = line.find(',', first+1);
                    name = line.substr(first+1, next-(first+1));
                    if(DEBUG) cout<<"Next: "<<next<<endl;
                    if(DEBUG) cout<<"Adding: "<<name<<endl;
                    vertex *v2 = find(name);
                    v->adjacency.push_back(v2);
                    first = next;
                };
                name = line.substr(last+1);
                if(DEBUG) cout<<"Adding: "<<name<<endl;
                vertex *v2 = find(name);
                v->adjacency.push_back(v2);
            }
            if(DEBUG) cout<<endl;
        }
    }

    //searches through the people vector and returns the pointer to the vertex of the person
    vertex* find(string name){
        for(auto i = people.begin(); i != people.end(); ++i){
            if((*i)->name == name){
                if(DEBUG) cout<<"Found "<<name<<" as "<<(*i)->name<<endl;
                return *i;
            }
        }
        if(DEBUG) cout<<"Couldn't find "<<name<<endl;
        return NULL;
    }

    //returns whether two people (names) share an edge to one another
    bool areFriends(string name1, string name2){
        for(auto i = people.begin(); i != people.end(); ++i){
            vertex *v = *i;
            if(v->name == name1 || v->name == name2){
                for(auto j = v->adjacency.begin(); j != v->adjacency.end(); ++j){
                    vertex *v2 = *j; 
                    if( (*j)->name == name1 || (*j)->name == name2 ) return true;
                }
            }
        }

        return false;
    }

    //prints the adjacency list of the graph
    void printGraph(){
        for(auto i = people.begin(); i != people.end(); ++i){
            vertex *v = *i;
            cout<<v->name<<"-";
            for(auto j = v->adjacency.begin(); j != v->adjacency.end(); ++j){
                vertex *v2 = *j; 
                cout<<v2->name;
                if(v->adjacency.end()-1 == v->adjacency.begin() || j == v->adjacency.end()-1) cout<<endl;
                else cout<<",";
            }
        }
        cout<<endl;
    }

    //resets the visited of all the vertices to false
    void resetVisited(){
        for(auto i = people.begin(); i != people.end(); ++i){
            vertex *v = *i;
            v->visited = false;
            for(auto j = v->adjacency.begin(); j != v->adjacency.end(); ++j){
                vertex *v2 = *j; 
                v2->visited = false;
                v2->path = "";
                v2->distance = 0;
            }
        }
    }

    //prints the group IDs and people in them
    void printGroups(){
        //DFT using a vector that acts as a stack
        vector<vertex*> stack;
        //int to count group #
        int ID = 1;
        //outer loop to make sure at least each person is in a group, traversing the people vector
        for(auto i = people.begin(); i != people.end(); ++i){
            if(DEBUG) cout<<"Checking "<<(*i)->name<<endl;
            //add unvisited vertex
            if(!(*i)->visited){
                if(DEBUG) cout<<"Initial push "<<(*i)->name<<endl;
                stack.push_back(*i);
                (*i)->visited = true;
                cout<<"Group ID #"<<ID<<endl;
                ++ID;
            }
            //push all unvisited neighbors of top of stack
            while(stack.size() != 0){
                vertex *v = *(stack.end()-1);
                stack.erase(stack.end()-1);
                cout<<v->name<<endl;
                for(auto j = v->adjacency.begin(); j != v->adjacency.end(); ++j){
                    if(!(*j)->visited){
                        if(DEBUG) cout<<"Additional push "<<(*j)->name<<endl;
                        (*j)->visited = true;
                        stack.push_back(*j);
                    }
                }
            }
        }
    }

    //prints shortest path, if any, between two people
    void lstNumIntro(string name1, string name2){
        vector<vertex*> queue;
        if(people.size() <= 0) return;
        vertex* v1 = find(name1);
        //check if name exists;
        if(v1 == NULL) return;
        //push back first person
        if(DEBUG) cout<<"Initial push "<<v1->name<<endl;
        queue.push_back(v1);
        v1->visited = true;
        //update source information
        string path = v1->name;
        v1->path = path;
        v1->distance = 0;
        while(queue.size() > 0){
            //pop front of queue
            v1 = *queue.begin();
            queue.erase(queue.begin());
            //add all unvitied neighbors of popped elements
            for(auto i = v1->adjacency.begin(); i != v1->adjacency.end(); ++i){
                if(!(*i)->visited){
                    if(DEBUG) cout<<"Additional push "<<(*i)->name<<endl;
                    //update information
                    (*i)->visited = true;
                    (*i)->path = v1->path + "," + ((*i)->name);
                    (*i)->distance = v1->distance + 1;
                    queue.push_back(*i);
                }
                //see if pushed element is destination
                if((*i)->name == name2){
                    cout<<"Path from "<<name1<<" to "<<name2<<" is: "<<((*i)->path)<<endl;
                    cout<<"Distance is "<<(*i)->distance<<endl;
                    cout<<endl;
                    return;
                }
            }
        }
    }
};

//prints user menu
void printMenu(){
    cout<<"1. Print list of people and their acquantances"<<endl;
    cout<<"2. Print if people know each other"<<endl;
    cout<<"3. Print groups"<<endl;
    cout<<"4. Find the least number of inductions required"<<endl;
    cout<<"5. Quit"<<endl;
}

//used to filter user input to just numbers
bool getNum(string &option){
    getline(cin, option);
    try{
            stoi(option);
    }catch(...){
            cout<<endl<<"Invalid input, enter a number"<<endl<<endl;
            return false;
    };
    return true;
}

int main(){
    //file name to build graph from
    const string FILE = "people.txt";
    //initialize city class used to store graph and perform operations
    City city;
    //build the graph
    city.buildGraph(FILE);

    //empty strings used to store user input
    string option = "", str1 = "", str2 = "";
    do{
        str1 = str2 = option = "";
        //prints the user menu
        printMenu();
        //filters user input
        while(!getNum(option));
        cout<<endl;
        //case switch to execute user operation
        switch(stoi(option)){
            case 1:
                city.printGraph();
                break;
            case 2:
                cout<<"enter friend 1: "<<endl;
                cin>>str1;
                cout<<endl<<"enter friend 2: "<<endl;
                cin>>str2;
                cout<<endl;
                if(city.areFriends(str1, str2)){
                    cout<<"\""<<str1<<"\" and \""<<str2<<"\" know each other"<<endl;
                } else {
                    cout<<"\""<<str1<<"\" and \""<<str2<<"\" do not know each other"<<endl;
                }
                cout<<endl;
                cin.ignore();
                break;
            case 3:
                city.printGroups();
                city.resetVisited();
                break;
            case 4:
                cout<<"enter friend 1: "<<endl;
                cin>>str1;
                cout<<endl<<"enter friend 2: "<<endl;
                cin>>str2;
                cout<<endl;
                city.lstNumIntro(str1, str2);
                city.resetVisited();
                cin.ignore();
                break;
            if(DEBUG){
                case 5:
                    break;
            }
            default:
                cout<<endl<<"Invalid option"<<endl<<endl;
        }
    }while(stoi(option) != 5);
    cout<<"Exiting program"<<endl;
}