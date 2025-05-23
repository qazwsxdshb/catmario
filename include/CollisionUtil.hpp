#ifndef CollisionUtil_HPP
#define CollisionUtil_HPP

#include "App.hpp"

class CollisionUtil {
    static bool Collision(int Ax, int Ay, int Awidth, int Aheight, int Bx, int By, int Bwidth, int Bheight);

    bool RLCollision(int xx, int yy, glm::vec2 playerpos, int rl, int speed, int height, int width,std::vector<std::shared_ptr<Obstacle>> tmp,int zerostart[][],int position[][],int boxsize=30);
    bool UDCollision(int xx, int yy, glm::vec2 playerpos, int ud, int speedd, int height, int width,std::vector<std::shared_ptr<Obstacle>> tmp,int zerostart[][],int position[][],int boxsize=30);

//    bool IsBlockVisible(int x, int y);
};

#endif // CollisionUtil_HPP
