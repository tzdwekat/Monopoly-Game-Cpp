/*
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
int endgame = 0;
void runGame() {
    while (runstate == 1) {
        list <Player> :: iterator iter1;
        for(iter1 = playerList.begin(); iter1 != playerList.end(); ++iter1) {
            iter1->Check_Status();
            // if (Player.Location == Go) {
            // cout << "1. Roll Dice (R)"
            // cin << move;
            // if (move == r) {rollDice();}
            //}
            // else if (in_jail == True) {
            // cout << "1. Roll Dice (R)" << "\n" << "2. Get out of Jail (J)" << "\n";
            // cin << move;
            //  if (move == r) {rollDice()};
            //  elseif (move == j) {cout << "
        }


        // Check for Bankruptcy and End Game
        list <Player> :: iterator iter;
        for(iter = playerList.begin(); iter != playerList.end(); ++iter) {
            if (iter->bankruptcyStatus == 1) {
                endgame = 1;
                break;
            }
        }
        if (endgame == 1) {
            break;
        }
    }
}



Player play1("fares", 1);
Property house(1, 2, 5000, "Blue House");
Property villa(2, 2, 60000, "Big House");
play1.addProperty(house);
play1.addProperty(villa);
play1.Check_Status();
play1.chargeMoney(3000);
cout << play1.bankruptcyStatus;
cout << "\n";
 */
