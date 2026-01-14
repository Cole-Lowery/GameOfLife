#include "raylib.h"

#include "resource_dir.h"	

#include <vector>

const int screenWidth = 800;
const int screenHeight = 800;

const int gridWidth = 80;
const int gridHeight = 80;

const int cellWidth = (float)screenWidth / float(gridWidth);
const int cellHeight = screenHeight / float(gridHeight);

using Cells = std::vector<bool>;

bool ReadCell(int x, int y, const Cells& cells)
{
	if (x < 0) x = gridWidth - 1;
	else if (x > gridWidth - 1) x = 0;

	if (y < 0) y = gridHeight - 1;
	else if (y > gridHeight - 1) y = 0;

	return cells[x + (y * gridWidth)];
}

bool WriteCell(int x, int y, bool value, Cells& cells) {
	if (x < 0) x = gridWidth - 1;
	else if (x > gridWidth - 1) x = 0;

	if (y < 0) y = gridHeight - 1;
	else if (y > gridHeight - 1) y = 0;

	return cells[x + y * gridWidth] = value;
}

void RandomizeCells(Cells& cells) {
	for (int i = 0; i < (int)cells.size(); i++) {
		cells[i] = GetRandomValue(0, 1) != 0;
	}
}

int CountAliveNeighbors(int x, int y, const Cells& cells) {
	int count = 0;
	if (ReadCell(x - 1, y + 1, cells)) count++;
	if (ReadCell(x + 0, y + 1, cells)) count++;
	if (ReadCell(x + 1, y + 1, cells)) count++;
	if (ReadCell(x - 1, y + 0, cells)) count++;
	if (ReadCell(x + 1, y + 0, cells)) count++;
	if (ReadCell(x - 1, y - 1, cells)) count++;
	if (ReadCell(x + 0, y - 1, cells)) count++;
	if (ReadCell(x + 1, y - 1, cells)) count++;

	return count;
}

int main ()
{
	int targetFPS = 10;

	InitWindow(screenWidth, screenHeight, "GameOfLife");

	SearchAndSetResourceDir("resources");
	
	Cells currentGeneration(gridWidth * gridHeight);
	Cells nextGeneration(gridWidth * gridHeight);

	RandomizeCells(currentGeneration);
	while (!WindowShouldClose())		
	{
		std::fill(nextGeneration.begin(), nextGeneration.end(), false);
		SetTargetFPS(targetFPS);

		BeginDrawing();

		ClearBackground(BLACK);
		if (!IsKeyDown(KEY_SPACE)) {
			for (int y = 0; y < gridHeight; y++) {
				for (int x = 0; x < gridWidth; x++) {
					if ((ReadCell(x, y, currentGeneration) && CountAliveNeighbors(x, y, currentGeneration) == 2) || CountAliveNeighbors(x, y, currentGeneration) == 3) {
						WriteCell(x, y, true, nextGeneration);
						DrawRectangle((int)(x * cellWidth), (int)(y * cellHeight), cellWidth, cellHeight, WHITE);
					}
					else {
						WriteCell(x, y, false, nextGeneration);
					}
				}
			}

			currentGeneration = nextGeneration;
			
		}
		else {
			RandomizeCells(currentGeneration);
			for (int y = 0; y < gridHeight; y++) {
				for (int x = 0; x < gridWidth; x++) {
					if (ReadCell(x, y, currentGeneration)) {
						DrawRectangle((int)(x * cellWidth), (int)(y * cellHeight), cellWidth, cellHeight, WHITE);
					}
				}
			}
		}
		
		DrawText("Space: Randomize", 40,20,20,WHITE);
		DrawFPS(40, 40);	
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
