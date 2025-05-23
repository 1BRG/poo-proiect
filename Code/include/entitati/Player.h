//
// Created by Gabriel on 4/16/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "Living.h"


class Player : public Living {
    static std::string MarioIDLE;
    static std::string MarioRUN;
    static std::string MarioJUMP;
    static std::string MarioSKIDDING;
    bool gaveDamage {false};

public:
    Player(float x, float y);

    Player() = default;

    void handleInput();

    // void moveX();
    //void moveY();
    void update() override;

    void collision(Entity &other, int direction) override;

    static void collision();

    void moveToTarget() override;

    [[nodiscard]] Player *clone() const override;

    Player(const Player &other) = default;

    //void moveToTarget() override;
    // void gravity() override;
    //  void setLastY() override;
};


#endif //PLAYER_H
