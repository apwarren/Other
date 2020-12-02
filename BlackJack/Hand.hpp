#pragma once
#include "Card.hpp"
#include "Container.hpp"
#include <iostream>
using namespace std;

/**
 * Hand
 *
 * Description:
 *      A class that holds all the cards for either the player
 *      and the dealer. Each hand must have at least two cards.
 *      Every time a card is added to a hand, the total sum
 *      of all values of cards in the hand is also added accordingly.
 *      This class can also compare the hand total of other hand objects
 *      using the < operator and can change any aces in the hand to a value
 *      of 1 if needed.
 *
 * Public Methods:
 *      - Hand(Card*)
 *      - Hand(Card*, Card*)
 *      - int getTotal()
 *      - void addSum(Card*)
 *      - void getCardFront(Card*)
 *      - int size()
 *      - void changeAce()
 *      - Hand operator<(const Hand&)
 *      - void PrintHand()
 *
 * Private Methods:
 *      - None
 *
 * Usage:
 *  Hand dHand(card1);		      //Create instance of Hand for dealer
 *  Hand pHand(card1, card2);   //Create instance of Hand for player
 *  pHand.getTotal();           //Get the total value of a hand
 *  pHand.addSum(card2);        //Increase total value when adding a card
 *  dHand.getCardFront(card1);  //Replace the first card in a hand with a different card
 *  pHand.size();               //Return the number of cards in a hand
 *  pHand.changeAce();          //Replace any ace values in hand with a value of 1
 *  pHand < dHand;              //Returns the Hand with the higher hand total
 *  pHand.PrintHand();          //Print out all cards in a hand with 5 per row
 *
 */
class Hand : public Container
{
  private:
	  int sum;    //Total card value of all cards in hand

  public:
    Hand(Card* card1);
	  Hand(Card* card1, Card* card2);
    int getTotal();
    void addSum(Card* another);
    void getCardFront(Card* temp);
    int size();
    void changeAce();
    Hand operator<(const Hand &rhs);
    void PrintHand();

};

/**
* Hand(Card*):
*
*    Constructor. Extends the Container(int) constructor.
*     It constructs the dealer's hand. It fills the vector with
*     two uninitialized cards and then assigns the first card to 
*     be a "blank" card with the true value stored elsewhere. The given
*     card is then pointed at by the second vector index. The sum is
*     then the value of the given card to be added with the true first
*     card in the dealer class.
*
* Params:
*    1 Card*  : The card to add to the second vector slot in the hand
*
* Returns:
*     Void
* 
*/
Hand :: Hand(Card* card1) : Container (2)
{
  Card* blank = new Card(-1); //Acts as the back side of the first card
  cards[0] = blank;
  cards[1] = card1;           //card1 is the second card in the hand
  sum = card1->getValue();    //Assign card1 to be the current Total of the hand

}//End of Hand(Card*)

/**
* Hand(Card*, Card*):
*
*    Constructor. Extends the Container(int) constructor.
*     It constructs the player's hand. It fills the vector with
*     two uninitialized cards and then assigns the two given cards
*     to the two vector spots. The sum is then calculated to be
*     the adding of the first two cards at the beginning of each game
*
* Params:
*    2 Card*  : The first two cards in a player's hand
*
* Returns:
*     Void
* 
*/
Hand ::	Hand(Card* card1, Card* card2): Container (2)
{
  cards[0] = card1;     //card1 is first card in hand
  cards[1] = card2;     //card2 is second card in hand
  sum = card1->getValue() + card2 -> getValue();

}//End of Hand(Card*, Card*)
  
/**
* Public: getTotal
*
*    This function is a getter function which returns
*     the current total value of all cards currently 
*     in the hand.
*
* Params:
*    None
*
* Returns:
*     1 int : Sum of all card values in hand
* 
*/  
int Hand :: getTotal()
{
  return sum;

}//End of getTotal()

/**
* Public: addSum
*
*    This function is called when a new card is added
*     to the hand. It takes the new card's value and adds
*     it to the total sum of all card values in the hand.
*
* Params:
*    1  Card* : Card whose value is to be added to total sum
*
* Returns:
*     Void
* 
*/  
void Hand :: addSum(Card* another)
{
  sum += another->getValue();

}//End of addSum()
    
