// L20250414_Ex.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>

struct PlayerInfo
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
std::string* Initialized(PlayerInfo* PlayerData, MapInfo* MapData);
char Input();
bool ChechDoMove(int X, int Y, std::string* Map);
bool Move(PlayerInfo* Player, MapInfo* MapData, std::string* Map, int MoveX, int MoveY);
bool Tick(char Input, PlayerInfo* PlayerData, MapInfo* MapData, std::string* Map);
void Render(PlayerInfo* PlayerDatas, std::string* Map, MapInfo* MapData);


int main()
{
	PlayerInfo PlayerData;
	MapInfo MapData;
	std::string* Map = nullptr;
	bool IsRunning = true;

	Map = Initialized(&PlayerData, &MapData);

	while (IsRunning)
	{
		char key = Input();
		bool Exit = Tick(key, &PlayerData, &MapData, Map);
		if (IsRunning != Exit)
		{
			IsRunning = Exit;
		}
		Render(&PlayerData, Map,&MapData);
	}
	delete[] Map;
}

void ClearMap(std::string* Map, MapInfo* MapData)
{
	for (int Y = 0; Y < MapData->Heigh; Y++)
	{
		std::string MapLine = "";
		for (int X = 0; X < MapData->Width; X++)
		{
			if (X == 0 || Y == 0 || X == (MapData->Width-1) || X == (MapData->Heigh - 1))
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

std::string* Initialized(PlayerInfo* PlayerData, MapInfo* MapData)
{
	PlayerData->X = 5;
	PlayerData->Y = 5;
	PlayerData->Shape = 'P';

	MapData->Heigh = 10;
	MapData->Width = 10;
	MapData->WallShape = '*';
	MapData->GroundShape = ' ';
	std::string* NewMap = new std::string[MapData->Width];
	ClearMap(NewMap,MapData);
	return NewMap;
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

bool ChechDoMove(int X, int Y, std::string* Map)
{
	return (Map[Y][X] != '*');
}

bool Move(PlayerInfo* Player, MapInfo* MapData, std::string* Map, int MoveX=0, int MoveY=0)
{
	int X = Player->X + MoveX;
	int Y = Player->Y + MoveY;
	if (X > MapData->Width || Y > MapData->Heigh)
		return false;

	if (ChechDoMove(X, Y, Map))
	{
		Player->X += MoveX;
		Player->Y += MoveY;
	}
	return true;
}


bool Tick(char Input, PlayerInfo* PlayerData, MapInfo* MapData, std::string* Map)
{
	bool value = true;
	switch (toupper(Input))
	{
	case 'W':
		Move(PlayerData, MapData, Map, 0, -1);
		break;
	case 'A':
		break;
		Move(PlayerData, MapData, Map, -1, 0);
	case 'S':
		Move(PlayerData, MapData, Map, 0, 1);
		break;
	case 'D':
		Move(PlayerData, MapData, Map, 1, 0);
		break;
	case 'P':
		value = false;
		break;
	default:
		break;
	}
	return value;
}

void Render(PlayerInfo* PlayerData, std::string* Map, MapInfo* MapData)
{
	ClearMap(Map,MapData);
	Map[PlayerData->Y][PlayerData->X] = PlayerData->Shape;
	for (int Y = 0; Y < MapData->Heigh; Y++)
	{
		std::cout << Map[Y] << std::endl;
	}
}