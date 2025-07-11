#include "CardThree.h"
#include "Ladder.h" // cause we need to move player to the start of the next ladder
//#include "Grid.h"

CardThree::CardThree(const CellPosition& pos) : Card(pos)
{
    cardNumber = 3; 
}


void CardThree::Apply(Grid* pGrid, Player* pPlayer)
{
    // Callation of the base class Apply() to print the card number
    Card::Apply(pGrid, pPlayer);

    //finds the next ladder from the player's current position
    CellPosition playerPos = pPlayer->GetCell()->GetCellPosition();  
    Ladder* pNextLadder = pGrid->GetNextLadder(playerPos);

    if (pNextLadder) {
        // Move the player to the start cell of the next ladder
        pGrid->UpdatePlayerCell(pPlayer, pNextLadder->GetPosition());
        pGrid->PrintErrorMessage("You moved to the start of the next ladder...");
    }
    else {
        pGrid->PrintErrorMessage("No ladders ahead. No action taken.");
    }
    


}
CardThree::~CardThree() {}
bool CardThree::IsCardDetailsOk() {
    return true; 
}
