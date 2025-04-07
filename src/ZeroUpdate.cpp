#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"


bool RectCollision(glm::vec2 r1,glm::vec2 r2,int r1width,int r1height,int r2width,int r2height) {
    int minX1 = r1.x-r1width/2;
    int maxX1 = r1.x+r1width/2;
    int minY1 = r1.y-r1height/2;
    int maxY1 = r1.y-r1height/2;

    int minX2 = r2.x-r2width/2;
    int maxX2 = r2.x+r2width/2;
    int minY2 = r2.y-r2height/2;
    int maxY2 = r2.y-r2height/2;

    if (maxX1>minX2 && maxX2>minX1 && maxY1>minY2 && maxY2>minY1) {
        return true;
    }
    return false;
}

void App::ZeroUpdate() {
    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if(Util::Input::IsKeyPressed(Util::Keycode::SPACE)){
        for (int i=0;i<tmp.size();i++) {m_Root.RemoveChild(tmp[i]);}
        m_PRM->NextPhase();
        m_CurrentState = State::START;
    }

    auto playerpos=m_player->GetPosition();
    int yy=int((345-playerpos.y)/30);
    int xx=int((345-playerpos.x)/30);

    if (0<=xx-1 && xx+1<std::size(zerostart[0]) && 0<=yy-1 && yy+1<std::size(zerostart)) {
        if (zerostart[yy+1][xx]==0 && playerpos.y>-360){
            auto test=m_player->GetPosition();
            Acceleration=(Acceleration+0.2)*0.98;
            m_player->SetPosition({test.x,test.y-Acceleration});
        }
        else {
            Acceleration=0;
        }
    }

    m_Root.Update();
}
