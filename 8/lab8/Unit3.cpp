//---------------------------------------------------------------------------

#pragma hdrstop

#include "Unit3.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TColor whiteLight = clWhite;
TColor whiteDark = clBlack;
TColor blackLight = (TColor)RGB(75,75,75);
TColor blackDark = clBlack;
TColor wTile = clCream;
TColor bTile = clDkGray;

void Helper::Turn(Tile* tiles, int X, int Y, int* turn, TImage* Image, int* whiteKing, int* blackKing, char** positions, int* psize)
{
	static int count_clicks = 0, tile1 = 0, tile2 = 0, moves[30], size = 0;
	if (X > 640 || Y > 640)
		return;
	int left = X - (X % Tile::TileSize);
	int top = Y - (Y % Tile::TileSize);
	int num = Helper::FindTile(tiles, left, top);
	if (count_clicks == 1)
	{
		if (tiles[tile1].piece != 0 && tiles[num].piece != 0)
			if (tiles[tile1].colr == tiles[num].colr)
				{
					for (int i = 0; i < size; i++)
						tiles[moves[i]].Show(Image);
					count_clicks--;
				}
	}
	count_clicks++;
	switch(count_clicks)
	{
		case 1:
		{
			if (tiles[num].piece == 0)
			{
				count_clicks = 0;
				return;
			}
			if (tiles[num].colr != *turn)
			{
				count_clicks = 0;
				return;
			}
			tile1 = num;
			size = Helper::AppropriateTiles(tiles, tile1, moves, whiteKing, blackKing);
			for (int i = 0; i < size; i++)
				tiles[moves[i]].ShowHint(Image);
			break;
		}
		case 2:
		{
			bool A = false;
			tile2 = num;
			for (int i = 0; i < size; i++)
			{
				if (tile2 == moves[i])
				{
					A = true;
					break;
				}
			}
			if (A)
			{

				if (tiles[tile1].piece != 10)
					Helper::Move(tiles, tile1, tile2, Image, whiteKing, blackKing, *turn, positions, psize);
				else if (tile1 == 32 && tile2 == 16)
				{
					tiles[16].SetPiece(10, 0, Image, whiteKing, blackKing);
					tiles[24].SetPiece(5, 0, Image, whiteKing, blackKing);
					tiles[32].TakePiece(Image);
					tiles[0].TakePiece(Image);
					Helper::ReverseField(tiles, Image);
					tiles[32].HighlightFrom(Image);
					tiles[16].HighlightTo(Image);
					Helper::SavePosition(tiles, positions, psize, *turn);
				}
				else if (tile1 == 32 && tile2 == 48)
				{
					tiles[48].SetPiece(10, 0, Image, whiteKing, blackKing);
					tiles[40].SetPiece(5, 0, Image, whiteKing, blackKing);
					tiles[32].TakePiece(Image);
					tiles[56].TakePiece(Image);
					Helper::ReverseField(tiles, Image);
					tiles[32].HighlightFrom(Image);
					tiles[48].HighlightTo(Image);
					Helper::SavePosition(tiles, positions, psize, *turn);
				}
				else if (tile1 == 39 && tile2 == 23)
				{
					tiles[23].SetPiece(10, 1, Image, whiteKing, blackKing);
					tiles[31].SetPiece(5, 1, Image, whiteKing, blackKing);
					tiles[39].TakePiece(Image);
					tiles[7].TakePiece(Image);
					Helper::ReverseField(tiles, Image);
					tiles[39].HighlightFrom(Image);
					tiles[23].HighlightTo(Image);
					Helper::SavePosition(tiles, positions, psize, *turn);
				}
				else if (tile1 == 39 && tile2 == 55)
				{
					tiles[55].SetPiece(10, 1, Image, whiteKing, blackKing);
					tiles[47].SetPiece(5, 1, Image, whiteKing, blackKing);
					tiles[39].TakePiece(Image);
					tiles[63].TakePiece(Image);
					Helper::ReverseField(tiles, Image);
					tiles[39].HighlightFrom(Image);
					tiles[55].HighlightTo(Image);
					Helper::SavePosition(tiles, positions, psize, *turn);
				}
				else Helper::Move(tiles, tile1, tile2, Image, whiteKing, blackKing, *turn, positions, psize);
				*turn = 1 - *turn;
			}
			else
			{
				for (int i = 0; i < size; i++)
					tiles[moves[i]].Show(Image);
            }
			count_clicks = 0;
			break;
		}
		default: return;
	}
}

int Helper::Game(Tile* tiles, int turn, int* whiteKing, int* blackKing)
{
	if (turn == 0)
	{
		int moves = Helper::AllMyMoves(tiles, 0, whiteKing, blackKing);
		if (moves == 0)
		{
			if (Helper::IsAttacked(tiles, *whiteKing, 1))
				return 2;
			else return 3;
		}
	}
	else if (Helper::IsAttacked(tiles, *blackKing, 0))
	{
		int moves = Helper::AllMyMoves(tiles, 1, whiteKing, blackKing);
		if (moves == 0)
		{
			if (Helper::IsAttacked(tiles, *blackKing, 0))
				return 2;
			else return 3;
		}
	}
	return 0;
}

int Helper::AllMyMoves(Tile* tiles, int MyColor, int* whiteKing, int* blackKing)
{
	int res = 0;
	int array[30];
	for (int i = 0; i < 64; i++)
	{
		if (tiles[i].piece != 0 && tiles[i].colr == MyColor)
			if (int j = Helper::AppropriateTiles(tiles, i, array, whiteKing, blackKing))
				{
					res += j;
				}
	}
	return res;
}

