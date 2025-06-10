#include "Monster.hpp"
#include "Util/Input.hpp"
#include "Util/Image.hpp"
#include "Character.hpp"
#include "App.hpp"


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
    if (gaint==1) {
        mon_wei/=2;
        SetImage(GA_RESOURCE_DIR"/res/monster3.png");
        if (name=="king2") {
            SetImage(GA_RESOURCE_DIR"/res/monster7.png");
        }
    }
    gaint=0;
    move=0;
    acceleration=oriacceleration;
    SetVisible(1);
    if (name=="claude2") {
        act=1;
    }
    else if (name=="claude") {
        SetImage(GA_RESOURCE_DIR"/res/claude.png");
    }
    else if (name=="boxSpiked") {
        SetImage(GA_RESOURCE_DIR"/res/brock8.png");
    }
    else if (name=="robot") {
        type=-1;
        act=-1;
        SetImage(GA_RESOURCE_DIR"/res/robot2.png");
    }
    else if (name=="flag"){act=3;}
    else if (name=="fly"){
        act=0;
        SetImage(GA_RESOURCE_DIR"/res/superman1.png");
    }
    else if (name=="state2") {
        act=-1;
    }
    else if (name=="yellowbat" || name=="flymoto") {
        SetVisible(0);
    }
    else if (name=="tatle") {
        type=-1;
        SetImage(GA_RESOURCE_DIR"/res/monster4.png");
    }
    else if (name=="motopro" || name=="king" || name=="fireball") {
        acceleration[1]=0;
        if (name=="king") {
            acceleration[1]=-2;
        }
        if (name=="fireball") {
            acceleration[1]=(((double)rand())/RAND_MAX)*2-1;
        }
        if (mon_mul==2) {
            acceleration[1]=0;
        }
        act=3;
        SetVisible(0);
    }
    m_Transform.translation = {pos.x-zerox,pos.y};
}

