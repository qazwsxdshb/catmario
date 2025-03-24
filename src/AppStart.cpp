#include "App.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"
#include "Util/BGM.hpp"


void App::Start() {

    Util::BGM bgm(GA_RESOURCE_DIR"/sound/field.mp3");
    bgm.Play(-1);
    LOG_TRACE("Start");
    for (int y=std::size(zerostart); y>=0; y--) {
        for (int x=std::size(zerostart[0]); x>=0; x--) {
            if(zerostart[y][x] == 1) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/brock10.png"));
                tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
                tmp[tmp.size()-1]->SetZIndex(49);
                m_Root.AddChild(tmp[tmp.size()-1]);
                position[y][x]=tmp.size()-1;
            }
            else if(zerostart[y][x] == 2) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/brock13.png"));
                tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
                tmp[tmp.size()-1]->SetZIndex(49);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
        }
    }


    m_PRM = std::make_shared<PhaseResourceManger>();
    m_Root.AddChildren(m_PRM->GetChildren());

    m_CurrentState = State::UPDATE;
}
