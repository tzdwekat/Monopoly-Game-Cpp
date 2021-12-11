#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <array>
#include <random>
#include "macros.h"
#include "functions.h"
#include "globals.h"
#include "objects.h"
#include <iterator>

using namespace std;
list<string> players_ll; //linked list of player names
int endgame = 0;
int seed;
char move;
int playerCount;
list<Player> playerList;
int state = 0;
bool turnFlg = 0;
int dice[2] = {0, 0};
string decision;
string exit_decision;
void* Board[40];


int main() {
//--------------------------------------------------------------------------------------------------//
//----------------------------------------Basic Starting Menu---------------------------------------//

    //-------------------------------------Player Name Input----------------------------------------//
    string input;
    chanceDeck myDeck;


    cout << "                  MONOPOlY\n" << "Enter seed number:\n";
    cin >> seed;
    cout << "2-8 players\n"
         << "Once all names are entered, type 'start' to begin.\n"
         << "Enter names below:\n";

    while (true) {
        while (input != "start") {
            cin >> input;
            if (playerCount > 7) cout << "Too many players! Please begin game.\n";
            else if (input != "start") {
                playerCount++;
                players_ll.push_back(input);
            }
        }
        input.clear();
        if (playerCount < 2) cout << "Too few players! Add more players before starting:\n";
        else break;
    }

    //----------------------------------Player Order Shuffle---------------------------------------//
    auto it = players_ll.cbegin();
    string players_arr[playerCount];
    for (int i = 0; i < playerCount; i++) {
        players_arr[i] = *it++;
    }

    shuffle(players_arr, players_arr + playerCount, default_random_engine(seed));

    cout << "Awesome! Before we begin, here is the order you will play in:\n";
    for (int i = 0; i < playerCount; i++) {
        cout << i << ": " << players_arr[i] << " -- $1,500" << endl;
    }

    cout << "As you can see, all of you have $1,500. Try not to lose it.\n";

    cout << "Enjoy!\n";
    for (int i = 0; i < playerCount; i++) {
        Player play1(players_arr[i], i);
        play1.jailStatus = false;
        playerList.push_back(play1);
    }
//------------------------------------------------------------------------------------------------//
//--------------------------------------Initialize Board Squares----------------------------------//

    Board[0] = new goSquare(200, "Go", 0);
    Board[1] = new propertySquare(1, "MEDITERRANEAN_AVENUE", 0, "brown", 60);
    Board[2] = new Chance;
    Board[3] = new propertySquare(3, "BALTIC_AVENUE", 1, "brown", 60);
    Board[4] = new taxSquare(200, "Tax", 5);
    Board[5] = new propertySquare(5, "READING_RAILROAD", 0, "black", 200);
    Board[6] = new propertySquare(6, "ORIENTAL_AVENUE", 0, "light_blue", 100);
    Board[7] = new Chance;
    Board[8] = new propertySquare(8, "VERMONT_AVENUE", 1, "light_blue", 100);
    Board[9] = new propertySquare(9, "CONNECTICUT_AVENUE", 2, "light_blue", 120);
    //Board[10] = new justVisitingSquare();
    Board[11] = new propertySquare(11, "ST.CHARLES_PLACE", 0, "pink", 140);
    Board[12] = new propertySquare(12, "ELECTRIC_COMPANY", 0, "white", 140);
    Board[13] = new propertySquare(13, "STATES_AVENUE", 1, "pink", 140);
    Board[14] = new propertySquare(14, "VIRGINIA_AVENUE", 2, "pink", 160);
    Board[15] = new propertySquare(15, "PENNSYLVANIA_RAILROAD", 1, "black", 200);
    Board[16] = new propertySquare(16, "ST.JAMES_PLACE", 0, "orange", 180);
    Board[17] = new Chance;
    Board[18] = new propertySquare(18, "TENNESSEE_AVENUE", 1, "orange", 180);
    Board[19] = new propertySquare(18, "NEWYORK_AVENUE", 2, "orange", 200);
    Board[20] = new freeParking;
    Board[21] = new propertySquare(20, "KENTUCKY_AVENUE", 0, "red", 220);
    Board[22] = new Chance;
    Board[23] = new propertySquare(23, "INDIAN_AVENUE", 1, "red", 220);
    Board[23] = new propertySquare(24, "ILLINOIS_AVENUE", 2, "red", 240);
    Board[25] = new propertySquare(25, "B.&O._RAILROAD", 2, "black", 200);
    Board[26] = new propertySquare(26,"ATLANTIC_AVENUE", 0, "yellow", 260);
    Board[27] = new propertySquare(27, "VENTNOR_AVENUE", 1, "yellow", 260);
    Board[28] = new propertySquare(28, "WATER_WORKS", 1, "white", 150);
    Board[29] = new propertySquare(29, "MARVIN_GARDENS", 2, "yellow", 280);
    Board[30] = new goToJailSquare(-1, "Got to Jail", 10);
    Board[31] = new propertySquare(31, "PACIFIC_AVENUE", 0, "green", 300);
    Board[32] = new propertySquare(32, "NORTH_CAROLINA_AVENUE", 1, "green", 300);
    Board[33] = new Chance;
    Board[34] = new propertySquare(34, "PENNSYLVANIA_AVENUE", 2, "green", 300);
    Board[35] = new propertySquare(35, "SHORT_LINE", 4, "black", 320);
    Board[36] = new Chance;
    Board[37] = new propertySquare(37, "PARK_PLACE", 0, "blue", 350);
    Board[38] = new taxSquare(100, "Luxury Tax", 38);
    Board[39] = new propertySquare(39, "BOARDWALK", 1, "blue", 400);

    // DECIPHERING BOARD ARRAY EXAMPLE:  cout << (*((goSquare *) Board[0])).money;
    //cout << (*((goSquare *) Board[0])).money;
    //cout << (*((propertySquare *) Board[9])).property.getValue();

//------------------------------------------------------------------------------------------------//
//--------------------------------------Game Operating System-------------------------------------//

    cout << "\n\nSTARTED GAME \n";
    cout << "press \"next\" to start turn.\n";
    while (true) {
        string command;
        cin >> command;

        if (command == "next") {
            state += 1;
            cout << "\nTURN " << state << "\n";
        }

        if (command == "show") {
            list<Player>::iterator iter;
            for (iter = playerList.begin(); iter != playerList.end(); ++iter) {
                iter->Check_Status();
                cout << "\n";
            }
        }

        if ((command == "quit") || (command == "q")) {
            cout << "Thanks for playing!";
            break;
        }

        // Check for Bankruptcy and End Game
        list<Player>::iterator iter_endgame;
        for (iter_endgame = playerList.begin(); iter_endgame != playerList.end(); ++iter_endgame) {
            iter_endgame->Is_Bankrupt();
            if (iter_endgame->bankruptcyStatus) {
                endgame = 1;
            }
        }

        if (endgame == 1) {
            cout << "END GAME\n";
            cout << "The winner is: \n";

            break;
        }


        if (command == "next") {

            list<Player>::iterator iter;
            for (iter = playerList.begin(); iter != playerList.end(); ++iter) {
                while(exit_decision != "no") {
                    cout << iter->name << " ,what action would you like to take?\n";
                    cin >> decision;

                    if (decision == "sell") {
                        /*
                         1. Your options to sell are: [DISPLAY OWNED PROPERTIES]
                         2. Pick property to sell:
                         3. IMPLEMENT SELLING PICKED PROPERTY
                         */
                        string propSell;
                        cout << "Your options to sell are: ";
                        iter->Check_Properties();
                        cout << "Which property to sell: ";
                        cin >> propSell;

                        iter->sellProperty(propSell);
                        cout << "\nProperty Sold!\n";

                        cout << "\nWant to take another action?\n";
                        cin >> exit_decision;
                    }
                    if (decision == "trade") {
                        string tradePartner;
                        double tradeAmount;
                        string tradeProperty;
                        string trade;
                        string agreement;
                        /*
                         1. What Player to Trade with?
                         2. Manually add or remove properties/money from both players through commands
                         */
                        cout << "Choose a player to trade with: ";
                        cin >> tradePartner;
                        cout << "\nChoose a positive monetary value to offer money and negative to request money: ";
                        cin >> tradeAmount;
                        cout << "\nChoose a property to trade: ";
                        cin >> tradeProperty;
                        cout << "\nWould you like to buy or sell this property? "; // ONLY OPTIONS SHOULD BE "BUY" OR "SELL"
                        cin >> trade;
                        cout << "\nDid the other player agree to your offer? ";
                        cin >> agreement;

                        if ((agreement == "no") || (agreement == "No")) {
                            // Do Nothing
                        }
                        else {
                            list<Player>::iterator iterator;
                            for (iterator = playerList.begin(); iterator != playerList.end(); ++iterator) {
                                if (iterator->name == tradePartner) {
                                    iter->payPlayer(*iterator, tradeAmount);
                                    iter->transferProperty(*iterator, tradeProperty, trade);
                                    cout << "\nTrade has been completed!\n";
                                }
                            }
                        }
                        cout << "Want to take another action?\n";
                        cin >> exit_decision;
                    }
                    if (iter->jailStatus) { // If in Jail then...
                        if (decision == "roll") {
                            cout << "\nYou cannot roll while in jail, please choose another option.\n";
                        }
                        if (decision == "pay_jail") {
                            /*
                             1. remove $50 from player's account
                             2. Roll dice for player to get to new index
                             */
                            iter->wallet -= 50;
                            iter->jailStatus = false;

                            cout << "Want to take another action?\n";
                            cin >> exit_decision;
                        }
                    }
                    else{ // Ensures that player can't roll while in jail
                        if (decision == "roll") {
                            dice[0] = 1 + (rand() % 6);
                            dice[1] = 1 + (rand() % 6);
                            iter->move_forward(dice[0] + dice[1]);
                            cout << "You are at position index " << iter->position << "\n";
                            cout << "Want to take another action?\n";
                            cin >> exit_decision;
                        }
                    }

                }
                exit_decision = " ";
            }
            cout << "\nEnter \"next\" for next turn.\n";
            cout << "      \"quit\" to exit the game.\n";
            cout << "      \"show\" to show players' info.\n";
        }

    }

//------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------//

        return 0;
}