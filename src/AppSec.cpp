#include "App.hpp"
#include "Util/Logger.hpp"
#include "Util/Input.hpp"
#include "Util/BGM.hpp"



void App::Sec() {
    playerstate= PlayerState::Normal;
    zerox=-110;
    checkpoint=0;
    tmp_monster=0;
    tmp.clear();
    tube.clear();
    reset.clear();
    m_monster.clear();
    m_Root.Clear();

    // 怪物
    // AddMonster({"res/monster3.png", {0.0f, -290.0f}, 51, {3.0f, 3.0f}, "", {0, -1}});

    AddMonster({
        "res/brock11.png", {-285, -315}, 48, {1.0f, 1.0f}, "box", {-10, 0},
        2, -1, 30, 60, 30
    });
    AddMonster({
        "res/brock14.png", {-285, -345}, 48, {1.0f, 1.0f}, "box", {-10, 0},
        2, -1, 30, 90, 30
    });
    AddMonster({
        "res/brock8.png", {195, -225}, 48, {1.0f, 1.0f}, "boxSpiked", {0, 0},
        2, -1, 30, 30, 30
    });
    //447.500000 -223.000000
    //751.500000 -307.000000
    //751.500000 -339.000000
    //
    m_player = std::make_shared<Character>(GA_RESOURCE_DIR"/res/player1.png");
    m_player->SetPosition({-112.5f, -280.0f});
    m_player->position={-112.5f, -280.0f};
    m_player->SetZIndex(48);
    m_Root.AddChild(m_player);


    // 障礙物類型映射
    std::unordered_map<int, ObstacleInfo> obstacleMap = {
        {1,  {"res/brock11.png", 49}},
        {2,  {"res/brock14.png", 49}},
        {3,  {"res/brock2.png", 49}},
        {4,  {"res/box.png", 50}},
        {5,  {"res/brock4.png", 49}},
        {6,  {"res/shorttube.png", -22, true, {-15.0f, 0.0f}, {0.8f, 1.0f}}},
        {7,  {"res/longtube.png", 48, true, {-15.0f, -2.0f}}},
        {8,  {"res/brock5.png", 48, false}},
        {9,  {"res/longtube_rotate90.png", 48, true, {-16.0f, -1.0f}}},
        {10, {"res/box.png", 48}},
        {11, {"res/brock1.png", 49}},
        {12, {"res/box.png", 49}},
        {13, {"res/castle.png", 30}},
        {14, {"res/brock8.png", 49}},
        {15, {"res/brock4.png", 48, false}},
        {16, {"res/flag.png", 49, true, {7.0f, 12.0f}}},
        {17, {"res/brock4.png", 48, false}},
        {18, {"res/brock10.png", 49}},
        {19, {"res/brock13.png", 49}},
        {20, {"res/claude.png",49,true,{0.0f, 0.0f},{1.1f, 1.0f}}},

        // {21, {"res/brock2.png", 49}},
        // {22, {"res/brock11.png", 49}},
        // {23, {"res/brock14.png", 49}},
        // {24, {"res/brock8.png", 49}},
        {25, {"res/brock5.png", 48,false}},
        {26, {"res/box.png", 49}},
        {27, {"res/flagpole.png", 48}},
        {28, {"res/button.png", 49}},
        {29, {"res/Tube.png", 49, true, {-14.0f, 14.0f}}},
        {30, {"res/claude3.png", 49, true, {0.0f, -15.0f}}},
        {31, {"res/flag_back.png", 49, true, {7.0f, 12.0f}}},
        {32, {"res/box.png", 49}},
        {33, {"res/longlongtube.png", 48, true, {-15.0f, -15.0f}}}
    };

    //copy
    for (int x = std::size(zerostart[0]) - 1; x >= 0; --x) {
        for (int y = std::size(zerostart) - 1; y >= 0; --y) {
            zerostart[y][x]=onestart[y][x];
        }
    }

    // 建立地圖障礙物
    for (int x = std::size(zerostart[0]) - 1; x >= 0; --x) {
        for (int y = std::size(zerostart) - 1; y >= 0; --y) {
            int type = zerostart[y][x];
            auto it = obstacleMap.find(type);
            if (it != obstacleMap.end()) {
                glm::vec2 basePos = {
                    // (x * boxsize) - ((WINDOW_WIDTH - boxsize) / 2),
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

    windows=8000;
    // 初始化資源管理器
    m_PRM = std::make_shared<PhaseResourceManger>();
    m_Root.AddChildren(m_PRM->GetChildren());
    m_Root.Update({zerox,0});
    m_CurrentState = State::UPDATE;
}
