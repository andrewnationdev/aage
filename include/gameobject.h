#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

struct EngineContext;

struct Vector2D {
    float x;
    float y;
};

struct GameObject {
    int id;
    Vector2D position;
    Vector2D speed;
    int health;
};

void gameobject_create(GameObject *obj, int id, float x, float y, float sx, float sy);

void gameobject_destroy(EngineContext *ctx, int index);

#endif