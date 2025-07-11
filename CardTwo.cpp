#include "CardTwo.h"
#include "Grid.h"
#include "Player.h"
#include "Output.h"
#include "Input.h"

CardTwo::CardTwo(const CellPosition& pos) : Card(pos) // Set the cell position of the card
{
    cardNumber = 2; // Set the card number to 2
}

CardTwo::~CardTwo(void)
{
}

void CardTwo::ReadCardParameters(Grid* pGrid)
{
    // Step 1: Get a pointer to the Input/Output interfaces from the Grid
    Input* pInput = pGrid->GetInput();
    Output* pOutput = pGrid->GetOutput();

    // Step 2: Prompt the user to enter the wallet amount to increment
    pOutput->PrintMessage("New CardTwo: Enter its wallet amount to increase for player..."); // Descriptive message to the user
    walletAmount = pInput->GetInteger(pOutput); // Get the wallet amount (integer value)

    // Step 3: Clear the status bar
    pOutput->ClearStatusBar();
}

void CardTwo::Apply(Grid* pGrid, Player* pPlayer)
{
    // Step 1: Call Apply() of the base class Card to print the message that the player reached this card number
    Card::Apply(pGrid, pPlayer);

    // Step 2: Increment the wallet of pPlayer by the walletAmount data member of CardTwo
    pPlayer->IncrementWallet(walletAmount); // Increase the player's wallet
}
bool CardTwo::IsCardDetailsOk() {
    return true; 
}
