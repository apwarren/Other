#pragma once
#include "Deck.hpp"
#include "Player.hpp"
#include "Dealer.hpp"
#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>
#include <thread>
using namespace std;

/**
 * BlackJack
 *
 * Description:
 *      A class that handles all relations between other classes for the 
 *      Blackjack program and is also in charge of the rules of the game.
 *      The class checks for everything from player bankruptcy to printing
 *      out each new status of the current game. The class keeps track of 
 *      player and dealer activity and when the user wishes to end the program.
 *
 * Public Methods:
 *      - BlackJack(int)
 *      - void Deal()
 *      - bool quit()
 *      - void PrintBeginning
 *
 * Private Methods:
 *      - void playerTurn()
 *      - void dealerTurn()
 *      - void resetGame()
 *      - void noBust()
 *      - void Print()
 *
 * Usage:
 *
 *  BlackJack game(3);           //Create instance of BlackJack
 *  Game.Deal();            //Initiate a game of BlackJack
 *  Game.quit();           //Flag to see is user wants to quit playing
 *  Game.PrintBeginning();  //Print out the Home screen before playing game
 *  playerTurn();           //Begin the player's turn
 *  dealerTurn();           //Begin the dealer's turn
 *  noBust();               //Determine winner and compare cards
 *  Print();                //Print out status of current game
 *
 */

class BlackJack
{
  private:
  //Member private Variables
    Deck CardDeck;        //All cards which can possibly be played
    Player* player;       //Instance of a player
    Dealer* dealer;       //Instance of the dealer
    char playerOutput;    //Determines actions chosen by user
    bool Quit;            //Flag to determine when user is done playing
    int Activity;         //Determines status of current game
    bool playerMoveOn;    //Used to determine when player has stood or quit
    bool showDealerSum;   //When game ends with no player bust, Dealer's total is shown

  //Member private functions
    void playerTurn();
    void dealerTurn();
    void resetGame();
    void noBust();
    void Print();

  public:
  //Member public functions
    BlackJack(int decks);
    void Deal();
    bool quit();
    void PrintBeginning();
    
};

/**
* BlackJack:
*
*    Constructor. 
*
* Params:
*    1 int : How many decks the user wishes to play with
*
* Returns:
*     Void
* 
* Detail:
*    Implements a Deck. Does not inherit from Deck class
*/
BlackJack :: BlackJack(int decks): CardDeck(decks * 52)
{
    //Create instance of a dealer and player-- Give each one's hand two cards
    dealer = new Dealer(CardDeck.remove(), CardDeck.remove());
		player = new Player(CardDeck.remove(), CardDeck.remove());

    //Eveything is active at start of game
    Activity = 3;          //Dealer, Player, and no bust represent 1 activity
    playerMoveOn = false;  //Player has not stood or quit
    showDealerSum = false; //Dealer has not finished its hand
    Quit = false;          //Player has not quit playing

}//End of BlackJack(int)

/**
* Public: Deal
* 
*    Begins a game of BlackJack. Primary function of the BlackJack class.
*    Handles dealer and player's turn and most private member functions.
*    Function starts by verifying that the user still has enough money to bet
*    then deals out the new game to the screen. The player will continue to play
*    until they choose to stand or quit. Once they choose one of those two options
*    then the program will pause for a second and the dealer will begin its turn. 
*    The pause is to mimic the computer "thinking" and then interacting. Once the dealer
*    has finished its turn, then if neither person busts, the program will compare hands
*    and declare the winner of the game. After that, the function will then reset all 
*    status and hands for the next possible game.
* 
* Params:
*    None
*
* Returns:
*     Void
*/
void BlackJack :: Deal()
{
    //Check if the player has enough money to bet on another game

  if(player->Bankrupt())
  {
      //Player has run out of money
      cout << "\n\nYou Are Out Of Money!!!";
      //End program
      Quit = true;  
  }

    //Player has enough Money to play game

  else
  {
      //User plays game and money is deducted

    player->Bet();   //Remove $100 from Bank
    Print();         //Show beginning game status

    //Check for BlackJack
    if(player->BlackJack())
    {
         //No Blackjack if dealer also has one
       if(dealer->BlackJack())
       { 
         player->Tie(); 
       }

         //Player gets 2.5X bet amount and wins game
       else
       {
         player->Win();
         Print();
         cout << "BLACKJACK!!!!\n";
         Activity = 0;
       }
    }

    //If no BlackJack then continue playing until everyone is finished with hand or someone busts
    if(Activity > 0)
    {    

      //Player's Turn until they stand or quit
      while(player->isActive() && Activity > 2)
      {
        playerTurn();
      
      }//Player is finished

      //Dealer's turn until they bust or gets total above 16
      while(dealer->isActive() && Activity > 1)
      {
        //Notify user of dealer status
        cout << "Dealer is Playing. . .\n";

        //Mimic computer interaction by pausing console
        chrono::milliseconds dura( 1000 );
        this_thread::sleep_for( dura );
        
        //Dealer makes their move
        dealerTurn();

      }//Dealer is finished

       //Both Player and Dealer have Stood/ No Bust
      if(Activity == 1) 
          noBust();   //Compare hand totals and determine winner

    }
  }//Game is Over

   //Reset everything for next possible game
    resetGame();

}//End of Deal()

