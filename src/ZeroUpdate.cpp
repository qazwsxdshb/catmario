#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

void App::ZeroUpdate() {

    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    glm::vec2 pos=Util::Input::GetCursorPosition();
    // if(0<pos.x && pos.x<100 && 0<pos.y && pos.y<100){
    if(Util::Input::IsKeyPressed(Util::Keycode::K)){
        for (int i=0;i<tmp.size();i++) {m_Root.RemoveChild(tmp[i]);}
        m_PRM->NextPhase();
        m_CurrentState = State::START;
    }

    m_Root.Update();
}
