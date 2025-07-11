#include "CardSeven.h"
//#include "Grid.h"
#include "Player.h"

CardSeven::CardSeven(const CellPosition& pos) : Card(pos)
{
    cardNumber = 7; 
}

void CardSeven::Apply(Grid* pGrid, Player* pPlayer)
{
    Card::Apply(pGrid, pPlayer);

    //message for the player
    pGrid->PrintErrorMessage("You get another dice roll! Click to continue...");

    //the logic to make theplayer roll again
    // suppose this player is number n  (n is from 0 to 3)
    // and we know it repeats each 4 times since they are 4 players
    //after the roll the game avances to (n+1)
    //so we advance three times to be (n+4) ==> (n+4)%4=n
    pGrid->AdvanceCurrentPlayer();
    pGrid->AdvanceCurrentPlayer();
    pGrid->AdvanceCurrentPlayer();
    
   
}

CardSeven::~CardSeven() {}
bool CardSeven::IsCardDetailsOk() {
    return true; 
}
