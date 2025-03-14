#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

void App::Update() {

    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::P) && sec==0) {
        bug=(bug+1)%2;
        sec=60;
    }

    int speed=3;

    if (bug==1) {
        if (sec!=0) {
            sec-=1;
        }
        auto playerpos=m_player->GetPosition();
        if (Util::Input::IsKeyPressed(Util::Keycode::W)) {
            m_player->SetPosition({playerpos.x,playerpos.y+speed});
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
            m_player->SetPosition({playerpos.x-speed,playerpos.y});
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::S)) {
            m_player->SetPosition({playerpos.x,playerpos.y-speed});
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::D) || Util::Input::IsKeyPressed(Util::Keycode::SPACE)) {
            m_player->SetPosition({playerpos.x+speed,playerpos.y});
        }
    }
    else {
        auto test=m_player->GetPosition();
        
        if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
            m_player->SetPosition({test.x-speed,test.y});
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::D)) {
            m_player->SetPosition({test.x+speed,test.y});
        }

        int yy=int((345-test.y)/30);
        int xx=int((345-test.x)/30);

        if(test.y>-360) {death-=1;}


        if (0<=xx-1 && xx+1<std::size(zerostart[0]) && 0<=yy-1 && yy+1<std::size(zerostart)) {
            glm::vec2 t1 = glm::vec2(xx*30,(yy+1)*30);
            if (zerostart[yy+1][xx]==0 && sec==0){
                Acceleration=(Acceleration+0.3)*0.98;
                if (zerostart[yy+1][xx]!=0) {
                    m_player->SetPosition({test.x,yy*30});
                    Acceleration=0;
                }
                else{
                    m_player->SetPosition({test.x,test.y-Acceleration});
                }
            }
            else if(sec!=0) {
                sec-=1;
                Acceleration=(Acceleration-1);
                if (zerostart[yy+1][xx]!=0) {
                    m_player->SetImage(GA_RESOURCE_DIR"/res/player1.png");
                    Acceleration=0;
                    sec=0;
                }
                m_player->SetPosition({test.x,test.y+Acceleration});
            }
            else {
                if (Util::Input::IsKeyPressed(Util::Keycode::W) || Util::Input::IsKeyPressed(Util::Keycode::SPACE)) {
                    sec=50;
                    Acceleration=20;
                    m_player->SetImage(GA_RESOURCE_DIR"/res/player3.png");
                    m_player->SetPosition({test.x,test.y+Acceleration});
                    }
            }

        }
    }


    // if(m_player->GetPosition().x>=0) {
    //     m_Root->m_Transform
    // }
    m_Root.Update();
}