/**
* Private: resetGame
*
*    This function resets all activity and sets up for a new 
*    game of Blackjack for the player if they choose to play again.
*    The function is similar to the constructor but rather than
*    create a new instance of the blackjack class, it is better
*    to call the deal method for each game and reset everything after.
*    This function is private as it is only to be called within the class.
*
* Params:
*    None
*
* Returns:
*     Void
* 
*/
void BlackJack :: resetGame()
{
    //Delete and recreate the player and dealer/ Give each one two starting cards
    delete dealer;
    delete player;

    dealer = new Dealer(CardDeck.remove(), CardDeck.remove());
		player = new Player(CardDeck.remove(), CardDeck.remove());

    //Everything is active at the start of each game
    Activity = 3;

    showDealerSum = false; //Dealer's total cannot be revealed for new game
    playerMoveOn = false;  // player has not made any moves

}//End of resetGame()

/**
* Private: playerTurn
*
*    This function handles player input and activity. The player
*    is able to Hit, Stand, Sort Hand, See the deck, or quit whenever 
*    it is their turn and may continue to do so as long as they do 
*    not choose to quit or stand. If they bust then the game is over.
*    If a player's initial hand total is 10 or 11 then the option to 
*    double down will appear meaning they player can bet an extra $50 if
*    their bank allows it. The player has the option to double down until
*    they choose to hit, stand, quit, or have already chosen to do so.
*    The computer will tell the player that it is still their turn until
*    their are finished with their hand. This function can only be called within
*    the BlackJack class.
*
* Params:
*    None
*
* Returns:
*     Void
* 
*/
void BlackJack :: playerTurn()
{
   while(!playerMoveOn)
   {
        //Check to see if player can double down and give option if able to
      player->DoubleDown();

        //Print out Player Choices
      cout << "H: Hit | S: Stand | A: Sort Hand | R: Show Deck | Q: Quit" << endl;
        //Get user input
      cin >> playerOutput;

      switch(playerOutput)
      {
          case 'D': case 'd': //Option does not appear if no DoubleDown
            player->chooseDD();
            Print();
            break;

            case 'H': case 'h': 
              player->Hit(CardDeck.remove()); //Add a card to player hand
              Print();                        //Print new status  
              playerMoveOn = true;            //Player moves on to check for bust/ Activity does not change
              break;

            case 'S': case 's':
              player->Stand();                //Player has finished with their hand
              Activity--;                     //Player is no longer active
              playerMoveOn = true;            //Player moves on
              break;

            case 'A': case 'a':
              player->sortHand();            //Sort the cards in player hand by value and rank
              Print();                       //Print new status with sort
              break;                         //Return to options

            case 'R': case 'r':
              CardDeck.PrintDeck();          //Show all cards remaining in deck with have not been played sorted
              cout << "Press enter any key and hit enter to return to game\n";
              cin >> playerOutput;           //If the deck is empty then a newly shuffled deck will replace it
              Print();                       //Return to game screen with options
              break;

            case 'Q': case 'q':
              Activity = 0;                  //Player no longer wishes to continue playing
              Quit = true;                   //Program ends
              playerMoveOn = true;
              break;

      }//End of switch(playerOutput)

    }//Player has made choice

        //Check to see if player went over 21
      if(player->Bust())
      {
          player->Stand();        //Game is over
          Activity=0;             //Player Loses
          cout << "\nYou Busted!\tYou Lose!\n";
      }

        //Player did not bust and did not quit game
      else
      {
          if(!Quit)
          {
            Print();               //Show new status
            if(player->isActive()) //Notify Player that it is still their turn
            cout << "Your Move.\n";
          }
      }

        //Reset for next player move
      playerMoveOn = false;
}//End of playerTurn()

