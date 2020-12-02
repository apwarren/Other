#pragma once
#include "Hand.hpp"
#include <iostream>
using namespace std;

/**
 * Human
 *
 * Description:
 *      A class that acts as the parent class for both
 *      the player and dealer class. It handles all overlapping
 *      requirements that both the player and dealer must abide by
 *      such as hitting, busting, and determining if each is done with their
 *      turn. It also handles printing out the cards in a hand for
 *      each person.
 *
 * Public Methods:
 *      - Human(Card*)
 *      - Human(Card*, Card*)
 *      - void Hit(Card*)
 *      - void Stand()
 *      - bool Bust()
 *      - int sum()
 *      - bool isActive()
 *      - void printHand()
 *
 * Private Methods:
 *      - None
 *
 * Usage:
 *  Human dPerson(card1);		      //Create instance of Human dealer
 *  Human pPerson(card1, card2);  //Create instance of Human player
 *  dperson.Hit(card1);           //add a card to human's hand
 *  dperson.Stand();              //Human has finished with turn
 *  dperson.Bust();               //Human has gone over 21
 *  dperson.sum();                //gets total hand value of human
 *  dperson.isActive();           //Returns whether the player has finished turn
 *  dperson.printHand();          //prints out the cards for human   
 *
 */
class Human
{
  protected:
    Hand Cards;     //Human's own respective cards
    string Name;    //Title of human
    bool Active;    //Whether the human has finished their turn

  public:
    Human(Card* card1);
    Human(Card* card1, Card* card2);
    void Hit(Card* another);
    void Stand();
    bool Bust();
    int sum();
    bool isActive();
    void printHand();

};

/**
* Human(Card*):
*
*    Constructor. This constructor is meant for the dealer class.
*     It creates an instance of the Hand class and then sets the human
*     as active as they have yet to make any actions yet. It then 
*     checks for the possibility of a bust not because it is possible
*     but because it is possible to have two aces as the first two
*     cards and those two aces would need to be changed to a value
*     of 2 rather than 22. The fuction would then have a proper hand value.
*     
* Params:
*    1 Card*  : The card to add to the second vector slot in the hand
*
* Returns:
*     Void
* 
*/
Human :: Human(Card* card1) : Cards(card1)
{
  Active = true;  //Human has not finished turn
  Bust();         //Checks for two aces to not equal 22

}//End of Human(Card*)

/**
* Human(Card*, Card*):
*
*    Constructor. This constructor is meant for the player class.
*     It creates an instance of the Hand class and then sets the human
*     as active as they have yet to make any actions yet. It then 
*     checks for the possibility of a bust not because it is possible
*     but because it is possible to have two aces as the first two
*     cards and those two aces would need to be changed to a value
*     of 2 rather than 22. The fuction would then have a proper hand value.
*     
* Params:
*    1 Card*  : The card to add to the second vector slot in the hand
*
* Returns:
*     Void
* 
*/
Human :: Human(Card* card1, Card* card2) : Cards(card1, card2)
{
  Active = true;  //Human has not finished turn
  Bust();         //checks for 2 aces to not equal 22

}//End of Human(Card*, Card*)

/**
* Public: Hit
*
*    This function is add a card to a person's hand and then
*     increases their total hand value by the new card's value.
*     The card added is taken and removed from the existing deck.
*
* Params:
*    1 Card*  : Card to be added to the hand
*
* Returns:
*     Void
* 
*/  
void Human :: Hit(Card* another)
{
  Cards.add(another);       //Add card to Hand
  Cards.addSum(another);    //Increase overall hand total
    
}//End of Hit()

/**
* Public: Stand
*
*    This function is called when a person has finished their
*    their turn by choosing to stand. They do not wish to 
*    add anymore cards to their hand and the next person moves
*    on to their turn. The person is no longer active.
*
* Params:
*    None
*
* Returns:
*     Void
* 
*/  
void Human :: Stand()
{
    //Person is done with turn
  Active = false;

}//End of Stand()

/**
* Public: Bust
*
*    This function checks to see if a player busts as 
*     well as changes all aces in the hand if the player
*     is capable of busting. The function checks to see if
*     the current hand value is over 21 and if so changes
*     any possible 11-value aces to be worth only 1 and
*     then checks again to see if the person has still gone
*     over 21. If so then the function returns true.
*
* Params:
*    None
*
* Returns:
*     1 bool : True if total hand value is greater than 21
* 
*/    
bool Human :: Bust()
{
      //Player has gone over 21
  if(Cards.getTotal() > 21)
  {
      //Change any aces to a value of 1
    Cards.changeAce();

      //Has still gone over 21
    if(Cards.getTotal() > 21)
    {
      return true;
    }

      //Did not bust
    else
      return false;
  }

      //Did not bust
  return false;

}//End of Bust()

/**
* Public: sum
*
*    This function gets and returns the person's
*     overall total value of all cards in their hand.
*
* Params:
*    None
*
* Returns:
*     1 int : Sum of all card values in hand
* 
*/  
int Human :: sum()
{
  return Cards.getTotal();

}//End of sum()

/**
* Public: isActive
*
*    This function returns the status of a person
*     and whether they are waiting to or are taking
*     their turn. When a person stands or quits, they 
*     will no longer be active.
*
* Params:
*    None
*
* Returns:
*     1 bool : Whether the player has not finished their turn
* 
*/  
bool Human :: isActive()
{
  return Active;

}//End of isActive()

/**
* Public: printHand()
*
*    This function is calls the PrintHand function from
*     the Hand class to print out all current cards in 
*     the person's hand. It will print them out 5 per row.

* Params:
*    None
*
* Returns:
*     Void
* 
*/  
void Human :: printHand()
{
  //Print out cards 5 per row
  Cards.PrintHand();

}//End of PrintHand()

