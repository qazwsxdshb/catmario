#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"

void App::Zero() {
    LOG_TRACE("Zero");

    m_player = std::make_shared<Character>(GA_RESOURCE_DIR"/res/player.png");
    m_player->SetPosition({-112.5f, -140.5f});
    m_player->SetVisible(true);
    m_player->SetZIndex(50);
    m_Root.AddChild(m_player);


    m_PRM = std::make_shared<PhaseResourceManger>();
    m_Root.AddChildren(m_PRM->GetChildren());

    glm::vec2 pos=Util::Input::GetCursorPosition();
    // if(0<pos.x && pos.x<100 && 0<pos.y && pos.y<100){
    if(Util::Input::IsKeyPressed(Util::Keycode::K)){
        m_CurrentState = State::START;
    }
    m_Root.Update();
}
