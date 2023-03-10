#include "CFigure.h"
CFigure::CFigure() {
	Selected = false;

}
CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
}

int CFigure::count = 0;

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}
void CFigure::setCrntFillClr(string a) // fun to set the fig fill color
{
	if (a != "NO_FILL")
	{
		FigGfxInfo.isFilled = true;
		if (a == "BLUE")
			FigGfxInfo.FillClr = BLUE;

		if (a == "ORANGE")
			FigGfxInfo.FillClr = ORANGE;
		if (a == "RED")
			FigGfxInfo.FillClr = RED;
		if (a == "BLACK")
			FigGfxInfo.FillClr = BLACK;
		if (a == "YELLOW")
			FigGfxInfo.FillClr = YELLOW;
		if (a == "GREEN")
			FigGfxInfo.FillClr = GREEN;
	}
	else
		FigGfxInfo.isFilled = false;


}
void CFigure::setCrntDrawClr(string a)
{
	// func to set fig draw clr


	if (a == "BLUE")
		FigGfxInfo.DrawClr = BLUE;

	if (a == "ORANGE")
		FigGfxInfo.DrawClr = ORANGE;
	if (a == "RED")
		FigGfxInfo.DrawClr = RED;
	if (a == "BLACK")
		FigGfxInfo.DrawClr = BLACK;
	if (a == "YELLOW")
		FigGfxInfo.DrawClr = YELLOW;
	if (a == "GREEN")
		FigGfxInfo.DrawClr = GREEN;


}
string CFigure::GetFigColor(color a)
{
	// get the curren draw/fill color as string so i can save it in a file.txt
	if (a == BLUE) {
		return "BLUE";
	}
	if (a == ORANGE)
		return "ORANGE";
	if (a == RED)
		return "RED";
	if (a == BLACK)
		return "BLACK";
	if (a == YELLOW)
		return "YELLOW";
	if (a == GREEN)
		return"GREEN";
	else
		return "NO_FILL";

}
void CFigure::setCount(int a) {
	count = a;

}


