#include "Monster.hpp"
#include "Util/Image.hpp"
#include "Character.hpp"
#include "CollisionUtil.hpp"


Monster::Monster(const std::string& ImagePath) {
    SetImage(ImagePath);
}

void Monster::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;
    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}

void Monster::Reset(int zerox) {
    act=0;
    talk=0;
    move=0;
    acceleration=oriacceleration;
    SetVisible(1);
    if (name=="yellowbat") {
        SetVisible(0);
    }
    else if (name=="tatle") {
        SetImage(GA_RESOURCE_DIR"/res/monster4.png");
    }
    else if (name=="motopro") {
        acceleration[1]=0;
        act=3;
    }
    m_Transform.translation = {pos.x-zerox,pos.y};
}

void Monster::Update(glm::vec2 monsterpos,int value,glm::vec2 playerpos,std::vector<std::shared_ptr<Monster>> mon) {
    //monster
    monsterpos.x+=zerox;
    int xx=round((345+monsterpos.x)/boxsize);
    int yy=round((345+monsterpos.y)/boxsize);

    if (mon[value]->talk==1 && mon[value]->name!="box") {
        text->SetColor(Util::Color::FromName(Util::Colors::BLACK));
        text->SetPosition({monsterpos.x+70-zerox,monsterpos.y+20});
        text->Settext("loser");
    }
    if (mon[value]->act==3) {
        if (CollisionUtil::Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_tragetrl,mon[value]->mon_traget)) {
            mon[value]->act=1;
        }
    }
    if (mon[value]->act!=3 && mon[value]->name!="fish" && mon[value]->name!="yellowbat" && mon[value]->name!="box"){
        if (mon[value]->time>0) {
            mon[value]->acceleration[0]-=1;
            mon[value]->time-=1;
        }
        if (mon[value]->time!=0) {
            monsterpos.y+=mon[value]->acceleration[0];
        }
        else if(yy>0 && UDCollision(xx,yy-1,monsterpos,-1,mon[value]->acceleration[0],mon[value]->mon_hei+2,mon[value]->mon_wei)){
            if(mon[value]->GetName()=="star"){
                mon[value]->acceleration[0]=15;
                mon[value]->time=15;
                mon[value]->acceleration[1]=3;
            }
            else {
                if (mon[value]->name=="motopro" && mon[value]->act==1) {
                    mon[value]->acceleration[1]=-1;
                    mon[value]->act=2;
                }
                mon[value]->acceleration[0]=0;
                monsterpos.y=(yy*boxsize)-345-2;
            }
        }
        else {
            mon[value]->acceleration[0]=(mon[value]->acceleration[0]+0.3)*0.98;
            monsterpos.y-=mon[value]->acceleration[0];
        }

        if (mon[value]->acceleration[1]<0) {
            mon[value]->m_Transform.scale = glm::vec2(1.0f, 1.0f);
            if (RLCollision(xx-1,yy,{monsterpos.x,monsterpos.y},-1,mon[value]->mon_hei,mon[value]->mon_wei)){
                mon[value]->acceleration[1]*=-1;
            }
        }
        else if (mon[value]->acceleration[1]>0){
            mon[value]->m_Transform.scale = glm::vec2(-1.0f, 1.0f);
            if (RLCollision(xx+1,yy,{monsterpos.x,monsterpos.y},1,mon[value]->mon_hei,mon[value]->mon_wei)){
                mon[value]->acceleration[1]*=-1;
            }
        }
        monsterpos.x+=mon[value]->acceleration[1];
    }

    else if (mon[value]->name=="fish") {
        if (Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),boxsize,mon[value]->mon_traget)) {
            mon[value]->act=1;
        }
        if (mon[value]->act==1) {
            monsterpos.y+=mon[value]->acceleration[0];
        }
    }

    else if (mon[value]->name=="yellowbat") {
        if (Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_tragetrl,mon[value]->mon_traget)) {
            mon[value]->act=1;
            mon[value]->SetVisible(1);
        }
        if (mon[value]->act==1) {
            monsterpos.x+=mon[value]->acceleration[1];
        }
    }
    else if (mon[value]->name=="box") {
        if (mon[value]->act!=1 && ((mon[value]->type==1 && playerpos.y<monsterpos.y) || (mon[value]->type==2 && playerpos.y>monsterpos.y)) && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_tragetrl,mon[value]->mon_traget)) {
            for (int ii=0;ii<(int)(mon[value]->mon_wei/boxsize);ii++) {
                int xxx=round((345+m_monster[value]->GetPosition().x+zerox)/boxsize+ii-(int)(mon[value]->mon_wei/boxsize)/2);
                int yyy=round((345+m_monster[value]->GetPosition().y)/boxsize);
                zerostart[23-yyy][xxx]=0;
                tmp[position[23-yyy][xxx]]->SetVisible(0);
                reset.push_back({23-yyy,xxx,3});
            }
            mon[value]->act=1;
        }
        if (mon[value]->act==1) {
            monsterpos.y+=mon[value]->acceleration[0];
        }
    }

    // die mon
    if (yy<0) {
        mon[value]->SetVisible(0);
    }

    else if (mon[value]->name=="tatle" && mon[value]->act==1 && playerstate!=PlayerState::Die && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_wei,mon[value]->mon_hei)) {
        if (playerpos.x>monsterpos.x) {
            mon[value]->acceleration[1]=-5;
        }
        else {
            mon[value]->acceleration[1]=5;
        }
    }

    else if (playerstate!=PlayerState::Die && mon[value]->name!="claude" && mon[value]->name!="yellowbat" && mon[value]->GetName()!="star" && mon[value]->GetName()!="fish" && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_wei,mon[value]->mon_hei) && playerpos.y>(monsterpos.y+6)) {
        if (mon[value]->name=="tatle" && mon[value]->act==0) {
            mon[value]->acceleration[1]=0;
            mon[value]->act=1;
            mon[value]->SetImage(GA_RESOURCE_DIR"/res/monster5.png");
        }
        else if (mon[value]->name!="tatle"){
            mon[value]->SetVisible(0);
        }
        Acceleration=10;
        sec=25;
    }

    //die plyaer
    else if ( (mon[value]->name!="tatle" || (mon[value]->name=="tatle" && mon[value]->act!=1)) && playerstate!=PlayerState::Die && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_wei,mon[value]->mon_hei)) {
        Acceleration=12;
        mon[value]->talk=1;
        m_player->SetImage(GA_RESOURCE_DIR"/res/player4.png");
        sec=30;
        playerstate=PlayerState::Die;
    }
    // die
    if (mon[value]->name!="claude") {
        mon[value]->SetPosition({monsterpos.x-zerox,monsterpos.y});
    }
}


