#include "App.hpp"
#include <vector>
#include "Util/Input.hpp"
#include "Util/Logger.hpp"

void App::Zero() {
    LOG_TRACE("Zero");

    m_player = std::make_shared<Character>(GA_RESOURCE_DIR"/res/player.png");
    m_player->SetPosition({-112.5f, -140.5f});
    m_player->SetZIndex(50);
    m_Root.AddChild(m_player);


    tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/logo.png"));
    tmp[0]->SetPosition({0, 300});
    tmp[0]->SetZIndex(49);
    m_Root.AddChild(tmp[0]);

    



    m_PRM = std::make_shared<PhaseResourceManger>();
    m_Root.AddChildren(m_PRM->GetChildren());


    m_CurrentState = State::ZEROUPDATE;

}
