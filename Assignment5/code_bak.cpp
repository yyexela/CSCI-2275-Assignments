#include<iostream>
#include<string>
#include<fstream>

using namespace std;

bool DEBUG = false;

//city struct 
struct city{
	//string members and pointers to the next and previous city
	string name, message;
	city *next, *previous;
	//three class constructors
	city(string name, string message){
		this->name = name;
		this->message = message;
	}
	city(string name){
		this->name = name;
		this->message = "";
	}
	city(){
		this->name = "";
		this->message = "";
	}
	//toString method which prints the name and message of the city
	string toString(){
		return this->name + ", \"" + this->message + "\"";
	}
	//name getter
	string getName(){
		return this->name;
	}
	//message getter
	string getMessage(){
		return this->message;
	}
	//message setter
	void setMessage(string wrd){
		//if(DEBUG) cout<<"set Message "<<this->name<<endl;
		this->message = wrd;
	}
};

//class CommunicationNetwork which contains the double linked list
class CommunicationNetwork{
	private:
	//declaration of the head and tail city pointers
	city *head, *tail;
	
	public:
	//class constructor, head and tail default to null
	CommunicationNetwork(){
		head = NULL;
		tail = NULL;
	}

	~CommunicationNetwork(){
		clearNetwork();
	}

	//insert a city to the double linked list
	void insert(city *tmp){
		if(DEBUG) cout<<"adding city "<<tmp->name<<endl;
		if(head == NULL){
			head = tmp;
			tail = tmp;
			tmp->next = NULL;
			tmp->previous = NULL;
		} else {
			tail->next = tmp;
			tmp->previous = tail;
			tail = tmp;
			tail->next = NULL;
			
		}
	}

	//print to cout the order of the city nodes names and messages
	void printFull(){
		if(DEBUG) cout<<endl<<"printing cities"<<endl;
		if(head == NULL){
			cout<<endl<<"EMPTY NETWORK"<<endl<<endl;;
		} else {
			city* tmp = head;
			cout<<endl<<"NULL <- ";
			while(tmp->next != NULL){
				//if(DEBUG) cout<<tmp->getName()<<endl;
				cout<<tmp->getName()<<","<<tmp->getMessage()<<" <-> ";
				tmp = tmp->next;
			}
			cout<<tmp->getName()<<","<<tmp->getMessage()<<" -> NULL"<<endl<<endl;
		}
	}

	//print to cout the order of the city nodes names
	void printNetwork(){
		if(DEBUG) cout<<endl<<"printing cities"<<endl;
		cout<<"===CURRENT PATH==="<<endl;
		if(head == NULL){
			cout<<endl<<"EMPTY NETWORK"<<endl<<endl;;
		} else {
			city* tmp = head;
			cout<<endl<<"NULL <- ";
			while(tmp->next != NULL){
				//if(DEBUG) cout<<tmp->getName()<<endl;
				cout<<tmp->getName()<<" <-> ";
				tmp = tmp->next;
			}
			cout<<tmp->getName()<<" -> NULL"<<endl<<endl;
		}
		cout<<"=================="<<endl;
	}
	
	//get pointer to the city with a given name
	city* getCity(string name){
		if(DEBUG) cout<<"searching for "<<name<<endl;
		city* tmp = head;
		while(tmp != NULL){
			if(tmp->getName() == name){
				if(DEBUG) cout<<"found "<<name<<" "<<tmp->getName()<<endl;
				return tmp;
			}
			tmp = tmp->next;
		}
		if(DEBUG) cout<<name<<" not found"<<endl;
		return NULL; //city not found;
	}

	//delete a city
	void deleteCity(city* tmp){
		//temporary pointer to delete the city at the end
		city* tmpdel = tmp;
		if(DEBUG) cout<<"deleting "<<tmp->getName()<<endl;
		//tmp is the only thing in the network
		if(tmp ->previous == NULL && tmp -> next == NULL){
			tail = NULL;
			head = NULL;
		}else if(tmp->previous == NULL){
			//tmp is head, set next city's previous to null
			tmp->next->previous = NULL;
			head = tmp->next;
		} else if (tmp->next == NULL){
			//tmp is tail, set previous city's next to null
			tmp->previous->next = NULL;
			tail = tmp->previous;
		} else {
			//tmp is within the center of the network
			tmp->previous->next = tmp->next;
			tmp->next->previous = tmp->previous;
		}
		delete tmpdel;
	}