// void Monster::Update(glm::vec2 playerpos,std::shared_ptr<Character> m_player,int zerox,int boxsize,int bug) {
//     //monster
//     pos.x+=zerox;
//     int xx=round((345+pos.x)/boxsize);
//     int yy=round((345+pos.y)/boxsize);
//
//     // if (talk==1 && name!="box") {
//     //     text->SetColor(Util::Color::FromName(Util::Colors::BLACK));
//     //     text->SetPosition({monsterpos.x+70-zerox,monsterpos.y+20});
//     //     text->Settext("loser");
//     // }
//     if (act==3) {
//         if (Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon_tragetrl,mon_traget)) {
//             act=1;
//         }
//     }
//     if (act!=3 && name!="fish" && name!="yellowbat" && name!="box"){
//         if (time>0) {
//             acceleration[0]-=1;
//             time-=1;
//         }
//         if (time!=0) {
//             monsterpos.y+=acceleration[0];
//         }
//         else if(yy>0 && UDCollision(xx,yy-1,monsterpos,-1,acceleration[0],mon_hei+2,mon_wei)){
//             if(GetName()=="star"){
//                 acceleration[0]=15;
//                 time=15;
//                 acceleration[1]=3;
//             }
//             else {
//                 if (name=="motopro" && act==1) {
//                     acceleration[1]=-1;
//                     act=2;
//                 }
//                 acceleration[0]=0;
//                 monsterpos.y=(yy*boxsize)-345-2;
//             }
//         }
//         else {
//             acceleration[0]=(acceleration[0]+0.3)*0.98;
//             monsterpos.y-=acceleration[0];
//         }
//
//         if (acceleration[1]<0) {
//             m_Transform.scale = glm::vec2(1.0f, 1.0f);
//             if (RLCollision(xx-1,yy,{monsterpos.x,monsterpos.y},-1,mon_hei,mon_wei)){
//                 acceleration[1]*=-1;
//             }
//         }
//         else if (acceleration[1]>0){
//             m_Transform.scale = glm::vec2(-1.0f, 1.0f);
//             if (RLCollision(xx+1,yy,{monsterpos.x,monsterpos.y},1,mon_hei,mon_wei)){
//                 acceleration[1]*=-1;
//             }
//         }
//         monsterpos.x+=acceleration[1];
//     }
//     else if (name=="fish") {
//         if (Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),boxsize,mon_traget)) {
//             act=1;
//         }
//         if (act==1) {
//             monsterpos.y+=acceleration[0];
//         }
//     }
//     else if (name=="yellowbat") {
//         if (Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon_tragetrl,mon_traget)) {
//             act=1;
//             SetVisible(1);
//         }
//         if (act==1) {
//             monsterpos.x+=acceleration[1];
//         }
//     }
//     else if (name=="box") {
//         if (act!=1 && ((type==1 && playerpos.y<monsterpos.y) || (type==2 && playerpos.y>monsterpos.y)) && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon_tragetrl,mon_traget)) {
//             for (int ii=0;ii<(int)(mon_wei/boxsize);ii++) {
//                 int xxx=round((345+m_monster[value]->GetPosition().x+zerox)/boxsize+ii-(int)(mon_wei/boxsize)/2);
//                 int yyy=round((345+m_monster[value]->GetPosition().y)/boxsize);
//                 zerostart[23-yyy][xxx]=0;
//                 tmp[position[23-yyy][xxx]]->SetVisible(0);
//                 reset.push_back({23-yyy,xxx,3});
//             }
//             act=1;
//         }
//         if (act==1) {
//             pos.y+=acceleration[0];
//         }
//     }
//
//     // die mon
//     if (yy<0) {
//         SetVisible(0);
//     }
//     else if (bug!=3 && name!="claude" && name!="yellowbat" && GetName()!="star" && GetName()!="fish" && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon_wei,mon_hei) && playerpos.y>(monsterpos.y+6)) {
//         SetVisible(0);
//         Acceleration=10;
//         sec=25;
//     }
//     // die
//
//     //die plyaer
//     else if (bug!=3 && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon_wei,mon_hei)) {
//         Acceleration=12;
//         talk=1;
//         m_player->SetImage(GA_RESOURCE_DIR"/res/player4.png");
//         sec=30;
//         bug=3;
//     }
//     // die
//     if (name!="claude") {
//         SetPosition({pos.x-zerox,pos.y});
//     }
// }