int Helper::AppropriateTiles(Tile* tiles, int tile, int* moves, int* whiteKing, int* blackKing)
{
	int array[30];
	int piece = tiles[tile].piece, color = tiles[tile].colr;
	int column = tiles[tile].column, row = tiles[tile].row;
	int size = 0;
	int num;
	switch (piece)
	{
		case 0: return 0;
		case 1:                          ///dobavit na prohode
		{
			if (color == 0)                            //white pawn
			{
				if (row == 2)
				{
					////////////////////////////na prohode
					num = (column - 1) * 8 + (4 - 1);
					if (tiles[num].piece == 0)
					{
						if (tiles[num - 1].piece == 0)
							array[size++] = num;
					}
				}
				int tcol = column, trow = row + 1;
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece == 0)
					array[size++] = num;
				tcol = column - 1;
				trow = row + 1;
				if (tcol > 0 && tcol < 9)
				{
					num = (tcol - 1) * 8 + (trow - 1);  //pawn attack
					if ((tiles[num].piece != 0) && (tiles[num].colr == 1))
						array[size++] = num;
				}
				tcol = column + 1;
				trow = row + 1;
				if (tcol > 0 && tcol < 9)
				{
					num = (tcol - 1) * 8 + (trow - 1);  //pawn attack
					if ((tiles[num].piece != 0) && (tiles[num].colr == 1))
						array[size++] = num;
				}

			}
			else                                       //black pawn
			{
				if (row == 7)
				{
					////////////////////////////na prohode
					num = (column - 1) * 8 + (5 - 1);
					if (tiles[num].piece == 0)
					{
						if (tiles[num + 1].piece == 0)
							array[size++] = num;
					}
				}
				int tcol = column, trow = row - 1;
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece == 0)
					array[size++] = num;
				tcol = column - 1;
				trow = row - 1;
				if (tcol > 0 && tcol < 9)
				{
					num = (tcol - 1) * 8 + (trow - 1);  //pawn attack
					if ((tiles[num].piece != 0) && (tiles[num].colr == 0))
						array[size++] = num;
				}
				tcol = column + 1;
				trow = row - 1;
				if (tcol > 0 && tcol < 9)
				{
					num = (tcol - 1) * 8 + (trow - 1); //pawn attack
					if ((tiles[num].piece != 0) && (tiles[num].colr == 0))
						array[size++] = num;
				}
			}
			break;
		}
		case 2:                      //num = (column - 1) * 8 + (row - 1);
		{
			int tcol = column + 2, trow = row + 1;
			num = (tcol - 1) * 8 + (trow - 1);
			if (tcol < 9 && trow < 9)
			{
				if (tiles[num].piece == 0)
					array[size++] = num;
				else if (tiles[num].colr != color)
				{
					array[size++] = num;
				}
			}
			tcol = column + 2;
			trow = row - 1;
			num = (tcol - 1) * 8 + (trow - 1);
			if (tcol < 9 && trow > 0)
			{
				if (tiles[num].piece == 0)
					array[size++] = num;
				else if (tiles[num].colr != color)
				{
					array[size++] = num;
				}
			}

			tcol = column - 1;
			trow = row - 2;
			num = (tcol - 1) * 8 + (trow - 1);
			if (tcol > 0 && trow > 0)
			{
				if (tiles[num].piece == 0)
					array[size++] = num;
				else if (tiles[num].colr != color)
				{
					array[size++] = num;
				}
			}
			tcol = column + 1;
			trow = row - 2;
			num = (tcol - 1) * 8 + (trow - 1);
			if (tcol < 9 && trow > 0)
			{
				if (tiles[num].piece == 0)
					array[size++] = num;
				else if (tiles[num].colr != color)
				{
					array[size++] = num;
				}
			}
			tcol = column - 2;
			trow = row - 1;
			num = (tcol - 1) * 8 + (trow - 1);
			if (tcol >0 && trow > 0)
			{
				if (tiles[num].piece == 0)
					array[size++] = num;
				else if (tiles[num].colr != color)
				{
					array[size++] = num;
				}
			}
			tcol = column - 2;
			trow = row + 1;
			num = (tcol - 1) * 8 + (trow - 1);
			if (tcol > 0 && trow < 9)
			{
				if (tiles[num].piece == 0)
					array[size++] = num;
				else if (tiles[num].colr != color)
				{
					array[size++] = num;
				}
			}
			tcol = column + 1;
			trow = row + 2;
			num = (tcol - 1) * 8 + (trow - 1);
			if (tcol < 9 && trow < 9)
			{
				if (tiles[num].piece == 0)
					array[size++] = num;
				else if (tiles[num].colr != color)
				{
					array[size++] = num;
				}
			}
			tcol = column - 1;
			trow = row + 2;
			num = (tcol - 1) * 8 + (trow - 1);
			if (tcol > 0 && trow < 9)
			{
				if (tiles[num].piece == 0)
					array[size++] = num;
				else if (tiles[num].colr != color)
				{
					array[size++] = num;
				}
			}
			break;
		}
		case 3:
		{
			int tcol = column + 1, trow = row + 1;
			while (tcol < 9 && trow < 9)
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece != 0)
				{
					if (tiles[num].colr == color)
						break;
					else
					{
						array[size++] = num;
						break;
					}
				}
				array[size++] = num;
				tcol++;
				trow++;
			}
			tcol = column - 1;
			trow = row - 1;
			while (tcol > 0 && trow > 0)
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece != 0)
				{
					if (tiles[num].colr == color)
						break;
					else
					{
						array[size++] = num;
						break;
					}
				}
				array[size++] = num;
				tcol--;
				trow--;
			}
			tcol = column + 1;
			trow = row - 1;
			while (tcol < 9 && trow > 0)
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece != 0)
				{
					if (tiles[num].colr == color)
						break;
					else
					{
						array[size++] = num;
						break;
					}
				}
				array[size++] = num;
				tcol++;
				trow--;
			}
			tcol = column - 1;
			trow = row + 1;
			while (tcol > 0 && trow < 9)
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece != 0)
				{
					if (tiles[num].colr == color)
						break;
					else
					{
						array[size++] = num;
						break;
					}
				}
				array[size++] = num;
				tcol--;
				trow++;
			}
			break;
		}
		case 5:
		{
			int tcol = column + 1, trow = row ;
			while (tcol < 9 )
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece != 0)
				{
					if (tiles[num].colr == color)
						break;
					else
					{
						array[size++] = num;
						break;
					}
				}
				array[size++] = num;
				tcol++;
			}
			tcol = column - 1;
			trow = row;
			while (tcol > 0)
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece != 0)
				{
					if (tiles[num].colr == color)
						break;
					else
					{
						array[size++] = num;
						break;
					}
				}
				array[size++] = num;
				tcol--;
			}
			tcol = column;
			trow = row + 1;
			while (trow < 9 )
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece != 0)
				{
					if (tiles[num].colr == color)
						break;
					else
					{
						array[size++] = num;
						break;
					}
				}
				array[size++] = num;
				trow++;
			}
			tcol = column;
			trow = row - 1;
			while (trow > 0 )
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece != 0)
				{
					if (tiles[num].colr == color)
						break;
					else
					{
						array[size++] = num;
						break;
					}
				}
				array[size++] = num;
				trow--;
			}
			break;
		}
		case 8:
		{
			int tcol = column + 1, trow = row + 1;
			while (tcol < 9 && trow < 9)
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece != 0)
				{
					if (tiles[num].colr == color)
						break;
					else
					{
						array[size++] = num;
						break;
					}
				}
				array[size++] = num;
				tcol++;
				trow++;
			}
			tcol = column - 1;
			trow = row - 1;
			while (tcol > 0 && trow > 0)
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece != 0)
				{
					if (tiles[num].colr == color)
						break;
					else
					{
						array[size++] = num;
						break;
					}
				}
				array[size++] = num;
				tcol--;
				trow--;
			}
			tcol = column + 1;
			trow = row - 1;
			while (tcol < 9 && trow > 0)
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece != 0)
				{
					if (tiles[num].colr == color)
						break;
					else
					{
						array[size++] = num;
						break;
					}
				}
				array[size++] = num;
				tcol++;
				trow--;
			}
			tcol = column - 1;
			trow = row + 1;
			while (tcol > 0 && trow < 9)
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece != 0)
				{
					if (tiles[num].colr == color)
						break;
					else
					{
						array[size++] = num;
						break;
					}
				}
				array[size++] = num;
				tcol--;
				trow++;
			}
