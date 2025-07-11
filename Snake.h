#pragma once

#include "GameObject.h"
//endcell=> tail
//startcell=> head
//movement from heam to tail (up to down)
class Snake : public GameObject // inherited from GameObject
{
    // Note: the "position" data member inherited from the GameObject class is used as the snake's "Start Cell Position"

    CellPosition endCellPos; // here is the snake's End Cell Position (where player goes when they land on the snake's head)

public:

    Snake(const CellPosition& startCellPos, const CellPosition& endCellPos); //constructor

    virtual void Draw(Output* pOut) const; // draws a snake from its start (head) cell to its end (tail) cell

    virtual void Apply(Grid* pGrid, Player* pPlayer); // applies the effect of the snake

    CellPosition GetEndPosition() const; //getter for the endCellPos (snake's tail)

    virtual ~Snake(); 

    bool IsOverlapping(GameObject* pNew) const;
};
