#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define screen_width  1920
#define screen_height  1080


#define XBOX360_LEGACY_NAME_ID "Xbox Controller"
#if defined(PLATFORM_RPI)
	#define XBOX360_NAME_ID	"Microsoft X-Box 360 pad"
#else
	#define XBOX360_NAME_ID "Xbox 360 Controller"
#endif 


typedef struct Player
{
	Vector2 position;
	//int posX;
	//int	posY;
	Vector2 rotation;
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
	//player_1->rotation.x = player_1->position.x / 2;
	//player_1->rotation.y = player_1->position.y / 2;
	player_1->width = 100;
	player_1->height = 100;
	player_1->color = RED;
}

//it would be better to have the polayer initialized with a global scope, in order for functions like this
//to access it in an easier way. 
void	ft_update(Player* player_1, int gamepad)
{
	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
		player_1->position.x += 10;
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
		player_1->position.x -= 10;
	if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
		player_1->position.y += 10;
	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
		player_1->position.y -= 10;

	//player_1->rotation = GetMousePosition();

	if (IsGamepadAvailable(gamepad))
		//printf("gamepad hello\n");
	{
		float left_joystick_x = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X);
		player_1->position.x += GetFrameTime() * 500.0f * left_joystick_x;
		float left_joystick_y = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y);
		player_1->position.y += GetFrameTime() * 500.0f * left_joystick_y;
	}
}



//whenever we want to add stuff to the world, we will update it's condition and position in these update functions
void UpdateCameraCenterSmoothFollow(Camera2D* camera, Vector2 target, float delta, int width, int height)
{
	static float minSpeed = 30;
	static float minEffectLength = 10;
	static float fractionSpeed = 0.8f;

	camera->offset = {width / 2.0f, height / 2.0f};
	Vector2 diff = Vector2Subtract(target, camera->target);
	float length = Vector2Length(diff);

	if (length > minEffectLength) //TODO: understand what's going on trigonometrically over here. 
	{
		float speed = fmaxf(fractionSpeed*length, minSpeed);
		camera->target = Vector2Add(camera->target, Vector2Scale(diff, speed * delta / length)); //this is the actual update function
	}

}


int main(void)
{
	Player player_1{};
	player_init(&player_1);
	int gamepad = 0;
	Camera2D camera = { 0 };
	camera.target = {player_1.position.x , player_1.position.y};
	camera.offset = { (float)screen_width / 2.0f, (float)screen_height / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f; //always remember to set the zoom to a non Zero value!

	Vector2 cameraTarget = { player_1.position.x, player_1.position.y };

	InitWindow(screen_width, screen_height, "Raylib Demo_1 Twitch");
	

	//TODO: Not a goo practice, better  to use Delta Time setup 
	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second


	Image image = LoadImage("C:\\Users\\salve\\source\\repos\\GAME_TEMPLATE\\Game_Template\\Background.png");
	Texture2D texture = LoadTextureFromImage(image);
	UnloadImage(image);


	float rotationAngle = 0.0f;
	float right_joystick_y = 0.0f;
	float right_joystick_x = 0.0f;
	//gameLoop
	while (!WindowShouldClose())
	{
		
		float deltaTime = GetFrameTime();
		

		//Probably not the best idea, 
		//find an intelligent way to handle both mouse and joypad.

			Vector2 mouse_position = GetMousePosition();
			rotationAngle = atan2(mouse_position.y - player_1.position.y, mouse_position.x - player_1.position.x);
	
		//else if(IsGamepadAvailable(gamepad))
			//right_joystick_y = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y);
			//right_joystick_x = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X);
			//Vector2 right_stick_rotation = { right  };
		//rotationAngle = atan2(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y), GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X));

		
		printf("%f\n", rotationAngle);
		
		ft_update(&player_1, gamepad);
		
		cameraTarget = player_1.position;

		UpdateCameraCenterSmoothFollow(&camera, cameraTarget, deltaTime, screen_width, screen_height);

		BeginDrawing();
			ClearBackground(RAYWHITE);
			//DrawRectangle PRO is better, of course. Use that. 

		//	BeginMode2D(camera);
				DrawTexture(texture, screen_width / 2 - texture.width / 2, screen_height / 2 - texture.height / 2, BLUE);
		
			//Vector2 origin = { player_1.position.x, player_1.position.y };
			//float rotation = Vector2Angle(player_1.rotation, GetMousePosition());
			//DrawRectanglePro(player_rect, player_1.rotation, rotationAngle * RAD2DEG, RED);
			//DrawRectangle(player_1.position.x, player_1.position.y, player_1.width, player_1.height,player_1.color);
			
				DrawRectanglePro(
					{player_1.position.x, player_1.position.y, (float)player_1.width, (float)player_1.height},
					{(float)player_1.width / 2, (float)player_1.height / 2 },
					rotationAngle * RAD2DEG , 
					RED);

		//	EndMode2D();
			//DrawText(rotationtxt, 70, 70, 30, BLUE);
			DrawFPS(50, 50);
		EndDrawing();
	}
	CloseWindow();


	return (0);
	//printf("hello world!\n");
}