////////
			tcol = column + 1;
			trow = row;
			while (tcol < 9 )
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece != 0)
				{
					if (tiles[num].colr == color)
						break;
					else
					{
						array[size++] = num;
						break;
					}
				}
				array[size++] = num;
				tcol++;
			}
			tcol = column - 1;
			trow = row;
			while (tcol > 0)
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece != 0)
				{
					if (tiles[num].colr == color)
						break;
					else
					{
						array[size++] = num;
						break;
					}
				}
				array[size++] = num;
				tcol--;
			}
			tcol = column;
			trow = row + 1;
			while (trow < 9 )
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece != 0)
				{
					if (tiles[num].colr == color)
						break;
					else
					{
						array[size++] = num;
						break;
					}
				}
				array[size++] = num;
				trow++;
			}
			tcol = column;
			trow = row - 1;
			while (trow > 0 )
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece != 0)
				{
					if (tiles[num].colr == color)
						break;
					else
					{
						array[size++] = num;
						break;
					}
				}
				array[size++] = num;
				trow--;
			}
			break;
		}
		case 10:  //King
		{
			int tcol = column + 1, trow = row;
			if (tcol > 0 && trow > 0 && tcol < 9 && trow < 9)
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece == 0)
				{
					if (!Helper::IsAttackedKing(tiles, num, tile, num, 1 - color))
						moves[size++] = num;
				}
				else if (tiles[num].colr != color)
				{
					if (!Helper::IsAttackedKing(tiles, num, tile, num, 1 - color))
						moves[size++] = num;
				}
			}
			tcol = column + 1;
			trow = row + 1;
			if (tcol > 0 && trow > 0 && tcol < 9 && trow < 9)
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece == 0)
				{
					if (!Helper::IsAttackedKing(tiles, num, tile, num, 1 - color))
						moves[size++] = num;
				}
				else if (tiles[num].colr != color)
				{
					if (!Helper::IsAttackedKing(tiles, num, tile, num, 1 - color))
						moves[size++] = num;
				}
			}
			tcol = column + 1;
			trow = row - 1;
			if (tcol > 0 && trow > 0 && tcol < 9 && trow < 9)
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece == 0)
				{
					if (!Helper::IsAttackedKing(tiles, num, tile, num, 1 - color))
						moves[size++] = num;
				}
				else if (tiles[num].colr != color)
				{
					if (!Helper::IsAttackedKing(tiles, num, tile, num, 1 - color))
						moves[size++] = num;
				}
			}
			tcol = column - 1;
			trow = row;
			if (tcol > 0 && trow > 0 && tcol < 9 && trow < 9)
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece == 0)
				{
					if (!Helper::IsAttackedKing(tiles, num, tile, num, 1 - color))
						moves[size++] = num;
				}
				else if (tiles[num].colr != color)
				{
					if (!Helper::IsAttackedKing(tiles, num, tile, num, 1 - color))
						moves[size++] = num;
				}
			}
			tcol = column - 1;
			trow = row + 1;
			if (tcol > 0 && trow > 0 && tcol < 9 && trow < 9)
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece == 0)
				{
					if (!Helper::IsAttackedKing(tiles, num, tile, num, 1 - color))
						moves[size++] = num;
				}
				else if (tiles[num].colr != color)
				{
					if (!Helper::IsAttackedKing(tiles, num, tile, num, 1 - color))
						moves[size++] = num;
				}
			}
			tcol = column - 1;
			trow = row - 1;
			if (tcol > 0 && trow > 0 && tcol < 9 && trow < 9)
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece == 0)
				{
					if (!Helper::IsAttackedKing(tiles, num, tile, num, 1 - color))
						moves[size++] = num;
				}
				else if (tiles[num].colr != color)
				{
					if (!Helper::IsAttackedKing(tiles, num, tile, num, 1 - color))
						moves[size++] = num;
				}
			}
			tcol = column;
			trow = row + 1;
			if (tcol > 0 && trow > 0 && tcol < 9 && trow < 9)
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece == 0)
				{
					if (!Helper::IsAttackedKing(tiles, num, tile, num, 1 - color))
						moves[size++] = num;
				}
				else if (tiles[num].colr != color)
				{
					if (!Helper::IsAttackedKing(tiles, num, tile, num, 1 - color))
						moves[size++] = num;
				}
			}
			tcol = column;
			trow = row - 1;
			if (tcol > 0 && trow > 0 && tcol < 9 && trow < 9)
			{
				num = (tcol - 1) * 8 + (trow - 1);
				if (tiles[num].piece == 0)
				{
					if (!Helper::IsAttackedKing(tiles, num, tile, num, 1 - color))
						moves[size++] = num;
				}
				else if (tiles[num].colr != color)
				{
					if (!Helper::IsAttackedKing(tiles, num, tile, num, 1 - color))
						moves[size++] = num;
				}
			}
			if (color == 0)
			{
				if (tiles[0].piece == 5 && tiles[32].piece == 10 && tiles[0].colr == 0 && tiles[32].colr == 0)
				{
					if (tiles[0].IsMoved == 0 && tiles[32].IsMoved == 0)
					{
						if (tiles[8].piece == 0 && tiles[16].piece == 0 && tiles[24].piece == 0)
							if (!Helper::IsAttacked(tiles, 16, 1) && !Helper::IsAttacked(tiles, 24, 1) && !Helper::IsAttacked(tiles, 32, 1))
								moves[size++] = 16;
					}
				}
				if (tiles[56].piece == 5 && tiles[32].piece == 10 && tiles[56].colr == 0 && tiles[32].colr == 0)
				{
					if (tiles[56].IsMoved == 0 && tiles[32].IsMoved == 0)
					{
						if (tiles[40].piece == 0 && tiles[48].piece == 0)
							if (!Helper::IsAttacked(tiles, 32, 1) && !Helper::IsAttacked(tiles, 40, 1) && !Helper::IsAttacked(tiles, 48, 1))
								moves[size++] = 48;
					}
				}
			}
			else
			{
				if (tiles[7].piece == 5 && tiles[39].piece == 10 && tiles[7].colr == 1 && tiles[39].colr == 1)
				{
					if (tiles[7].IsMoved == 0 && tiles[39].IsMoved == 0)
					{
						if (tiles[15].piece == 0 && tiles[23].piece == 0 && tiles[31].piece == 0)
							if (!Helper::IsAttacked(tiles, 23, 0) && !Helper::IsAttacked(tiles, 31, 0) && !Helper::IsAttacked(tiles, 39, 0))
								moves[size++] = 23;
					}
				}
				if (tiles[63].piece == 5 && tiles[39].piece == 10 && tiles[63].colr == 1 && tiles[39].colr == 1)
				{
					if (tiles[63].IsMoved == 0 && tiles[39].IsMoved == 0)
					{
						if (tiles[47].piece == 0 && tiles[55].piece == 0)
							if (!Helper::IsAttacked(tiles, 39, 0) && !Helper::IsAttacked(tiles, 47, 0) && !Helper::IsAttacked(tiles, 55, 0))
								moves[size++] = 55;
					}
				}
			}
			return size;
		}
		default: return 0;
	}
	int resSize = 0;
	for (int i = 0; i < size; i++)
	{
		if (color == 0)
		{
			if (!Helper::IsAttackedKing(tiles, *whiteKing , tile, array[i], 1))
				moves[resSize++] = array[i];
		}
		else
		{
			if (!Helper::IsAttackedKing(tiles, *blackKing, tile, array[i], 0))
				moves[resSize++] = array[i];
		}
	}
	return resSize;
}

