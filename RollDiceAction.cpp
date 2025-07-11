#include "RollDiceAction.h"

#include "Grid.h"
#include "Player.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"

#include <time.h> // used to in srand to generate random numbers with different seed

RollDiceAction::RollDiceAction(ApplicationManager *pApp) : Action(pApp)
{
}

void RollDiceAction::ReadActionParameters()
{
	// no parameters to read from user
}

void RollDiceAction::Execute()
{
    
	srand((int)time(NULL)); // time is for different seed each run
	int diceNumber = 1 + rand() % 6; // from 1 to 6 --> should change seed

	Grid* pGrid = pManager->GetGrid(); // to access the grid

    Output* pOut = pGrid->GetOutput();
    pOut->ClearStatusBar();

	// 1: Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action
	if (pGrid->GetEndGame())
	{
		pGrid->PrintErrorMessage("The game has ended! Click to continue...");
		return; 
	}
	// 2: given
	// 3- Get the "current" player from pGrid
	Player* pCurrentPlayer = pGrid->GetCurrentPlayer();

	// 4- Move the currentPlayer using function Move of class player
	pCurrentPlayer->Move(pGrid, diceNumber);

	// get the type of object the player landed on
	Cell* pCurrentCell = pCurrentPlayer->GetCell();
	GameObject* pGameObject = pCurrentCell->GetGameObject();

    if(Ladder * pLadder = dynamic_cast<Ladder*>(pGameObject)) // If ladder
    {
        pGrid->PrintErrorMessage("You have reached a ladder. Click to continue...");
        pGrid->GetInput()->GetCellClicked(); // waiting for a click
        CellPosition ladderTop = pLadder->GetEndPosition(); // get the Ladder top
        pGrid->UpdatePlayerCell(pCurrentPlayer, ladderTop); // move player to the ladder top
        
    }
    else if (Snake * pSnake=dynamic_cast<Snake*>(pGameObject)) // If snake
    {
        pGrid->PrintErrorMessage("You have reached a snake. Click to continue...");
        pGrid->GetInput()->GetCellClicked(); // wait for a click
        CellPosition snakeTail = pSnake->GetEndPosition(); // get the tail 
        pGrid->UpdatePlayerCell(pCurrentPlayer, snakeTail); // move player to the snake tail
        
    }
    else if (dynamic_cast<Card*>(pGameObject)) // if card
    {
        Card* pCard = dynamic_cast<Card*>(pGameObject);
        int cardNumber = pCard->GetCardNumber(); // get the card number

        if (cardNumber >= 1 && cardNumber <= 9) // cards 1-9
        {
            pGrid->PrintErrorMessage("You have reached Card " + std::to_string(cardNumber) + ". Click to continue...");
            
        }
    }

    //advance to the next player
   pGrid->AdvanceCurrentPlayer();

}

    RollDiceAction::~RollDiceAction() {}
