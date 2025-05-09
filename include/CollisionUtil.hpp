#ifndef CollisionUtil_HPP
#define CollisionUtil_HPP

#include "App.hpp"

class CollisionUtil : public App {
    static bool Collision(int Ax, int Ay, int Awidth, int Aheight, int Bx, int By, int Bwidth, int Bheight);

    bool RLCollision(int xx, int yy, glm::vec2 playerpos, int rl, int speed, int height, int width);
    bool UDCollision(int xx, int yy, glm::vec2 playerpos, int ud, int speedd, int height, int width);

//    bool IsBlockVisible(int x, int y);
};

#endif // CollisionUtil_HPP
