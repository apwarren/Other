#pragma once
#include <iostream>
using namespace std;


/**
 * Card
 *
 * Description:
 *      A class that creates an instance of a standard card. The card
 * 		is given a rank from 2-10, Jack, Queen, King, or Ace and then
 * 		given its respective value worth. A ten is printed as a 0 to
 * 		have all display be single character. Aces are always worth 11 at
 * 		first and then if there is a potential bust the changeAce() 
 * 		function will be called to change all aces to ones. The cards
 * 		are also given a suit of heart, spade, club, or diamond to
 * 		be shown when the card is printed out. The cards also have a 
 * 		position to make sorting them easier. 
 *
 * Public Methods:
 *      - Card(int)
 * 		- void setValue(int)
 *		- void setRank(int)
 *		- void setValue(int)
 *		- void setSuit(int)
 *		- int getValue()
 *		- char getRank()
 *		- int getSuit()
 *		- int getPosition()
 *		- bool isAce()
 *		- void Print()
 *		- string cardMiddle(int)
 *
 * Private Methods:
 *      - None
 *
 * Usage:
 *
 *  Card card1(52);				//Create instance of a card
 *  card1.setValue(2);		//Make the card worth the value of 2
 *  card1.setRank(2);		//Set the rank of the card as 2
 *  card1.setSuit(3);		//Assign the card to the Hearts suit
 *  card1.getValue();		//Get the value of the card
 *  card1.getRank();		//Get the rank of the card
 *  card1.getSuit();		//Get the suit number of the card
 *  card1.isAce();			//See if the card rank is an ace
 * 	card1.print();			//Print out one instance of a card
 * 	card1.cardMiddle(2);	//Print out the middle of a card where the suit is
 *
 */
class Card
{
private:
	int value;		//How much card is worth in sum
	int Suit;		//Heart, Club, Spade, Diamond
	char Rank;		//2-10, Jack, Queen, King, Ace
  	int Position; 	//Where it originally was in the deck
public:
	Card(int);
	void setValue(int);
	void setRank(int);
	void setSuit(int);
	int getValue();
	char getRank();
	int getSuit();
	int getPosition();
	bool isAce();
	void Print();
	string cardMiddle(int);

};//End of class definition

/**
* Card:
*
*    Constructor. Card is not initialized, just created.
*
* Params:
*    1 int : Where the card is in the deck
*
* Returns:
*     Void
* 
*/
Card :: Card(int _position)
{
	value = 0;				//Value is default to 0
	Suit = 5;				//Suit is blank card
	Rank = ' ';				//No rank currently exists
   	Position =  _position;	//Position is the value given to the function

}//End of Card(int)

/**
* Public: setValue
*
*    A function which sets the value of a card.
*	 If the card is an ace already in play then the 
*	 card will change its value to one. All cards
*	 higher than nine will have a value of 10 with
*	 the exception of an Ace which is initialized to
*	 11;
*
* Params:
*    1 int : One less than the value of to be given for 2-9
*
* Returns:
*     Void
* 
*/
void Card :: setValue(int val)
{
  val++;

	if (Rank == 'A')		//card is an Ace-- starting value is 11
	{
		if (value == 11) 	//Already in play as 11
			value = 1; 		//Change to 1
		else 				//Set it to 11 if not played yet
			value = 11;
	}

	else if (val < 10)		//If card is less than 10
		value = val;		//Give card respective value
	else

		value = 10;			//All cards above 9 are worth 10

}//End of setValue(int)

/**
* Public: setRank
*
*    A function which sets the rank of a card.
*	 Cards are given a rank in the order, Ace to King.
*	 All ranks are characters rather than integers as some
*	 are ranked as Jack, Queen, King, and Ace.
*
* Params:
*    1 int : Value of card to be converted to its proper rank
*
* Returns:
*     Void
* 
*/
void Card :: setRank(int _rank)
{
	switch (_rank)
	{
		case 0:				//Card is Ace
			Rank = 'A';
			break;
			case 9:				//Card is a 10
			Rank = '0';		//Rank = 0 to have all single digits
			break;

		case 10:			//Rank is Jack
			Rank = 'J';
			break;

		case 11:			//Rank is Queen
			Rank = 'Q';
			break;

		case 12:			//Rank is King
			Rank = 'K';
			break;

		default:			//Rank is #2-9
			Rank = 49 + _rank;
			break;
	}
}//End of setRank()

