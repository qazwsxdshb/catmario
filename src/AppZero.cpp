#include "App.hpp"
#include <vector>
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "Util/GameObject.hpp"
#include "Util/Transform.hpp"

void App::Zero() {
    LOG_TRACE("Zero");

    m_player = std::make_shared<Character>(GA_RESOURCE_DIR"/res/player1.png");
    m_player->SetPosition({-112.5f, -280.0f});
    m_player->SetZIndex(50);
    // m_player->m_Transform.rotation = 3;
    m_Root.AddChild(m_player);


    tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/logo.png"));
    tmp[0]->SetPosition({0, 300});
    tmp[0]->SetZIndex(49);
    m_Root.AddChild(tmp[0]);

    tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/grass.png"));
    tmp[1]->SetPosition({0, -285});
    tmp[1]->SetZIndex(49);
    m_Root.AddChild(tmp[1]);

    tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/mountain.png"));
    tmp[2]->SetPosition({300, -255});
    tmp[2]->SetZIndex(49);
    tmp[2]->m_Transform.scale = glm::vec2(1.0f, 1.0f);
    m_Root.AddChild(tmp[2]);


    for (int y=std::size(zerostart)-1; y>=0; y--) {
        for (int x=0; x<std::size(zerostart[0]); x++) {
            if(zerostart[y][x] == 1) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/brock10.png"));
                tmp[tmp.size()-1]->SetPosition({3450-(x*30), 345-(y*30)});
                tmp[tmp.size()-1]->SetZIndex(49);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
            else if(zerostart[y][x] == 2) {
                tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/brock13.png"));
                tmp[tmp.size()-1]->SetPosition({3450-(x*30), 345-(y*30)});
                tmp[tmp.size()-1]->SetZIndex(49);
                m_Root.AddChild(tmp[tmp.size()-1]);
            }
        }
    }

    // std::shared_ptr<Textt> test=std::make_shared<Textt>();
    // test->texte=std::to_string('test');
    // tmptext.push_back(test);

    m_PRM = std::make_shared<PhaseResourceManger>();
    m_Root.AddChildren(m_PRM->GetChildren());

    m_CurrentState = State::ZEROUPDATE;
}