/**
* Private: dealerTurn
*
*    This function handles Dealer activity. The dealer
*    must continue to hit and add cards to its hand until
*    the total sum of their hand is 17 or higher. If the
*    dealer busts then the player wins. Once the dealer has
*    either busted or finished its hand then it will reveal 
*    its hidden card and show its total hand sum. This 
*    function can only be called within the BlackJack class.
*
* Params:
*    None
*
* Returns:
*     Void
* 
*/
void BlackJack :: dealerTurn()
{
  if(!dealer->Bust())
  {
    if(dealer->underHit())            //Dealer hand is less than 17
    {
      dealer->Hit(CardDeck.remove()); //Add card to dealer's hand

      if(dealer->Bust())              //Dealer went over 21
      {
          player->Win();              //Player wins- Money is awarded to bank
          showDealerSum = true;       //Show the dealer's final hand
          dealer->revealBlank();      //Flip over the first card
          Print();                    //Show Full Dealer Hand and declare player victory
          cout << "Dealer Busts!\t You Win!\n";
          Activity = 0;               //Game is over
      }

      else          //Dealer did not bust
      {
          Print(); //Show new game status with dealer's new card
      }

    }

    else  //Dealer's hand is at least 17
    {
          dealer->Stand();  //Dealer is done playing
          Activity--;       //Move on to determine winner
    }
  }

  else    //Dealer went over 21
  {
     player->Win();              //Player wins- Money is awarded to bank
     showDealerSum = true;       //Show the dealer's final hand
     dealer->revealBlank();      //Flip over the first card
     Print();                    //Show Full Dealer Hand and declare player victory
     cout << "Dealer Busts!\t You Win!\n";
     Activity = 0;               //Game is over
  }

}//End of dealerTurn()

/**
* Private: noBust
*
*    This function determines the winner if neither the
*    player nor the dealer gets a bust. The function
*    will show the dealer's hidden card and reveal its 
*    final hand total then declare the winner or state
*    if it was a tie. All winnings are distributed accordingly.
*    This function can only be called within the BlackJack class.
*
* Params:
*    None
*
* Returns:
*     Void
* 
*/
void BlackJack :: noBust()
{
    //Show the dealer's final result and hidden card
  showDealerSum = true;
  dealer->revealBlank();

    //Player Wins
  if(player->sum() > dealer->sum())
  {
    //Award 2X betting amount and print results
     player->Win(); 
     Print();       
     cout<< "YOU WIN!\n";
  }

    //It's a tie
  else if(player->sum() == dealer->sum())
  {
    //Return bet amount to player and print results
     player->Tie();
     Print();
     cout << "It's a Tie!\n";

  }
    //Player Loses
  else
  {
    //Print results of defeat
     Print();
     cout << "Dealer Was Highest!\tYou Lose!\n";
  }

    //Game is over
  Activity--; 

}//End of noBust()

/**
* Public: quit
*
*    This function determines when the player no longer wishes
*    continue to play blackjack and will end the program when 
*    desired. The function acts as a flag to notify the other 
*    functions of the user's decision.
*
* Params:
*    None
*
* Returns:
*     1 bool  : Whether the player wishes to quit or not
* 
*/
bool BlackJack:: quit()
{
  return Quit;   //Is true when Q is pressed

}//End of quit()
    
