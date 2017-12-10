#include "stdafx.h"
#include "Engine42.h"
#include <fstream>
#include <conio.h>
#include <iostream>
#include <string>
#include <windows.h>

int Engine42::IDCounter = 0;

const enum GameObjects { PLAYER = 'P', NPC = 'N', MOB = 'M', SEWER = 'O', DOOR = '"', COLLECTIBLE = '^', DROP = '*' };

Engine42::Engine42() : m_id(IDCounter++), IsRunning(false), MapLoaded(false)
{
	// Initialize Handle
	console = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Engine42::SetConsoleSize(int height, int width)
{
	// Source: https://stackoverflow.com/questions/21238806/how-to-set-output-console-width-in-visual-studio
	// Solution Author: https://stackoverflow.com/users/2589776/herohuyongtao

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); // Retrieves Consoles Dimensions
	MoveWindow(console, r.left, r.top, width, height, TRUE); // Resizes Console
}

void Engine42::InitializeMap(const std::string FILENAME)
{
	// Set Console Size
	SetConsoleSize(500, 700);

	//Draw Map Layout
	DrawMap(FILENAME);
}

void Engine42::Update()
{
	ListenKeyInput();
	//DebugPosition();
}

void Engine42::Run()
{
	PlayerPosition.first = 7; // X Position
	PlayerPosition.second = 2; // Y Position

	InitializeMap("Map3.txt");


	if (MapLoaded)
	{
		IsRunning = true;
	}

	while (IsRunning)
	{
		Update();
		Draw();
		Sleep(50);
	}
}

void Engine42::Draw()
{
	GotoXY(PlayerPosition.first, PlayerPosition.second, PlayerIcon);
}

void Engine42::DrawMap(const std::string FILENAME)
{
	LoadMapFile(FILENAME);

	if (MapLoaded)
	{
		system("CLS");

		for (auto YPos : Map)
		{
			for (auto XPos : YPos)
			{
				std::cout << XPos;
			}
			std::cout << "\n";
		}
	}
	else
	{
		std::cout << "Map Was Not Loaded Successfully." << std::endl;
	}
}

void Engine42::MovePlayer(enum Direction DIRECTION, int MovementSpeed)
{

	int X = PlayerPosition.first;
	int Y = PlayerPosition.second;
	switch (DIRECTION)
	{
	case RIGHT:
		GotoXY(PlayerPosition.first, PlayerPosition.second, FloorTexture);

		if (Map.at(Y).at(X+2) != WallIcon)
		{
			PlayerPosition.first++;
		}
		break;

	case LEFT:
		GotoXY(PlayerPosition.first, PlayerPosition.second, FloorTexture);

		if (Map.at(Y).at(X-2) != WallIcon)
		{
			PlayerPosition.first--;
		}
		break;

	case UP:
		GotoXY(PlayerPosition.first, PlayerPosition.second, FloorTexture);

		if (Map.at(Y-2).at(X) != WallIcon)
		{
			PlayerPosition.second--;
		}
		break;

	case DOWN:
		GotoXY(PlayerPosition.first, PlayerPosition.second, FloorTexture);
		if (Map.at(Y+2).at(X) != WallIcon)
		{
			PlayerPosition.second++;
		}
		break;
	}
}

void Engine42::DebugPosition()
{

	int X = PlayerPosition.first;
	int Y = PlayerPosition.second;

	GotoXY(0, 27);
	std::cout << "X: " << PlayerPosition.first << "\tY: " << PlayerPosition.second;

	GotoXY(0, 28);
	std::cout << "Next Right Char: " << Map.at(Y).at(X + 2);
}

void Engine42::ListenKeyInput()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		MovePlayer(UP);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		MovePlayer(DOWN);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		MovePlayer(LEFT);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		MovePlayer(RIGHT);
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		IsRunning = false;
	}
}

void Engine42::GotoXY(int X, int Y)
{
	// Author: whitenite1
	// Source : http://www.cplusplus.com/forum/general/51271/
	CursorPosition.X = X;
	CursorPosition.Y = Y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void Engine42::GotoXY(int X, int Y, std::string text)
{
	CursorPosition.X = X;
	CursorPosition.Y = Y;
	SetConsoleCursorPosition(console, CursorPosition);
	std::cout << text;
}

void Engine42::LoadMapFile(const std::string FILENAME)
{
	std::ifstream file(FILENAME);
	std::string line;

	if (file.is_open()) // Test if File Opens Successfully
	{
		Map.clear(); //Clear Map Incase New Map Is Being Loaded

		//Initialise X Position of Map
		std::vector<char> XPos;

		while (file.good()) // Loop While File Is In A Good State
		{
			getline(file, line);

			if (!line.empty())
			{
				for (char c : line)
				{
					// Push Current Character into 'XPos' vector
					XPos.push_back(c);

					switch (c)
					{
					case PLAYER:
						break;
					case NPC:
						break;
					case MOB:
						break;
					case DOOR:
						break;
					case DROP:
						break;
					case COLLECTIBLE:
						break;
					}
				}
			}
			// Push Vector of X-Positions and it's corresponding Character
			Map.push_back(XPos);

			XPos.clear(); // Clear X-Position Array for Next Line
		}

		file.close(); // Close File

		MapLoaded = true;
	}
}