	//delete the network
	void clearNetwork(){
		city* tmp;
		//keep clearing head until it's null
		if(head == NULL){
			cout<<"Network is empty"<<endl;
		}
		while(head != NULL){
			tmp = head;
			cout<<"deleting "<<tmp->getName()<<endl;
			deleteCity(head);
		}
		cout<<endl;
	}

	//send a string wrd from city* city1 to city* city2
	//city1 and city2 are actual cities in the network
	void sendMessage(city* city1, city* city2, string wrd){
		if(DEBUG) cout<<"sendMessage from "<<city1->getName()<<" to "<<city2->getName()<<endl;
		//set message for the sender
		city1->setMessage(wrd);
		if(DEBUG) cout<<"set sender "<<city1->getName()<<" to "<<wrd<<endl;
		//cout<<city1->getName()<<" recieved "<<city1->getMessage()<<endl;
		//locate which city comes first
		city* tmp = head;//start search at head
		while(tmp != NULL && tmp != city1 && tmp != city2){
			if(DEBUG) cout<<tmp<<":"<<city1<<":"<<city2<<endl;
			if(DEBUG) cout<<"checking if "<<tmp->getName()<<" is "<<city1->getName()<<" or "<<city2->getName()<<endl;
			tmp = tmp->next;
		}
		if(DEBUG) cout<<"first is "<<tmp->getName()<<endl;
		//exit loop with tmp being city1 or city2, whichever is first
		if(tmp == city1){
			//loop from city1 to city2 since city1 is first
			while(tmp != city2){
				//set next city's message
				tmp->next->setMessage(tmp->getMessage());
				tmp->setMessage("");
				cout<<tmp->next->getName()<<" recieved "<<tmp->next->getMessage()<<endl;
				tmp = tmp->next;
			}
		}
		else if(tmp == city2){
			//loop backwards from city1 to city2 since city1 is last
			tmp = city1;
			while(tmp != city2){
				//set previous city's message
				tmp->previous->setMessage(tmp->getMessage());
				tmp->setMessage("");
				cout<<tmp->previous->getName()<<" recieved "<<tmp->previous->getMessage()<<endl;
				tmp = tmp->previous;
			}
		}
	}

	//add city1 after city2, prepend if city2 is NULL
	void addCity(city *city1, city *city2){
		if(DEBUG) cout<<"adding city "<<city1->getName();
		if(city2 == NULL){
			if(DEBUG) cout<<"prepending city "<<city1->getName();
			city1->next = head;
			city1->previous = NULL;
			//check for if head exists
			if(head != NULL){
				head->previous = city1;
			} else {
				//if head == NULL, tail == NULL
				tail = city1;
			}
			head = city1;
		} else if(city2 == tail){
			tail->next = city1;
			city1->previous = tail;
			city1->next = NULL;
			tail = city1;
		} else {
			city1->next = city2->next;
			city1->previous = city2;
			city1->next->previous = city1;
			city2->next = city1;
		}
	}
	
	//head getter
	city* getHead(){
		return head;
	}

	//tail getter
	city* getTail(){
		return tail;
	}
};

//add all of the default cities to 'network'
void buildNetwork(CommunicationNetwork &network){
	network.insert(new city("Los Angeles"));
	network.insert(new city("Phoenix"));
	network.insert(new city("Denver"));
	network.insert(new city("Dallas"));
	network.insert(new city("St. Louis"));
	network.insert(new city("Chicago"));
	network.insert(new city("Atlanta"));
	network.insert(new city("Washington, D.C."));
	network.insert(new city("New York"));
	network.insert(new city("Boston"));
	network.printNetwork();
}

void printMenu(){
	cout<<"====Main Menu===="<<endl;
	cout<<"1. Build network"<<endl;
	cout<<"2. Print network path"<<endl;
	cout<<"3. Transmit message from city x to city y"<<endl;
	cout<<"4. Add city"<<endl;
	cout<<"5. Delete city"<<endl;
	cout<<"6. Clear network"<<endl;
	cout<<"7. Quit program"<<endl;
}

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

