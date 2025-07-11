#include "AddCardAction.h"

#include "Input.h"
#include "Output.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "Card9.h"


AddCardAction::AddCardAction(ApplicationManager *pApp) : Action(pApp)
{

}

AddCardAction::~AddCardAction()
{
}

void AddCardAction::ReadActionParameters() 
{	


	// 1 Get Input/Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	//2 Read Card Num
	pOut->PrintMessage("Enter card number (1 to 9): ");
	cardNumber = pIn->GetInteger(pOut);

			//make sure it's valid
			if (cardNumber < 1 || cardNumber > 9) 
			{
				pOut->PrintMessage("Invalid card number! Operation cancelled.");
				return;
			}

	//3 Read Card Position
	pOut->PrintMessage("Click on the cell to put the card: ");
	cardPosition = pIn->GetCellClicked();

			// make sure it's valid position for the cell
			if (!cardPosition.IsValidCell())
			{
				pOut->PrintMessage("Invalid cell position! Operation cancelled.");
				return;
			}

	// 4: Ensure no start of "ladder / snake", or card is already there
	GameObject* pGameObject = pGrid->GetGameObjectAt(cardPosition);
	if (pGameObject)
	{
				pOut->PrintMessage("Cell already has a game object! Operation cancelled.");
				return;
	}
	//5 Clear Status Bar
    pOut->ClearStatusBar();
}

void AddCardAction::Execute() 
{

	// 1- The first line of any Action Execution is to read its parameter first
	
	ReadActionParameters();
	
	// 2- Switch case on cardNumber data member and create the appropriate card object type
	Card * pCard = NULL; // will point to the card object type
	
	switch (cardNumber)
	{
	case 1:
		pCard = new CardOne(cardPosition);
		break;
	case 2:
		pCard = new CardTwo(cardPosition);
		break;
	case 3:
		pCard = new CardThree(cardPosition);
		break;
	case 4:
		pCard = new CardFour(cardPosition);
		break;
	case 5:
		pCard = new CardFive(cardPosition);
		break;
	case 6:
		pCard = new CardSix(cardPosition);
		break;
	case 7:
		pCard = new CardSeven(cardPosition);
		break;
	case 8:
		pCard = new CardEight(cardPosition);
		break;
	case 9:
			pCard = new Card9(cardPosition);
			break;

	default:
		pCard = nullptr;

		// A- Add the remaining cases

	}

	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)
	if (pCard)
	{
		// A- We get a pointer to the Grid from the ApplicationManager
		Grid* pGrid = pManager->GetGrid();

		// B- Make the "pCard" reads its card parameters: ReadCardParameters(), It is virtual and depends on the card type
			//if the card has no parameters the base function will execute ==> base function does nothing
		pCard->ReadCardParameters(pGrid);

		
		

		// C- Add the card object to the GameObject of its Cell:
		// D- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar
		      //remember AddObjectToCell()  ==> true and add the object, ==> flase and doesn't add it
			  
		//remember IsCardDetailsOk() ==> true then we can add, flase then cannot
		if (!pCard->IsCardDetailsOk()) {
			return;
		}

		bool x = pGrid->AddObjectToCell(pCard);

		if (!x )
		{
			Output* pOut = pGrid->GetOutput();
			//pOut->PrintMessage("Error: Cell already contains another game object!");
			pOut->PrintMessage("Error: can't add card");
			delete pCard; // Avoid memory leak
			return;
		}
		
	}

	// Here, the card is created and added to the GameObject of its Cell

}
