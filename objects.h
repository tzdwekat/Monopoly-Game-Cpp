#ifndef MONOPOLY_CPP_OBJECTS_H
#define MONOPOLY_CPP_OBJECTS_H

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

class Property {
public:
    int id; //Unique ID of the property
    std::string color; //What color it has
    int value; //Its value according to the bank
    std::string name; //Name of the property

public:
    Property() { //default constructor
        id = 0;
        color = "none";
        value = 0;
        name = "No name";
    }
    Property(int ID, std::string col, int val, std::string nam) { //parameterized constructor
        id = ID;
        color = col;
        value = val;
        name = nam;
    }
    Property operator = (const Property & other) { //= operator overload
        id = other.id;
        color = other.color;
        value = other.value;
        name = other.name;
        return *this;
    }
    std::string getName() {
        return name;
    }

    int getValue() {
        return value;
    }
};

class Player {
public:
    string name; // Name of player
    int playerNumber; // Player identification number
    int position; // Position of player on the board
    double wallet; // Amount of money player has
    list<Property> ownedProperties; // List of properties that the player own
public:
    Player(string nam, int num, int pos = 0, double money = 1500) {
        name = nam;
        playerNumber = num;
        position = pos;
        wallet = money;
    }
    bool jailStatus; // Whether player is in jail
    bool outJailCard; // Whether the player has the "Get out of jail free" card
    bool bankruptcyStatus = false; // Whether player is bankrupt

    void Check_Status(void) {
        cout << "Player Name: " << name << "\n";
        cout << "Player ID: " << playerNumber << "\n";
        cout << "Player Position: " << position << "\n";
        cout << "Wallet Amount: " << wallet << "\n";
        cout << "Properties Held: ";
        list <Property> :: iterator it;
        for(it = ownedProperties.begin(); it != ownedProperties.end(); ++it)
            cout << '\t' << it->getName();
        cout << '\n';
    }

    void Check_Properties(void) {
        list <Property> :: iterator it;
        for(it = ownedProperties.begin(); it != ownedProperties.end(); ++it)
            cout << '\t' << it->getName();
        cout << '\n';
    }


    void Is_Bankrupt (void) {
        double totalVal = 0;
        list <Property> :: iterator it;
        for(it = ownedProperties.begin(); it != ownedProperties.end(); ++it) {
            totalVal = totalVal + (double)it->getValue();
        }
        totalVal = totalVal + wallet;
        if (totalVal < 0) {
            bankruptcyStatus = true;
        }
    }


    void move_back(int n) { //this function will move a player back with loopback
        if (position - n >= 0) position -= n;
        else position = (position - n) % 40;
    }

    void move_forward(int n) { //this function will move a player forward with loopback
        if (position + n < 40) position += n;
        else position = (position + n) % 40;
    }

    void addProperty(Property house) {
        ownedProperties.push_back(house);
    }

    void chargeMoney(double charge) {
        wallet -= charge;
    }

    void sellProperty(string Prop) {
        for (auto itr = ownedProperties.begin(); itr != ownedProperties.end(); itr++) {
            if (itr->name == Prop) {
                ownedProperties.erase(itr);
                wallet += itr->value;
            }
        }
    }
    void addMoney(double add) {
        wallet += add;
    }

    void goToJail(void) {
        jailStatus = true;
        position = 10;
    }

    void payPlayer (Player other, double sum) {
        wallet -= sum;
        other.wallet += sum;
    }

    void transferProperty(Player other, string prop, string transaction) {
        if (transaction == "buy") {
            for (auto itr = other.ownedProperties.begin(); itr != other.ownedProperties.end(); itr++) {
                if (itr->name == prop) {
                    ownedProperties.push_back(*itr);
                    other.ownedProperties.erase(itr);
                }
            }
        }
        if (transaction == "sell") {
            for (auto itr = other.ownedProperties.begin(); itr != other.ownedProperties.end(); itr++) {
                if (itr->name == prop) {
                    other.ownedProperties.push_back(*itr);
                    ownedProperties.erase(itr);
                }
            }
        }
    }
};