bool Helper::IsAttacked(Tile* tiles, int tile, int EnemyColor)
{
	int size;
	int array[200];
	for (int i = 0; i < 64; i++)
	{
		if (tiles[i].piece != 0 && tiles[i].colr == EnemyColor)
		{
			int piece = tiles[i].piece, color = EnemyColor;
			int column = tiles[i].column, row = tiles[i].row;
			int num;
////////////////////////////////////////////////////////////////////////////////
			switch (piece)
			{
				case 1:
				{
					if (EnemyColor == 0)
					{
						int tcol = column - 1, trow = row + 1;
						num = (tcol - 1) * 8 + (trow - 1);
						if (tile == num) return true;
						tcol = column + 1;
						trow = row + 1;
						num = (tcol - 1) * 8 + (trow - 1);
						if (tile == num) return true;
					}
					else
					{
						int tcol = column - 1, trow = row - 1;
						num = (tcol - 1) * 8 + (trow - 1);
						if (tile == num) return true;
						tcol = column + 1;
						trow = row - 1;
						num = (tcol - 1) * 8 + (trow - 1);
						if (tile == num) return true;
                    }
					break;
				}
				case 2:
				{
                    int tcol = column + 2, trow = row + 1;
					num = (tcol - 1) * 8 + (trow - 1);
					if (tcol < 9 && trow < 9)
					{
						if (tile == num) return true;
					}
					tcol = column + 2;
					trow = row - 1;
					num = (tcol - 1) * 8 + (trow - 1);
					if (tcol < 9 && trow > 0)
					{
						if (tile == num) return true;
					}
					tcol = column - 1;
					trow = row - 2;
					num = (tcol - 1) * 8 + (trow - 1);
					if (tcol > 0 && trow > 0)
					{
						if (tile == num) return true;

					}
					tcol = column + 1;
					trow = row - 2;
					num = (tcol - 1) * 8 + (trow - 1);
					if (tcol < 9 && trow > 0)
					{
						if (tile == num) return true;
					}
					tcol = column - 2;
					trow = row - 1;
					num = (tcol - 1) * 8 + (trow - 1);
					if (tcol >0 && trow > 0)
					{
						if (tile == num) return true;
					}
					tcol = column - 2;
					trow = row + 1;
					num = (tcol - 1) * 8 + (trow - 1);
					if (tcol > 0 && trow < 9)
					{
						if (tile == num) return true;
					}
					tcol = column + 1;
					trow = row + 2;
					num = (tcol - 1) * 8 + (trow - 1);
					if (tcol < 9 && trow < 9)
					{
						if (tile == num) return true;
					}
					tcol = column - 1;
					trow = row + 2;
					num = (tcol - 1) * 8 + (trow - 1);
					if (tcol > 0 && trow < 9)
					{
						if (tile == num) return true;
					}
					break;
				}
				case 3:
				{
					int tcol = column + 1, trow = row + 1;
					while (tcol < 9 && trow < 9)
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tiles[num].piece != 0)
						{
							if (tile == num) return true;
							break;
						}
						if (tile == num) return true;
						tcol++;
						trow++;
					}
					tcol = column - 1;
					trow = row - 1;
					while (tcol > 0 && trow > 0)
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tiles[num].piece != 0)
						{
							if (tile == num) return true;
							break;
						}
						if (tile == num) return true;
						tcol--;
						trow--;
					}
					tcol = column + 1;
					trow = row - 1;
					while (tcol < 9 && trow > 0)
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tiles[num].piece != 0)
						{
							if (tile == num) return true;
							break;
						}
						if (tile == num) return true;
						tcol++;
						trow--;
					}
					tcol = column - 1;
					trow = row + 1;
					while (tcol > 0 && trow < 9)
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tiles[num].piece != 0)
						{
							if (tile == num) return true;
							break;
						}
						if (tile == num) return true;
						tcol--;
						trow++;
					}
					break;
				}
				case 5:
				{
					int tcol = column + 1, trow = row ;
					while (tcol < 9 )
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tiles[num].piece != 0)
						{
							if (tile == num) return true;
							break;
						}
						if (tile == num) return true;
						tcol++;
					}
					tcol = column - 1;
					trow = row;
					while (tcol > 0)
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tiles[num].piece != 0)
						{
							if (tile == num) return true;
							break;
						}
						if (tile == num) return true;
						tcol--;
					}
					tcol = column;
					trow = row + 1;
					while (trow < 9 )
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tiles[num].piece != 0)
						{
							if (tile == num) return true;
							break;
						}
						if (tile == num) return true;
						trow++;
					}
					tcol = column;
					trow = row - 1;
					while (trow > 0 )
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tiles[num].piece != 0)
						{
							if (tile == num) return true;
							break;
						}
						if (tile == num) return true;
						trow--;
					}
					break;
				}
				case 8:
				{
					int tcol = column + 1, trow = row + 1;
					while (tcol < 9 && trow < 9)
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tiles[num].piece != 0)
						{
							if (tile == num) return true;
							break;
						}
						if (tile == num) return true;
						tcol++;
						trow++;
					}
					tcol = column - 1;
					trow = row - 1;
					while (tcol > 0 && trow > 0)
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tiles[num].piece != 0)
						{
							if (tile == num) return true;
							break;
						}
						if (tile == num) return true;
						tcol--;
						trow--;
					}
					tcol = column + 1;
					trow = row - 1;
					while (tcol < 9 && trow > 0)
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tiles[num].piece != 0)
						{
							if (tile == num) return true;
							break;
						}
						if (tile == num) return true;
						tcol++;
						trow--;
					}
					tcol = column - 1;
					trow = row + 1;
					while (tcol > 0 && trow < 9)
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tiles[num].piece != 0)
						{
							if (tile == num) return true;
							break;
						}
						if (tile == num) return true;
						tcol--;
						trow++;
					}
					tcol = column + 1;
					trow = row;
					while (tcol < 9 )
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tiles[num].piece != 0)
						{
							if (tile == num) return true;
							break;
						}
						if (tile == num) return true;
						tcol++;
					}
					tcol = column - 1;
					trow = row;
					while (tcol > 0)
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tiles[num].piece != 0)
						{
							if (tile == num) return true;
							break;
						}
						if (tile == num) return true;
						tcol--;
					}
					tcol = column;
					trow = row + 1;
					while (trow < 9 )
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tiles[num].piece != 0)
						{
							if (tile == num) return true;
							break;
						}
						if (tile == num) return true;
						trow++;
					}
					tcol = column;
					trow = row - 1;
					while (trow > 0 )
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tiles[num].piece != 0)
						{
							if (tile == num) return true;
							break;
						}
						if (tile == num) return true;
						trow--;
					}
					break;
				}
				case 10:
				{
					int num, tcol, trow;
					tcol = column;
					trow = row + 1;
					if (trow < 9)
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tile == num) return true;
					}
					tcol = column;
					trow = row - 1;
					if (trow > 0)
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tile == num) return true;
					}
					tcol = column + 1;
					trow = row + 1;
					if (trow < 9 && tcol < 9)
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tile == num) return true;
					}
					tcol = column - 1;
					trow = row + 1;
					if (trow < 9 && tcol > 0)
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tile == num) return true;
					}
					tcol = column + 1;
					trow = row;
					if (tcol < 9)
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tile == num) return true;
					}
					tcol = column - 1;
					trow = row;
					if (tcol > 0)
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tile == num) return true;
					}
					tcol = column - 1;
					trow = row - 1;
					if (trow > 0 && tcol > 0)
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tile == num) return true;
					}
					tcol = column + 1;
					trow = row - 1;
					if (trow > 0 && tcol < 9)
					{
						num = (tcol - 1) * 8 + (trow - 1);
						if (tile == num) return true;
					}
