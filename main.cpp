#include "raylib.h"
#include "objects.h"

int main(void)
{
    static int Width = 1920/2;
    static int Height = 1080/2;
    InitWindow(Width, Height, "whatthefuck");

    bool drawing = false;
    bool Vdrawing = false;

    Vector2 mousePos[2];

    //spawn a circle which we will control!
    circle C1({(float)Width/2, (float)Height/2,}, {0,0}, WHITE, 20);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Detect if we are clicking currently
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            drawing = true;
            mousePos[0] = GetMousePosition();
            
            // Let's see if we are clicking on our ball, if yes - Vdrawing = true
            if (C1.isClicked(GetMousePosition(), drawing, 10.0f)) Vdrawing = true;
        }

        if (drawing) mousePos[1] = GetMousePosition();

                // If we release LMB
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            drawing = false;
                // If we were holding the ball - calculate it's  velocity!
            if (Vdrawing) {
                C1.velocity.x = 0;
                C1.velocity.y = 0;
                C1.velocityUpdate(mousePos[0], math::getLineMax(mousePos[0], mousePos[1]));
                Vdrawing = false;
            }
        }

        if (!Vdrawing) {
            //C1.velocityUpdateOnGravityPull(C1.position, {(float)Width/2, (float)Height/2}, 32, 32);
            C1.velocityUpdate(GetFrameTime());
            C1.positionUpdate();
        }
        
        preventClipping(&C1, checkWindowBorderCollision(&C1, Width, Height), Width, Height);

        BeginDrawing();

        ClearBackground(DARKBLUE);
        if (drawing) DrawLineV(mousePos[0], math::getLineMax(mousePos[0], mousePos[1]), WHITE);
        if (drawing) {
            //std::cout << "M0x: " << mousePos[0].x << " M0y: " << mousePos[0].y << " M1x: " << mousePos[1].x << " M1y: " << mousePos[1].y << std::endl;
        }
        DrawCircleV(C1.position, C1.radius, C1.color);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    char c;
    std::cin >> c;
    return 0;
}