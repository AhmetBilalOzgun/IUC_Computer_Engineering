#include <iostream>
#include <string>
using namespace std;
//creating a node structure
struct Node{
    int day;
    string priority, title, content;
    Node* next;
    Node* prev;
//constructor
    Node(int d) {
        day = d;
        title = "";
        content = "";
        priority = "";
        next = nullptr;
        prev = nullptr;
    }

};

//function to add nodes
void add_event(Node* head, int day){
    //get the properties of the event
    string title,content,priority;
    cout<<"Enter the title of the event:"<<endl;
    cin>>title;
    cout<<"Enter the content of the event:"<<endl;
    cin>>content;
    cout<<"Enter the priority of the event:"<<endl;
    cin>>priority;

    //find the day asked
    Node* current= head;
    while(current->day < day){
        current= current->next;
    }
    //if an event exists
    if(current->title != ""){
        cout<<"An event already exists on day "<<day<<endl;
        return;
    }
    //adding the properties to the node
    else{
        current->content=content;
        current->title=title;
        current->priority=priority;
    }
}

void modify_event(Node* head, int day){

    Node* current= head;
    while(current->day < day){
        current= current->next;
    }
    //if no event exists on that day
    if(current->title == ""){
        add_event(head,day);
    }

    else {
        //print the properties
        bool flag;
        cout<<"Information of the day "<<current->day<<endl;
        cout<<"Title:"<<current->title<<endl;
        cout<<"Content:"<<current->content<<endl;
        cout<<"Priority:"<<current->priority<<endl;
        cout<<"-------------------------"<<endl;
        cout<<"Do you want to modify?(0/1)"<<endl;
        cin>>flag;
        //modifying the node
        if (flag==true){
            string title,content,priority;
            cout<<"Enter new title:"<<endl;
            cin>>title;
            cout<<"Enter new content:"<<endl;
            cin>>content;
            cout<<"Enter new priority:"<<endl;
            cin>>priority;

            current->title=title;
            current->priority=priority;
            current->content=content;
        }
        else {
            return;
        }   
    }
}
//listing events
void list_event(Node* head, int day){
    bool submenu=true;
    string userInput;

    Node* current= head;    
    while(current->day < day){
        current= current->next;
    }

    //if there is no event
    while(submenu == true){
    if(current->title == ""){
        cout<<"The day "<<current-> day<<" has no event"<<endl;
    }

    //print if an event exists on that day
    else {
        cout<<"Information of the day "<<current->day<<endl;
        cout<<"Title:"<<current->title<<endl;
        cout<<"Content:"<<current->content<<endl;
        cout<<"Priority:"<<current->priority<<endl;
        cout<<"-------------------------"<<endl;
    }
    //for user to check nodes
    cout<<"(p)previous day, (n)next day, (q)back to menu"<<endl;
    cin>>userInput;

    if(userInput=="p"){
        current=current->prev;
    }
    else if(userInput=="n"){
        current=current->next;
    }
    else if(userInput=="q"){
        submenu=false;
    }
    else{
        cout<<"Please enter a valid key"<<endl;
    }
}
}
//to delete an event
void delete_event(Node* head, int day){

    Node* current= head;
    while(current->day < day){
        current= current->next;
    }
    if(current->title == ""){
        cout<<"This day already has no event"<<endl;
    }
    else {
        current->title="";
        current->content="";
        current->priority="";
        return;
    }

}


int main(){
    int day;
    int userInput;
    bool menu=true;
    //create the first node
    Node* head = new Node(1);
    Node* prevNode = head;

    //create the circular double linked list
    for(int i = 2; i<=30;i++){
        Node* newNode = new Node(i);
        prevNode->next = newNode;
        newNode->prev = prevNode; 
        prevNode = newNode;       
    }
    prevNode->next=head;
    head->prev = prevNode;

    //menu
    while(menu==true){
        int userInput;
        std::cout<< "========== Event Planner =========="<<std::endl;
        std::cout<< "1. Add Event"<<std::endl;
        std::cout<< "2. Modify Event"<<std::endl;
        std::cout<< "3. List Event"<<std::endl;
        std::cout<< "4. Delete Event"<<std::endl;
        std::cout<< "0. Quit"<<std::endl;
        std::cout<< ":";
        std::cin>>userInput;

        

        if(userInput == 1){
            cout<<"Enter the day of the event you want to work with:"<<endl;
            cin>>day;
            add_event(head,day);
        }
        else if(userInput==2){
            cout<<"Enter the day of the event you want to work with:"<<endl;
            cin>>day;
            modify_event(head,day);
        }
        else if(userInput==3){
            cout<<"Enter the day of the event you want to work with:"<<endl;
            cin>>day;
            list_event(head,day);
        }
        else if(userInput==4){
            cout<<"Enter the day of the event you want to work with:"<<endl;
            cin>>day;
            delete_event(head,day);
        }
        else if(userInput==0){
            menu=false;
        }
        else{
            cout<<"Please enter a valid number."<<endl;
        }
    }
}