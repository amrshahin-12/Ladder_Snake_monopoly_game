#pragma once

#include "GameObject.h"
//startcell: ladder bottom
//endcell: ladder top
class Ladder : public GameObject // inherited from GameObject
{
	// Note: the "position" data member inherited from the GameObject class is used as the ladder's "Start Cell Position"

	CellPosition endCellPos; // here is the ladder's End Cell Position

public:

	Ladder(const CellPosition& startCellPos, const CellPosition& endCellPos); // A constructor for initialization

	virtual void Draw(Output* pOut) const; // Draws a ladder from its start cell to its end cell

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the ladder by moving player to ladder's end cell

	CellPosition GetEndPosition() const; // A getter for the endCellPos data member

	virtual ~Ladder(); // Virtual destructor
	//me: 
	//validation1: if the startcell> endcell    ===> add more later !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	static bool ValidateLadderPositions(const CellPosition& startCellPos, const CellPosition& endCellPos);

	bool IsOverlapping(GameObject* otherObj) const;

};