#include "CardOne.h"

CardOne::CardOne(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 1; // set the inherited cardNumber data member with the card number (1 here)
}

CardOne::~CardOne(void)
{
}

void CardOne::ReadCardParameters(Grid * pGrid)
{
	
	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==


	// 1- Get a Pointer to the Input / Output Interfaces from the Grid

	// 2- Read an Integer from the user using the Input class and set the walletAmount parameter with it
	//    Don't forget to first print to a descriptive message to the user like:"New CardOne: Enter its wallet amount ..."
	

	// [ Note ]:
	// In CardOne, the only parameter of CardOne is the "walletAmount" value to decrease from player
	// Card parameters are the inputs you need to take from the user in the time of adding the Card in the grid
	// to be able to perform his Apply() action

	// 3- Clear the status bar

	// Step 1: Get a pointer to the Input/Output interfaces from the Grid
	Input* pInput = pGrid->GetInput();
	Output* pOutput = pGrid->GetOutput();

	// Step 2: Prompt the user to enter the wallet amount to decrement
	pOutput->PrintMessage("New CardOne: Enter its wallet amount to decrease from player..."); // Descriptive message to the user
	walletAmount = pInput->GetInteger(pOutput); // Get the wallet amount (integer value)

	// Step 3: Clear the status bar
	pOutput->ClearStatusBar();

}

void CardOne::Apply(Grid* pGrid, Player* pPlayer)
{
		
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	

	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number

	// 2- Decrement the wallet of pPlayer by the walletAmount data member of CardOne

	// Step 1: Call Apply() of the base class Card to print the message that the player reached this card number
	Card::Apply(pGrid, pPlayer);

	// Step 2: Decrement the wallet of pPlayer by the walletAmount data member of CardOne
	pPlayer->DecrementWallet(walletAmount);

}
bool CardOne::IsCardDetailsOk() {
	return true;
}