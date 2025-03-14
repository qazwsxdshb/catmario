#include "App.hpp"
#include <vector>
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "Util/GameObject.hpp"

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

    for (int i=tmp.size();i<26;i++) {
        tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/brock10.png"));
        tmp[i]->SetPosition({-350+(i-1)*30, -300});
        tmp[i]->SetZIndex(49);
        m_Root.AddChild(tmp[i]);
    }

    for (int i=0;i<25;i++) {
        tmp.push_back(std::make_shared<Character>(GA_RESOURCE_DIR"/res/brock13.png"));
        tmp[i+26]->SetPosition({-350+i*30, -330});
        tmp[i+26]->SetZIndex(49);
        m_Root.AddChild(tmp[i+26]);
    }

    // std::shared_ptr<Textt> test=std::make_shared<Textt>();
    // test->texte=std::to_string('test');
    // tmptext.push_back(test);

    m_PRM = std::make_shared<PhaseResourceManger>();
    m_Root.AddChildren(m_PRM->GetChildren());

    m_CurrentState = State::ZEROUPDATE;
}
