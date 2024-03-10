#include <iostream>
#include "Board.h"
#include "Player.h"
using namespace std;

int mypower(int a, int b, int m)
{
    int res = 1;
    a = a % m;
    for(int i=1 ; i<=b ; ++i)
        res = (res * a) % m;
    return res;
}

int  rand_CS(int seed)
{
    static int recurseed = seed;
    int randnum = mypower (393, recurseed, 15307) % 6 +1;
    recurseed = recurseed*2 % 15307;
    return randnum;
}


int main() {

    //************************************************** Initial Inputs ***********************************************//

    int maximum_number_of_rounds = 5;
    cout << "Please enter the maximum number of rounds(>0): "<< endl;  cin >> maximum_number_of_rounds;
    if(maximum_number_of_rounds<=0){cout<<"Maximum number of rounds has to be >0. Terminating program"<<endl; return 1;}

    int initial_balance = 1000; // initial capital to be deposited to both players at the beginning of the game
    cout << "Please enter the starting capital(>0): "<< endl;  cin >> initial_balance;
    if(initial_balance<=0){cout<<"Initial capital has to be >0. Terminating program"<<endl; return 1;}

    int passing_starting_slot_deposit = 100; // a deposit that is added to any player's balance when he/she passes by or land on the starting slot during the game.
    cout << "Please enter the passing starting slot deposit(>0): "<< endl;  cin >> passing_starting_slot_deposit;
    if(passing_starting_slot_deposit<=0){cout<<"The passing starting slot deposit has to be >0. Terminating program"<<endl; return 1;}

    int slot_price = 100; // unique price for every slot
    cout << "Please enter the slot price(>0): "<< endl;  cin >> slot_price;
    if(slot_price<=0){cout<<"Slot price has to be >0. Terminating program"<<endl; return 1;}

    int number_of_slots = 6;  // number of slots to be inserted in the circular linked list (6 is the minimum number)
    cout << "Please enter the number of slots(>=6): "<< endl; cin >> number_of_slots;
    if (number_of_slots<6){cout<<"Number of slots has to be >=6. Terminating program"<<endl; return 1;}

    int seed = 1;
    cout << "Please enter the seed for the random number generation (>0): "<<endl; cin >> seed;
    if (seed<=0){cout<<"Seed has to be >0. Terminating program"<<endl; return 1;}


    //****************************************** Creating the Board (circular linked list) ****************************//

    Board board(number_of_slots);// Create a board (circular linked list) with 'number_of_slots' nodes

    //****************************************** Creating two players objects *****************************************//

    Player p1(board,"Ali",initial_balance), p2 (board,"Liz", initial_balance);

    char answer;
    int moves, n = 0;

    while ( ( p1.get_balance()>=0 && p2.get_balance()>=0 ) && n<maximum_number_of_rounds )
    {
        //******************************************  Ali's turn ******************************************************//

        cout << endl;
        cout << "******************************** Ali's turn **********************";
        cout << endl;

        moves=rand_CS(seed);
        cout<< "[Ali] You are going to move "<< moves<<" move(s)."<<endl;
        if(p1.move(moves)==1) // it means that the player has passed by the initial starting slot, so he/she deserves a deposit (the new_round_deposit)
        {
            cout << "[Ali] You passed by (or landed on) the starting slot. "<< passing_starting_slot_deposit <<" will be deposited to your balance."<<endl;
            p1.deposit_money(passing_starting_slot_deposit);
        }

        Node * t = p1.where_am_I(); // (check who owns it)
        if(board.who_owns(t) == "Ali")
        {
            cout<<"[Ali] You stepped on your own slot."<<endl;
        }
        else if(board.who_owns(t) == "Liz")
        {
            cout<< "[Ali] You stepped on one of Liz's slots, you will pay " << slot_price/2 <<"."<<endl;
            p1.pay_to_player(p2,slot_price/2);
        }
        else // None (unclaimed slot)
        {
            cout<< "[Ali] You stepped on an unclaimed slot, do you want to buy it? (Y/N) "<<endl;
            cin>>answer;
            if (answer=='Y')
            {
                if (p1.get_balance()>=slot_price)
                {
                    p1.buy_slot(slot_price);
                    cout << "[Ali] The slot has been sold to you." << endl;
                }
                else
                {
                    cout<< "[Ali] Sorry, you don't have enough balance to buy this slot."<<endl;
                }
            }
            else if (answer=='N')
            {
                cout<< "[Ali] You didn't buy this slot."<<endl;
            }
        }

        //******************************************  Liz's turn ******************************************************//

        cout << endl;
        cout << "******************************** Liz's turn **********************";
        cout << endl;

        moves=rand_CS(seed);
        cout<< "[Liz] You are going to move "<< moves<<" move(s)."<<endl;
        if(p2.move(moves)==1) // it means that the player has passed by the initial starting slot, so he/she deserves a deposit (the passing_starting_slot_deposit)
        {
            cout << "[Liz] You passed by (or landed on) the starting slot. "<< passing_starting_slot_deposit <<" will be deposited to your balance."<<endl;
            p2.deposit_money(passing_starting_slot_deposit);
        }

        Node * t2 = p2.where_am_I(); // (check who owns it)
        if(board.who_owns(t2) == "Liz")
        {
            cout<<"[Liz] You stepped on your own slot."<<endl;
        }
        else if(board.who_owns(t2) == "Ali")
        {
            cout<< "[Liz] You stepped on one of Ali's slots, you will pay " << slot_price/2 <<"."<<endl;
            p2.pay_to_player(p1,slot_price/2);
        }
        else // None (unclaimed slot)
        {
            cout<< "[Liz] You stepped on an unclaimed slot, do you want to buy it? (Y/N) "<<endl;
            cin>>answer;
            if (answer=='Y')
            {
                if (p2.get_balance() >= slot_price)
                {
                    p2.buy_slot(slot_price);
                    cout << "[Liz] The slot has been sold to you." << endl;
                }
                else
                {
                    cout<< "[Liz] Sorry, you don't have enough balance to buy this slot."<<endl;
                }
            }
            else if (answer=='N')
            {
                cout<< "[Liz] You didn't buy this slot."<<endl;
            }
        }

        cout << endl;
        p1.display();
        p2.display();
        board.display();
        cout << endl;
        n++;
    }

    cout << "The game came to an end."<<endl;
    //  display balances
    cout<<"Ali's balance is: "<<p1.get_balance()<<endl;
    cout<<"Liz's balance is: "<<p2.get_balance()<<endl;

    if (p1.is_bankrupt() && !p2.is_bankrupt()) // (Sample Run #5 (Ali’s bankrupt))
    {
        cout << "Liz won."<<endl;
    }
    else if (!p1.is_bankrupt() && p2.is_bankrupt())// (Sample Run #4 (Liz’s bankrupt))
    {
        cout << "Ali won."<<endl;
    }
    else
    {
        if (p1.get_balance() > p2.get_balance())  // (Sample Run #3 (reached max. no. of rounds and Ali won))
        {
            cout << "Ali won."<<endl;
        }
        else if (p2.get_balance() > p1.get_balance())// (Sample Run #2 (reached max. no. of rounds and Liz won))
        {
            cout << "Liz won."<<endl;
        }
        else // (Sample Run #1 (reached max. no. of rounds and tie))
        {
            cout << "Tie."<<endl;
        }
    }

    return 0;
}