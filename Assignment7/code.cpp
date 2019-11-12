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

const bool DEBUG = true;

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
        while(ifs.good()){
            //get the line as a string and the first and last index of commas
            getline(ifs, line);
            if(DEBUG) cout<<"Working with: "<<line<<endl;
            int first = line.find(',');
            int last = line.rfind(',');
            if(DEBUG) cout<<"first: "<<first<<" last: "<<last<<endl;

            //see if a comma exists in the line
            if(first == -1){
                vertex *v = new vertex(line);
                people.push_back(v);
                continue;
            }
            while(first != last);
        }
    }
};


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
    City city;
    //build the graph
    city.buildGraph(FILE);

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
            default:
                cout<<endl<<"Invalid option"<<endl<<endl;
        }
    }while(stoi(option) != 5);
    cout<<"Exiting program"<<endl;
}