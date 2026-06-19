#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

struct Vector2D {
    float x;
    float y;
};

struct GameObject {
    int id;
    Vector2D position;
    Vector2D speed;
};

void gameobject_create(GameObject *obj, int id, float x, float y, float sx, float sy);

#endif