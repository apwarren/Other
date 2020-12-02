/*********************************************************************************
*
* Author:           Allyson Warren
* Email:            allywarren7@gmail.com
* Label:            P02
* Title:            Blackjack Game
* Course:           2143
* Semester:         Fall 2020
*
* Description:
*       This program implements a game of classic Blackjack by
*       creating multiple classes which act as specific parts of
*       the game such as cards, players, etc. The program starts by
*       asking the user how many decks they wish to play with and then
*       takes them to a "home screen" in which they see the layout of 
*       the game with their initial bank total. Once the player presses
*       a character and hits enter, then a game of BlackJack will begin.
*       The player will be able to hit, stand, sort hand, see the remaining
*       cards in the deck, and also quit the game. If the player does not 
*       choose to stand, quit, or go bust then they will be able to continue to 
*       select the available options. At the end of each game, the program will
*       ask the user if they wish to continue playing and the user may do so as 
*       long as they have enough money to bet in their bank. Otherwise, the program
*       will say goodbye to the user. 
*
* Usage:
*       None for now
*
* Files:
*       main.cpp        :  driver program
*       BlackJack.hpp   :  Class program containing all the rules of BlackJack
*       Card.hpp        :  Class program containing the type and value of a specific card. 
*       Container.hpp   :  Class program which is the parent class for Deck and Hand. Holds instances of Cards
*       Dealer.hpp      :  Class program which implements a dealer who the user plays against. 
*       Deck.hpp        :  Class program which inherits from the Container class. Holds all nonplayed instances of Cards
*       Hand.hpp        :  Class program which inherits from the Container Class. Holds all instances of the dealer's and user's cards
*       Human.hpp       :  Class program which is the parent class for the Dealer and Player. Handles all overlapping Dealer
*                          and Player functions
*       Player.hpp      :  Class program which handles all actions available to a player. Handles player's money as well
*
*******************************************************************************/

#include <iostream>
#include <chrono>
#include <thread>
#include "BlackJack.hpp"

using namespace std;

int main() {

    //Declarations
    char playAgain;     //User input to continue playing
    int decks;          //How many decks are to be implemented into the game

    //Determine amount of decks needed for game
    cout << "How many decks do you want to play with? ";
    cin >> decks;

    //Create game and display the Home Screen
    BlackJack Game(decks);
    Game.PrintBeginning();

    //Wait for the user to press a character and enter
    cin >> playAgain;

    //Begin first game of BlackJack
    Game.Deal();

    //See if the user wants to continue to play more games of blackjack
    if(!Game.quit())
    {

    cout << "\nDo you want to play again? (y/n)\n";
    cin >> playAgain;
    }

    //Continue to play blackjack until told to stop by the user
    while((playAgain == 'y' || playAgain == 'Y') && !Game.quit())
    {

      Game.Deal();

      //Pause the console after finishing a game to have the computer mimic movement
       chrono::milliseconds dura( 1500 );
       this_thread::sleep_for( dura );

      if(!Game.quit())
      {
        cout << "Do you want to play again? (y/n)\n";
        cin >> playAgain;
      }
    } 

    //Pause the console and then bid farewell when user if finished
    chrono::milliseconds dura( 1000 ); 
    this_thread::sleep_for( dura );
    cout << "\nGoodBye";   
}
