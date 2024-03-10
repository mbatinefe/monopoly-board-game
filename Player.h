// MUSTAFA BATIN EFE
#ifndef THE5_PLAYER_H
#define THE5_PLAYER_H
#include "Board.h"

class Player
{
private:
    Node *position;
    int balance;
    string pName;
    Board & myBoard;
public:

    Player (Board & sharedBoard, const string & name, int & balance ); // Construct a player with sharedBoard

    int move(int steps); // Move the player on sharedBoard
    Node* where_am_I(); // Tell the player where its on the Board
    void pay_to_player(Player& otherPlayer, int money); // Pay money to otherPlayer from this
    int get_balance(); // Learn balance of the player
    void deposit_money(int addMoney); // Deposit addMoney to asked player
    void buy_slot(int slotPrice); // Buy slot with slotPrice, make necessary changes on Board and Player
    bool is_bankrupt(); // Check if the money of the player is negative
    void display(); // Print the players information

};
#endif //THE5_PLAYER_H
