#include "CardEight.h"
#include "Grid.h"
#include "Player.h"


CardEight::CardEight(const CellPosition& pos) : Card(pos) {
    cardNumber = 8; 
}


void CardEight::Apply(Grid* pGrid, Player* pPlayer) {
    
    Card::Apply(pGrid, pPlayer);

    // Prevent the player from rolling in their next turn
    pPlayer->SetTurnCanceled(true);

    pGrid->PrintErrorMessage("Card 8: Your next turn is canceled. Press any key to continue...");
}
bool CardEight::IsCardDetailsOk() {
    return true;
}


CardEight::~CardEight() { 
    //......
}
