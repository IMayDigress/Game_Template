#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>

#define screen_width  1920
#define screen_height  1080


typedef struct Player
{
	Vector2 position;
	//int posX;
	//int	posY;
	int width;
	int height;
	Color color;
} Player;



void	player_init(Player *player_1)
{
	//maybe use a vector? with floats.
	//the ints are probably causing a weird blur in our square character.
	player_1->position.x = screen_width / 2;
	player_1->position.y = screen_height / 2;
	player_1->width = 100;
	player_1->height = 100;
	player_1->color = RED;
}

//it would be better to have the polayer initialized with a global scope, in order for functions like this
//to access it in an easier way. 
void	ft_update(Player* player_1)
{
	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
		player_1->position.x += 10;
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
		player_1->position.x -= 10;
	if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
		player_1->position.y += 10;
	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
		player_1->position.y -= 10;
}



//whenever we want to add stuff to the world, we will update it's condition and position in these update functions
void UpdateCameraCenterSmoothFollow(Camera2D* camera, Player* player, float delta, int width, int height)
{
	static float minSpeed = 30;
	static float minEffectLength = 10;
	static float fractionSpeed = 0.8f;

	camera->offset = {width / 2.0f, height / 2.0f};
	Vector2 diff = Vector2Subtract(player->position, camera->target);
	float length = Vector2Length(diff);

	if (length > minEffectLength)
	{
		float speed = fmaxf(fractionSpeed*length, minSpeed);
		camera->target = Vector2Add(camera->target, Vector2Scale(diff, speed * delta / length));
	}

}




int main(void)
{
	Player player_1{};
	player_init(&player_1);

	Camera2D camera = { 0 };
	camera.target = {player_1.position.x + 20, player_1.position.y + 20};
	camera.offset = { (float)screen_width / 2.0f, (float)screen_height / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f; //always remember to set the zoom to a non Zero value!


	InitWindow(screen_width, screen_height, "Raylib Demo_1 Twitch");
		
	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

	Image image = LoadImage("C:\\Users\\salve\\source\\repos\\GAME_TEMPLATE\\Game_Template\\Background.png");
	Texture2D texture = LoadTextureFromImage(image);
	UnloadImage(image);
	printf("%d\n", texture.height);


	//gameLoop
	while (!WindowShouldClose())
	{
		
		float deltaTime = GetFrameTime();

		ft_update(&player_1);


		UpdateCameraCenterSmoothFollow(&camera, &player_1, deltaTime, screen_width, screen_height);

		BeginDrawing();
			ClearBackground(RAYWHITE);
			//DrawRectangle PRO is better, of course. Use that. 

			BeginMode2D(camera);
			DrawTexture(texture, screen_width / 2 - texture.width / 2, screen_height / 2 - texture.height / 2, BLUE);


			DrawRectangle(player_1.position.x, player_1.position.y, player_1.width, player_1.height,player_1.color);
			EndMode2D();
			
			DrawFPS(50, 50);
		EndDrawing();
	}
	CloseWindow();


	return (0);
	//printf("hello world!\n");
}