void App::Monsteract(glm::vec2 monsterpos,int value,glm::vec2 playerpos,std::vector<std::shared_ptr<Monster>> mon) {
    //monster
    monsterpos.x+=zerox;
    int xx=round((345+monsterpos.x)/boxsize);
    int yy=round((345+monsterpos.y)/boxsize);

    if (mon[value]->talk==1 && mon[value]->name!="box") {
        text->SetColor(Util::Color::FromName(Util::Colors::BLACK));
        if (level==3) {
            text->SetColor(Util::Color::FromName(Util::Colors::WHITE));
        }
        text->SetPosition({monsterpos.x+70-zerox,monsterpos.y+20});
        text->Settext("loser");
    }
    if (mon[value]->name=="flag") {
        if (Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_tragetrl,mon[value]->mon_traget)) {
            mon[value]->act=1;
        }
    }
    else if (mon[value]->act==3) {
        mon[value]->SetVisible(0);
        if (Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_tragetrl,mon[value]->mon_traget)) {
            mon[value]->act=1;
            mon[value]->SetVisible(1);
            if (mon[value]->name=="king") {
                mon[value]->time=15;
            }
            else if (mon[value]->name=="fireball") {
                mon[value]->time=20;
            }
        }
    }

    if (mon[value]->name=="claude2" && mon[value]->act==1) {
        mon[value]->act=2;
        mon[value]->SetVisible(0);
    }
    if (mon[value]->name=="tatle" && mon[value]->type>-1) {
        mon[value]->type-=1;
    }

    if (mon[value]->name=="state" || mon[value]->name=="state2") {
        if (mon[value]->name=="state" && mon[value]->acceleration[0]<0 && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_tragetrl,mon[value]->mon_traget)) {
            mon[value]->acceleration[0]=-3;
        }
        else if(mon[value]->acceleration[0]<0){
            mon[value]->acceleration[0]=-1;
        }
        if (Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_wei,mon[value]->mon_hei+6) && playerpos.y>(monsterpos.y)) {
            mon[value]->act=1;
            if ((Util::Input::IsKeyPressed(Util::Keycode::W) || Util::Input::IsKeyPressed(Util::Keycode::SPACE))) {
                sec=50;
                Acceleration=16;
            }
        }
        if (Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_wei,mon[value]->mon_hei+1) && playerpos.y>(monsterpos.y)) {
            Acceleration=-(mon[value]->acceleration[0]*2);
            if (mon[value]->acceleration[0]<0) {
                Acceleration=(mon[value]->acceleration[0]*0.5);
            }
            if (mon[value]->acceleration[0]>0 && mon[value]->name!="state2") {
                Acceleration-=mon[value]->acceleration[0];
            }
        }
        monsterpos.y+=mon[value]->acceleration[0];
    }
    else if (mon[value]->act!=3 && mon[value]->name!="fish" && mon[value]->name!="yellowbat" && mon[value]->name!="flymoto" && mon[value]->name!="box" && mon[value]->name!="dropbox"){
        if (mon[value]->time>0) {
            mon[value]->acceleration[0]-=1;
            mon[value]->time-=1;
        }

        //gaint
        if(mon[value]->gaint==1) {
            tmp[position[24-yy][xx+1]]->SetVisible(0);
            tmp[position[24-yy][xx]]->SetVisible(0);
            tmp[position[24-yy][xx-1]]->SetVisible(0);
            reset.push_back({24-yy,xx+1,zerostart[24-yy][xx+1]});
            reset.push_back({24-yy,xx,zerostart[24-yy][xx]});
            reset.push_back({24-yy,xx-1,zerostart[24-yy][xx-1]});
        }
        //

        if (mon[value]->time!=0) {
            monsterpos.y+=mon[value]->acceleration[0];
        }
        else if(mon[value]->name!="fireball" && mon[value]->name!="fly" && yy>0 && UDCollision(xx,yy-1,monsterpos,-1,mon[value]->acceleration[0],mon[value]->mon_hei+2,mon[value]->mon_wei)){
            if(mon[value]->GetName()=="star"){
                mon[value]->acceleration[0]=15;
                mon[value]->time=15;
                mon[value]->acceleration[1]=3;
            }
            else if(mon[value]->GetName()=="king3" && sec>0 && Acceleration>0){
                mon[value]->acceleration[0]=15;
                mon[value]->time=15;
            }
            else {
                if ((mon[value]->name=="motopro" || mon[value]->name=="king" || mon[value]->name=="fireball") && mon[value]->act==1) {
                    mon[value]->acceleration[1]=-1;
                    mon[value]->act=2;
                }
                mon[value]->acceleration[0]=0;
                monsterpos.y=(yy*boxsize)-345-2;
            }
        }
        else if (mon[value]->name=="fly" && mon[value]->act==0) {
            if (monsterpos.y>-100){
                mon[value]->acceleration[0]=-1;
            }
            else if (monsterpos.y<-240) {
                mon[value]->acceleration[0]=1;
            }
            monsterpos.y+=mon[value]->acceleration[0];
        }
        else {
            mon[value]->acceleration[0]=(mon[value]->acceleration[0]+0.3)*0.98;
            monsterpos.y-=mon[value]->acceleration[0];
        }

        if (mon[value]->acceleration[1]<0) {
            mon[value]->m_Transform.scale = glm::vec2(1.0f, 1.0f);
            if (zerostart[23-yy][xx-1]==8 && mon[value]->name=="tatle" && mon[value]->acceleration[1]<-4){
                tmp[position[23-yy][xx-1]]->SetVisible(1);
                reset.push_back({23-yy,xx-1,8});
            }
            else if (zerostart[23-yy][xx-1]==3 && mon[value]->name=="tatle" && mon[value]->acceleration[1]<-4){
                tmp[position[23-yy][xx-1]]->SetVisible(0);
                zerostart[23-yy][xx-1]=0;
                reset.push_back({23-yy,xx-1,3});
                mon[value]->acceleration[1]*=-1;
            }
            if (zerostart[23-yy][xx-1]==22 || RLCollision(xx-1,yy,{monsterpos.x,monsterpos.y},-1,mon[value]->mon_hei,mon[value]->mon_wei)){
                mon[value]->acceleration[1]*=-1;
            }
        }
        else if (mon[value]->acceleration[1]>0){
            mon[value]->m_Transform.scale = glm::vec2(-1.0f, 1.0f);
            if (zerostart[23-yy][xx+1]==8 && mon[value]->name=="tatle" && mon[value]->acceleration[1]>4) {
                tmp[position[23-yy][xx+1]]->SetVisible(1);
                reset.push_back({23-yy,xx+1,8});
            }
            else if (zerostart[23-yy][xx+1]==3 && mon[value]->name=="tatle" && mon[value]->acceleration[1]>4){
                tmp[position[23-yy][xx+1]]->SetVisible(0);
                zerostart[23-yy][xx+1]=0;
                reset.push_back({23-yy,xx+1,3});
                mon[value]->acceleration[1]*=-1;
            }
            if (zerostart[23-yy][xx+1]==22 || RLCollision(xx+1,yy,{monsterpos.x,monsterpos.y},1,mon[value]->mon_hei,mon[value]->mon_wei)){
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

    else if (mon[value]->name=="yellowbat" || mon[value]->name=="flymoto") {
        if (Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_tragetrl,mon[value]->mon_traget)) {
            mon[value]->act=1;
            mon[value]->SetVisible(1);
        }
        if (mon[value]->act==1) {
            monsterpos.x+=mon[value]->acceleration[1];
            monsterpos.y+=mon[value]->acceleration[0];
        }
    }
    else if (mon[value]->name=="dropbox") {
        if (mon[value]->act!=1 && ((mon[value]->type==1 && playerpos.y<monsterpos.y) || (mon[value]->type==2 && playerpos.y>monsterpos.y)) && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_tragetrl,mon[value]->mon_traget)) {
            for (int ii=0;ii<(int)(mon[value]->mon_wei/boxsize);ii++) {
                int xxx=round((345+m_monster[value]->GetPosition().x+zerox)/boxsize+ii-(int)(mon[value]->mon_wei/boxsize)/2);
                int yyy=round((345+m_monster[value]->GetPosition().y)/boxsize);
                zerostart[23-yyy][xxx]=0;
                tmp[position[23-yyy][xxx]]->SetVisible(0);
                reset.push_back({23-yyy,xxx,3});
            }
            mon[value]->act=1;
            dropdrop++;
        }
        if (mon[value]->act==1) {
            monsterpos.y+=(mon[value]->acceleration[0]);
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
            if (Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_wei,mon[value]->mon_hei+8) && playerpos.y>(monsterpos.y)) {
                if ((Util::Input::IsKeyPressed(Util::Keycode::W) || Util::Input::IsKeyPressed(Util::Keycode::SPACE))) {
                    sec=50;
                    Acceleration=16;
                }
                else{
                    Acceleration=-1;
                }
            }
            monsterpos.y+=(mon[value]->acceleration[0]/5);
        }
    }

    // die mon
    if (yy<0) {
        mon[value]->SetVisible(0);
    }
    else if (mon[value]->name=="blueP" && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_wei,mon[value]->mon_hei * mon[value]->mon_mul)){
        mon[value]->SetVisible(0);
        for (int x = 70; x >= 49; --x) {
            for (int y = std::size(zerostart) - 1; y >= 14; --y) {
                if(zerostart[y][x]==1 || zerostart[y][x]==2 || zerostart[y][x]==3 || zerostart[y][x]==12 || zerostart[y][x]==21 || zerostart[y][x]==38 || zerostart[y][x]==39) {
                    m_coin.push_back(std::make_shared<Coin>(GA_RESOURCE_DIR"/res/coin.png"));
                    m_coin[m_coin.size()-1]->SetPosition(tmp[position[y][x]]->GetPosition());
                    m_coin[m_coin.size()-1]->time=11;
                    m_coin[m_coin.size()-1]->SetZIndex(51);
                    m_Root.AddChild(m_coin[m_coin.size()-1]);
                    tmp[position[y][x]]->SetVisible(0);
                    reset.push_back({y,x,zerostart[y][x]});
                }
            }
        }
    }
    else if (mon[value]->name=="greenball" && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_wei,mon[value]->mon_hei * mon[value]->mon_mul)){
        fireball=1;
        mon[value]->SetVisible(0);
    }
    else if (mon[value]->name=="tatle" && mon[value]->act==1 && playerstate!=PlayerState::Die && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_wei,mon[value]->mon_hei)) {
        if (playerpos.x>monsterpos.x) {
            mon[value]->acceleration[1]=-5;
        }
        else {
            mon[value]->acceleration[1]=5;
        }
        mon[value]->type=20;
        mon[value]->act=2;
    }

    else if (mon[value]->name=="redmushroom" && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_wei,mon[value]->mon_hei)) {
        m_player->SetImage(GA_RESOURCE_DIR"/res/giant.png");
        m_player->gaint=1;
        mon[value]->SetVisible(0);
        playerstate=PlayerState::Die;
    }


    else if (playerstate!=PlayerState::Die && mon[value]->name=="flag" && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_wei,mon[value]->mon_hei * mon[value]->mon_mul) && (playerpos.y>(monsterpos.y+(13 * mon[value]->mon_mul)+6))){
        Acceleration=10;
        sec=25;
        mon[value]->act=1;
    }
    //die monster
    else if (playerstate!=PlayerState::Die && mon[value]->name!="Poisonous" && mon[value]->name!="robot" && mon[value]->name!="state" && mon[value]->name!="state2" && mon[value]->name!="king2" && mon[value]->name!="king3" && mon[value]->name!="fireball" && mon[value]->name!="box" &&  playerstate!=PlayerState::Die && mon[value]->name!="boxSpiked" && mon[value]->name!="claude" && mon[value]->name!="claude2" && mon[value]->name!="yellowbat" && mon[value]->GetName()!="star" && mon[value]->GetName()!="fish" && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_wei,mon[value]->mon_hei * mon[value]->mon_mul) &&  (playerpos.y>(monsterpos.y+(13 * (mon[value]->mon_mul-1))+6))) {
        if (mon[value]->name=="tatle" && mon[value]->act==0) {
            mon[value]->acceleration[1]=0;
            mon[value]->act=1;
            mon[value]->SetImage(GA_RESOURCE_DIR"/res/monster5.png");
        }
        else if (mon[value]->name=="fly" && mon[value]->act==0) {
            mon[value]->SetImage(GA_RESOURCE_DIR"/res/happy.png");
            mon[value]->act=1;
        }
        else if (mon[value]->name!="tatle" && mon[value]->name!="greenbat" && mon[value]->name!="king"){
            mon[value]->SetVisible(0);
        }
        Acceleration=10;
        sec=25;
        if (mon[value]->name=="greenbat") {
            playerstate=PlayerState::Die;
            rlsec=120;
            sec=90;
            Acceleration=0;
        }
    }

    //die plyaer
    else if (Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_wei,mon[value]->mon_hei * mon[value]->mon_mul) && mon[value]->name=="robot") {
        mon[value]->SetImage(GA_RESOURCE_DIR"/res/robot3.png");
        m_player->SetPosition({monsterpos.x-zerox,monsterpos.y+30});
        playerstate=PlayerState::Die;
        sec=30;
        Acceleration=12;
        m_player->SetImage(GA_RESOURCE_DIR"/res/player3.png");
        mon[value]->m_Transform.scale = glm::vec2(-1.0f, 1.0f);
        mon[value]->acceleration[1]=0;
        rlsec=-1;
    }
    else if (mon[value]->name=="robot" && (zerostart[22-yy][xx-1]==27 || mon[value]->act==1)) {
        if (mon[value]->act!=1) {
            playerstate=PlayerState::Normal;
            mon[value]->SetImage(GA_RESOURCE_DIR"/res/robot3.png");
            mon[value]->act=1;
            mon[value]->type=position[22-yy][xx-1];
            zerostart[22-yy][xx-1]=0;
            tmp[mon[value]->type]->SetPosition({monsterpos.x-zerox,monsterpos.y+180});
            printf("xx %d yy %d\n\n",xx-1,22-yy);
            reset.push_back({22-yy,xx-1,27});
        }
        else {
            tmp[mon[value]->type]->SetPosition({monsterpos.x-zerox,monsterpos.y+180});
            if (yy==1) {
                tmp[mon[value]->type]->SetVisible(0);
            }
        }
    }

    else if (mon[value]->name!="greenbat" && mon[value]->name!="state" && mon[value]->name!="state2" && (mon[value]->name!="tatle" || (mon[value]->name=="tatle" && mon[value]->act!=1 && mon[value]->type==-1)) && playerstate!=PlayerState::Die && Collision((int)(playerpos.x),(int)(playerpos.y),playerwidth,playerheight,(int)(monsterpos.x),(int)(monsterpos.y),mon[value]->mon_wei,mon[value]->mon_hei * mon[value]->mon_mul)) {
        if (mon[value]->name=="boxSpiked") {
            mon[value]->SetImage(GA_RESOURCE_DIR"/res/rock.png");
        }
        else if (mon[value]->name=="claude2") {
            mon[value]->SetVisible(1);
        }
        else if (mon[value]->name=="claude") {
            mon[value]->SetImage(GA_RESOURCE_DIR"/res/claude2.png");
        }
        Acceleration=12;
        mon[value]->talk=1;
        m_player->SetImage(GA_RESOURCE_DIR"/res/player4.png");
        sec=30;
        playerstate=PlayerState::Die;
    }
    // die
    if (mon[value]->name!="claude" && mon[value]->name!="claude2" && mon[value]->name!="boxSpiked" && mon[value]->name!="state2" && mon[value]->name!="greenbat") {
        mon[value]->SetPosition({monsterpos.x-zerox,monsterpos.y});
    }
    else if (mon[value]->name=="state2" && mon[value]->act==1) {
        mon[value]->SetPosition({monsterpos.x-zerox,monsterpos.y});
    }
}
