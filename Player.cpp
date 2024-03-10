// MUSTAFA BATIN EFE
#include "Player.h"
#include "Board.h"
#include <iostream>

/* Following constructor will create a player on given board */
Player::Player(Board & sharedBoard, const string &name, int &balance) : pName(name), balance(balance), myBoard(sharedBoard)
{
    Node * ptrFirst = myBoard.getFirst(); // Get first of the shared board
    position = ptrFirst; // set players' first position on board
}

/* Following member function will move the player on the board with given steps */
int Player::move(int steps) {
    Node * ptrFirst = myBoard.getFirst(); // Get first node of board
    Node * temp = this->position; // See position of player
    bool flag = false; // If we pass start point

    /* If player is in the position just before first node of board */
    if(temp->next == ptrFirst){ // If next is first board node, we will return 1
       flag = true;
    }

    /* Continue to moving stage */
    temp = temp->next;
    for(int m = 1; m < steps; m++){ // Go through number of steps
        if(temp->next != ptrFirst){
            //If there is not only one board member, and position not in first
            temp = temp->next;
        }
        else{
            // If he passed initial point or stopped by
            temp = temp->next;
            flag = true;
        }
    }
    this->position = temp; // Set the position of player
    if(flag == true){
        return 1;
    } else {
        return 0;
    }
}

/* Following member function will return the players' position on sharedBoard */
Node *Player::where_am_I() {
    Node * ptrFirst = myBoard.getFirst(); // get first node of board
    Node * ptrFollow = this->position; // get player's position

    while(ptrFirst != ptrFollow){ // find players' position
        ptrFirst = ptrFirst->next;
    }
    return ptrFirst; // return position of player
}

/* Following member function will pay money from this' balance to otherPlayer */
void Player::pay_to_player(Player &otherPlayer, int money) {
    this->balance = this->balance - money; // Remove from THIS PLAYER
    otherPlayer.balance = otherPlayer.balance + money; // Pay to otherPlayer

}

/* Following member function will return the balance of THIS PLAYER */
int Player::get_balance() {
    return this->balance;
}

/* Following member function will deposit addMoney to THIS PLAYER'S balance*/
void Player::deposit_money(int addMoney) {
    this->balance = this->balance + addMoney; // add to THIS PLAYER
}

/* Following member function will secure the board place for THIS PLAYER
 * and decrease slotPrice from its balance*/
void Player::buy_slot(int slotPrice) {
    this->balance = this->balance - slotPrice; // Decrease players' balance (slotPrice)
    Node * ptrFirst = myBoard.getFirst();
    Node * placedTemp = this->position;

    while(ptrFirst != placedTemp){ // Go till you find which slot player is
        ptrFirst = ptrFirst->next;
    }
    ptrFirst->owner = this->pName; // Also change owner of that board slot
}

/* Following member function will check if THIS BALANCE is negative */
bool Player::is_bankrupt() {

    if(this->balance <= 0){
        return true; // true if THIS PLAYER is bankrupt
    }else {
        return false; // false if not bankrupt
    }
}

/* Following member function will print THIS PLAYER's last location
 * as well as its name and balance */
void Player::display() {
    Node * ptrFirst = myBoard.getFirst();
    Node * ptrPos = this->where_am_I();

    /* To find number of element between player and first node of board */
    int findInd = 0;
    while (ptrFirst != ptrPos){
        ptrFirst = ptrFirst->next;
        findInd++;
    }
    // Print space for that distance
    for (int m = 0; m < findInd; m++){
        cout << "      ";
    }
    cout << this->pName << " " << this->balance << endl;

}


