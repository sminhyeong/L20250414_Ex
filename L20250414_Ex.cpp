// L20250414_Ex.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <windows.h>

enum GameMode
{
	Start = 0,
	Do,
	Exit,
	Lose,
	Win
};
struct CharacerInfo
{
	int X;
	int Y;
	char Shape;
};

struct MapInfo
{
	int Width;
	int Heigh;
	char WallShape;
	char GroundShape;
};
void ClearMap(std::string* Map, MapInfo* MapData);
void Initialized(CharacerInfo* PlayerData, CharacerInfo* MonsterData, MapInfo* MapData, std::string** Map);
char Input();
bool PredictMove(int X, int Y, std::string* Map);
bool Move(CharacerInfo* Player, MapInfo* MapData, std::string* Map, int MoveX, int MoveY);
void MonsterMove(CharacerInfo* MonsterData, MapInfo* MapData, std::string* Map, int MoveX, int MoveY);
GameMode Tick(char Input, CharacerInfo* PlayerData, CharacerInfo* MonsterData, MapInfo* MapData, std::string* Map);
void Render(CharacerInfo* PlayerDatas, CharacerInfo* MonsterData, std::string* Map, MapInfo* MapData);

void GotoXY(int X, int Y)
{
	COORD Cur;
	Cur.X = X;
	Cur.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}


int main()
{
	CharacerInfo* PlayerData = new CharacerInfo();
	CharacerInfo*MonsterData = new CharacerInfo();
	MapInfo *MapData = new MapInfo();
	std::string* Map = nullptr;
	bool IsRunning = true;

	Initialized(PlayerData, MonsterData, MapData, &Map);
	
	while (IsRunning)
	{
		char key = Input();
		GameMode Exit = Tick(key, PlayerData, MonsterData, MapData, Map);
		if (Exit >= GameMode::Exit)
		{
			IsRunning = false;
		}

		Render(PlayerData, MonsterData, Map, MapData);
	}

	delete PlayerData;
	PlayerData = nullptr;
	delete MapData;
	MapData = nullptr;
	delete[] Map;
	Map = nullptr;
}

void ClearMap(std::string* Map, MapInfo* MapData)
{
	for (int Y = 0; Y < MapData->Heigh; Y++)
	{
		std::string MapLine = "";
		for (int X = 0; X < MapData->Width; X++)
		{
			if (X == 0 || Y == 0 || X == (MapData->Width - 1) || Y == (MapData->Heigh - 1))
			{
				MapLine += "*";
			}
			else
			{
				MapLine += " ";
			}
		}
		Map[Y] = MapLine;
	}
}

void Initialized(CharacerInfo* PlayerData, CharacerInfo* MonsterData,MapInfo* MapData, std::string** Map)
{
	PlayerData->X = 5;
	PlayerData->Y = 5;
	PlayerData->Shape = 'P';

	MonsterData->X = 7;
	MonsterData->Y = 7;
	MonsterData->Shape = 'M';


	MapData->Heigh = 10;
	MapData->Width = 10;
	MapData->WallShape = '*';
	MapData->GroundShape = ' ';
	std::string* NewMap = new std::string[MapData->Width];
	ClearMap(NewMap, MapData);
	*Map = NewMap;
	srand((unsigned int)time(NULL));
}

char Input()
{
	char var = '\0';
	if (_kbhit())
	{
		int key = _getch();
		var = key;
	}
	return var;
}

bool PredictMove(int X, int Y, std::string* Map)
{
	return (Map[Y][X] != '*');
}

bool Move(CharacerInfo* Player, MapInfo* MapData, std::string* Map, int MoveX = 0, int MoveY = 0)
{
	int X = Player->X + MoveX;
	int Y = Player->Y + MoveY;
	if (X > MapData->Width - 1 || Y > MapData->Heigh - 1 || X < 0 || Y < 0)
		return false;

	if (PredictMove(X, Y, Map))
	{
		Player->X = Player->X + MoveX;
		Player->Y = Player->Y + MoveY;
	}
	return true;
}

void MonsterMove(CharacerInfo* MonsterData, MapInfo* MapData, std::string* Map, int MoveX = 0, int MoveY = 0)
{
	switch (((rand() % 4) + 1))
	{
	case 1:
		Move(MonsterData, MapData, Map, 0, -1);
		break;
	case 2:
		Move(MonsterData, MapData, Map, -1, 0);
		break;
	case 3:
		Move(MonsterData, MapData, Map, 0, 1);
		break;
	case 4:
		Move(MonsterData, MapData, Map, 1, 0);
		break;
	default:
		break;
	}
}
GameMode Tick(char Input, CharacerInfo* PlayerData, CharacerInfo* MonsterData, MapInfo* MapData, std::string* Map)
{
	GameMode value = GameMode::Do;

	switch (toupper(Input))
	{
	case 'W':
		Move(PlayerData, MapData, Map, 0, -1);
		MonsterMove(MonsterData, MapData, Map, 0, -1);
		break;
	case 'A':
		Move(PlayerData, MapData, Map, -1, 0);
		MonsterMove(MonsterData, MapData, Map, -1, 0);
		break;
	case 'S':
		Move(PlayerData, MapData, Map, 0, 1);
		MonsterMove(MonsterData, MapData, Map, 0, 1);
		break;
	case 'D':
		Move(PlayerData, MapData, Map, 1, 0);
		MonsterMove(MonsterData, MapData, Map, 1, 0);
		break;
	case 'P':
		value = GameMode::Exit;
		break;
	default:
		break;
	}


	if (Map[PlayerData->Y][PlayerData->X] == 'G')
	{
		value = GameMode::Win;
	}

	return value;
}

void Render(CharacerInfo* PlayerData, CharacerInfo* MonsterData, std::string* Map, MapInfo* MapData)
{
	//system("cls");

	ClearMap(Map, MapData);
	Map[MapData->Heigh - 2][MapData->Width - 2] = 'G';
	Map[MonsterData->Y][MonsterData->X] = MonsterData->Shape;
	Map[PlayerData->Y][PlayerData->X] = PlayerData->Shape;
	for (int Y = 0; Y < MapData->Heigh; Y++)
	{
		GotoXY(0,Y);
		std::cout << Map[Y] << std::endl;
	}
}