class Chance {
public:
    std::string Name; // Name of chance card
    int index;
public:
    Chance() {
        Name = "No name";
        index = 0;
    }

    Chance(int Num) { //parameterized constructor
        index = Num;
    }
    Chance operator = (const Chance & other) { //= operator overload
        Name = other.Name;
        index = other.index;
        return *this;
    }
    std::string getName() {
        return Name;
    }

    int getIndex() {
        return index;
    }
};

class chanceDeck {
private:
    list <Chance> deck;
public:
    chanceDeck() {
        int indexArr[10] = {0,1,2,3,4,5,6,7,8,9};
        shuffle(indexArr, indexArr + 10, default_random_engine(1 + (rand() % 10)));

        for (int i = 0; i < 10; i++) {
            Chance card (indexArr[i]);
            deck.push_back(card);
        }
        //auto it = deck.begin();
        list<Chance>::iterator it;
        for (it = deck.begin(); it != deck.end(); ++it) {
            switch (it->index) {
                case 0: {
                    it->Name = "Get Out of Jail Free Card";
                    break;
                }
                case 1: {
                    it->Name = "Go Back 3 Spaces";
                    break;
                }
                case 2: {
                    it->Name = "Go to Jail. Do Not Collect $200";
                    break;
                }
                case 3: {
                    it->Name = "Pay each player $50";
                    break;
                }
                case 4: {
                    it->Name = "Advance to GO. Collect $200";
                    break;
                }
                case 5: {
                    it->Name = "Dividend From Bank! Collect $200";
                    break;
                }
                case 6: {
                    it->Name = "Move forward 3 spaces";
                    break;
                }
                case 7: {
                    it->Name = "Collect $200 From Bank!";
                    break;
                }
                case 8: {
                    it->Name = "Speeding Ticket! Pay $50";
                    break;
                }
                case 9: {
                    it->Name = "Property Repair! Pay $25 For Each Property Owned.";
                    break;
                }
            }
        }

    }
    //This function will take the first chance card and push it to the back, then it will pop it from the front
    void popChance () {
        auto it = deck.begin();
        deck.push_back(*it);
        deck.pop_front();
    }

    void executeChance (Player play, list<Player> playerList) {
        auto it = deck.begin();
        cout << '\n' << it -> Name << '\n';
        switch (it->getIndex()) {
            case 0: { //Get out of jail free
                play.jailStatus = true;
                break;
            }
            case 1: { //Go back 3 spaces
                play.move_back(3);
                break;
            }
            case 2: { //Go to jail, no $200
                play.goToJail();
                break;
            }
            case 3: { //Pay each player $50
                list<Player>::iterator it;
                for (it = playerList.begin(); it != playerList.end(); ++it) {
                    play.payPlayer(*it, 50);
                }
                break;
            }
            case 4: { //Advance to Go, collect $200
                play.position = 0;
                break;
            }

            case 5: { //Dividend from bank, collect $50
                play.wallet += 50;
                break;
            }

            case 6: { //Move forward three spaces
                play.move_forward(3);
                break;
            }
            case 7: { //Collect $200 from bank
                play.wallet += 200;
                break;
            }

            case 8: { //Speeding ticket worth $50
                play.wallet -= 50;
                break;
            }

            case 9: { //Make general repairs on all your property. For each house pay $25.
                list<Property>::iterator it;
                for (it = play.ownedProperties.begin(); it != play.ownedProperties.end(); ++it) {
                    play.wallet -= 25;
                }
                break;
            }
        }
        popChance();
    }
};

class Square {
public:
    int index;
    std::string name;
};

class propertySquare : public Square {
public:
    Property property; //each Property Square contains a pointer to a property
public:
    propertySquare(int myIndex, std::string myName, int ID, std::string col, int val) {
        Property newProp(myIndex, col, val, myName); //allocating memory for the new property
        index = myIndex; //setting square index to argument
        name = myName; //setting square name to argument
        property = newProp; //setting property to newly allocated one
    }
};