///////////////////
					break;
				}
				default: break;
			}
////////////////////////////////////////////////////////////////////////////////
		}
	}
	return false;
}

bool Helper::IsAttackedKing(Tile* tiles, int me, int tile1, int tile2, int EnemyColor)
{
	Tile temp1 = tiles[tile1];
	Tile temp2 = tiles[tile2];
	tiles[tile2].piece = tiles[tile1].piece;
	tiles[tile2].colr = tiles[tile1].colr;
	tiles[tile1].piece = 0;
	bool A = Helper::IsAttacked(tiles, me, EnemyColor);
	tiles[tile1] = temp1;
	tiles[tile2] = temp2;
	return A;

}

void Helper::Move(Tile* tiles, int tile1, int tile2, TImage* Image, int* whiteKing, int* blackKing, int turn, char** positions, int* size)
{
	int piece = tiles[tile1].piece;
	if (piece == 1)
	{
		if (tiles[tile1].colr == 0)
		{
			if (tiles[tile1].row == 7)
			{
				piece = Form5->ShowModal();
			}
		}
		else
		{
			if (tiles[tile1].row == 2)
			{
				piece = Form5->ShowModal();
			}
		}
	}
	tiles[tile2].SetPiece(piece, tiles[tile1].colr, Image, whiteKing, blackKing);
	tiles[tile1].TakePiece(Image);
	Sleep(400);
	Helper::ReverseField(tiles, Image);
	tiles[tile1].HighlightFrom(Image);
	tiles[tile2].HighlightTo(Image);
	tiles[tile2].IsMoved = 1;
	Helper::SavePosition(tiles, positions, size, turn);
}

