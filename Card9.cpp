#include "Card9.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include "Player.h"

Card9::Card9(const CellPosition& pos) : Card(pos)
{
    cardNumber = 9;
}

Card9::~Card9()
{
}

void Card9::ReadCardParameters(Grid* pGrid)
{
    Input* pInput = pGrid->GetInput();
    Output* pOutput = pGrid->GetOutput();

    // Prompt the user to enter the target cell
    pOutput->PrintMessage("New CardNine: Enter a valid target cell position (1-99)...");

    // Validate the entered target position
    int enteredCell = pInput->GetInteger(pOutput);
    if (enteredCell < 1 || enteredCell > 99)
    {
        pOutput->PrintMessage("Invalid cell! Card will not be added. Click anywhere to continue...");
        pInput->GetCellClicked(); // Pause for user acknowledgment
        pOutput->ClearStatusBar();
        target = -1; // Set an invalid value to indicate that the card should not be added
        return;
    }

    // if the target cell is valid,i can save it
    target = enteredCell;
    pOutput->ClearStatusBar();
}

void Card9::Apply(Grid* pGrid, Player* pPlayer)
{
    // If the card's target is invalid, do nothing


    // Call the base class Apply to print the message
    Card::Apply(pGrid, pPlayer);

    // Calculate the number of cells to move
    int between = pPlayer->GetBetweenCellsNum(target);

    // Move the player
    pPlayer->Move(pGrid, between);
    pPlayer->DecTurnCount();
}
bool Card9::IsCardDetailsOk() {

    if (target < 1 || target > 99)
    {
        //pGrid->PrintErrorMessage("Invalid card target! Operation canceled. Click to continue...");
       // Output* pOutput = pGrid->GetOutput();
        //pOutput->PrintMessage("invalid target cell, card won't be added");

        return false;
    }
    return true;

}
