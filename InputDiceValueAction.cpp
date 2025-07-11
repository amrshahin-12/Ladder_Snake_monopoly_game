#include "InputDiceValueAction.h"

#include "Grid.h"
#include "Player.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"


InputDiceValueAction::InputDiceValueAction(ApplicationManager* pApp) : Action(pApp) {      }    

void InputDiceValueAction::ReadActionParameters() {
    
}

void InputDiceValueAction::Execute() {
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    // 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action
    if (pGrid->GetEndGame()) {
        pGrid->PrintErrorMessage("The game has ended! Click to continue...");
        return; 
    }

    // 2. ask the user to input a dice value
    
    pOut->PrintMessage("Please enter a dice value between 1 and 6: ");

    Input* pInput = pGrid->GetInput();
    int diceValue = pInput->GetInteger(pGrid->GetOutput());
        //validation
    if (diceValue < 1 || diceValue > 6) {
        pGrid->PrintErrorMessage("Invalid dice value! Operation canceled. Click to continue...");
        return; 
        // cancel if the dice value is invalid
    }

    // 3. get the current player
    Player* pCurrentPlayer = pGrid->GetCurrentPlayer();

    // 4- move the currentPlayer using function Move of class player
    pCurrentPlayer->Move(pGrid, diceValue);

    // get the type of object the player landed on
    Cell* pCurrentCell = pCurrentPlayer->GetCell();
    GameObject* pGameObject = pCurrentCell->GetGameObject();

    if (Ladder* pLadder = dynamic_cast<Ladder*>(pGameObject)) // if ladder
    {
        pGrid->PrintErrorMessage("You have reached a ladder. Click to continue...");
        pGrid->GetInput()->GetCellClicked(); // waiting for a click
        CellPosition ladderTop = pLadder->GetEndPosition(); // get the Ladder top
        pGrid->UpdatePlayerCell(pCurrentPlayer, ladderTop); // move player to the ladder top
    }
    else if (Snake* pSnake = dynamic_cast<Snake*>(pGameObject)) // if snake
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
        
            pGrid->PrintErrorMessage("You have reached Card " + to_string(cardNumber) + ". Click to continue...");

        }
    }

    //advance to the next player
    pGrid->AdvanceCurrentPlayer();

}
InputDiceValueAction::~InputDiceValueAction() {}