void Helper::SavePosition(Tile* tiles, char** positions, int* size, int turn)
{
	int piece, column, row, color;
	char word[6];
	AnsiString str;
	if (turn == 0)
	{
		word[0] = 'b';
		word[1] = '\0';
	}
	else
	{
		word[0] = 'w';
		word[1] = '\0';
	}
	str = str + (AnsiString)word + " ";
	for (int i = 0; i < 64; i++)
	{
		piece = tiles[i].piece;
		color = tiles[i].colr;
		row = tiles[i].row;
		column = tiles[i].column;
		switch(piece)
		{
			case 0: break;
			case 1:
			{
				word[0] = 'p';
				break;
			}
			case 2:
			{
				word[0] = 'n';
				break;
			}
			case 3:
			{
				word[0] = 'b';
				break;
			}
			case 5:
			{
				word[0] = 'r';
				break;
			}
			case 8:
			{
				word[0] = 'q';
				break;
			}
			case 10:
			{
				word[0] = 'k';
				break;
			}
			default: break;
		}
		if (piece == 0)
			continue;
		word[1] = 'a' + column - 1;
		word[2] = '0' + row;
		if (color == 0)
			word[3] = 'w';
		else
			word[3] = 'b';
		word[4] = '\0';
		str = str + (AnsiString)word + " ";
	}
	strcpy(positions[*size], str.c_str());
	*size = *size + 1;
}

int Helper::FindTile(Tile* tiles, int left, int top)
{
	for (int i = 0; i < 64; i++)
	{
		if (tiles[i].left == left && tiles[i].top == top)
		{
			return i;
		}
	}
	return -1;
}

void Helper::ReverseField(Tile* tiles, TImage* Image)
{
	int temp;
	for (int i = 0; i < 64; i++)
	{
		temp = tiles[i].right;
		tiles[i].right = 640 - tiles[i].left;
		tiles[i].left  = 640 - temp;
		temp = tiles[i].bottom;
		tiles[i].bottom = 640 - tiles[i].top;
		tiles[i].top = 640 - temp;
		tiles[i].Show(Image);
	}
}

void Helper::LoadPositionNoReverse(const char* str, Tile* array, int* turn, TImage* Image, int* whiteKing, int* blackKing)
{
	char word[6];
	int pos = 0, index, len, cl, num, piece, i, j;
	TColor col;
	for (i = 1; i <= 8; i++)
		for (j = 1; j <=8; j++)
		{
			col = ((i + j) % 2 == 0)? bTile : wTile;
			array[(i - 1) * 8 + (j - 1)].SetFirstValue(i, j, col);
			array[(i - 1) * 8 + (j - 1)].Show(Image);
		}
	len = strlen(str);
	switch(str[0])
	{
		case 'w': *turn = 0; break;
		case 'b': *turn = 1; break;
		default : return;
	}
	pos = 2;
	while (str[pos] != ' ' && str[pos] != '\n' && pos != len - 1)
	{
		index = 0;
		while (str[pos] != ' ' && str[pos] != '\n' && pos != len - 1)
		{
			word[index++] = str[pos++];
		}
		word[index] = '\0';
		switch(word[3])
		{
			case 'w': cl = 0; break;
			case 'b': cl = 1; break;
		}
		num = (word[1] - 'a') * 8 + (word[2] - '1');
		switch(word[0])
		{
			case 'p': piece = 1; break;
			case 'n': piece = 2; break;
			case 'b': piece = 3; break;
			case 'r': piece = 5; break;
			case 'q': piece = 8; break;
			case 'k':
			{
				if (cl == 0)
					*whiteKing = num;
				if (cl == 1)
					*blackKing = num;
				piece = 10;
				break;
			}
			default : piece = 0; break;
		}
		array[num].SetPiece(piece, cl, Image, whiteKing, blackKing);
		if (pos != strlen(str) - 1)
			pos++;
	}
}

