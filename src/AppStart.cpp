#include "App.hpp"
#include "Util/Logger.hpp"
#include "Util/Input.hpp"
#include "Util/BGM.hpp"

void App::Start() {
    // Util::BGM bgm(GA_RESOURCE_DIR"/sound/field.mp3");
    // bgm.Play(-1);
    // LOG_TRACE("Start");


    if (level==1) {
        // 怪物
        AddMonster({"res/monster3.png", {100.0f, -290.0f}, 51, {1.0f, 1.0f}, "", {0, -1}});

        //
        AddMonster({
            "res/brock1.png", {1700 - 574.5f + 30, -75}, 48, {3.0f, 1.0f}, "dropbox", {-10, 0},
            -1, -1, 90, 1024, 90
        });
        //

        AddMonster({
            "res/brock10.png", {2390 - 574.5f + 60, -315}, 48, {5.0f, 1.0f}, "box", {-10, 0},
            2, -1, 150, 90, 120
        });

        AddMonster({
            "res/brock13.png", {2390 - 574.5f + 60, -345}, 48, {5.0f, 1.0f}, "box", {-10, 0},
            2, -1, 150, 150, 120
        });

        AddMonster({
            "res/monster6.png", {269.0f, -280.0f}, 0, {1.0f, 1.0f}, "fish", {10, 0}
        });

        AddMonster({
            "res/monster6.png", {1335.0f, 380.0f}, 0, {1.0f, -1.0f}, "fish", {-15, 0},
            -1, -1, -1, 1900
        });

        AddMonster({
            "res/monster4.png", {-112.5f + 1700, -280.0f}, 51, {1.0f, 1.0f}, "tatle", {0, 1}
        });

        AddMonster({
            "res/monster3.png", {-112.5f + 1600, -280.0f}, 51, {1.0f, 1.0f}, "", {0, 1}
        });

        AddMonster({
            "res/monster3.png", {-112.5f + 1800, -280.0f}, 51, {1.0f, 1.0f}, "", {0, 1}
        });

        AddMonster({
            "res/claude.png", {2780.0f, -60.0f}, 51, {1.0f, 1.0f}, "claude", {0, 0}, -1, -1, 86
        });

        for (int i = 0; i < 4; ++i) {
            AddMonster({
                "res/monster3.png", {3013 + i * 30, 375.0f}, 51, {1.0f, 1.0f}, "motopro", {0, 0},
                -1, 3, 31, 1024, i * 2 * 30
            });
        }

        AddMonster({
            "res/yellowbat.png", {2780 + 720, 60.0f}, 51, {1.0f, 1.0f}, "yellowbat", {0, -15},
            -1, -1, 35, 80, 650, 20, -1,-1,false
        });

        AddMonster({
            "res/monster6.png", {3590-120, 380.0f}, 0, {1.0f, -1.0f}, "fish", {-20, 0},
            -1, -1, -1, 1900
        });
    }
    else if (level==2) {
        AddMonster({
            "res/monster6.png", {90.0f, -280.0f}, 0, {1.0f, 1.0f}, "fish", {10, 0}
        });
    }

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
        {16, {"res/flag.png", 49, true, {7.0f, 12.0f}}},
        {17, {"res/brock4.png", 48, false}},
        {18, {"res/brock10.png", 49}},
        {19, {"res/brock13.png", 49}},
        {20, {"res/claude.png",49,true,{0.0f, 0.0f},{1.1f, 1.0f}}},
        {21, {"res/brock2.png", 49}},
        {22, {"res/brock11.png", 49,false}},
        {23, {"res/brock14.png", 49}},
        {24, {"res/brock8.png", 49}},
        {25, {"res/brock5.png", 48}},
        {26, {"res/box.png", 49}},
        {27, {"res/flagpole.png", 49}},
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
        {39, {"res/box.png", 49}}
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
                    tube.push_back(tmp.size()-1);
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
