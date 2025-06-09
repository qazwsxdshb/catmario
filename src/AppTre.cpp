#include "App.hpp"
#include "Util/Logger.hpp"
#include "Util/Input.hpp"
#include "Util/BGM.hpp"



void App::Tre() {
    auto createObstacle = [&](const std::string& path, float x, float y, int zIndex, glm::vec2 scale = {1.0f, 1.0f}) {
        auto obs = std::make_shared<Obstacle>(path);
        obs->SetPosition({x, y});
        obs->SetZIndex(zIndex);
        obs->m_Transform.scale = scale;
        m_Root.AddChild(obs);
        tmp.push_back(obs);
    };

    m_player->SetPosition({-285.0f, -260.0f});
    m_player->position={-175.0f, -260.0f};
    // 怪物
    AddMonster({"res/greenball.png", {-45.0f, -285.0f}, 51, {1.0f, 1.0f}, "greenball", {0, 0}});

    AddMonster({
        "res/monster7.png", { 465.0f, 15.0f}, 51, {1.0f, 1.0f}, "king2", {0, -1}
    });

    AddMonster({
        "res/brock7.png", {945, -255}, 48, {1.0f, 1.0f}, "boxSpiked", {0, 0},
        2, -1, 30, 30, 30
    });
    AddMonster({
        "res/yellowbat.png", {825, -105.0f}, 51, {1.0f, 1.0f}, "state2", {-1, 0},
        -1, -1, 90, 1024, 120, 20,1
    });
    AddMonster({
        "res/greenbat.png", {1035, -195.0f}, 51, {1.0f, 1.0f}, "greenbat", {0, 0},
        -1, -1, 90, -1, -1, 20
    });


    AddMonster({"res/monster3.png", {1665.0f, -285.0f}, 51, {1.0f, 1.0f}, "", {0, -1}});
    AddMonster({"res/monster3.png", {1725.0f, -290.0f}, 51, {1.0f, 1.0f}, "", {0, -1}});

    AddMonster({"res/robot2.png", {2145.0f, -195.0f}, 51, {1.0f, 1.0f}, "robot", {0, -1}});

    AddMonster({
        "res/monster4.png", {3465.0, -45.0f}, 51, {1.0f, 1.0f}, "tatle", {0, 1}
    });

    AddMonster({"res/robot2.png", {4005.0f, -285.0f}, 51, {1.0f, 1.0f}, "robot", {0, -1}});


    // 障礙物類型映射
    std::unordered_map<int, ObstacleInfo> obstacleMap = {
        {1,  {"res/brock10.png", 49}},
        {2,  {"res/brock13.png", 49}},
        {3,  {"res/brock1.png", 49}},
        {4,  {"res/box.png", 50}},
        {5,  {"res/brock4.png", 49}},
        {6,  {"res/shorttube.png", -22, true, {-15.0f, 0.0f}, {0.8f, 1.0f}}},
        {7,  {"res/longtube.png", 48, true, {-15.0f, -2.0f}}},
        {8,  {"res/brock4.png", 48, false}},
        {9,  {"res/longtube_rotate90.png", 48, true, {-16.0f, -1.0f}}},
        {10, {"res/box.png", 48}},
        {11, {"res/brock1.png", 49}},
        {12, {"res/box.png", 49}},
        {13, {"res/castle.png", 30}},
        {14, {"res/brock7.png", 49}},
        {15, {"res/brock4.png", 48, false}},
        {16, {"res/flag_back.png", 49, true, {7.0f, 12.0f}}},
        {17, {"res/brock4.png", 48, false}},
        {18, {"res/brock10.png", 49}},
        {19, {"res/brock13.png", 49}},
        {20, {"res/claude.png",49,true,{0.0f, 0.0f},{1.1f, 1.0f}}},
        {21, {"res/brock1.png", 49}},
        {22, {"res/brock11.png", 49,false}},
        {23, {"res/brock14.png", 49}},
        {24, {"res/brock8.png", 49}},
        {25, {"res/brock5.png", 48}},
        {26, {"res/box.png", 49}},
        {27, {"res/flagpole.png", 30}},
        {28, {"res/button.png", 49}},
        {29, {"res/Tube.png", 49, true, {-14.0f, 14.0f}}},
        {30, {"res/claude3.png", 49, true, {0.0f, -15.0f}}},
        {31, {"res/flag_back.png", 49, true, {7.0f, 12.0f}}},
        {32, {"res/box.png", 49}},
        {33, {"res/longlongtube.png", 48, true, {-15.0f, -15.0f}}},
        {34, {"res/box.png", 50}},
        {35, {"res/note2.png", 48, false}},
        {36, {"res/yellowbat.png", 49, true, {0.0f, 12.0f}}},
        {37, {"res/greenbat.png", 49, true, {0.0f, 12.0f}}},
        {38, {"res/box.png", 50}},
        {39, {"res/box.png", 49}},
        {40, {"res/platform.png", 49}}
    };


    // 建立地圖障礙物
    for (int x = std::size(zerostart[0]) - 1; x >= 0; --x) {
        for (int y = std::size(zerostart) - 1; y >= 0; --y) {
            int type = zerostart[y][x];
            auto it = obstacleMap.find(type);
            if (it != obstacleMap.end()) {
                glm::vec2 basePos = {
                    (x * boxsize) - ((WINDOW_WIDTH - boxsize) / 2),
                    ((23 - y) * boxsize) - ((WINDOW_HEIGHT - boxsize) / 2)
                };
                AddObstacle(it->second, basePos);
                if (type == 7) {
                    tube.push_back(tmp.size() - 1);
                }
            }
            position[y][x] = tmp.size() - 1;
        }
    }

    // 初始化資源管理器
    m_PRM = std::make_shared<PhaseResourceManger>();
    m_Root.AddChildren(m_PRM->GetChildren());
    m_Root.Update({zerox,0});
    m_CurrentState = State::UPDATE;
}
