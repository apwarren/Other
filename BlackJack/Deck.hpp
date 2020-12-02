#pragma once
#include "Card.hpp"
#include "Container.hpp"
#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

/**
 * Deck
 *
 * Description:
 *      A class that creates the game deck containing
 *      all playable cards for the program length. The deck comes in 
 *      multiples of 52 as that is how many cards are in a single standard
 *      deck. This class inherits from the Container class and contains functions
 *      such as filling and initializing all cards as well as placing cards
 *      in a random order in the deck.
 *
 * Public Methods:
 *      - Deck()
 *      - Deck(int)
 *      - Card* remove()
 *      - void PrintDeck()
 *
 * Private Methods:
 *      - void Fill()
 *      - void reset()
 *      - void Shuffle()
 *
 * Usage:
 *  Deck Cdeck;		      //Create instance of Deck
 *  Deck Cdeck(2);      //Create instance of Deck with 2 standard decks
 *  Cdeck.remove();     //Remove card from the back of deck
 *  Cdeck.PrintDeck();  //Print out all cards in rank order in rows of 13
 *  Fill();             //Initialize all cards in deck in suit and rank order
 *  reset();            //Refill and shuffle deck when all cards are gone from deck
 *  Shuffle();          //swap each card with another card in a random index
 *
 */
class Deck : public Container
{
  private:
      //Private Variables
	  int OriginalSize;   //The maximum amount of cards that can be in the deck

      //Private Methods
    void Fill();
    void reset();
    void Shuffle();

  public:
      //Public Methods
	  Deck(); 
	  Deck(int GivenSize);
    Card* remove();
    void PrintDeck();

};

/**
* Dealer:
*
*    Default Constructor. Extends the Container(int) constructor.
*     It fills the deck with initialized cards and sets the maximum
*     capacity of the deck size. It then shuffles the deck placing
*     each card in a random index location. The default constructor
*     assumes only one deck is to be used for the game.
*
* Params:
*    None
*
* Returns:
*     Void
* 
*/
Deck :: Deck() : Container (52) //Initialize a deck of 52 cards
{
  OriginalSize = 52;            //Deck can have up to 52 cards
  Fill();                       //Fill Deck with cards
  Shuffle();                    //Move cards to a random index

}//End of Deck()

/**
* Dealer(int):
*
*    Constructor. Extends the Container(int) constructor.
*     It fills the deck with initialized cards and sets the maximum
*     capacity of the deck size. It then shuffles the deck placing
*     each card in a random index location. This constructor relies
*     on the user choosing how many standard decks they wish to play 
*     with and will fill the deck with 52 times that number for cards.
*
* Params:
*    1 int  : Size of deck/ How many cards are to be in the deck
*
* Returns:
*     Void
* 
*/
Deck :: Deck(int GivenSize): Container (GivenSize)
{
  OriginalSize = GivenSize;   //Set the capacity of the deck  
  Fill();                     //Fill Deck with cards
  Shuffle();                  //Randomly swap each card to a new index

}//End of Deck(int)

/**
* Public: remove
*
*    This function removes a card from the back of the vector and
*     returns it. It places the card in a temporary location and 
*     decreases the current size of the deck. It then gives the
*     card to be used. If there are no cards in the deck to give
*     then the function will first reset the deck completely 
*     with shuffled cards before removing one.
*
* Params:
*    None
*
* Returns:
*     1 Card* : card which is removed from the deck
* 
*/  
Card* Deck :: remove()
{
  if(Size == 0)                 //Reset the deck if it has run out of cards
    reset();

  Card* temp = cards[Size - 1]; //Store card to be removed
	cards.pop_back();	            //Remove card from container
	Size--;		                    //Decrement size of container
	return temp;                  //Return removed card

}//End of remove()

