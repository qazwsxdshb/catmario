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

bool App::RLCollision(int xx,int yy,glm::vec2 playerpos,int rl,int height){
    //right xx+1 rl=1
    //left  xx-1 rl=-1
    if ((zerostart[23-yy][xx]!=0 && tmp[position[23-yy][xx]]->GetVisibility()==1 && Collision((int)(playerpos.x+speed*rl),(int)(playerpos.y),playerwidth,height,(xx*boxsize)-345,(yy*boxsize)-345,boxsize,boxsize))
        || (zerostart[23-yy-1][xx]!=0 && tmp[position[23-yy-1][xx]]->GetVisibility()==1 && Collision((int)(playerpos.x+speed*rl),(int)(playerpos.y),playerwidth,height,(xx*boxsize)-345,((yy+1)*boxsize)-345,boxsize,boxsize))
        || (zerostart[23-yy+1][xx]!=0 && tmp[position[23-yy+1][xx]]->GetVisibility()==1 && Collision((int)(playerpos.x+speed*rl),(int)(playerpos.y),playerwidth,height,(xx*boxsize)-345,((yy-1)*boxsize)-345,boxsize,boxsize))
    ){return true;}
    return false;
}

bool App::UDCollision(int xx,int yy,glm::vec2 playerpos,int ud,int speedd,int height){
    //up    yy+1 ud=1
    //down  yy-1 ud=-1
    if (
        (zerostart[23-yy][xx]!=0 && tmp[position[23-yy][xx]]->GetVisibility()==1 && Collision((int)(playerpos.x),(int)(playerpos.y+(speedd*ud)),playerwidth,height,(xx*boxsize)-345,(yy*boxsize)-345,boxsize,boxsize))
        || (zerostart[23-yy][xx+1]!=0 && tmp[position[23-yy][xx+1]]->GetVisibility()==1 && Collision((int)(playerpos.x),(int)(playerpos.y+(speedd*ud)),playerwidth,height,((xx+1)*boxsize)-345,(yy*boxsize)-345,boxsize,boxsize))
        || (zerostart[23-yy][xx-1]!=0 && tmp[position[23-yy][xx-1]]->GetVisibility()==1 && Collision((int)(playerpos.x),(int)(playerpos.y+(speedd*ud)),playerwidth,height,((xx-1)*boxsize)-345,(yy*boxsize)-345,boxsize,boxsize))
    ){return true;}
    return false;
}

void App::Monsteract(glm::vec2 monsterpos,int value,glm::vec2 playerpos,std::vector<std::shared_ptr<Monster>> mon){
    //monster
    monsterpos.x+=zerox;
    int xx=round((345+monsterpos.x)/boxsize);
    int yy=round((345+monsterpos.y)/boxsize);

    if (UDCollision(xx,yy-1,monsterpos,-1,monsterAcceleration[value][0],26)){
        monsterAcceleration[value][0]=0;
        monsterpos.y=(yy*boxsize)-345-3;

        if (monsterAcceleration[value][1]<0) {
            mon[value]->m_Transform.scale = glm::vec2(1.0f, 1.0f);
            if (RLCollision(xx-1,yy,{monsterpos.x,monsterpos.y},-1,24)){
                monsterAcceleration[value][1]*=-1;
            }
        }
        else if (monsterAcceleration[value][1]>0){
            mon[value]->m_Transform.scale = glm::vec2(-1.0f, 1.0f);
            if (RLCollision(xx+1,yy,{monsterpos.x,monsterpos.y},1,24)){
                monsterAcceleration[value][1]*=-1;
            }
        }
        monsterpos.x+=monsterAcceleration[value][1];
    }
    else {
        monsterAcceleration[value][0]=(monsterAcceleration[value][0]+0.3)*0.98;
        monsterpos.y-=monsterAcceleration[value][0];
    }

    if (Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),boxsize,24) && playerpos.y>(monsterpos.y+6)) {
        mon[value]->SetVisible(0);
        Acceleration=10;
        sec=50;
    }
    else if (Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),boxsize,24)) {
        // text->SetPosition({monsterpos.x+50,monsterpos.y});
        // text->Settext("loser");
        sec=120;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        m_CurrentState=State::DIE;
    }

    mon[value]->SetPosition({monsterpos.x-zerox,monsterpos.y});
}

