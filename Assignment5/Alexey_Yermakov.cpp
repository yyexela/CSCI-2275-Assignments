/*
 * Alexey Yermakov
 * CSCI 2275
 * Assignment 5
 * October 18, 2019
 */


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
	int queueFront, queueRear, queue_size;
	string *arrayQueue;
	
	public:
	//class constructor, head and tail default to null
	CommunicationNetwork(){
		//queue initialization
		queue_size = 10;
		arrayQueue = new string[queue_size];
		queueFront = -1;
		queueRear = -1;
		//linked list initialization
		head = NULL;
		tail = NULL;
	}

	//destructor, removes the cities and queue
	~CommunicationNetwork(){
		cout<<"Removing queue"<<endl;
		delete[]arrayQueue;
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

	//remove the front of the queue if it exists and send it as a message
	void dequeue(){
		cout<<endl;
		string str3 = peekQueue();
		city *city1 = NULL, *city2 = NULL;
		//if the front of the queue isn't valid, return
		if(str3 == ""){
			return;
		}
		//see if Boston and Los Angeles exist
		city1 = getCity("Boston");
		city2 = getCity("Los Angeles");
		if(city1 == NULL || city2 == NULL){
			cout<<"at least one city not found, exiting"<<endl;
			return;
		}
		//Send the message from Boston to L.A.
		if(DEBUG) cout<<"message: "<<str3<<endl;
		cout<<city1->getName()<<" recieved "<<str3<<endl;
		sendMessage(city1, city2, str3);
		if(DEBUG) printFull();
		sendMessage(city2, city1, str3);
		cout<<endl;
		//Move queue after the message is sent
		++queueFront;
		//Check if there is another element in the queue to send
		if(queueFront > queueRear){
			if(DEBUG) cout<<"reset queueFront"<<endl;
			queueFront = queueRear = -1;
		}
		//print queueFront and queueRear
		cout<<"queueFront: "<<queueFront<<endl;
		cout<<"queueRear: "<<queueRear<<endl;
	}

	//Continuously call dequeue() until the queue is empty
	void emptyQueue(){
		city *city1 = NULL, *city2 = NULL;
		city1 = getCity("Boston");
		city2 = getCity("Los Angeles");
		if(city1 == NULL || city2 == NULL){
			cout<<"at least one city not found, exiting"<<endl;
			return;
		}
		while(queueFront != queueRear){
			dequeue();
		}
		dequeue();
	}

	//returns empty string if underflow, otherwise the front of the queue
	string peekQueue(){
		if(queueFront > queueRear || queueFront == -1){
			cout<<"Queue Underflow"<<endl;
			return "";
		} else {
			string top = arrayQueue[queueFront];
			if(DEBUG) cout<<"Peeked Word:"<<top<<"|"<<endl;
			return top;
		}
	}

	void enqueue(string word){
		if(DEBUG) cout<<"called enqueue"<<endl;
		//check if array is empty
		if(queueFront = -1){
			++queueFront;
		}
		++queueRear;
		//double array if it's not large enough
		if(queueRear >= queue_size)
			doubleArray();
		arrayQueue[queueRear] = word;
		cout<<"Enqueued: "<<word<<endl;
		cout<<"queueFront: "<<queueFront<<endl;
		cout<<"queueRear: "<<queueRear<<endl;
	}


	//Double the size of the array arrayQueue
	void doubleArray(){
		if(DEBUG) cout<<"Doubling Array Size from "<<queue_size<<" to "<<queue_size * 2<<endl;
		//create a temporary array twice the size of the original
		string *temp = new string[queue_size * 2];
		//fill the temporary array with the original array
		for(int i = 0; i < queue_size; i++){
			temp[i] = arrayQueue[i];
		}
		//delete the original array
		delete[]arrayQueue;
		//point the original array to the temp array, which is twice the size
		arrayQueue = temp;
		//update queue_size to the new array size
		queue_size *= 2;
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
	cout<<"3. Enqueue"<<endl;
	cout<<"4. Dequeue"<<endl;
	cout<<"5. Peek"<<endl;
	cout<<"6. Empty Queue"<<endl;
	cout<<"7. Quit program"<<endl;
}

//filter user input to int
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

//Return the number of words in the line (a word is separated by spaces)
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

//put words in each element of stringwords[] from the input string line
void makeStrArr(string line, string words[]){
	if(DEBUG) cout<<"called makeStrArr"<<endl;
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
		if(DEBUG) cout<<"adding "<<line.substr(index1, index2-index1)<<endl;
		words[i] = line.substr(index1, index2-index1);
		index1 = index2 + 1;
		index2 = line.find(' ', index1);
	}
	if(DEBUG) cout<<"adding "<<line.substr(lastIndex + 1)<<endl;
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
	ifs.close();
	//number of words to add
	int numWords = wordCount(line);
	//make words[] which contains words of the input file
	string words[numWords];
	makeStrArr(line, words);
	CommunicationNetwork network; //initialization of the CommunicationNetwork class
	int count = 0; //number of words enqueued
	string str1, option;
	do{
		str1 = option = "";
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
				//print network
				if(!DEBUG) network.printNetwork();
				if(DEBUG) network.printFull();
				break;
			case 3:
				cout<<endl;
				//cout<<"adding word, count: "<<count<<" total: "<<numWords<<endl;
				if(count >= numWords)
					cout<<"No more words to enqueue"<<endl;
				else
					network.enqueue(words[count++]);
				cout<<endl;
				break;
			case 4:
				//call dequeue()
				network.dequeue();
				cout<<endl;
				break;
			case 5:
				//call peekQueue()
				cout<<endl;
				str1 = network.peekQueue();
				if(str1 != "")
					cout<<"Peeked Word: "<<str1<<endl;
				cout<<endl;
				break;
			case 6:
				//call emptyQueue()
				cout<<endl;
				network.emptyQueue();
				cout<<endl;
				break;
			case 7:
				cout<<endl<<"Goodbye!"<<endl;
				break;
			default:
				cout<<endl<<"invalid option, choose a number between 1 and 7"<<endl<<endl;
		}
	}while(stoi(option) != 7);
}
