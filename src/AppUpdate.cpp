#include "App.hpp"
#include "spdlog/fmt/bundled/xchar.h"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include <thread>
#include <chrono>

// 判斷兩個矩形 A 與 B 是否發生碰撞（矩形中心點為基準）
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

// 判斷玩家往左（rl=-1）或往右（rl=1）時，是否會與障礙物發生碰撞
bool App::RLCollision(int xx,int yy,glm::vec2 playerpos,int rl,int height){
    // right xx+1 rl=1
    // left  xx-1 rl=-1
    // 右移 = xx+1；左移 = xx-1（rl 決定方向）
    // 檢查以下三個格子是否有障礙物並與玩家碰撞：
    // 1. 玩家正前方格子（同一 row）
    // 2. 玩家上方一格（上半身）
    // 3. 玩家下方一格（下半身）
    if ((zerostart[23-yy][xx]!=0 && tmp[position[23-yy][xx]]->GetVisibility()==1 && Collision((int)(playerpos.x+speed*rl),(int)(playerpos.y),playerwidth,height,(xx*boxsize)-345,(yy*boxsize)-345,boxsize,boxsize))
        || (zerostart[23-yy-1][xx]!=0 && tmp[position[23-yy-1][xx]]->GetVisibility()==1 && Collision((int)(playerpos.x+speed*rl),(int)(playerpos.y),playerwidth,height,(xx*boxsize)-345,((yy+1)*boxsize)-345,boxsize,boxsize))
        || (zerostart[23-yy+1][xx]!=0 && tmp[position[23-yy+1][xx]]->GetVisibility()==1 && Collision((int)(playerpos.x+speed*rl),(int)(playerpos.y),playerwidth,height,(xx*boxsize)-345,((yy-1)*boxsize)-345,boxsize,boxsize))
    ){return true;}
    return false;
}

// 判斷玩家往上（ud=1）或往下（ud=-1）跳動或掉落時，是否會與障礙物發生碰撞
bool App::UDCollision(int xx,int yy,glm::vec2 playerpos,int ud,int speedd,int height){
    // up    yy+1 ud=1
    // down  yy-1 ud=-1
    // 上移 = yy+1；下移 = yy-1（ud 決定方向）
    // 1. 檢查玩家正上（或正下）方格子是否碰撞
    // 2. 再加上玩家左右兩邊也可能會碰撞（寬度判定）
    if (
        (zerostart[23-yy][xx]!=0 && tmp[position[23-yy][xx]]->GetVisibility()==1 && Collision((int)(playerpos.x),(int)(playerpos.y+(speedd*ud)),playerwidth,height,(xx*boxsize)-345,(yy*boxsize)-345,boxsize,boxsize))
        || (zerostart[23-yy][xx+1]!=0 && tmp[position[23-yy][xx+1]]->GetVisibility()==1 && Collision((int)(playerpos.x),(int)(playerpos.y+(speedd*ud)),playerwidth,height,((xx+1)*boxsize)-345,(yy*boxsize)-345,boxsize,boxsize))
        || (zerostart[23-yy][xx-1]!=0 && tmp[position[23-yy][xx-1]]->GetVisibility()==1 && Collision((int)(playerpos.x),(int)(playerpos.y+(speedd*ud)),playerwidth,height,((xx-1)*boxsize)-345,(yy*boxsize)-345,boxsize,boxsize))
    ){return true;}
    return false;
}

