#include "CardSix.h"
#include "Player.h"
#include "Grid.h"

CardSix::CardSix(const CellPosition& pos) : Card(pos)
{
    cardNumber = 6; 
}

void CardSix::Apply(Grid* pGrid, Player* pPlayer)
{
    // Step 1: Call the base class Apply to print the card number message
    Card::Apply(pGrid, pPlayer);

    // Step 2: Get the last rolled dice value from the player
    int roll = pPlayer->GetLastDiceRoll();

    
    pPlayer->Move(pGrid, -roll);
    pPlayer->DecTurnCount();

}

CardSix::~CardSix()
{
   
}
bool CardSix::IsCardDetailsOk() {
    return true; 
}

