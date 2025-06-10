#include "App.hpp"
#include <vector>
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "Util/GameObject.hpp"
#include "Util/Transform.hpp"

void App::Zero() {
    LOG_TRACE("Zero");

    auto createObstacle = [&](const std::string& path, float x, float y, int zIndex, glm::vec2 scale = {1.0f, 1.0f}) {
        auto obs = std::make_shared<Obstacle>(path);
        obs->SetPosition({x, y});
        obs->SetZIndex(zIndex);
        obs->m_Transform.scale = scale;
        m_Root.AddChild(obs);
        tmp.push_back(obs);
    };

    m_player = std::make_shared<Character>(GA_RESOURCE_DIR"/res/player1.png");
    m_player->SetPosition({-180.5f, -280.0f});
    m_player->position={-180.5f, -280.0f};
    m_player->SetZIndex(48);
    m_Root.AddChild(m_player);

    createObstacle(GA_RESOURCE_DIR"/res/logo.png", 0, 300, 49);
    createObstacle(GA_RESOURCE_DIR"/res/grass.png", -50, -285, 49);
    createObstacle(GA_RESOURCE_DIR"/res/mountain.png", 200, -255, 49);

    text = std::make_shared<Textt>();
    text->SetPosition({0, 0});
    text->SetZIndex(70);
    text->Settext(" ");
    m_Root.AddChild(text);

    for (int y = std::size(zerostart) - 1; y >= 0; --y) {
        for (int x = std::size(zerostart[0]) - 1; x >= 0; --x) {
            int tile = zerostart[y][x];
            if (tile == 1) {
                createObstacle(
                    GA_RESOURCE_DIR"/res/brock10.png",
                    (x * boxsize) - ((WINDOW_WIDTH - boxsize) / 2),
                    ((23 - y) * boxsize) - ((WINDOW_HEIGHT - boxsize) / 2),
                    49
                );
            } else if (tile == 2) {
                createObstacle(
                    GA_RESOURCE_DIR"/res/brock13.png",
                    (x * boxsize) - ((WINDOW_WIDTH - boxsize) / 2),
                    ((23 - y) * boxsize) - ((WINDOW_HEIGHT - boxsize) / 2),
                    49
                );
            }
        }
    }

    m_PRM = std::make_shared<PhaseResourceManger>();
    m_Root.AddChildren(m_PRM->GetChildren());

    m_CurrentState = State::ZEROUPDATE;
}

