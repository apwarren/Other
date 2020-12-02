#pragma once
#include "Hand.hpp"
#include <iostream>
using namespace std;

/**
 * Dealer
 *
 * Description:
 *      A class that creates and is responsible for
 *      the actions of a game dealer. The dealer inherits from
 *      the human class as it acts as a person; however, unlike
 *      a player, the dealer must abide by certain rules. The 
 *      dealer must continue to draw cards if their hand total
 *      is less than 17 and does not possess any money as it 
 *      do not have a bank. The dealer's first card is also hidden
 *      until it is time to compare both the dealer's and player's hand.
 *
 * Public Methods:
 *      - Dealer(Card*, Card*)
 *      - bool underHit()
 *      - bool BlackJack()
 *      - void revealBlank()
 *
 * Private Methods:
 *      - None
 *
 * Usage:
 *  Dealer dealer(card1, card2);			//Create instance of Dealer
 *  dealer.underHit();        //Checks to see if hand total is below 17
 *  dealer.BlackJack();       //Checks to see if initial two cards total 21
 *  dealer.revealBlank();     //Swaps blank card with original actual card
 *
 */
class Dealer : public Human
{
  private:

    Card* temp;   //Stores the first card of the dealer
    int handSum;  //Total sum of dealer's hand

  public:

    Dealer(Card* card1, Card* card2);
    bool underHit();
    bool BlackJack();
    void revealBlank();

};

/**
* Dealer:
*
*    Constructor. Extends the Human(Card*) constructor. 
*     It assigns two cards from the deck to the dealer and
*     stores the first in a temporary location and add that
*     cards value to the total. 
*
* Params:
*    2 Card*  : the first two cards to put into dealer's hand
*
* Returns:
*     Void
* 
*/
Dealer :: Dealer(Card* card1, Card* card2) : Human(card2)
{
  Name = "Dealer";     //Assign title to the dealer
  temp = card1;        //Place card1 in a temporary location
  Cards.addSum(card1); //Add value of card1 to sum of hand value

}//End of Dealer(Card*, Card*)

/**
* Public: underHit
*
*    This function checks to see see if the hand total
*     of the dealer is under 17. It will return true if so.
*
* Params:
*    None
*
* Returns:
*     1 bool  : return true if hand total is less than 17
* 
*/
bool Dealer :: underHit()
{
  return (Cards.getTotal() < 17);

}//End of underHit()

/**
* Public: BlackJack()
*
*    This function checks to see if the dealer's initial
*     hand total equals 21. If it does equal 21 then the
*     function will return true and the game will end in a tie.
*     This function is only called if the player also gets 
*     a blackjack.
*
* Params:
*    None
*
* Returns:
*     1 bool  : Return true is dealer hand equals 21
* 
*/
bool Dealer :: BlackJack()
{
  if(Cards.getTotal() == 21)
  {
    return true; //Ends in tie if player gets a BlackJack
  }
    return false; //Player gets a blackjack

}//End of BlackJack()

/**
* public:  revealBlank
*
*    This function calls for the function in the Hand class
*     to swap the blank card for the actual first card in the hand
*      which was stored in the temporary location (temp). The card
*      can then be printed out and revealed to the user when desired.
*
* Params:
*    None
*
* Returns:
*     Void
* 
*/
  void Dealer :: revealBlank()
  {
      //Replace blank card with true first card in deck
    Cards.getCardFront(temp);

  }//End of revealBlank()
