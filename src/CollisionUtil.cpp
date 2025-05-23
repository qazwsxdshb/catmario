#include "CollisionUtil.hpp"
#include "App.hpp"
// 判斷兩個矩形 A 與 B 是否發生碰撞（矩形中心點為基準）
bool CollisionUtil::Collision(int Ax, int Ay, int Awidth, int Aheight, int Bx, int By, int Bwidth, int Bheight){
    int Aleft   = Ax - Awidth/2;
    int Aright  = Ax + Awidth/2;
    int Abottom = Ay - Aheight/2;
    int Atop    = Ay + Aheight/2;

    int Bleft   = Bx - Bwidth/2;
    int Bright  = Bx + Bwidth/2;
    int Bbottom = By - Bheight/2;
    int Btop    = By + Bheight/2;

    return (Aright > Bleft && Bright > Aleft && Btop > Abottom && Atop > Bbottom);
}

// 判斷玩家往左（rl=-1）或往右（rl=1）時，是否會與障礙物發生碰撞
bool CollisionUtil::RLCollision(int xx, int yy, glm::vec2 playerpos, int rl, int speed, int height, int width,std::vector<std::shared_ptr<Obstacle>> tmp,int zerostart[][],int position[][],int boxsize=30){
    // right xx+1 rl=1
    // left  xx-1 rl=-1
    // 右移 = xx+1；左移 = xx-1（rl 決定方向）
    // 檢查以下三個格子是否有障礙物並與玩家碰撞：
    // 1. 玩家正前方格子（同一 row）
    // 2. 玩家上方一格（上半身）
    // 3. 玩家下方一格（下半身）
    if ((zerostart[23-yy][xx]!=0 && tmp[position[23-yy][xx]]->GetVisibility()==1 && Collision((int)(playerpos.x+speed*rl),(int)(playerpos.y),width,height,(xx*boxsize)-345,(yy*boxsize)-345,boxsize,boxsize))
        || (zerostart[23-yy-1][xx]!=0 && tmp[position[23-yy-1][xx]]->GetVisibility()==1 && Collision((int)(playerpos.x+speed*rl),(int)(playerpos.y),width,height,(xx*boxsize)-345,((yy+1)*boxsize)-345,boxsize,boxsize))
        || (zerostart[23-yy+1][xx]!=0 && tmp[position[23-yy+1][xx]]->GetVisibility()==1 && Collision((int)(playerpos.x+speed*rl),(int)(playerpos.y),width,height,(xx*boxsize)-345,((yy-1)*boxsize)-345,boxsize,boxsize))
    ){return true;}
    return false;
}

// 判斷玩家往上（ud=1）或往下（ud=-1）跳動或掉落時，是否會與障礙物發生碰撞
bool CollisionUtil::UDCollision(int xx, int yy, glm::vec2 playerpos, int ud, int speedd, int height, int width,std::vector<std::shared_ptr<Obstacle>> tmp,int zerostart[][],int position[][],int boxsize=30){
    // up    yy+1 ud=1
    // down  yy-1 ud=-1
    // 上移 = yy+1；下移 = yy-1（ud 決定方向）
    // 1. 檢查玩家正上（或正下）方格子是否碰撞
    // 2. 再加上玩家左右兩邊也可能會碰撞（寬度判定）
    if (
        (zerostart[23-yy][xx]!=0 && tmp[position[23-yy][xx]]->GetVisibility()==1 && Collision((int)(playerpos.x),(int)(playerpos.y+(speedd*ud)),width,height,(xx*boxsize)-345,(yy*boxsize)-345,boxsize,boxsize))
        || (zerostart[23-yy][xx+1]!=0 && tmp[position[23-yy][xx+1]]->GetVisibility()==1 && Collision((int)(playerpos.x),(int)(playerpos.y+(speedd*ud)),width,height,((xx+1)*boxsize)-345,(yy*boxsize)-345,boxsize,boxsize))
        || (zerostart[23-yy][xx-1]!=0 && tmp[position[23-yy][xx-1]]->GetVisibility()==1 && Collision((int)(playerpos.x),(int)(playerpos.y+(speedd*ud)),width,height,((xx-1)*boxsize)-345,(yy*boxsize)-345,boxsize,boxsize))
    ){return true;}
    return false;
}

#include "Util/Logger.hpp"

