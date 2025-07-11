#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition()
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	hCell = -1; vCell = -1;
}

CellPosition::CellPosition(int v, int h)
{
	// (-1) indicating an invalid cell (uninitialized by the user)


	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition(int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
	// from the passed (cellNum)
	// (*this) = ... --> this will copy the returned (vCell and hCell)
	//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v)
{
	if (v >= 0 && v <= 8)

		///TODO: Implement this function as described in the .h file (don't forget the validation)
	{
		vCell = v;

		return true;

	}
	else { return false; }

}

bool CellPosition::SetHCell(int h)
{
	if (h >= 0 && h <= 10)
		///TODO: Implement this function as described in the .h file (don't forget the validation)
	{
		hCell = h;

		return true;
	}
	else { return false; }// this line s///TODO: Implement this function as described in the .h file (don't forget the validation)


	// this line sould be changed with your implementation
}

int CellPosition::VCell() const
{
	return vCell;

}

int CellPosition::HCell() const
{
	return hCell;

}

bool CellPosition::IsValidCell() const
{
	if (hCell < 0 || hCell>10)
		return false;
	else if (vCell < 0 || vCell>8)
		///TODO: Implement this function as described in the .h file
		return false;
	else return true;// this line sould be changed with your implementation

	///TODO: Implement this function as described in the .h file


	 // this line sould be changed with your implementation
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
	// which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition& cellPosition)
{
	int x;

	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it

	///TODO: Implement this function as described in the .h file
	x = ((8 - cellPosition.VCell()) * 11) + (cellPosition.HCell() + 1);


	return x; // this line should be changed with your implementation
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;

	/// TODO: Implement this function as described in the .h file
	position.SetHCell((cellNum - 1) % 11);
	position.SetVCell(8 - ((cellNum - 1) / 11));

	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it


	return position;
}

void CellPosition::AddCellNum(int addedNum)
{
	int x;

	/// TODO: Implement this function as described in the .h file
	x = ((8 - VCell()) * 11) + (HCell() + 1);
	x = x + addedNum;
	if (x > 99) {
		x = 99;
	}
	SetHCell((x - 1) % 11);
	SetVCell(8 - ((x - 1) / 11));

	// Note: this function updates the data members (vCell and hCell) of the calling object

}
bool CellPosition::operator==(const CellPosition& poss) const
{
	// Check if the v and h cell indices are the same ==> is so then return true
	return (this->VCell() == poss.VCell()) && (this->HCell() == poss.HCell());
}