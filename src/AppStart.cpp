#include "App.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"
#include "Util/BGM.hpp"


void App::Start() {

    // Util::BGM bgm(GA_RESOURCE_DIR"/sound/field.mp3");
    // bgm.Play(-1);
    // LOG_TRACE("Start");

    m_monster.push_back(std::make_shared<Monster>(GA_RESOURCE_DIR"/res/monster3.png"));
    m_monster[m_monster.size()-1]->SetPosition({-112.5f, 0.0f});
    m_monster[m_monster.size()-1]->SetZIndex(51);
    m_monster[m_monster.size()-1]->SetOrigin({100,-280});
    m_Root.AddChild(m_monster[m_monster.size()-1]);

    monsterAcceleration.push_back({0,1});

    for (int x=std::size(zerostart[0]); x>=0; x--) {
        for (int y=std::size(zerostart); y>=0; y--) {
            if(zerostart[y][x] == 1) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/brock10.png"));
                tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
                tmp[tmp.size()-1]->SetZIndex(49);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
            else if(zerostart[y][x] == 2) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/brock13.png"));
                tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
                tmp[tmp.size()-1]->SetZIndex(49);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
            else if(zerostart[y][x] == 3) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/brock1.png"));
                tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
                tmp[tmp.size()-1]->SetZIndex(49);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
            else if(zerostart[y][x] == 4) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/box.png"));
                tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
                tmp[tmp.size()-1]->SetZIndex(48);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }//饅頭
            else if(zerostart[y][x] == 5) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/brock4.png"));
                tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
                tmp[tmp.size()-1]->SetZIndex(49);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
            else if(zerostart[y][x] == 6) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/shorttube.png"));
                tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2) - 15, ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
                tmp[tmp.size()-1]->SetZIndex(-22);
                tmp[tmp.size()-1]->m_Transform.scale = glm::vec2(0.8f, 1.0f);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
            else if(zerostart[y][x] == 7) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/longtube.png"));
                tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2) - 15, ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2) - 2});
                tmp[tmp.size()-1]->SetZIndex(48);
                tube.push_back((tmp.size()-1));
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
            else if(zerostart[y][x] == 8) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/brock4.png"));
                tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
                tmp[tmp.size()-1]->SetZIndex(48);
                tmp[tmp.size()-1]->SetVisible(0);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
            else if(zerostart[y][x] == 9) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/longtube_rotate90.png"));
                tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2) - 16, ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2) - 1});
                tmp[tmp.size()-1]->SetZIndex(48);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
            else if(zerostart[y][x] == 10) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/box.png"));
                tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
                tmp[tmp.size()-1]->SetZIndex(48);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }//會移動
            else if(zerostart[y][x] == 11) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/box.png"));
                tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
                tmp[tmp.size()-1]->SetZIndex(49);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }//星星
            else if(zerostart[y][x] == 12) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/box.png"));
                tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
                tmp[tmp.size()-1]->SetZIndex(49);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }//金幣
            else if(zerostart[y][x] == 14) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/brock7.png"));
                tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
                tmp[tmp.size()-1]->SetZIndex(49);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
            else if(zerostart[y][x] == 15) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/brock4.png"));
                tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
                tmp[tmp.size()-1]->SetZIndex(48);
                tmp[tmp.size()-1]->SetVisible(0);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }//ㄅㄥ金幣
            else if(zerostart[y][x] == 16) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/flag.png"));
                tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2) + 7, ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2) + 12});
                tmp[tmp.size()-1]->SetZIndex(49);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
            position[y][x]=tmp.size()-1;

        }
    }

    m_PRM = std::make_shared<PhaseResourceManger>();
    m_Root.AddChildren(m_PRM->GetChildren());

    m_CurrentState = State::UPDATE;
}