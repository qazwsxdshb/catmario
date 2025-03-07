#include "App.hpp"

#include "Util/Logger.hpp"
#include "Util/Input.hpp"


void App::Start() {
    LOG_TRACE("Start");

    m_player = std::make_shared<Character>(GA_RESOURCE_DIR"/res/player.png");
    m_player->SetPosition({-112.5f, -140.5f});
    m_player->SetZIndex(50);
    m_Root.AddChild(m_player);


    // glm::vec2 pos=Util::Input::GetCursorPosition();
    // // if(0<pos.x && pos.x<100 && 0<pos.y && pos.y<100){
    // if(Util::Input::IsKeyPressed(Util::Keycode::K)){
    //     m_CurrentState = State::START;
    // }
    // m_CurrentState = State::UPDATE;
//
//
//    std::vector<std::string> beeImages;
//    beeImages.reserve(2);
//    for (int i = 0; i < 2; ++i) {
//        beeImages.emplace_back(GA_RESOURCE_DIR"/Image/Character/bee_" + std::to_string(i + 1) + ".png");
//    }
//
//    m_Bee = std::make_shared<AnimatedCharacter>(beeImages);
//    m_Bee->SetZIndex(5);
//    m_Bee->SetVisible(false);
//    m_Root.AddChild(m_Bee);
//
//    for (int i = 0; i < 3; ++i) {
//        m_Doors.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/Image/Character/door_close.png"));
//        m_Doors[i]->SetZIndex(5);
//        m_Doors[i]->SetPosition({205.5f - 80.f * i, -3.5f});
//        m_Doors[i]->SetVisible(false);
//        m_Root.AddChild(m_Doors[i]);
//    }


    m_PRM = std::make_shared<PhaseResourceManger>();
    m_Root.AddChildren(m_PRM->GetChildren());


    m_CurrentState = State::UPDATE;
}