void App::Monsteract(glm::vec2 monsterpos,int value,glm::vec2 playerpos,std::vector<std::shared_ptr<Monster>> mon) {
    //monster
    monsterpos.x+=zerox;
    int xx=round((345+monsterpos.x)/boxsize);
    int yy=round((345+monsterpos.y)/boxsize);

    if (mon[value]->talk==1 && mon[value]->name!="box") {
        text->SetColor(Util::Color::FromName(Util::Colors::BLACK));
        text->SetPosition({monsterpos.x+70-zerox,monsterpos.y+20});
        text->Settext("loser");
    }

    if (mon[value]->name!="fish" && mon[value]->name!="box"){
        if (mon[value]->time>0) {
            monsterAcceleration[value][0]-=1;
            mon[value]->time-=1;
        }
        if (mon[value]->time!=0) {
            monsterpos.y+=monsterAcceleration[value][0];
        }
        else if(yy>0 && UDCollision(xx,yy-1,monsterpos,-1,monsterAcceleration[value][0],26)){
            if(mon[value]->GetName()=="star"){
                monsterAcceleration[value][0]=15;
                mon[value]->time=15;
                monsterAcceleration[value][1]=3;
            }
            else {
                monsterAcceleration[value][0]=0;
                monsterpos.y=(yy*boxsize)-345-3;
            }
        }
        else {
            monsterAcceleration[value][0]=(monsterAcceleration[value][0]+0.3)*0.98;
            monsterpos.y-=monsterAcceleration[value][0];
        }

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
    else if (mon[value]->name=="fish") {
        if (Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),boxsize,1024)) {
            mon[value]->act=1;
        }
        if (mon[value]->act==1) {
            monsterpos.y+=monsterAcceleration[value][0];
        }
    }
    else if (mon[value]->name=="box") {
        if (mon[value]->act!=1 && playerpos.y<monsterpos.y && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),boxsize,1024)) {
            for (int ii=0;ii<3;ii++) {
                mon[value+ii]->act=1;
                int xxx=round((345+m_monster[value+ii]->GetPosition().x+zerox)/boxsize);
                int yyy=round((345+m_monster[value+ii]->GetPosition().y)/boxsize);
                printf("%d %d \n\n",xxx,yyy);
                zerostart[23-yyy][xxx]=0;
                tmp[position[23-yyy][xxx]]->SetVisible(0);
                reset.push_back({23-yyy,xxx,3});
            }
        }
        if (mon[value]->act==1) {
            monsterpos.y+=monsterAcceleration[value][0];
        }
    }

    // die mon
    if (yy<0) {
        mon[value]->SetVisible(0);
    }
    else if (bug!=3 && mon[value]->GetName()!="star" && mon[value]->GetName()!="fish" && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),boxsize,24) && playerpos.y>(monsterpos.y+6)) {
        mon[value]->SetVisible(0);
        Acceleration=10;
        sec=25;
    }
    // die

    //die plyaer
    else if (bug!=3 && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),boxsize,24)) {
        Acceleration=12;
        mon[value]->talk=1;
        m_player->SetImage(GA_RESOURCE_DIR"/res/player4.png");
        sec=30;
        bug=3;
    }
    // die

    mon[value]->SetPosition({monsterpos.x-zerox,monsterpos.y});
}