void Helper::LoadPosition(const char* str, Tile* array, int* turn, TImage* Image, int* whiteKing, int* blackKing)
{
	char word[6];
	int pos = 0, index, len, cl, num, piece, i, j;
	TColor col;
	for (i = 1; i <= 8; i++)
		for (j = 1; j <=8; j++)
		{
			col = ((i + j) % 2 == 0)? bTile : wTile;
			array[(i - 1) * 8 + (j - 1)].SetFirstValue(i, j, col);
			array[(i - 1) * 8 + (j - 1)].Show(Image);
		}
	len = strlen(str);
	switch(str[0])
	{
		case 'w': *turn = 0; break;
		case 'b': *turn = 1; break;
		default : return;
	}
	pos = 2;
	while (str[pos] != ' ' && str[pos] != '\n' && pos != len - 1)
	{
		index = 0;
		while (str[pos] != ' ' && str[pos] != '\n' && pos != len - 1)
		{
			word[index++] = str[pos++];
		}
		word[index] = '\0';
		switch(word[3])
		{
			case 'w': cl = 0; break;
			case 'b': cl = 1; break;
		}
		num = (word[1] - 'a') * 8 + (word[2] - '1');
		switch(word[0])
		{
			case 'p': piece = 1; break;
			case 'n': piece = 2; break;
			case 'b': piece = 3; break;
			case 'r': piece = 5; break;
			case 'q': piece = 8; break;
			case 'k':
			{
				if (cl == 0)
					*whiteKing = num;
				if (cl == 1)
					*blackKing = num;
				piece = 10;
				break;
			}
			default : piece = 0; break;
		}
		array[num].SetPiece(piece, cl, Image, whiteKing, blackKing);
		if (pos != strlen(str) - 1)
			pos++;
	}
	if (*turn == 1)
		Helper::ReverseField(array, Image);
}

void Tile::Show(TImage *Image)
{
	Image->Canvas->Brush->Color = color;
	Image->Canvas->Pen->Color = clBlack;
	Image->Canvas->Rectangle(left, top, right, bottom);
	MyGraphics::ShowPiece(piece, top, left, colr, Image);
}

void Tile::SetFirstValue(int column, int row, TColor color)
{
	this->column = column;
	this->row = row;
	this->color = color;
	this->piece = 0;
	this->left = (column - 1) * TileSize;
	this->right = (column) * TileSize;
	this->top = (8 - row) * TileSize;
	this->bottom = (9 - row) * TileSize;
}

void Tile::SetPiece(int piece, int colr, TImage* Image, int* whiteKing, int* blackKing)
{
	if (piece == 10 && colr == 0)
	{
		*whiteKing = (this->column - 1) * 8 + (this->row - 1);
	}
	if (piece == 10 && colr == 1)
	{
		*blackKing = (this->column - 1) * 8 + (this->row - 1);
	}
	this->piece = piece;
	this->colr = colr;
	this->Show(Image);
}

void Tile::TakePiece(TImage* Image)
{
	piece = 0;
	this->Show(Image);
}

void Tile::HighlightFrom(TImage* Image)
{
	Image->Canvas->Brush->Color = clYellow;
	Image->Canvas->Pen->Color = clBlack;
	Image->Canvas->Rectangle(left, top, right, bottom);
	MyGraphics::ShowPiece(piece, top, left, colr, Image);
}

void Tile::HighlightTo(TImage* Image)
{
	Image->Canvas->Brush->Color = (TColor)RGB(170,170,0);
	Image->Canvas->Pen->Color = clBlack;
	Image->Canvas->Rectangle(left, top, right, bottom);
	MyGraphics::ShowPiece(piece, top, left, colr, Image);
}


void Tile::ShowHint(TImage* Image)
{
	if (piece == 0)
	{
		Image->Canvas->Brush->Color = (TColor)RGB(38,38,38);
		Image->Canvas->Pen->Color = clBlack;
		Image->Canvas->Ellipse(left + 20, top + 20, right - 20, bottom - 20);
	}
}