/**
* Private: Print
*
*    This function prints out the game layout and current status
*    the game. It is the graphics for the game. The function is 
*    called whenever a new interaction is made during a game.
*    This function can only be called from within the BlackJack 
*    class as a different function is called to display the
*    starting screen
*
* Params:
*    None
*
* Returns:
*     Void
* 
*/
void BlackJack :: Print()
{
            //Print out Game status
    cout << "\n\n\n\n\n\n\n\n\n";
    cout << "██████  ██       █████   ██████ ██   ██      ██  █████   ██████ ██   ██\n";
    cout << "██   ██ ██      ██   ██ ██      ██  ██       ██ ██   ██ ██      ██  ██\n";
    cout << "██████  ██      ███████ ██      █████        ██ ███████ ██      █████\n";
    cout << "██   ██ ██      ██   ██ ██      ██  ██  ██   ██ ██   ██ ██      ██  ██\n";
    cout << "██████  ███████ ██   ██  ██████ ██   ██  █████  ██   ██  ██████ ██   ██\n"; 
    cout << endl;

    cout << "  ___  ___   _   _    ___ ___\n";
    cout << " |   \\| __| /_\\ | |  | __| _ \\\n";
    cout << " | |) | _| / _ \\| |__| _||   /\n";
    cout << " |___/|___/_/ \\_\\____|___|_|_\\\n";
    cout << endl;

    dealer->printHand();

        //Reveal dealer sum if finished with game
    if(showDealerSum)     
      cout << "\t\tDealer Total: " << dealer->sum();

    cout << endl;
    cout << endl;

    cout << "  ___ _      ___   _____ ___\n";
    cout << " | _ \\ |    /_\\ \\ / / __| _ \\\n";
    cout << " |  _/ |__ / _ \\ V /| _||   /\n";
    cout << " |_| |____/_/ \\_\\_| |___|_|_\\\n";
    cout << endl;

    player->printHand();

    cout << "\t\tPlayer Total: "<< setw(2) << player->sum();
    cout << "\n\nBank: $" << setw(4) << player->getBank();
    cout << "\n\n";

}//End of Print()

/**
* Public: PrintBeginning
*
*    This function prints out a "Home Screen" for the game when the
*    the program gets called. It is part of the graphics for the game.
*    This function shows the bank's initial total and also shows the 
*    credits screen. The display will continue to appear until the
*    user hits a character and then presses enter where they will
*    then begin a game of black jack. This function is only called once.
*
* Params:
*    None
*
* Returns:
*     Void
* 
*/
void BlackJack :: PrintBeginning()
{

    cout << "██████  ██       █████   ██████ ██   ██      ██  █████   ██████ ██   ██\n";
    cout << "██   ██ ██      ██   ██ ██      ██  ██       ██ ██   ██ ██      ██  ██\n";
    cout << "██████  ██      ███████ ██      █████        ██ ███████ ██      █████\n";
    cout << "██   ██ ██      ██   ██ ██      ██  ██  ██   ██ ██   ██ ██      ██  ██\n";
    cout << "██████  ███████ ██   ██  ██████ ██   ██  █████  ██   ██  ██████ ██   ██\n"; 
    cout << endl;

    cout << "  ___  ___   _   _    ___ ___\n";
    cout << " |   \\| __| /_\\ | |  | __| _ \\\n";
    cout << " | |) | _| / _ \\| |__| _||   /\n";
    cout << " |___/|___/_/ \\_\\____|___|_|_\\\n";
    cout << endl;

            //Hold spaces for future cards
    cout << endl;
    cout << "\n\n\n\n\n";
    cout << endl;

    cout << "  ___ _      ___   _____ ___\n";
    cout << " | _ \\ |    /_\\ \\ / / __| _ \\\n";
    cout << " |  _/ |__ / _ \\ V /| _||   /\n";
    cout << " |_| |____/_/ \\_\\_| |___|_|_\\\n";
    cout << endl;

                //Hold spaces for future cards
    cout << "\n\n\n\n\n";
    cout<< endl;

                //Game has not started. Bank = $1000
    cout << "Total: --";
    cout << "\n\nBank: $" << player->getBank();
    cout << endl;

            //Get Player input
    cout << "\n\t\t| Press Any Key And Hit Enter To Begin Playing |" << endl;
            //Credits
    cout << "\nCreated by: Allyson Warren \nProgram: PO2 \nDate: 15 Nov 2020\n";

}//End of PrintBeginning()
