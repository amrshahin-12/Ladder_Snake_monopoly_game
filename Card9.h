#pragma once
#include "Card.h"
#include "Player.h"

class Card9 : public Card
{
private:

    int target;
    //Player* pPlayer;

public:
    Card9(const CellPosition& pos);
    virtual ~Card9();

    virtual void ReadCardParameters(Grid* pGrid); // Reads the target cell position
    virtual void Apply(Grid* pGrid, Player* pPlayer); // Moves the player to the target cell
    virtual bool IsCardDetailsOk();
};
