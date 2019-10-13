#include<iostream>
#include<string>
#include<fstream>

using namespace std;

bool DEBUG = true;

//city struct 
struct city{
	//string members and pointers to the next and previous city
	string name, message;
	city *next = NULL, *previous = NULL;
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

//class Network which contains the double linked list
class Network{
	private:
	//declaration of the head and tail city pointers
	city *head, *tail;
	
	public:
	//class constructor, head and tail default to null
	Network(){
		head = NULL;
		tail = NULL;
	}

	~Network(){
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
	void print(){
		if(DEBUG) cout<<endl<<"printing cities"<<endl;
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
		cout<<city1->getName()<<" recieved "<<city1->getMessage()<<endl;
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

	//add city1 after city2, check for tail
	void addCity(city *city1, city *city2){
		if(DEBUG) cout<<"adding city "<<city1->getName();
		if(city2 == tail){
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

	//add city1 to the beginning of the network
	void prependCity(city *city1){
		if(DEBUG) cout<<"prepending city"<<endl;
		city1->next = head;
		city1->previous = NULL;
		head->previous = city1;
		head = city1;
	}
};

//add 3 of the default cities to 'network'
void buildNetworkSmall(Network &network){
	city* phoenix = new city("Phoenix");
	city* denver = new city("Denver");
	city* dallas = new city("Dallas");

	network.insert(phoenix);
	network.insert(denver);
	network.insert(dallas);
}

//add all of the default cities to 'network'
void buildNetwork(Network &network){
	city* los_angeles = new city("Los Angeles");
	city* phoenix = new city("Phoenix");
	city* denver = new city("Denver");
	city* dallas = new city("Dallas");
	city* st_louis = new city("St. Louis");
	city* chicago = new city("Chicago");
	city* atlanta = new city("Atlanta");
	city* washington_dc = new city("Washington, D.C.");
	city* new_york = new city("New York");
	city* boston = new city("Boston");

	network.insert(los_angeles);
	network.insert(phoenix);
	network.insert(denver);
	network.insert(dallas);
	network.insert(st_louis);
	network.insert(chicago);
	network.insert(atlanta);
	network.insert(washington_dc);
	network.insert(new_york);
	network.insert(boston);
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

int main(){
	cout<<"PROGRAM START"<<endl<<endl;
	const string FILE = "messageToTransmit.txt";
	ifstream ifs;//initialization of inputfilestream
	Network network; //initialization of the Network class
	int option = 7;
	string str1, str2, str3;
	city *city1, *city2;
	do{
		str1 = "", str2 = "", str3 = "";
		city1 = NULL, city2 = NULL;
		printMenu();
		cin>>option;
		switch(option){
			case 1:
				buildNetwork(network);
				break;
			case 2:
				if(!DEBUG) network.print();
				if(DEBUG) network.printFull();
				break;
			case 3:
				cout<<endl<<"Enter city x"<<endl;
				getline(cin,str1);
				getline(cin,str1);
				cout<<"Enter city y"<<endl;
				getline(cin,str2);
				cout<<endl;
				city1 = network.getCity(str1);
				city2 = network.getCity(str2);
				ifs.open(FILE);//open file
				if(city1 == NULL || city2 == NULL){
					cout<<"both cities not found, exiting"<<endl<<endl;
					break;
				}
					//str3 = "Wrd";
				while(ifs.good()){
					//getline(ifs, str3, ' ');
					ifs>>str3;
					if(DEBUG) cout<<"message: "<<str3<<endl;
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
				getline(cin, str1);
				cout<<"Enter name of previous city:"<<endl;
				getline(cin, str2);
				city1 = new city(str1);
				if(str2 == "First"){
					cout<<"calling prependCity"<<endl;
					network.prependCity(city1);
					break;
				}
				network.addCity(city1,network.getCity(str2));
				cout<<endl;
				break;
			case 5:
				cout<<endl<<"Enter city name"<<endl;
				getline(cin,str1);
				getline(cin,str1);
				cout<<endl;
				network.deleteCity(network.getCity(str1));
				break;
			case 6:
				network.clearNetwork();
				break;
			case 7:
				cout<<"exiting"<<endl;
				break;
			default:
				cout<<"invalid option"<<endl;
		}
	}while(option != 7);
}
