#include "App.hpp"
#include "spdlog/fmt/bundled/xchar.h"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include <thread>
#include <chrono>

bool Collision(int Ax, int Ay, int Awidth, int Aheight, int Bx, int By, int Bwidth, int Bheight) {
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

void App::Die() {
    if (sec==0){
        m_PRM->BgZindex(-10);
        m_PRM->Select(1);
        text->Settext(" ");
        m_CurrentState=State::UPDATE;
    }
    else{sec-=1;}
    m_Root.Update({0,0});
}

void App::Update() {
    if(sec>0) {sec-=1;}
    if(opsec>0) {opsec-=1;}
    glm::vec2 ofsetzero={0,0};

    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::P) && opsec==0) {
        opsec=60;
        Acceleration=0;
        bug=(bug+1)%2;
    }

    auto playerpos=m_player->GetPosition();
    playerpos.x+=zerox;
    int yy=round((345+playerpos.y)/boxsize);
    int xx=round((345+playerpos.x)/boxsize);

    if (bug==1) {
        if (Util::Input::IsKeyPressed(Util::Keycode::W) || Util::Input::IsKeyPressed(Util::Keycode::SPACE)) {
            if ((zerostart[23-yy-1][xx]!=0 && Collision((int)(playerpos.x),(int)(playerpos.y+speed),playerwidth,playerheight,(xx*boxsize)-345,((yy+1)*boxsize)-345,boxsize,boxsize))
            || (zerostart[23-yy-1][xx+1]!=0 && Collision((int)(playerpos.x),(int)(playerpos.y+speed),playerwidth,playerheight,((xx+1)*boxsize)-345,((yy+1)*boxsize)-345,boxsize,boxsize))
            || (zerostart[23-yy-1][xx-1]!=0 && Collision((int)(playerpos.x),(int)(playerpos.y+speed),playerwidth,playerheight,((xx-1)*boxsize)-345,((yy+1)*boxsize)-345,boxsize,boxsize))
            ) {
                // printf("Collision");
            }
            else{
                playerpos.y+=speed;
            }
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::S)) {
            if (zerostart[23-yy+1][xx]!=0 && Collision((int)(playerpos.x),(int)(playerpos.y-speed),playerwidth,playerheight,(xx*boxsize)-345,((yy-1)*boxsize)-345,boxsize,boxsize)
            || (zerostart[23-yy+1][xx+1]!=0 && Collision((int)(playerpos.x),(int)(playerpos.y-speed),playerwidth,playerheight,((xx+1)*boxsize)-345,((yy-1)*boxsize)-345,boxsize,boxsize))
            || (zerostart[23-yy+1][xx-1]!=0 && Collision((int)(playerpos.x),(int)(playerpos.y-speed),playerwidth,playerheight,((xx-1)*boxsize)-345,((yy-1)*boxsize)-345,boxsize,boxsize))
            ) {
                // printf("Collision");
            }
            else{
                playerpos.y-=speed;
            }
        }
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
        m_player->m_Transform.scale = glm::vec2(-1.0f, 1.0f);
        printf("play:%d %d\nboxx:%d %d\nboxx:%d %d\n\n",(int)playerpos.x-speed,(int)playerpos.y,((xx-1)*boxsize)-345,(yy*boxsize)-345,xx,yy);
        if ((zerostart[23-yy][xx-1]!=0 && Collision((int)(playerpos.x-speed),(int)(playerpos.y),playerwidth,playerheight,((xx-1)*boxsize)-345,(yy*boxsize)-345,boxsize,boxsize))
        || (zerostart[23-yy-1][xx-1]!=0 && Collision((int)(playerpos.x-speed),(int)(playerpos.y),playerwidth,playerheight,((xx-1)*boxsize)-345,((yy+1)*boxsize)-345,boxsize,boxsize))
        || (zerostart[23-yy+1][xx-1]!=0 && Collision((int)(playerpos.x-speed),(int)(playerpos.y),playerwidth,playerheight,((xx-1)*boxsize)-345,((yy-1)*boxsize)-345,boxsize,boxsize))
        || ((playerpos.x-zerox)-playerwidth<=-360)) {
            // printf("Collision");
        }
        else{
            playerpos.x-=speed;
        }
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::D)) {
        m_player->m_Transform.scale = glm::vec2(1.0f, 1.0f);
        printf("play:%d %d\nplay:%d %d\nboxx:%d %d\nboxx:%d %d %d\n\n",(int)playerpos.x-speed,(int)playerpos.y,xx,yy,((xx+1)*boxsize)-345,((yy-1)*boxsize)-345,xx,yy,Collision((int)(playerpos.x+speed),(int)(playerpos.y),playerwidth,playerheight,((xx+1)*boxsize)-345,((yy-1)*boxsize)-345,boxsize,boxsize));
        if ((zerostart[23-yy][xx+1]!=0 && Collision((int)(playerpos.x+speed),(int)(playerpos.y),playerwidth,playerheight,((xx+1)*boxsize)-345,(yy*boxsize)-345,boxsize,boxsize))
        || (zerostart[23-yy-1][xx+1]!=0 && Collision((int)(playerpos.x+speed),(int)(playerpos.y),playerwidth,playerheight,((xx+1)*boxsize)-345,((yy+1)*boxsize)-345,boxsize,boxsize))
        || (zerostart[23-yy+1][xx+1]!=0 && Collision((int)(playerpos.x+speed),(int)(playerpos.y),playerwidth,playerheight,((xx+1)*boxsize)-345,((yy-1)*boxsize)-345,boxsize,boxsize))
        || ((playerpos.x-zerox)+playerwidth>=360)) {
            // printf("Collision");
        }
        else{
            playerpos.x+=speed;
        }
    }

    if (bug==0) {
        if (((zerostart[23-yy+1][xx]!=0 && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight+2,(xx*boxsize)-345,((yy-1)*boxsize)-345,boxsize,boxsize))
            || (zerostart[23-yy+1][xx+1]!=0 && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight+2,((xx+1)*boxsize)-345,((yy-1)*boxsize)-345,boxsize,boxsize))
            || (zerostart[23-yy+1][xx-1]!=0 && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight+2,((xx-1)*boxsize)-345,((yy-1)*boxsize)-345,boxsize,boxsize)))
            && (Util::Input::IsKeyPressed(Util::Keycode::W) || Util::Input::IsKeyPressed(Util::Keycode::SPACE)) ) {
            sec=50;
            Acceleration=16;
            m_player->SetImage(GA_RESOURCE_DIR"/res/player3.png");
            playerpos.y=playerpos.y+Acceleration;
        }
        else if (yy<=0) {
            playerpos.y-=Acceleration*1.5;
            sec+=2;
            if (sec==10) {
                std::this_thread::sleep_for(std::chrono::seconds(2));
                ofsetzero.x-=zerox;
                playerpos.x=-112.5f-zerox;
                playerpos.y=-280.0f;
                zerox=0;
                sec=120;
                life-=1;
                m_PRM->BgZindex(60);
                text->Settext("X"+std::to_string(life));
                m_PRM->Select(0);
                m_CurrentState=State::DIE;
            }
        }
        else if (sec==0){
            if ((zerostart[23-yy+1][xx]!=0 && Collision((int)(playerpos.x),(int)(playerpos.y-Acceleration),playerwidth,playerheight+2,(xx*boxsize)-345,((yy-1)*boxsize)-345,boxsize,boxsize))
            || (zerostart[23-yy+1][xx+1]!=0 && Collision((int)(playerpos.x),(int)(playerpos.y-Acceleration),playerwidth,playerheight+2,((xx+1)*boxsize)-345,((yy-1)*boxsize)-345,boxsize,boxsize))
            || (zerostart[23-yy+1][xx-1]!=0 && Collision((int)(playerpos.x),(int)(playerpos.y-Acceleration),playerwidth,playerheight+2,((xx-1)*boxsize)-345,((yy-1)*boxsize)-345,boxsize,boxsize))
            ){
                m_player->SetImage(GA_RESOURCE_DIR"/res/player1.png");
                Acceleration=0;
                playerpos.y=(yy*boxsize)-345+2;
            }
            else {
                Acceleration=(Acceleration+0.3)*0.98;
                playerpos.y-=Acceleration;
            }
        }
        else if(sec!=0) {
            if (Acceleration>0) {
                Acceleration-=1;
            }
            else if (Acceleration<=0) {sec=0;}
            if ((zerostart[23-yy+1][xx]!=0 && Collision((int)(playerpos.x),(int)(playerpos.y+Acceleration),playerwidth,playerheight,(xx*boxsize)-345,((yy-1)*boxsize)-345,boxsize,boxsize))
            || (zerostart[23-yy+1][xx+1]!=0 && Collision((int)(playerpos.x),(int)(playerpos.y+Acceleration),playerwidth,playerheight,((xx+1)*boxsize)-345,((yy-1)*boxsize)-345,boxsize,boxsize))
            || (zerostart[23-yy+1][xx-1]!=0 && Collision((int)(playerpos.x),(int)(playerpos.y+Acceleration),playerwidth,playerheight,((xx-1)*boxsize)-345,((yy-1)*boxsize)-345,boxsize,boxsize))
            ){
                m_player->SetImage(GA_RESOURCE_DIR"/res/player1.png");
                Acceleration=0;
                sec=0;
                playerpos.y=(yy*boxsize)-345+2;
            }

            //向上碰撞
            else if ((zerostart[23-yy-1][xx]!=0 && Collision((int)(playerpos.x),(int)(playerpos.y+Acceleration),playerwidth,playerheight,(xx*boxsize)-345,((yy+1)*boxsize)-345,boxsize,boxsize))
            || (zerostart[23-yy-1][xx+1]!=0 && Collision((int)(playerpos.x),(int)(playerpos.y+Acceleration),playerwidth,playerheight,((xx+1)*boxsize)-345,((yy+1)*boxsize)-345,boxsize,boxsize))
            || (zerostart[23-yy-1][xx-1]!=0 && Collision((int)(playerpos.x),(int)(playerpos.y+Acceleration),playerwidth,playerheight,((xx-1)*boxsize)-345,((yy+1)*boxsize)-345,boxsize,boxsize))
            ){
                Acceleration=0;
                sec=0;
                playerpos.y=(yy*boxsize)-345;

                //碰撞
                zerostart[23-yy-1][xx]=0;
                printf("x y:%d",position[22-yy][xx]);
                tmp[position[22-yy][xx]]->SetVisible(0);
                // bgm.LoadMedia(GA_RESOURCE_DIR"/sound/field.mp3");

            }
            playerpos.y+=Acceleration;
        }
    }

    m_player->SetPosition({playerpos.x-zerox,playerpos.y});

    //視角控制
    if(m_player->GetPosition().x>=0) {
        ofsetzero.x+=speed;
        zerox+=speed;
    }

    m_Root.Update(ofsetzero);
}
