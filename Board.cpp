// MUSTAFA BATIN EFE
#include "Board.h"
#include <iostream>

using namespace std;

/* Following constructor will create a board */
Board::Board(int number_of_slots){
    first = nullptr;
    Node* start = first;
    Node* ptr;

    // If there are more than 1 slot going to be created
    if(number_of_slots >= 1){
        start = new Node("None", nullptr); // Create first one
        ptr = start; // Set as a start
        for(int m = 1; m < number_of_slots; m++){ // Iterate through number of slots
            ptr->next = new Node("None" , nullptr);
            ptr = ptr->next;
        }
    }
    ptr->next = start; // Connect to start node
    first = start; // Set first as start node
}

/* Following de-constructor will delete every board node */
Board::~Board(){
    Node* begin = first;
    Node* ptr = first;
    while(ptr->next != begin){
        ptr = ptr->next;
        delete ptr;
    }
    delete begin; // Delete first one in the end
}

/* Following member function will print the board with manipulation */
void Board::display() {
    Node * ptr = first;
    Node * stand = first;

    /* STEP 1: Print the owners of shared board*/
    if(stand->owner != "None"){
        cout << stand->owner << " ";
    } else{
        cout << stand->owner;
    }
    if(stand->next != stand){
        cout << "->";
    }

    ptr = ptr->next;
    while(ptr != first){
        if(ptr->owner != "None"){
            cout << ptr->owner << " ";
        } else{
            cout << ptr->owner;
        }
        if(ptr->next != stand){
            cout << "->";
        }
        ptr = ptr->next;
    }

    /* STEP 2 : Show start point and end point */
    cout << endl << "^";
    Node * ptrLast = first->next;
    int countS = 2;
    // Find number of element in board
    while(first != ptrLast->next){
        ptrLast = ptrLast->next;
        countS++;
    }

    for(int y = 0; y < countS * 6 - 4; y++ ){ // This Math expression sets number of space for given countS
        cout<<" ";
    }
    cout <<"|" <<endl;

    /* STEP 3 : Print the base of board */
    cout << "|----";
    for(int y = 0; y < countS-2; y++ ){
        cout<<"<-----";
    }
    cout << "<---v" << endl;

}

/* Following member function will return the owner of that board */
string Board::who_owns(Node *ss) {
    Node * ptr = first;
    while (ptr != ss){ // If given ss is not first one, go next
        ptr = ptr->next;
    }
    return ptr->owner; // return the owner of that board
}

/* Following member function will return private member of Board */
Node *Board::getFirst() {
    return first;
}

/* Following will initialize the owner and next */
Node::Node(string o, Node *p): owner(o), next(p) {}

