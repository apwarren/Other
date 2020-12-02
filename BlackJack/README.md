### Description:
This program implements a console game of BlackJack by encapsulating several different classes representing different aspects of the game such as cards, players, and 
a deck. The user can play against a dealer with a starting amount of $1000 and play until they choose to quit or go bankrupt. The player is also able to make other choices 
during their turn such as viewing all remaining cards in the deck and sorting the cards in their hand by rank. If the player gets an initial hand of 10 or 11, they are
also able to choose if they wish to bet and additional $50 during a game. There is no ability to Split in this program however. If the player manages to get a 
Blackjack, they will be awared 2.5X their betting amount. When a player finishes a game, the computer will ask if they wish to play again, if the player wishes to quit 
then the program will bid farewell and end.

### Files:

|   #   | File                                                                                         | Description                     |
| :---: | -------------------------------------------------------------------------------------------- | ------------------------------- |
|   1   | [main.cpp](https://github.com/apwarren/2143-OOP-Warren/blob/master/Assignments/P02/main.cpp) | Main driver of my blakcjack program. |
|   2   | [BlackJack.hpp](https://github.com/apwarren/2143-OOP-Warren/blob/master/Assignments/P02/BlackJack.hpp) | File containing the rules and implementation of a blackjack game |
|   3   | [Card.hpp](https://github.com/apwarren/2143-OOP-Warren/blob/master/Assignments/P02/Card.hpp) | File containing the implementation of a single card. Contains value, rank, and suit of a card|
|   4   | [Container.hpp](https://github.com/apwarren/2143-OOP-Warren/blob/master/Assignments/P02/Container.hpp) | File containing all instances of Cards. Cards are stored in a vector which can grow or shrink when desired |
|   5   | [Dealer.hpp](https://github.com/apwarren/2143-OOP-Warren/blob/master/Assignments/P02/Dealer.hpp) | File containing the rules and actions of a Dealer. The dealer is managed by the computer. It has one hidden card at beginning of game |
|   6   | [Deck.hpp](https://github.com/apwarren/2143-OOP-Warren/blob/master/Assignments/P02/Deck.hpp) | File containing all playable and unused cards for the game. User can play with as many decks as desired |
|   7   | [Hand.hpp](https://github.com/apwarren/2143-OOP-Warren/blob/master/Assignments/P02/Hand.hpp) | File containing all cards in use by either the player or dealer. Cards can be sorted when desired |
|   8   | [Human.hpp](https://github.com/apwarren/2143-OOP-Warren/blob/master/Assignments/P02/Human.hpp) | File containing all actions expected by both the player and dealer. Player and Dealer inherit from this class |
|   9   | [Player.hpp](https://github.com/apwarren/2143-OOP-Warren/blob/master/Assignments/P02/Player.hpp) | File containing all the capable actions that can be executed by the player. The user can choose certain actions during a game such as hit or stand.  |

### Class Designs

#### Class Card
  - Description:
    - A class containing the type and value of a specific card. Each card gets assigned its identity of a value, rank, and suit. 
    - A default card is the "back side" of a card.
- Private:
   - Data: 
     - int value 		  How much card is worth in sum
     - int Suit    	  Heart, Club, Spade, Diamond
     - char Rank	 	  2-10, Jack, Queen, King, Ace
     - int Position   Where it originally was in the deck
- Public:
  - Methods:
     - Card(int):  	Sets a card's initial positon if the deck
     - setValue:  	Sets value of card
     - setRank:  		Gives the card its rank
     - setSuit:    	Sets the suit of the card
     - getValue: 		Returns value of card
     - getRank:		  Returns rank of card
     - getSuit:		  Returns number repsresenting a suit
     - getPosition:	Returns where the card iniitally was
     - isAce: 		  Returns true if card rank is Ace
     - Print: 	  	Prints out card to screen
     - cardMiddle: 	Return middle of card containing suit symbol
#### Class Container
  - Description:
    - A class containing all instances of a card and adding cards 
  - Protected:
    - Data:
      - vector<Card *> cards; 	Vector of all cards in the container
      - unsigned int Size; 	  	Size of how many cards are created
  - Public:
    - Methods:
      - Container(int numCard);	Constructor. How many cards to make
      - void add(Card* card);	Add a card to a container
      - bool isEmpty();			See if no cards are in container
      - int size();				Current  amount of cards in container
      - void Sort();			 Arrange cards in container by rank
#### Class Deck
  - Description:
    - It is in charge of shuffling and keeping track of all undealed cards.
  - Private:
    - Data:
      - int OriginalSize;     The maximum amount of cards that can be in the deck
    - Methods:
      - void Fill();		Initialize all cards in container
      - void reset();	Refill and shuffle the deck
      - void Shuffle();	Randomly swap elements in deck
  - Public:
    - Methods:
      - Deck();			Construtctor creates 52 cards 
      - Deck(int GivenSize); Constructor creates 52 * # of decks
      - Card* remove();	 Removes card from back of deck
      - void PrintDeck();	Print	 out 13 cards per row for all cards
#### Class Hand
  - Description:
    - A class containing all instances of cards currently obtained by a specific player.
    - A subclass that inherits from the Container class and is composed in the Human class.
  - Private:
    - Data:
      - int sum;    Total card value of all cards in hand
  - Public:
    - Methods:
      - Hand(Card* card1);				Consturctor for dealer
      - Hand(Card* card1, Card* card2);	Constructor for player
      - int getTotal();			          Get the total value of all cards
      - void addSum(Card* another);     Add value of new card to sum
      - void getCardFront(Card* temp);  Replace first card with another
      - int size();					 Return how many card in hand
      - void changeAce();			Change ace value to 1
      - Hand operator<(const Hand &rhs); Compare hand values
      - void PrintHand();			Print cards in hand 5 per row
  #### Class Human
   - Description:
     - Parent class for the Player and Dealer class
     - Responsible for creating each classes hand
     - And overlapping methods such as adding cards to hand and busting.
   - Protected
     - Data:
       - Hand Cards;      Human's own respective cards
       - string Name;     Title of human
       - bool Active;     Whether the human has finished their turn
   - Public:
     - Methods:
       - Human(Card* card1);		          	Constructor for Dealer class
       - Human(Card* card1, Card* card2);   Constructor for Player class
       - void Hit(Card* another);		Add a card to a human's hand
       - void Stand();			      	Sets player to inactive
       - bool Bust();			         	Hand total is over 21
       - int sum();				         	Returns total hand value
       - bool isActive();	    			Checks to see if active is true
       - void printHand();    			Print out a hand 5 cards per row

 #### Class Player
   - Description:
     - A class containing the rules and behavior of a single player.
   - Private
     - Data:
       - static int Bank;       How much money the player has over all games
       - int BetAmount;         How much the player is going to bet
       - bool DoubledDown;      Whether the player has already chosen to doubledown if allowed
   - Public:
     - Methods:
       - Player(Card* card1, Card* card2);	Constructor--Gives two cards from deck
       - void Bet();				  Removes money from bank to place bet
       - void Win();			    Gives player twice bet amount to their bank
       - void Tie();				  Returns bet money to player
       - bool Bankrupt();		  Player bank is less than $100- cannot bet money
       - int getBank();			  Returns how much money is in bank
       - bool BlackJack();		Checks to see if player's initial hand equals 21
       - void DoubleDown();		Player initial hand is either 11 or 10. can bet +$50
       - void chooseDD();		  Player bets additional $50 on game
       - void sortHand()	;		Sort cards in hand by rank
 #### Class Dealer
   - Description:
     - Acts as the game's dealer
     - The dealer only shows one of its initial cards and must keep hitting until its hand is above a certain value 
     - Does not have a bank
   - Private:
     - Data:
       - Card* temp;   		Stores the first card of the dealer
       - int handSum;  	  Total sum of dealer's hand
   - Public:
     - Methods:
       - Dealer(Card* card1, Card* card2);	Gives Dealer two cards from deck and stores the first card in a temporary location
       - bool underHit();		Dealer hand value in under 17
       -  bool BlackJack();		Dealer's iniital hand equals 21
       - void revealBlank();		Swaps blank card for the first card in the temp location
      
 #### Class BlackJack
   - Description:
     - A class in charge of implementing the rules of the BlackJack. 
     - It manages the Player, Dealer, and the Deck. 
     - It determines the winner of each game and distributes winnings.
   - Private:
     - Data:
       - Deck CardDeck;             All cards which can possibly be played
       - Player* player;            Instance of a player
       - Dealer* dealer;            Instance of the dealer
       - char playerOutput;         Determines actions chosen by user
       - bool Quit;                 Flag to determine when user is done playing
       - int Activity;              Determines status of current game
       - bool playerMoveOn;         Used to determine when player has stood or quit
       - bool showDealerSum;        When game ends with no player bust, Dealer's total is shown
     - Methods:
       - void playerTurn();	Handles activity for player's and prints actions for user to choose
       - void dealerTurn();	Handles activity for dealer and hits until value is at least 17
       - void resetGame();	Resets all variables for the next possible game
       - void noBust();		Neither the player nor dealer bust so it compares the two hand values
       - void Print();		Prints out all graphics for current game activity
   - Public:
     - Methods:
       - BlackJack(int decks);	Constructor, sets how many decks are needed in game and sets all flags
       - void Deal();			      Begins and enacts a game of BlackJack
       - bool quit();			      Returns whether player has chosen to quit game
       - void PrintBeginning();	Prints out a home screen for beginning of program
 #### Diagram
<img src="https://i.imgur.com/R5jr9sw.png" width="900">