class goSquare : public Square {
public:
    int money;
    std::string Name;
    int index;
public:
    goSquare(int myMoney, std::string myName, int myIndex) {
        money = myMoney;
        index = myIndex;
        name = myName;
    }
};

class Jail {
private:
    int diceRoll; // last recorded dice roll from jail
    int turns; // turns in jail
    std::string Name; // Name of chance card
    int index; // Index of card
public:
    Jail() {
        diceRoll = 0;
        turns = 0;
        Name = "No name";
        index = 0;
    }

    Jail(int Tur, int Rol, std::string Nam, int ind) { //parameterized constructor
        diceRoll = Rol;
        turns = Tur;
        Name = Nam;
        index = ind;
    }
    Jail operator = (const Jail & other) { //= operator overload
        diceRoll = other.diceRoll;
        turns = other.turns;
        Name = other.Name;
        index = other.index;
        return *this;
    }
    std::string getName() {
        return Name;
    }
};

class jailSquare : public Square {
private:
    Jail jail;
public:
    jailSquare(int mydiceRoll, int myturns, std::string myName, int myIndex) {
        Jail newJail(mydiceRoll, myturns, myName, myIndex);
        index = myIndex;
        name = myName;
        jail = newJail;
    }
};

class GoToJail {
private:
    int player; // player id to land on spot
    std::string Name; // Name
    int index; // Index of card
public:
    GoToJail() {
        player = 0;
        Name = "No name";
        index = 0;
    }

    GoToJail(int pla, std::string Nam, int ind) { //parameterized constructor
        player = pla;
        Name = Nam;
        index = ind;
    }
    GoToJail operator = (const GoToJail & other) { //= operator overload
        player = other.player;
        Name = other.Name;
        index = other.index;
        return *this;
    }
    std::string getName() {
        return Name;
    }
};

class goToJailSquare : public Square {
private:
    GoToJail go_to_jail;
public:
    goToJailSquare(int player, std::string myName, int myIndex) {
        GoToJail newGoToJail(player, myName, myIndex);
        index = myIndex;
        name = myName;
        go_to_jail = newGoToJail;
    }
};

class freeParking {
private:
    std::string Name; // Name of chance card
    int index; // Index of card
public:
    freeParking() {
        Name = "No name";
        index = 0;
    }

    freeParking(std::string Nam, int ind) { //parameterized constructor
        Name = Nam;
        index = ind;
    }
    freeParking operator = (const freeParking & other) { //= operator overload
        Name = other.Name;
        index = other.index;
        return *this;
    }
    std::string getName() {
        return Name;
    }
};

class freeParkingSquare : public Square {
private:
    freeParking free_parking;
public:
    freeParkingSquare(std::string myName, int myIndex) {
        freeParking new_freeParking(myName, myIndex);
        index = myIndex;
        name = myName;
        free_parking = new_freeParking;
    }
};

class tax {
private:
    int taxRate; // Amount paid for tax
    std::string Name; // Name of chance card
    int index; // Index of card
public:
    tax() {
        taxRate = 0;
        Name = "No name";
        index = 0;
    }

    tax(int rate, std::string Nam, int ind) { //parameterized constructor
        taxRate = rate;
        Name = Nam;
        index = ind;
    }
    tax operator = (const tax & other) { //= operator overload
        taxRate = other.taxRate;
        Name = other.Name;
        index = other.index;
        return *this;
    }
    std::string getName() {
        return Name;
    }
};

class taxSquare : public Square {
private:
    tax Tax;
public:
    taxSquare(int mytaxRate, std::string myName, int myIndex) {
        tax new_tax(mytaxRate, myName, myIndex);
        index = myIndex;
        name = myName;
        Tax = new_tax;
    }
};




#endif //MONOPOLY_CPP_OBJECTS_H