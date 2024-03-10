// MUSTAFA BATIN EFE
#ifndef Board_h
#define Board_h
#include <string>

using namespace std;

struct Node {
    string owner;
    Node* next;
    Node ();
    Node (string o, Node * p);
};

class Board
{
private:
    Node *first;
public:
    Board(int number_of_slots); // Constructor with given slot number
    ~Board(); // De-constructor for board object

    void display(); // Print the board
    string who_owns(Node* ss); // Check who owns given node
    Node * getFirst(); // Access private member (first) and return
};

#endif /* Board_h */