void MyGraphics ::ShowPiece(int piece, int top, int left, int col, TImage* Image)
{
	TColor clPen;
	TColor clBrush;
	if (col == 0)
	{
		clPen = whiteDark;
		clBrush = whiteLight;
	}
	else
	{
		clPen = blackLight;
		clBrush = blackDark;
	}
	switch (piece)
	{
		case 0: break;
		case 1:
		{
			int r = 13;
			int X = 40 + left;
			int Y = 25 + top;
			int width = Image->Canvas->Pen->Width;
			Image->Canvas->Pen->Width = 2;
			Image->Canvas->Pen->Color = clPen;
			Image->Canvas->Brush->Color = clBrush;
			Image->Canvas->Ellipse(X - r, Y - r, X + r, Y + r);
			TPoint* points = new TPoint[4];
			points[0] = Point(X + r + 2, Y + r - 2);
			points[1] = Point(X + r + 7, Y + r + 3);
			points[2] = Point(X - r - 7, Y + r + 3);
			points[3] = Point(X - r - 2, Y + r - 2);
			Image->Canvas->Polygon(points, 3);
			delete points;
			points = new TPoint[6];
			points[0] = Point(X + 6, Y + 16);
			points[1] = Point(X + 6, Y + 36);
			points[2] = Point(X + 21,Y + 45);
			points[3] = Point(X - 21,Y + 45);
			points[4] = Point(X - 6, Y + 36);
			points[5] = Point(X - 6, Y + 16);
			Image->Canvas->Polygon(points, 5);
			delete points;
			Image->Canvas->Pen->Width = width;
			break;
		}
		case 2:
		{
			int width = Image->Canvas->Pen->Width;
			Image->Canvas->Pen->Width = 2;
			Image->Canvas->Pen->Color = clPen;
			Image->Canvas->Brush->Color = clBrush;
			int X = 40 + left;
			int Y = 40 + top;
			Image->Canvas->Rectangle(X - 20,Y + 25,X + 20,Y + 30);
			TPoint* points = new TPoint[8];
			points[0]  = Point(X - 18,Y + 25);
			points[1]  = Point(X     ,Y + 10);
			points[2]  = Point(X     ,Y - 8);
			points[3]  = Point(X - 20,Y);
			points[4]  = Point(X - 25,Y - 5);
			points[5]  = Point(X + 5 ,Y - 25);
			points[6]  = Point(X + 15,Y - 18);
			points[7]  = Point(X + 18,Y + 25);
			Image->Canvas->Polygon(points, 7);
			delete points;
			Image->Canvas->Pen->Width = width;
			break;
		}
		case 3:
		{
			int width = Image->Canvas->Pen->Width;
			Image->Canvas->Pen->Width = 2;
			Image->Canvas->Pen->Color = clPen;
			Image->Canvas->Brush->Color = clBrush;
			int X = 40 + left;
			int Y = 40 + top;
			TPoint* points = new TPoint[7];
			points[0]  = Point(X - 15,Y + 25);
			points[1]  = Point(X - 4 ,Y + 7);
			points[2]  = Point(X - 2 ,Y - 5);
			points[3]  = Point(X + 2 ,Y - 5);
			points[4]  = Point(X + 4 ,Y + 7);
			points[5]  = Point(X + 15,Y + 25);
			Image->Canvas->Polygon(points, 5);
			delete points;
			Image->Canvas->Rectangle(X - 19,Y + 25,X + 21,Y + 30);
			Image->Canvas->Ellipse(X - 10,Y - 30,X + 10,Y);
			Image->Canvas->MoveTo(X,Y - 11);
			Image->Canvas->LineTo(X,Y - 20);
			Image->Canvas->LineTo(X,Y - 11);
			Image->Canvas->MoveTo(X - 5,Y - 15);
			Image->Canvas->LineTo(X + 4,Y - 15);
			Image->Canvas->LineTo(X - 5,Y - 15);
			Image->Canvas->Ellipse(X - 4,Y - 38,X + 4,Y - 28);
			Image->Canvas->Pen->Width = width;
			break;
		}
		case 5:
		{
			int width = Image->Canvas->Pen->Width;
			Image->Canvas->Pen->Width = 2;
			Image->Canvas->Pen->Color = clPen;
			Image->Canvas->Brush->Color = clBrush;
			int X = 40 + left;
			int Y = 40 + top;
			Image->Canvas->Rectangle(X - 19,Y + 15,X + 20,Y + 30);
			TPoint* points = new TPoint[16];
			points[0]  = Point(X - 15,Y + 15);
			points[1]  = Point(X - 15,Y - 15);
			points[2]  = Point(X - 20,Y - 15);
			points[3]  = Point(X - 20,Y - 30);
			points[4]  = Point(X - 10,Y - 30);
			points[5]  = Point(X - 10,Y - 25);
			points[6]  = Point(X - 5, Y - 25);
			points[7]  = Point(X - 5, Y - 30);
			points[8]  = Point(X + 5, Y - 30);
			points[9]  = Point(X + 5, Y - 25);
			points[10] = Point(X + 10,Y - 25);
			points[11] = Point(X + 10,Y - 30);
			points[12] = Point(X + 20,Y - 30);
			points[13] = Point(X + 20,Y - 15);
			points[14] = Point(X + 15,Y - 15);
			points[15] = Point(X + 15,Y + 15);
			Image->Canvas->Polygon(points, 15);
			delete points;
			Image->Canvas->Pen->Width = width;
			break;
		}
		case 8:
		{
			int width = Image->Canvas->Pen->Width;
			Image->Canvas->Pen->Width = 2;
			Image->Canvas->Pen->Color = clPen;
			Image->Canvas->Brush->Color = clBrush;
			int X = 40 + left;
			int Y = 40 + top;
			Image->Canvas->Rectangle(X - 19,Y + 25,X + 20,Y + 30);
			Image->Canvas->Rectangle(X - 15,Y + 16,X + 15,Y + 26);
			TPoint* points = new TPoint[11];
			points[0]  = Point(X - 15,Y + 16);
			points[1]  = Point(X - 20,Y - 13);
			points[2]  = Point(X - 10,Y + 5);
			points[3]  = Point(X - 13,Y - 20);
			points[4]  = Point(X - 5,Y );
			points[5]  = Point(X ,Y - 25);
			points[6]  = Point(X + 5,Y );
			points[7]  = Point(X + 13,Y - 20);
			points[8]  = Point(X + 10,Y + 5);
			points[9]  = Point(X + 20,Y - 13);
			points[10] = Point(X + 13,Y + 16);
			Image->Canvas->Polygon(points, 10);
			delete points;
			Image->Canvas->Pen->Width = width;
			break;
		}
		case 10:
		{
			int X = 40 + left;
			int Y = 40 + top;
			int width = Image->Canvas->Pen->Width;
			Image->Canvas->Pen->Width = 2;
			Image->Canvas->Pen->Color = clPen;
			Image->Canvas->Brush->Color = clBrush;
			Image->Canvas->Rectangle(X - 19,Y + 25,X + 20,Y + 30);
			TPoint* points = new TPoint[10];
			points[0]  = Point(X + 3,Y - 15);
			points[1]  = Point(X - 3,Y - 15);
			points[2]  = Point(X - 3,Y - 26);
			points[3]  = Point(X - 9,Y - 26);
			points[4]  = Point(X - 9,Y - 32);
			points[5]  = Point(X - 3,Y - 32);
			points[6]  = Point(X - 3, Y - 38);
			points[7]  = Point(X + 3, Y - 38);
			points[8]  = Point(X + 3, Y - 32);
			points[9]  = Point(X + 9, Y - 32);
			points[10] = Point(X + 9,Y - 26);
			points[11] = Point(X + 3,Y - 26);
			Image->Canvas->Polygon(points, 11);
			delete points;
			Image->Canvas->Ellipse(X - 20,Y - 20,X + 20,Y);
			points = new TPoint[4];
			points[0]  = Point(X - 5,Y + 25);
			points[1]  = Point(X - 20,Y - 10);
			points[2]  = Point(X + 20,Y - 10);
			points[3]  = Point(X + 5,Y + 25);
			Image->Canvas->Polygon(points, 3);
			delete points;
			Image->Canvas->MoveTo(X, Y - 5);
			Image->Canvas->LineTo(X, Y + 4);
			Image->Canvas->LineTo(X, Y - 5);
			Image->Canvas->MoveTo(X - 5, Y);
			Image->Canvas->LineTo(X + 4, Y);
			Image->Canvas->LineTo(X - 5, Y);
			Image->Canvas->Pen->Width = width;
			break;
		}
		default: break;
	}
}