/**
* Public: PrintDeck
*
*    This function prints out all remaining cards in the deck.
*     It will print out 13 cards per row all sorted with all
*     remaining aces printed first then two's until all cards
*     have been printed in order. Once all cards are printed
*     the function will then reshuffle the cards in the deck
*     to continue the game of blackjack.
*
* Params:
*    None
*
* Returns:
*     Void
* 
*/  
void Deck :: PrintDeck()  //Print 13 cards on one line
{
  int counter = 0;        //No cards have been printed yet
  Sort();                 //Sort the deck to print by rank

  while(counter < size()) //Print until all cards are printed
  {
        //Print out all cards by rows of 13, 
    if(size() - counter > 12)
    {
      for(int j = 0; j < 13; j++)
      {
          //Top of Cards
        cout << ".-----. ";
      }

      cout << endl;

      for(int j = 0; j < 13; j++)
      {
        cout << "|" << cards[j + counter]->getRank() << ".-. | ";
      }

      cout << endl;

      for(int j = 0; j < 13; j++)
      {
          //Middle of Cards
        cout << cards[j + counter]->cardMiddle(cards[j + counter]->getSuit()) << ' ';
      }

      cout << endl;

      for(int j = 0; j < 13; j++)
      {
        cout << "| '-'" << cards[j + counter]->getRank() << "| ";
      }

      cout << endl;

      for(int j = 0; j < 13; j++)
      {
          //Bottom of Cards
        cout << "`-----' ";
      }

      cout<< endl;

        //13 Cards have been printed
      counter += 13;
    }

     //Less than 13 cards need to be printed
    else
    {

      for(int i = counter; i < size(); i++)
      {
          //Top of cards
        cout << ".-----. ";   
      }

      cout << endl;

      for(int i = counter; i < size(); i++)
      {
        cout << "|" << cards[i]->getRank() << ".-. | ";
      }

      cout << endl;

      for(int i = counter; i < size(); i++)
      {
          //Middle of cards with symbol
        cout << cards[i-1]->cardMiddle(cards[i]->getSuit()) << ' ';   
      }

      cout << endl;

      for(int i = counter; i < size(); i++)
      {
        cout << "| '-'" << cards[i]->getRank() << "| ";
      }

      cout << endl;

      for(int i = counter; i < size(); i++)    
      {
          //Bottom of cards
        cout << "`-----' ";  
      }

      cout<< endl;

        //All cards have been accouted for
      counter = size();     

    }
  }     //All cards have been printed

        //Reshuffle the deck after printing it
      Shuffle(); 

}//End of PrintDeck()


/**
* Private: Fill
*
*    This function traverses through the uninitialized vector of 
*     cards and initializes each one starting with one suit and working
*     through the ranks for each suit. This function is only called within
*     the Deck class. 
*
* Params:
*    None
*
* Returns:
*     Void
* 
*/
void Deck :: Fill()
{
		 
	for(int i = 0; i < size(); i++)      //Give each card an initialized value, rank, suit
	{
		cards[i]->setRank(i % 13);         //Sets the Rank of the Card From Ace - King
		cards[i]->setValue(i % 13);        //Sets all card values from 1 - 10
		cards[i]->setSuit( (i / 13) % 4);  //Sets the suit from 1-4 each representing a suit
	}

}//end of Fill()

/**
* Private: reset()
*
*    This function adds all cards back into the deck by 
*    adding new uninitialized cards to the vector. After
*    creating new instances of cards, it then initializes 
*    them all like the constructors. The function then 
*    shuffles the new deck to be used for the game.
*     This function can only be called in the Deck class.
*
* Params:
*    None
*
* Returns:
*     Void
* 
*/
void Deck :: reset()
{
  Size = OriginalSize;             //Deck is completely full

  for (int i = 0; i < Size; i++)
  {
  cards.push_back(new Card(i));    //Fills deck with uninitialized cards
  } 

  Fill();                          //Initialize all cards in the deck
  Shuffle();                       //ReShuffle the deck

}//End of reset()

/**
* Private: Shuffle
*
*    This function goes through the vector of cards and swaps 
*     each card with another card in a random index. The random 
*     number can only go up to the current size of the deck. 
*     All cards will randomly be swapped at least once depending
*     on how many times an index is chosen.
*
* Params:
*    None
*
* Returns:
*     Void
* 
*/
void Deck :: Shuffle()
{
  int j;          //Assigned a random number
  srand(time(0)); //Seed the random generator will a different random number each time
  
  for (int i=0; i<size() ;i++) 
  { 
       // Random for remaining positions. 
    j = (rand() % size()); 
       //Swap Card at i with random card
    Card* temp = cards[i];
    cards[i] = cards[j];
    cards[j] = temp;
  } 

}//End of Shuffle()
    
