#pragma once

#include "Card.h"

class CardSeven : public Card
{
public:
    CardSeven(const CellPosition& pos); // Constructor
    virtual void Apply(Grid* pGrid, Player* pPlayer) override; // Applies the effect of CardSeven
    virtual ~CardSeven(); // Des...
   virtual bool IsCardDetailsOk();
};
