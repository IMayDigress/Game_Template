#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define screen_width  1920
#define screen_height  1080


typedef struct Player
{
	int posX;
	int	posY;
	int width;
	int height;
	Color color;
} Player;



void	player_init(Player *player_1)
{
	//maybe use a vector? with floats.
	//the ints are probably causing a weird blur in our square character.
	player_1->posX = screen_width / 2;
	player_1->posY = screen_height / 2;
	player_1->width = 100;
	player_1->height = 100;
	player_1->color = RED;
}

//it would be better to have the polayer initialized with a global scope, in order for functions like this
//to access it in an easier way. 
void	ft_update(Player *player_1)
{
	if (IsKeyDown(KEY_RIGHT))
		player_1->posX += 10;
	if (IsKeyDown(KEY_LEFT))
		player_1->posX -= 10;
	if (IsKeyDown(KEY_DOWN))
		player_1->posY += 10;
	if (IsKeyDown(KEY_UP))
		player_1->posY -= 10;
}


int main(void)
{
	Player player_1{};
	player_init(&player_1);

	Camera2D camera = { 0 };
	camera.target = {(float)player_1.posX + 20, (float)player_1.posY + 20 };
	camera.offset = { (float)screen_width / 2.0f, (float)screen_height / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;


	InitWindow(screen_width, screen_height, "Raylib Demo_1 Twitch");
		
	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

	while (!WindowShouldClose())
	{

		ft_update(&player_1);

		BeginDrawing();
			ClearBackground(RAYWHITE);
			
			//DrawRectangle PRO is better, of course. Use that. 
			DrawRectangle(player_1.posX, player_1.posY, player_1.width, player_1.height,player_1.color);
			DrawFPS(50, 50);
		EndDrawing();
	}
	CloseWindow();

	return (0);
	//printf("hello world!\n");
}