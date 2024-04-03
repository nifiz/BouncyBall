#pragma once
#include "raylib.h"
#include <cmath>
//Default earth acceleration
#define GRAVITY 9.81
#define GRAV_CONST 6.673
namespace math {

Vector2 getLineMax(Vector2 start, Vector2 end, float MAX_DISTANCE = 100.0f);

}

float getDistanceV(Vector2 A, Vector2 B);

float gravityForce(float M1, float M2, float dist);