/**
* Public: setSuit
*
*    A function which gives each card its suit.
*	Suits are from Hearts, Diamonds, Clubs, to spades
*	The suit is a number rather than a character because 
*	the characters for each symbol would not fit into a 
*	char and string was acting strange for me so this was easier.
*	The number given is icremented by one because the switch case 
*	for the symbols goes from 1-4 and any other number is determined 
*	to be a slash for the back side of a card.
*
* Params:
*    1 int : Value to be incremented and assigned as the suit value
*
* Returns:
*     Void
* 
*/
void Card :: setSuit(int _suit)
{
	Suit = _suit + 1;	//Suit value goes from 1-4

}//End of setSuit()

/**
* Public: getValue
*
*    A getter function which returns the value of a card
*
* Params:
*    None
*
* Returns:
*     1 int	:	returns how much the card is worth
* 
*/
int Card :: getValue()
{
	return value;

}//End of getValue()

/**
* Public: getRank
*
*    A getter function which returns a card's rank
*
* Params:
*    None
*
* Returns:
*     1 char	:	2-9, 0, J, Q, K, A
* 
*/
char Card :: getRank()
{
	return Rank;

}//End of getRank()

/**
* Public: getSuit
*
*    A getter function which returns the number designated to a certain suit
*
* Params:
*    None
*
* Returns:
*     1 int	:	A number from 1-4 usually
* 
*/
int Card :: getSuit()
{
	return Suit;

}//End of getSuit()

/**
* Public: getPosition
*
*    A getter function which returns the position of where the card was initially in the deck
*
* Params:
*    None
*
* Returns:
*     1 int	:	How far in the deck the card was
* 
*/
int Card :: getPosition()
{
   return Position;

}//End of getPosition()

/**
* Public: isAce
*    A function which determines whether a card is an Ace or not
* Params:
*    None
*
* Returns:
*     1 bool	:	returns true is rank is ace
* 
*/
bool Card :: isAce()
{
	if (Rank == 'A')
		return true;

	//else-- not an ace
	return false;

}//End of isAce()

/**
* Public: Print
*
*    A getter function which prints out a single card is desired.
*	 This function is more for testing rather than used in the 
*	 blackjack game. Cards are 5x7. Symbols are printed based 
*	 on the suit number using a switch case.
*
* Params:
*    None
*
* Returns:
*     Void
* 
*/
void Card :: Print()
{
	cout << ".-----.\n";
	cout << "|" << Rank << ".-. |\n";

	switch (Suit)
	{
		case 1://Club
			cout << "| :♣: |\n";
			break;

		case 2://Diamond
			cout << "| :♦: |\n";
			break;

		case 3://Heart
			cout << "| :♥: |\n";
			break;

		case 4://Spade
			cout << "| :♠: |\n";
			break;

		default://Back side of card
			cout << "| :/: |\n";

	}//end of switch case

	cout << "| '-'" << Rank << "|\n";
	cout << "`-----'" << endl;

}//end of Print()

/**
* Public: cardMiddle
*    A function which returns the middle of a card
*	 as well as the appropriate symbol for a card.
*	 This function is necessary rather than just returning
*	 the symbol because the program acts strangely with 
*	 properly formatting the rest of the card otherwise.
*
* Params:
*    None
*
* Returns:
*     1 string	:	returns the middle of a card with a specific suit symbol
* 
*/
string Card :: cardMiddle(int suit)
{
	string middle;

	switch (suit)
	{
		case 1://Club
			cout << "| :♣: |";
			break;

		case 2://Diamond
			cout << "| :♦: |";
			break;

		case 3://Heart
			cout << "| :♥: |";
			break;

		case 4://Spade
			cout << "| :♠: |";
			break;

		default://Back side of card
			cout << "| :/: |";

	}//End of switch
	 
	 //Return the middle of the card 
	return middle;

}//End of printMiddle()


