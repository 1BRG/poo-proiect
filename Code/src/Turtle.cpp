//
// Created by Gabriel on 4/16/2025.
//

#include "../include/entitati/Turtle.h"

int Turtle::isd = 0;



Turtle::Turtle(const double x, const double y) : Enemy(x, y, TurtleTexture) {
    health = 2;
    damage = 1;
    speed = DefaultSpeed;
}

void Turtle::update() {
    moveX();
    moveY();
}

void Turtle::collision(Entity &other, int directie) {

    if (directie == 1) {
        lastY = coordY;
        updateBottom = false;
        targetY = min(targetY, other.coord_y() - y - 1);
    }
    else if (directie == -1) {
        cont = false;
        updateTop = false;
        cont = false;
        canJump = false;
    }
    else if (directie == 2 && targetX - coordX > 0) {
        targetX = min(targetX, other.coord_x() - x - 1), change = true;
    }
    else if (directie == -2 && targetX - coordX < 0) {
        targetX = max(targetX, other.coord_x() + other.width() + 1), change = true;
    }
    if (other.danger() > 1)
        tookDamage = true;
}

void Turtle::collision(){}

void Turtle::moveToTarget() {
    if (change) speed *= -1;
    else coordX = targetX, coordY = targetY;
    change = false;
    if (tookDamage) {
        health --;
        texture = FuriousTurtleTexture;
        x = texture.width;
        y = texture.height;
        damage ++;
        speed *= 2;
    }
    tookDamage = false;
    targetY = coordY;
    targetX = coordX;
}