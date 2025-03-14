#include "App.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"


void App::Start() {
    LOG_TRACE("Start");


    for (int y=std::size(zerostart)-1; y>=0; y--) {
        for (int x=0; x<std::size(zerostart[0]); x++) {
            if(zerostart[y][x] == 1) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/brock10.png"));
                tmp[tmp.size()-1]->SetPosition({345-(x*30), 345-(y*30)});
                tmp[tmp.size()-1]->SetZIndex(49);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
            else if(zerostart[y][x] == 2) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/brock13.png"));
                tmp[tmp.size()-1]->SetPosition({345-(x*30), 345-(y*30)});
                tmp[tmp.size()-1]->SetZIndex(49);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
        }
    }


    m_PRM = std::make_shared<PhaseResourceManger>();
    m_Root.AddChildren(m_PRM->GetChildren());


    m_CurrentState = State::UPDATE;
}
