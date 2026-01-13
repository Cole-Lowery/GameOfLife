/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include "resource_dir.h"
#include <vector>

	const int screenWidth = 800;
	const int screenHeight = 800;

	const int gridWidth = 80;
	const int gridHeight = 80;
	
	const float cellWidth = screenWidth / (float)gridWidth;
	const float cellHeight = screenHeight / (float)gridHeight;

	using Cells = std::vector<bool>;

	bool readCell(int x, int y, const Cells& cells)
	{
		if (x < 0) x = gridWidth - 1;
		if (x >= gridWidth -1) x = 0;
		if (y < 0) y = gridWidth - 1;
		if (y >= gridWidth -1) y = 0;

		return cells[x + (y * gridWidth)];
	}

	void writeCell(int x, int y, Cells& cells,  bool value)
	{
		cells[x + (y * gridWidth)] = value;
	}

	void randomizeCells(Cells& cells)
	{
		for (int y = 0; y < gridHeight; ++y)
		{
			for (int x = 0; x < gridWidth; ++x)
			{
				writeCell(x, y, cells, GetRandomValue(0, 1) == 1);
			}
		}
	}

	int countLiveNeighbors(int x, int y, const Cells& cells)
	{
		int count = 0;
		if (readCell(x-1, y-1, cells)) ++count;
		if (readCell(x+1, y - 1, cells)) ++count;
		if (readCell(x+1, y + 1, cells)) ++count;
		if (readCell(x-1, y + 1, cells)) ++count;

		if (readCell(x-1, y + 0, cells)) ++count;
		if (readCell(x+1, y - 0, cells)) ++count;
		if (readCell(x+0, y - 1, cells)) ++count;
		if (readCell(x-0, y + 1, cells)) ++count;
		return count;
	}

int main ()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(screenWidth, screenHeight, "Game of Life");


	SearchAndSetResourceDir("resources");

	Cells currentGeneration(gridWidth * gridHeight, false);

	Cells nextGeneration(gridWidth * gridHeight, false);

	randomizeCells(currentGeneration);

	while (!WindowShouldClose())	
	{
		std::fill(nextGeneration.begin(), nextGeneration.end(), false);

		BeginDrawing();

		ClearBackground(BLACK); 

		for (int y = 0; y< gridHeight; ++y)
		{
			for (int x = 0; x< gridWidth; ++x)
			{
				if (readCell(x, y, currentGeneration))
				{
					DrawRectangle((int)(x * cellWidth), (int)(y * cellHeight), (int)cellWidth + 1, (int)cellHeight + 1, WHITE);
				}
			}
		}

		DrawText("Space: Randomize Cells", 20, 20, 20, BLUE);

		if (IsKeyPressed(KEY_SPACE))
		{
			randomizeCells(currentGeneration);
		}

		DrawFPS(40, 40);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