/**
* Public: getCardFront
*
*    This function replaces the first card in the hand with
*     a new given card. This function is meant to replace
*     the dealer's hidden card with the actual rank and value
*     of the card. When the card is replaced, the true card can 
*     be printed to show on the screen.
*
* Params:
*     1 Card* : card to replace the first card with
*
* Returns:
*     Void
*/  
void Hand :: getCardFront(Card* temp)
{
  cards[0] = temp; //Originally should be a blank card

}//End of getCardFront()

/**
* Public: size
*
*    This function returns how many cards are currently in
*     a person's hand. 
*
* Params:
*    None
*
* Returns:
*     1 int : Returns how many cards are in the hand
* 
*/  
int Hand :: size()
{
  return cards.size(); //Amount of cards in a hand

}//End of size()

/**
* Public: changeAce
*
*    This function traveses through the hand and when it 
*    finds an ace will lower the value from 11 to 1. This
*    function is only called when the dealer or player may
*    potentially bust and an ace cannot be decreased once it
*    has already been changed to a one. When an ace is changed,
*    the sum of the hand will be decreased by 10 as the ace is now
*    worth only a value of 1.
*
* Params:
*    None
*
* Returns:
*     Void
* 
*/  
void Hand :: changeAce()
{
      //Look at every card in hand
  for(int i = 0; i < cards.size(); i++)
  {
      //If card is an ace and does not already have value of 1
    if(cards[i]->isAce() && cards[i]->getValue() != 1)
    {
      cards[i]->setValue(1);  //Set ace to new value of 1
      sum -= 10;              //Decrease overall hand total by 10
    }
  }

}//End of changeAce()

/**
* Public: operator<
*
*    This function iverloads the < operator to 
*    compare the total sum of one hand to the total 
*    sum of another hand and then returns the card 
*    pointer that has the lowest total value.
*
* Params:
*    1 const Hand&  : the other hand to compare to the current hand
*
* Returns:
*     1 Hand  : The hand with the lowest total hand value
* 
*/  
Hand Hand :: operator<(const Hand &rhs)
{

  if(this->sum < rhs.sum)
    return *this;    //this is lowest
  //else
    return rhs;     //rhs is lowest

}//End of operator<

/**
* Public: PrintHand
*
*     This function prints out all cards in the hand to the screen.
*     It will print out 5 cards per row starting with the first card
*     in the hand. This function is called frequently for every change
*     in the current game when a card is added.
*
* Params:
*    None
*
* Returns:
*     Void
* 
*/  
void Hand :: PrintHand()
{
      //No cards have been printed yet
  int counter = 0;

  while(counter < size())
  {
      //Print out all cards by rows of 5 if player has more than 5 cards
    if(size() - counter > 4)
    {
      cout << '\t';

      for(int j = 0; j < 5; j++)
      {
        //Top of Card
        cout << ".-----. ";
      }

      cout << endl;
      cout << '\t';

      for(int j = 0; j < 5; j++)
      {
        cout << "|" << cards[j + counter]->getRank() << ".-. | ";
      }

      cout << endl;
      cout << '\t';

      for(int j = 0; j < 5; j++)
      {
        //Middle of card
        cout << cards[j + counter]->cardMiddle(cards[j + counter]->getSuit()) << ' ';
      }

      cout << endl;
      cout << '\t';     

      for(int j = 0; j < 5; j++)
      {
        cout << "| '-'" << cards[j + counter]->getRank() << "| ";
      }

      cout << endl;
      cout << '\t';

      for(int j = 0; j < 5; j++)
      {
        //Bottom of card
        cout << "`-----' ";
      }

      cout<< endl;

      //Five cards have been printed
      counter += 5;
    }

      //Print remaining cards
    else
    {
      cout << '\t';

      for(int i = counter; i < size(); i++)
      {
        //Top of card
        cout << ".-----. ";
      }

      cout << endl;
      cout << '\t';

      for(int i = counter; i < size(); i++)
      {
        cout << "|" << cards[i]->getRank() << ".-. | ";
      }

      cout << endl;
      cout << '\t';

      for(int i = counter; i < size(); i++)
      {
        //Middle of card
        cout << cards[i-1]->cardMiddle(cards[i]->getSuit()) << ' ';
      }

      cout << endl;
      cout << '\t';

      for(int i = counter; i < size(); i++)
      {
        cout << "| '-'" << cards[i]->getRank() << "| ";
      }

      cout << endl;
      cout << '\t';

      for(int i = counter; i < size(); i++)    
      {
        //Bottom of card
        cout << "`-----' ";
      }

      cout<< endl;

        //All cards have been printed
      counter = size();
    }
  }
}//End of PrintHand()
