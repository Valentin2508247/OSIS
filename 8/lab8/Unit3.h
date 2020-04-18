//---------------------------------------------------------------------------
#include <vcl.h>
#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#endif

class Piece;
class Pawn;
class Rook;
class Bishop;
class Knight;
class King;
class Queen;
class Tile;

class Helper
{
	public:
	static void LoadPosition(const char* filename, Tile* array, int* turn, TImage* Image, int* whiteKing, int* blackKing);
	static void LoadPositionNoReverse(const char* filename, Tile* array, int* turn, TImage* Image, int* whiteKing, int* blackKing);
	static void ReverseField(Tile* tiles, TImage* Image);
	static int FindTile(Tile* tiles, int left, int top);
	static void SavePosition(Tile* tiles, char** positions, int* size, int turn);
	static void Move(Tile* tiles, int tile1, int tile2, TImage* Image, int* whiteKing, int* blackKing, int turn, char** positions, int* size);
	static void Turn(Tile* tiles, int X, int Y, int* turn, TImage* Image, int* whiteKing, int* blackKing, char** positions, int* size); ////finish
	static int AppropriateTiles(Tile* tiles, int tile, int* array, int* whiteKing, int* blackKing);//finish  // returns array size
	static bool IsAttacked(Tile* tiles, int tile, int EnemyColor);
	static bool IsAttackedKing(Tile* tiles, int me, int tile1, int tile2, int EnemyColor);
	static int AllMyMoves(Tile* tiles, int MyColor, int* whiteKing, int* blackKing);
	static int Game(Tile* tiles, int turn, int* whiteKing, int* blackKing);
};

class MyGraphics
{
	public:
	static void ShowPiece(int piece, int top, int left, int col, TImage* Image);
};

class Tile
{
	public:
	static const int TileSize = 80;
	int piece;
	int colr;
	int column;
	int row;
	int left;
	int right;
	int top;
	int bottom;
	int IsMoved;
	TColor color;
	void SetPiece(int piece, int colr, TImage* Image, int* whiteKing, int* blackKing);
	void TakePiece(TImage* Image);
	void SetFirstValue(int column, int row, TColor color);
	void Show(TImage* Image);
	void ShowHint(TImage* Image);
	void HighlightFrom(TImage* Image);
	void HighlightTo(TImage* Image);
};