void App::ResetAll() {
    for (int i = 0; i < tmp_monster; ++i) {
        m_monster[m_monster.size()-1]->SetVisible(0);
        m_monster.erase(m_monster.end()-1);
        monsterAcceleration.erase(monsterAcceleration.end()-1);
    }
    tmp_monster=0;
    for (int i = 0; i < m_monster.size(); ++i) {
        m_monster[i]->act=0;
        m_monster[i]->talk=0;
        m_monster[i]->move=0;
        m_monster[i]->SetVisible(1);
        m_monster[i]->ResetPosition(zerox);
    }
    for (int i = 0; i < reset.size(); ++i) {
        tmp[position[reset[i][0]][reset[i][1]]]->SetVisible(1);
        zerostart[reset[i][0]][reset[i][1]]=reset[i][2];
        tmp[position[reset[i][0]][reset[i][1]]]->posup=0;
        if (reset[i][2]==4 || reset[i][2]==12) {
            tmp[position[reset[i][0]][reset[i][1]]]->SetImage(GA_RESOURCE_DIR"/res/box.png");
        }
        if(reset[i][2]==8) {
            tmp[position[reset[i][0]][reset[i][1]]]->SetVisible(0);
        }
         if (reset[i][2]==10) {
             tmp[position[reset[i][0]][reset[i][1]]]->SetPosition({(reset[i][1]*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-reset[i][0])*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
         }
    }
    m_player->ResetPosition();
    reset.clear();
}


void App::Die() {
    ofsetzero={0,0};
    text->SetColor(Util::Color::FromName(Util::Colors::WHITE));
    text->SetPosition({0+zerox-checkpoint,0});
    if (sec==120) {
        ofsetzero.x=ofsetzero.x-zerox+checkpoint;
        m_player->SetPosition({-112.5f-zerox+checkpoint,-280.0f});
        zerox=checkpoint;
        m_PRM->BgZindex(60);
        text->Settext("X"+std::to_string(--life));
        m_PRM->Select(0);
    }
    else if (sec==1){
        m_PRM->BgZindex(-10);
        m_PRM->Select(1);
        text->Settext(" ");
        ResetAll();
        m_player->SetImage(GA_RESOURCE_DIR"/res/player1.png");
        m_CurrentState=State::UPDATE;
    }
    sec-=1;
    m_Root.Update(ofsetzero);
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

    ///
    //die space
    ///
    if (opsec>120) {
        m_player->SetZIndex(40);
        if (opsec>=240) {
            playerpos.y-=1;
        }
        else {
            playerpos.y+=10;
            auto tttt=tmp[tube[3]]->GetPosition();
            tmp[tube[3]]->SetPosition({tttt.x,tttt.y+10});
        }
        if (opsec==121) {
            sec=120;
            bug=0;
            m_player->SetZIndex(50);
            m_CurrentState=State::DIE;
        }
    }

    if (bug==3) {
        if (sec<=0) {
            Acceleration=(Acceleration+0.4)*0.98;
            playerpos.y-=Acceleration;
        }
        else {
            if (Acceleration>0){Acceleration--;}
            playerpos.y+=Acceleration;
        }
        if ((sec--)<=-100) {
            bug=0;
            sec=120;
            Acceleration=0;
            m_CurrentState=State::DIE;
        }
    }
    /////////////////////////////////
    if (bug!=3 && Util::Input::IsKeyPressed(Util::Keycode::O)) {
        printf("%f %f\n\n",playerpos.x+zerox-112.5f,playerpos.y);
    }

    if (bug!=3 && Util::Input::IsKeyPressed(Util::Keycode::A)) {
        m_player->m_Transform.scale = glm::vec2(-1.0f, 1.0f);
        if (!(RLCollision(xx-1,yy,{playerpos.x,playerpos.y},-1,playerheight) || ((playerpos.x-zerox)-playerwidth<=-360))){
            playerpos.x-=speed;
        }
        else if (zerostart[23-yy][xx-1]==16) {
            playerpos.x-=speed;
            tmp[position[23-yy][xx-1]]->SetVisible(0);
            checkpoint=zerox;
            m_player->position={((xx-1)*boxsize)-((WINDOW_WIDTH-boxsize)/2)-zerox, ((yy+2)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)};
        }
    }
    else if (bug!=3 && Util::Input::IsKeyPressed(Util::Keycode::D)) {
        m_player->m_Transform.scale = glm::vec2(1.0f, 1.0f);
        if (!(RLCollision(xx+1,yy,{playerpos.x,playerpos.y},1,playerheight) || ((playerpos.x-zerox)+playerwidth>=360))){
            playerpos.x+=speed;
        }
        else if (zerostart[23-yy][xx+1]==16) {
            playerpos.x+=speed;
            tmp[position[23-yy][xx+1]]->SetVisible(0);
            checkpoint=zerox;
            m_player->position={((xx+1)*boxsize)-((WINDOW_WIDTH-boxsize)/2)-zerox, ((yy+2)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)};
        }
    }

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
    else if (bug==0) {
        if (yy>0 && UDCollision(xx,yy-1,playerpos,-1,0,playerheight+2) && (Util::Input::IsKeyPressed(Util::Keycode::W) || Util::Input::IsKeyPressed(Util::Keycode::SPACE))) {
            sec=50;
            Acceleration=16;
            m_player->SetImage(GA_RESOURCE_DIR"/res/player3.png");
            playerpos.y=playerpos.y+Acceleration;
        }

        //die die die drop die
        else if (yy<=0) {
            playerpos.y-=Acceleration*1.5;
            sec+=2;
            if (sec==10) {
                std::this_thread::sleep_for(std::chrono::seconds(2));
                sec=120;
                m_CurrentState=State::DIE;
            }
        }
        //pipe die
        else if (Util::Input::IsKeyPressed(Util::Keycode::S)) {
            if ((xx==30 && yy==6) || (xx==31 && yy==6)){
                opsec=300;
                bug=2;
            }
        }

        // if ((xx==30 && yy==6) || (xx==31 && yy==6)){
        //     opsec=300;
        //     bug=2;
        // }
        //////////////////////////////////

        else if (sec==0){
            if (UDCollision(xx,yy-1,playerpos,-1,Acceleration,playerheight+2)){
                m_player->SetImage(GA_RESOURCE_DIR"/res/player1.png");
                Acceleration=0;
                playerpos.y=(yy*boxsize)-345+2;
            }
            else {
                Acceleration=(Acceleration+0.4)*0.98;
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

            //?方塊向上
            else if ((zerostart[23-yy-1][xx]==10 && Collision((int)(playerpos.x),(int)(playerpos.y+Acceleration),playerwidth,playerheight,(xx*boxsize)-345,((yy+1)*boxsize)-345,boxsize,boxsize))
            || (zerostart[23-yy-1][xx+1]==10 && tmp[position[23-yy-1][xx+1]]->GetVisibility()==1 && Collision((int)(playerpos.x),(int)(playerpos.y+Acceleration),playerwidth,playerheight,((xx+1)*boxsize)-345,((yy+1)*boxsize)-345,boxsize,boxsize))
            || (zerostart[23-yy-1][xx-1]==10 && tmp[position[23-yy-1][xx-1]]->GetVisibility()==1 && Collision((int)(playerpos.x),(int)(playerpos.y+Acceleration),playerwidth,playerheight,((xx-1)*boxsize)-345,((yy+1)*boxsize)-345,boxsize,boxsize))
            ) {
                if (zerostart[23-yy-1][xx]==10) {
                    zerostart[21-yy][xx]=10;
                    zerostart[22-yy][xx]=0;
                    if (tmp[position[22-yy][xx]]->posup++==0) {
                        reset.push_back({22-yy,xx,10});
                    }
                    tmp[position[22-yy][xx]]->SetPosition({tmp[position[22-yy][xx]]->GetPosition().x, tmp[position[22-yy][xx]]->GetPosition().y+boxsize});
                    reset.push_back({21-yy,xx,0});
                }
                else if (zerostart[23-yy-1][xx+1]==10) {
                    zerostart[21-yy][xx+1]=10;
                    zerostart[22-yy][xx+1]=0;
                    if (tmp[position[22-yy][xx+1]]->posup++==0) {
                        reset.push_back({22-yy,xx+1,10});
                    }
                    tmp[position[22-yy][xx+1]]->SetPosition({tmp[position[22-yy][xx+1]]->GetPosition().x, tmp[position[22-yy][xx+1]]->GetPosition().y+boxsize});
                    reset.push_back({21-yy,xx+1,0});
                }
                else if (zerostart[23-yy-1][xx-1]==10) {
                    zerostart[21-yy][xx-1]=10;
                    zerostart[22-yy][xx-1]=0;
                    if (tmp[position[22-yy][xx-1]]->posup++==0) {
                        reset.push_back({22-yy,xx-1,10});
                    }
                    tmp[position[22-yy][xx-1]]->SetPosition({tmp[position[22-yy][xx-1]]->GetPosition().x, tmp[position[22-yy][xx-1]]->GetPosition().y+boxsize});
                    reset.push_back({21-yy,xx-1,0});
                }
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
                    tmp[position[22-yy][xx]]->SetImage(GA_RESOURCE_DIR"/res/brock4.png");

                    m_monster.push_back(std::make_shared<Monster>(GA_RESOURCE_DIR"/res/monster3.png"));
                    m_monster[m_monster.size()-1]->SetPosition({((xx)*boxsize)-((WINDOW_WIDTH-boxsize)/2)-zerox, ((yy+2)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
                    m_monster[m_monster.size()-1]->SetZIndex(52);
                    monsterAcceleration.push_back({0,1});
                     m_Root.AddChild(m_monster[m_monster.size()-1]);
                    tmp_monster+=1;
                    // bgm.LoadMedia(GA_RESOURCE_DIR"/sound/field.mp3");
                    reset.push_back({22-yy,xx,4});
                }
                else if (zerostart[23-yy-1][xx]==11 && tmp[position[22-yy][xx]]->posup==0) {
                    tmp[position[22-yy][xx]]->posup=1;
                    tmp[position[22-yy][xx]]->SetVisible(0);
                    m_monster.push_back(std::make_shared<Monster>(GA_RESOURCE_DIR"/res/glassstar.png"));
                    m_monster[m_monster.size()-1]->name="star";
                    m_monster[m_monster.size()-1]->SetPosition({((xx)*boxsize)-((WINDOW_WIDTH-boxsize)/2)-zerox, ((yy+2)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
                    m_monster[m_monster.size()-1]->SetZIndex(51);
                    monsterAcceleration.push_back({0,1});
                    m_Root.AddChild(m_monster[m_monster.size()-1]);
                    tmp_monster+=1;
                    // bgm.LoadMedia(GA_RESOURCE_DIR"/sound/field.mp3");
                    reset.push_back({22-yy,xx,11});
                }
                else if (zerostart[23-yy-1][xx]==8) {
                    tmp[position[23-yy-1][xx]]->SetVisible(1);
                    reset.push_back({22-yy,xx,8});
                    // bgm.LoadMedia(GA_RESOURCE_DIR"/sound/field.mp3");
                }
                else if (zerostart[23-yy-1][xx]==12 && tmp[position[22-yy][xx]]->posup==0) {
                    tmp[position[22-yy][xx]]->posup=1;
                    tmp[position[22-yy][xx]]->SetImage(GA_RESOURCE_DIR"/res/brock4.png");

                    m_coin.push_back(std::make_shared<Coin>(GA_RESOURCE_DIR"/res/coin.png"));
                    m_coin[m_coin.size()-1]->SetPosition({((xx)*boxsize)-((WINDOW_WIDTH-boxsize)/2)-zerox, ((yy+2)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)-10});
                    m_coin[m_coin.size()-1]->SetZIndex(51);

                    m_Root.AddChild(m_coin[m_coin.size()-1]);
                    reset.push_back({22-yy,xx,12});
                }
                else if (zerostart[23-yy-1][xx]==17 && tmp[position[22-yy][xx]]->posup==0) {
                    tmp[position[23-yy-1][xx]]->SetVisible(1);
                    tmp[position[22-yy][xx]]->SetImage(GA_RESOURCE_DIR"/res/brock4.png");

                    m_monster.push_back(std::make_shared<Monster>(GA_RESOURCE_DIR"/res/purplemushroom.png"));
                    m_monster[m_monster.size()-1]->SetPosition({((xx)*boxsize)-((WINDOW_WIDTH-boxsize)/2)-zerox, ((yy+2)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
                    m_monster[m_monster.size()-1]->SetZIndex(51);
                    monsterAcceleration.push_back({0,1});
                    m_Root.AddChild(m_monster[m_monster.size()-1]);
                    // bgm.LoadMedia(GA_RESOURCE_DIR"/sound/field.mp3");
                    reset.push_back({22-yy,xx,4});
                }
            }
            playerpos.y+=Acceleration;
        }
    }

    m_player->SetPosition({playerpos.x-zerox,playerpos.y});

    for(int i=0;i<m_monster.size();i++) {
        if (m_player->GetPosition().x-WINDOW_WIDTH/2<m_monster[i]->GetPosition().x && m_monster[i]->GetPosition().x<m_player->GetPosition().x+WINDOW_WIDTH/2) {
            m_monster[i]->move=1;
        }
        if (m_monster[i]->GetVisibility() && m_monster[i]->move==1) {
            Monsteract(m_monster[i]->GetPosition(),i,playerpos,m_monster);
        }
    }

    for(int i=0;i<m_coin.size();i++) {
        if (m_coin[i]->GetVisibility()) {
            m_coin[i]->SetPosition({m_coin[i]->GetPosition().x,m_coin[i]->GetPosition().y+5});
        }
        if (m_coin[i]->time++==10) {
            m_Root.RemoveChild(m_coin[i]);
            m_coin.erase(m_coin.begin()+i);
        }
    }


    //視角控制
    if(m_player->GetPosition().x>=0 && m_player->GetPosition().x<=145) {
        ofsetzero.x+=speed;
        zerox+=speed;
    }

    m_Root.Update(ofsetzero);
}
