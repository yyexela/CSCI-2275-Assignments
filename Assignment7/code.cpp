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
        string s = name;
        if (!s.empty() && s[s.length()-1] == '\n') {
            if(DEBUG) cout<<"Newline encountered"<<endl;
            s.erase(s.length()-1);
        }

        for(auto i = people.begin(); i != people.end(); ++i){
            if((*i)->name == name){
                if(DEBUG) cout<<"Found "<<name<<" as "<<(*i)->name<<endl;
                return *i;
            }
        }
        if(DEBUG) cout<<"Couldn't find "<<name<<endl;
        return NULL;
    }

    //prints the adjacency list of the graph
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

    string option = "", str1 = "", str2 = "";
    do{
        str1 = str2 = option = "";
        printMenu();
        while(!getNum(option));
        cout<<endl;
        switch(stoi(option)){
            case 1:
                city.printGraph();
                break;
            case 2:
                cout<<"Enter friend 1: "<<endl;
                cin>>str1;
                cout<<endl<<"Enter friend 2: "<<endl;
                cin>>str2;
                cout<<endl;
                if(city.areFriends(str1, str2)){
                    cout<<"They know each other"<<endl;
                } else {
                    cout<<"They do not know each other"<<endl;
                }
                cout<<endl;
                cin.ignore();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            if(DEBUG){
                case 6:
                    break;
            }
            default:
                cout<<endl<<"Invalid option"<<endl<<endl;
        }
    }while(stoi(option) != 5);
    cout<<"Exiting program"<<endl;
}