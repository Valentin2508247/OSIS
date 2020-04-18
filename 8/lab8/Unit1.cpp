//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

enum chessTile
{
	a = 1,b,c,d,e,f,g,h
};

const char* filename = "DefaultPosition.txt";

Tile tiles[64];
char** positions;
char str[200];
int size = 0;
TColor hint = (TColor)RGB(38,38,38);

int rever = 0;
int countclick = 0;
int tile1, tile2;
int turn;
int whiteKing = 32;
int blackKing = 39;



void __fastcall TForm1::Button1Click(TObject *Sender)
{
	this->Canvas->Brush->Color = (TColor)RGB(256,256,256);
	this->Canvas->Rectangle(0, 0, this->Width, this->Height);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	this->Canvas->Brush->Color = (TColor)RGB(200,200,200);
	this->Canvas->Rectangle(0, 0, this->Width, this->Height);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormActivate(TObject *Sender)
{
	positions = (char**)malloc(300 * sizeof(char*));
	for (int i = 0; i < 300; i++)
		positions[i] = (char*)malloc(200 * sizeof(char));
	FILE* fp = fopen(filename, "r");
	if (fp)
	{
		fgets(str, 200, fp);
	}
	else
	{
		ShowMessage("Can't load the position from file \"" + (AnsiString)filename + "\"");
	}
	fclose(fp);
	Helper::LoadPosition(str, tiles, &turn, this->Image1, &whiteKing, &blackKing);
}
//---------------------------------------------------------------------------
