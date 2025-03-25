#include "App.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"


void App::Start() {
    LOG_TRACE("Start");


    for (int y=std::size(zerostart)-1; y>=0; y--) {
        for (int x=0; x<std::size(zerostart[0]); x++) {
            if(zerostart[y][x] == 1) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/brock10.png"));
                tmp[tmp.size()-1]->SetPosition({(x*30) - 345, ((23-y) * 30)-345});
                tmp[tmp.size()-1]->SetZIndex(49);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
            else if(zerostart[y][x] == 2) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/brock13.png"));
                tmp[tmp.size()-1]->SetPosition({(x*30) - 345, ((23-y) * 30)-345});
                tmp[tmp.size()-1]->SetZIndex(49);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
            else if(zerostart[y][x] == 3) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/brock1.png"));
                tmp[tmp.size()-1]->SetPosition({(x*30) - 345, ((23-y) * 30)-345});
                tmp[tmp.size()-1]->SetZIndex(49);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
            else if(zerostart[y][x] == 4) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/box.png"));
                tmp[tmp.size()-1]->SetPosition({(x*30) - 345, ((23-y) * 30)-345});
                tmp[tmp.size()-1]->SetZIndex(49);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
            else if(zerostart[y][x] == 5) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/brock4.png"));
                tmp[tmp.size()-1]->SetPosition({(x*30) - 345, ((23-y) * 30)-345});
                tmp[tmp.size()-1]->SetZIndex(49);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
            else if(zerostart[y][x] == 6) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/shorttube.png"));
                tmp[tmp.size()-1]->SetPosition({(x*30) - 345, ((23-y) * 30)-345});
                tmp[tmp.size()-1]->SetZIndex(49);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
            else if(zerostart[y][x] == 7) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/longtube.png"));
                tmp[tmp.size()-1]->SetPosition({(x*30) - 345, ((23-y) * 30)-345});
                tmp[tmp.size()-1]->SetZIndex(48);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
        }


        m_PRM = std::make_shared<PhaseResourceManger>();
        m_Root.AddChildren(m_PRM->GetChildren());


        m_CurrentState = State::UPDATE;
    }
}