int wordCount(string line){
	if(line.size() <= 0) return 0;
	int index = line.find(' ');
	int count = 1;
	do{
		//cout<<line.substr(0, index)<<endl;
		index = line.find(' ', index+1);
		++count;
	} while (index != string::npos);
	return count;
}

void makeStrArr(string line, string words[]){
	cout<<"called makeStrArr"<<endl;
	int count = wordCount(line);
	int lastIndex = line.rfind(' ');
	//string contains one word
	if(lastIndex == string::npos){
		words[0] = line;
		return;
	}
	int index1 = 0; //start pos
	int index2 = line.find(' '); //end pos
	int wrd = 0;
	for(int i = 0; i < count-1; ++i){
		cout<<"adding "<<line.substr(index1, index2-index1)<<endl;;
		words[i] = line.substr(index1, index2-index1);
		index1 = index2 + 1;
		index2 = line.find(' ', index1);
	}
	cout<<"adding "<<line.substr(lastIndex + 1)<<endl;;
	words[count-1] = line.substr(lastIndex + 1);
}

int main(int argc, char* argv[]){
	cout<<"PROGRAM START"<<endl<<endl;
	if(argc <= 1){
		cout<<"Enter command line argument"<<endl;
		return 1;
	}
	ifstream ifs;//initialization of inputfilestream
	ifs.open(argv[1]);
	//variables used to input the file into
	if(!ifs.good()){
		cout<<"File unable to open"<<endl;
		return 1;
	}
	string line;
	getline(ifs, line);
	cout<<wordCount(line)<<endl;
	string words[wordCount(line)];
	makeStrArr(line, words);
	return 0;
	CommunicationNetwork network; //initialization of the CommunicationNetwork class
	string str1, str2, str3, option;
	city *city1, *city2;
	do{
		str1 = str2 = str3 = option = "";
		city1 = city2 = NULL;
		printMenu();
		//loop through til cin is a valid integer input
		while(!getNum(option));
		if(DEBUG) cout<<"Switch"<<endl;
		switch(stoi(option)){
			case 1:
				//build the network from scratch, clearing if not empty
				if(network.getHead() != NULL)
					network.clearNetwork();
				buildNetwork(network);
				break;
			case 2:
				if(!DEBUG) network.printNetwork();
				if(DEBUG) network.printFull();
				break;
			case 3:
				cout<<endl<<"Enter city x"<<endl;
				getline(cin,str1);
				cout<<"Enter city y"<<endl;
				getline(cin,str2);
				cout<<endl;
				city1 = network.getCity(str1);
				city2 = network.getCity(str2);
				ifs.open(argv[1]);//open file
				if(city1 == NULL || city2 == NULL){
					cout<<"at least one city not found, exiting"<<endl<<endl;
					break;
				}
				//str3 = "Wrd";
				while(ifs>>str3){
					//getline(ifs, str3, ' ');
					if(DEBUG) cout<<"message: "<<str3<<endl;
					cout<<city1->getName()<<" recieved "<<str3<<endl;
					network.sendMessage(city1, city2, str3);
					if(DEBUG) network.printFull();
					network.sendMessage(city2, city1, str3);
				}
				cout<<endl;
				ifs.close();
				break;
			case 4:
				cout<<endl<<"Enter name of city to add:"<<endl;
				getline(cin, str1);
				cout<<"Enter name of previous city:"<<endl;
				getline(cin, str2);
				city1 = new city(str1);
				if(str2 == "First"){
					network.addCity(city1, NULL);
					break;
				} else {
					city2 = network.getCity(str2);
					if(city2 != NULL){
						network.addCity(city1, city2);
						cout<<endl;
					} else {
						cout<<endl<<str2<<" not found"<<endl;
					}
				}
				break;
			case 5:
				cout<<endl<<"Enter city name"<<endl;
				getline(cin,str1);
				cout<<endl;
				city1 = network.getCity(str1);
				if(city1 != NULL)
					network.deleteCity(network.getCity(str1));
				else
					cout<<str1<<" not found"<<endl<<endl;
				break;
			case 6:
				network.clearNetwork();
				break;
			case 7:
				cout<<"Goodbye!"<<endl;
				break;
			default:
				cout<<endl<<"invalid option, choose a number between 1 and 7"<<endl<<endl;
		}
	}while(stoi(option) != 7);
}
