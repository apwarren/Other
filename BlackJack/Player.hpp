#pragma once
#include "Hand.hpp"
#include "Human.hpp"
#include <iostream>
using namespace std;

/**
 * Player
 *
 * Description:
 *      A class that handles all activity for the player. The
 *      class inherits from the Humans class and then also 
 *      implements a static bank to maintain is last value after
 *      every game. The bank does not reset in order to allow 
 *      the player to continue playing a new game until they 
 *      run out of money. The player can also choose to DoubleDown
 *      if they wish when possible but there is no ability to split.
 *      It also allows the player to sort their hand by rank if desired.
 *
 * Public Methods:
 *      - Player(Card*, Card*)
 *      - void Bet()
 *      - void Win()
 *      - void Tie()
 *      - bool Bankrupt()
 *      - int getBank()
 *      - bool BlackJack
 *      - void DoubleDown
 *      - void chooseDD
 *      - void sortHand
 *
 * Private Methods:
 *      - None
 *
 * Usage:
 *  Player gamer(card1, card2);		    //Create instance of Player 
 *  gamer.Bet();                      //Money is deducted from bank of gamer
 *  gamer.Win();                      //2X bet money is awarded to gamer
 *  gamer.Tie();                      //Bet money is given back to gamer
 *  gamer.Bankrupt();                 //Checks to see if gamer still has money
 *  gamer.getBank();                  //Returns how much money gamer has in bank
 *  gamer.BlackJack();                //Sees if gamer has a blackjack
 *  gamer.DoubleDown();               //Offers choice of doubledown if requirements are met
 *  gamer.chooseDD();                 //Gamer chooses to do doubledown
 *  gamer.sortHand();                 //Sorts cards in gamer's hand by rank
 *
 */
class Player : public Human
{
  private:
    static int Bank;    //How much money the player has over all games
    int BetAmount;      //How much the player is going to bet
    bool DoubledDown;   //Whether the player has already chosen to doubledown if allowed

  public:
    Player(Card* card1, Card* card2);
    void Bet();
    void Win();
    void Tie();
    bool Bankrupt();
    int getBank();
    bool BlackJack();
    void DoubleDown();
    void chooseDD();
    void sortHand();
};

//Player starts off with $1,000 in the bank
 int Player :: Bank = 1000;

/**
* Player(Card*, Card*):
*
*    Constructor. This constructor gives the player two cards
*      in their deck of random worth from the deck. It then sets the
*      initial bet amount to $100. The player is given its respective 
*      title and does not yet have the option to double down so it
*      is set to false.
*     
* Params:
*    1 Card*  : The card to add to the second vector slot in the hand
*
* Returns:
*     Void
* 
*/
Player :: Player(Card* card1, Card* card2) : Human(card1, card2)
{
  BetAmount = 100;      //Always bet 100 at first for every game
  Name = "Player ";     //Player is given its title
  DoubledDown = false;  //Is not allowed to Double down yet

}//End of Player(Card*, Card*)

/**
* Public: Bet
*
*    This function deducts the amount of money the 
*     player wishes to bet from the bank. 
*
* Params:
*    None
*
* Returns:
*     Void
* 
*/  
void Player :: Bet()
{
      //Deduct money from bank to bet
  Bank -= BetAmount;

}//End of Bet()

/**
* Public: Win
*
*    This function adds twice the final bet amount
*     to the player's bank if they beat the dealer. 
*
* Params:
*    None
*
* Returns:
*     Void
* 
*/  
void Player :: Win()
{
    //Player won the game
  Bank += 2 * BetAmount;

}//End of Win()

/**
* Public: Tie
*
*    This function returns the bet amount to the player
*     if they tie with the dealer. If the player got a 
*     blackjack and so did the dealer, then 50 is deducted
*     from the bet amount before returning the money as
*     when the blackjack function is called and true it
*     adds $25 to the bet amount and the blackjack function
*     will be true twice.
*
* Params:
*    None
*
* Returns:
*     Void
* 
*/  
void Player :: Tie()
{
    //The player and dealer tied on a blackjack
  if(BlackJack())
    BetAmount -= 50;

    //Return bet amount to the player
  Bank += BetAmount;

}//End of Tie()

/**
* Public: Bankrupt
*
*    This function is checks to see if the player 
*    has enough money in the bank to play another
*    game of blackjack. If the player does not then
*    the function will return true and the player will
*    not be able to continue playing as they have run
*    out of money.
*
* Params:
*    None
*
* Returns:
*     1 bool  : Returns true if bank is under $100
* 
*/  
bool Player :: Bankrupt()
{
      //Not enough money to bet in bank
    return Bank < 100;

}//End of Bankrupt()

/**
* Public: getBank
*
*    This function returns how much money the player has
*    at a current time in the bank. 
*
* Params:
*    None
*
* Returns:
*     1 int : Total amount of money the player currently has
* 
*/  
int Player :: getBank()
{
  return Bank;

}//End of getBank()

/**
* Public: BlackJack()
*
*    This function checks to see if the player is capable of
*     having a blackjack at the start of a game. If the 
*     player does have one, then $25 is added to the 
*     bet amount to be doubled with the existing $100
*     to award the player $250 for getting a blackjack.
*     A blackjack can only occur at the start of a game.
*
* Params:
*    
*
* Returns:
*     1 bool  : True if there is a blackjack
* 
*/  
bool Player :: BlackJack()
{
    //Player has a blackjack
  if(Cards.getTotal() == 21 && Cards.size() == 2)
  {
    BetAmount += 25;
    return true; 
  }
    //Player does not have a blackjack
  return false;

}//End of BlackJack()

/**
* Public: DoubleDown
*
*    This function checks to see if the player's initial hand
*     total is either a 10 or 11 and if so allows the option
*     to appear for the player to be able to bet an additional
*     $50 on the current game. The option will continue to appear
*     unti the player chooses to either hit, stand, or quit, or
*     if they have already chosen to double down. A person can 
*     choose the option once per game.
* Params:
*     None
*
* Returns:
*     Void
* 
*/  
void Player :: DoubleDown()
{
      //Hand value is either 10 or 11 at start of game
  if(Cards.size() == 2 && (Cards.getTotal() == 10 || Cards.getTotal() == 11 ))
  {
      //Allow for DoubleDown if player has enough money and has not already done so
    if(Bank >= 50 && !DoubledDown)
    {
      cout << "| D: Double Down | ";
    }
  } 
}//End of DoubleDown()

/**
* Public: chooseDD
*
*    This function enacts a double down if the player
*     chooses to bet an additional $50 on the game. 
*     This function can only be called when the
*     requirements for a double down have been met.
*     Once the player calls this function it cannot
*     be called again for the current game.
*
* Params:
*     None
*
* Returns:
*     Void
* 
*/  
void Player :: chooseDD()
{
    //Player chooses to do a Double Down
  DoubledDown = true; 

    //Add money to bet and subtract extra bet from bank
  BetAmount += 50;
  Bank -= 50;

}//End of chooseDD()

/**
* Public: sortHand
*
*    This function calls the sort method in the hand class
*     to put all of the player's cards in order by rank 
*     when the player chooses to sort their hand on the
*     screen. 
*
* Params:
*     None
*
* Returns:
*     Void
* 
*/  
void Player :: sortHand()
{
    //Calls sort method in Hand class
  Cards.Sort();

}//End of sortHand()
  

