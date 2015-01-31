
#include "stdafx.h"
#include "Cell.h"

Cell::Cell(int l, int t, int r, int b)
	: mLeft(l), mTop(t), mRight(r), mBottom(b)
{
	this->mSelected = false;
	this->mInit = true;
}

void Cell::Draw(CPaintDC &dc)
{
	CRect rect;
	dc.Rectangle(rect);
	dc.Rectangle(mLeft, mTop, mRight, mBottom);

	const int PADDING = 2;
	const int CARD_OFFSET = 25;
	bool highlighted;
	int xc = mLeft + PADDING;
	int yc = mTop + PADDING;

	if(this->mSelected){ highlighted = true; }
	else if(!this->mSelected){ highlighted = false; }
	if(mCards.size() > 0)
	{
		DrawCard(dc, xc, yc, mCards.back(), highlighted);
	}
}
bool Cell::CanRemoveCard()
{
	if( mCards.size() == 0) { return false; }
	else { return true; }
}
bool Cell::CanAcceptCard(int index)
{
	if((index >= 0) && (mCards.size() == 0))
	{
		return true;
	}
	else { return  false; }
}
void Cell::AddCard(int index)
{
	//if(CanAcceptCard(index) || this->mInit)
	//{
	if(index >= 0)
	{
		mCards.push_back(index);
	}
	//}
}
int Cell::RemoveCard()
{
	if(!mCards.empty())
	{
		int last = mCards.back();
		mCards.pop_back();
		return last;
	}
	else { return -1; }
}
bool Cell::IsPointWithinCell(CPoint point)
{
	if((point.x >= mLeft) && (point.x <= mRight) && (point.y >= mTop) && (point.y <= mBottom))
	{
		return true;
	}
	else { return false; }
} 
int Cell::GetCardOnTop()
{ 
	if(!mCards.empty()) { return mCards.back(); }
	else { return -1; }
} 
void Cell::SetSelected(bool selected)
{ 
	this->mSelected = selected; 
}
void Cell::SetInit(bool init){ this->mInit = init; }




TempCell::TempCell(int l, int t, int r, int b)
	: Cell(l,t,r,b)
{
	this->mSelected = false;
	this->mInit = true;
}



EndCell::EndCell(int l, int t, int r, int b)
	: Cell(l,t,r,b)
{
	this->mSelected = false;
	this->mInit = true;
}
bool EndCell::CanRemoveCard()
{
	return true;
}
bool EndCell::CanAcceptCard(int index)
{

	if(mCards.size() == 0 && ((index >= 0) && (index <= 3))) 
	{ 
		return true; 
	}
	else if(mCards.size() > 0)
	{
		int last = mCards.back();
		if((index%4 == last%4) && (index/4 == (last/4)+1))
		{
			return true;
		}
		else { return false; }
	}
	else { return false; }
}


StartCell::StartCell(int l, int t, int r, int b)
	: Cell(l,t,r,b)
{
	this->mSelected = false;
	this->mInit = true;
}
void StartCell::Draw(CPaintDC &dc)
{
	CRect rect;
	dc.Rectangle(mLeft, mTop, mRight, mBottom);
	//dc.RoundRect(rect,CPoint(15,15));

	const int PADDING = 2;
	const int CARD_OFFSET = 25;
	bool highlighted;
	int xc = mLeft + PADDING;
	int yc;

	if(this->mSelected){ highlighted = true; }
	else if(!this->mSelected){ highlighted = false; }

	for(unsigned int c=0; c<mCards.size(); c++)
	{
		yc = mTop + PADDING + (CARD_OFFSET*c);

		if(this->mSelected && (c == (mCards.size()-1))){ highlighted = true; }
		else { highlighted = false; }

		DrawCard(dc, xc, yc, mCards.at(c), highlighted);
	}
}
bool StartCell::CanAcceptCard(int index)
{
	//rank = index/4
	//suit = index%4 0=club, 1=diamond, 2=heart, 3=spade
	if( mCards.empty()) { return true; }
	else if(!mCards.empty())
	{
		int last = mCards.back();//to column last
		if((index%4 == 0 || index%4 == 3) && (last%4 == 1 || last%4 == 2))//black on red
		{
			if((index/4) == (last/4)-1)
			{
				return true;
			}
			else { return false; } 
		}
		else if((index%4 == 1|| index%4 == 2) && (last%4 == 0 || last%4 == 3))//red on black
		{
			if((index/4) == (last/4)-1)
			{
				return true;
			}
			else { return false; } 
		}
		else { return false; }
	}
}
