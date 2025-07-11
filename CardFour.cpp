#include "CardFour.h"
#include "Snake.h"

CardFour::CardFour(const CellPosition& pos) : Card(pos)
{
    cardNumber = 4; 
}


void CardFour::Apply(Grid* pGrid, Player* pPlayer)
{
    Card::Apply(pGrid, pPlayer); // Call the base class's Apply method

    CellPosition playerPos = pPlayer->GetCell()->GetCellPosition();
    Snake* pNextSnake = pGrid->GetNextSnake(playerPos); // Find the next snake

    if (pNextSnake)
    {
        // Move the player to the start of the next snake
        pGrid->UpdatePlayerCell(pPlayer, pNextSnake->GetPosition());
        pGrid->PrintErrorMessage("You moved to the start of the next snake...");
    }
    else
    {
        pGrid->PrintErrorMessage("No snakes ahead. No action taken.");
    }
}

CardFour::~CardFour()
{
    // ...
}
bool CardFour::IsCardDetailsOk() {
    return true; 
}