void App::ResetAll() {
    for (int i = 0; i < m_monster.size(); ++i) {
        m_monster[i]->SetVisible(1);
        m_monster[i]->ResetPosition();
    }
    for (int i = 0; i < reset.size(); ++i) {
        tmp[position[reset[i][0]][reset[i][1]]]->SetVisible(1);
        zerostart[reset[i][0]][reset[i][1]]=reset[i][2];
        if(reset[i][2]==8) {
            tmp[position[reset[i][0]][reset[i][1]]]->SetVisible(0);
        }
        if (reset[i][2]==10) {
            tmp[position[reset[i][0]][reset[i][1]]]->posup=0;
            tmp[position[reset[i][0]][reset[i][1]]]->SetPosition({(reset[i][1]*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-reset[i][0])*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
        }
        if (reset[i][2]==4) {
            tmp[position[reset[i][0]][reset[i][1]]]->posup=0;
        }
    }
    reset.clear();
}

void App::Die() {
    ofsetzero={0,0};
    if (sec==120) {
        ofsetzero.x-=zerox;
        m_player->SetPosition({-112.5f-zerox,-280.0f});
        zerox=0;
        m_PRM->BgZindex(60);
        // text->SetPosition({0,0});
        text->Settext("X"+std::to_string(--life));
        m_PRM->Select(0);
    }

    else if (sec==1){
        m_PRM->BgZindex(-10);
        m_PRM->Select(1);
        text->Settext(" ");
        m_CurrentState=State::UPDATE;
    }
    sec-=1;
    m_Root.Update(ofsetzero);
    ResetAll();
}

void App::Update() {
    if(sec>0) {sec-=1;}
    if(opsec>0) {opsec-=1;}
    ofsetzero={0,0};

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
    int xx=round((345+playerpos.x)/boxsize);
    int yy=round((345+playerpos.y)/boxsize);

    if (bug==1) {
        if (Util::Input::IsKeyPressed(Util::Keycode::W) || Util::Input::IsKeyPressed(Util::Keycode::SPACE)){
            if (!UDCollision(xx,yy+1,playerpos,1,speed,playerheight+2)){
                playerpos.y+=speed;
            }
        }
        else if (Util::Input::IsKeyPressed(Util::Keycode::S)) {
            if (!UDCollision(xx,yy-1,playerpos,-1,0,playerheight+2)){
                playerpos.y-=speed;
            }
        }
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
        m_player->m_Transform.scale = glm::vec2(-1.0f, 1.0f);
        if (!(RLCollision(xx-1,yy,{playerpos.x,playerpos.y},-1,playerheight) || ((playerpos.x-zerox)-playerwidth<=-360))){
            playerpos.x-=speed;
        }
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::D)) {
        m_player->m_Transform.scale = glm::vec2(1.0f, 1.0f);
        if (!(RLCollision(xx+1,yy,{playerpos.x,playerpos.y},1,playerheight) || ((playerpos.x-zerox)+playerwidth>=360))){
            playerpos.x+=speed;
        }
    }

    if (bug==0) {
        if (UDCollision(xx,yy-1,playerpos,-1,0,playerheight+2) && (Util::Input::IsKeyPressed(Util::Keycode::W) || Util::Input::IsKeyPressed(Util::Keycode::SPACE))) {
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
                sec=120;
                m_CurrentState=State::DIE;
            }
        }
        else if (sec==0){
            if (UDCollision(xx,yy-1,playerpos,-1,Acceleration,playerheight+2)){
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
            if (Acceleration>0) {Acceleration-=1;}
            else if (Acceleration<=0) {sec=0;}

            if (UDCollision(xx,yy-1,playerpos,1,Acceleration,playerheight+2)){
                m_player->SetImage(GA_RESOURCE_DIR"/res/player1.png");
                Acceleration=0;
                sec=0;
                playerpos.y=(yy*boxsize)-345+2;
            }
            else if (zerostart[23-yy-1][xx]==10 && ((zerostart[23-yy-1][xx]!=0 && Collision((int)(playerpos.x),(int)(playerpos.y+Acceleration),playerwidth,playerheight,(xx*boxsize)-345,((yy+1)*boxsize)-345,boxsize,boxsize))
            || (zerostart[23-yy-1][xx+1]!=0 && tmp[position[23-yy-1][xx+1]]->GetVisibility()==1 && Collision((int)(playerpos.x),(int)(playerpos.y+Acceleration),playerwidth,playerheight,((xx+1)*boxsize)-345,((yy+1)*boxsize)-345,boxsize,boxsize))
            || (zerostart[23-yy-1][xx-1]!=0 && tmp[position[23-yy-1][xx-1]]->GetVisibility()==1 && Collision((int)(playerpos.x),(int)(playerpos.y+Acceleration),playerwidth,playerheight,((xx-1)*boxsize)-345,((yy+1)*boxsize)-345,boxsize,boxsize))
            )) {
                zerostart[21-yy][xx]=10;
                zerostart[22-yy][xx]=0;
                if (tmp[position[23-yy-1][xx]]->posup++==0) {
                    reset.push_back({22-yy,xx,10});
                }
                tmp[position[23-yy-1][xx]]->SetPosition({(xx*boxsize)-((WINDOW_WIDTH-boxsize)/2)-zerox, ((yy+2)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
                reset.push_back({21-yy,xx,0});
            }

            //向上碰撞
            else if (
            (zerostart[23-yy-1][xx]!=0 && Collision((int)(playerpos.x),(int)(playerpos.y+Acceleration),playerwidth,playerheight,(xx*boxsize)-345,((yy+1)*boxsize)-345,boxsize,boxsize))
            || (zerostart[23-yy-1][xx+1]!=0 && tmp[position[23-yy-1][xx+1]]->GetVisibility()==1 && Collision((int)(playerpos.x),(int)(playerpos.y+Acceleration),playerwidth,playerheight,((xx+1)*boxsize)-345,((yy+1)*boxsize)-345,boxsize,boxsize))
            || (zerostart[23-yy-1][xx-1]!=0 && tmp[position[23-yy-1][xx-1]]->GetVisibility()==1 && Collision((int)(playerpos.x),(int)(playerpos.y+Acceleration),playerwidth,playerheight,((xx-1)*boxsize)-345,((yy+1)*boxsize)-345,boxsize,boxsize))
            ){
                Acceleration=0;
                sec=0;
                playerpos.y=(yy*boxsize)-345;

                //碰撞
                if (zerostart[23-yy-1][xx]==3) {
                    zerostart[23-yy-1][xx]=0;
                    tmp[position[22-yy][xx]]->SetVisible(0);
                    // bgm.LoadMedia(GA_RESOURCE_DIR"/sound/field.mp3");
                    reset.push_back({22-yy,xx,3});
                }
                else if (zerostart[23-yy-1][xx]==4 && tmp[position[22-yy][xx]]->posup==0) {
                    tmp[position[22-yy][xx]]->posup=1;

                    m_monster.push_back(std::make_shared<Monster>(GA_RESOURCE_DIR"/res/monster3.png"));
                    m_monster[m_monster.size()-1]->SetPosition({((xx)*boxsize)-((WINDOW_WIDTH-boxsize)/2)-zerox, ((yy+2)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
                    m_monster[m_monster.size()-1]->SetZIndex(51);
                    monsterAcceleration.push_back({0,1});
                    m_Root.AddChild(m_monster[m_monster.size()-1]);
                    // bgm.LoadMedia(GA_RESOURCE_DIR"/sound/field.mp3");
                    reset.push_back({22-yy,xx,4});
                }
                else if (zerostart[23-yy-1][xx]==8) {
                    tmp[position[23-yy-1][xx]]->SetVisible(1);
                    reset.push_back({22-yy,xx,8});
                    // bgm.LoadMedia(GA_RESOURCE_DIR"/sound/field.mp3");
                }

            }
            playerpos.y+=Acceleration;
        }
    }

    m_player->SetPosition({playerpos.x-zerox,playerpos.y});

    for(int i=0;i<m_monster.size();i++) {
        if (m_monster[i]->GetVisibility()) {
            Monsteract(m_monster[i]->GetPosition(),i,playerpos,m_monster);
        }
    }
    // for(int i=0;i<tmp_monster.size();i++) {
    //     if (tmp_monster[i]->GetVisibility()) {
    //         Monsteract(tmp_monster[i]->GetPosition(),i,playerpos,tmp_monster);
    //     }
    // }


    //視角控制
    if(m_player->GetPosition().x>=0) {
        ofsetzero.x+=speed;
        zerox+=speed;
    }

    m_Root.Update(ofsetzero);
}
