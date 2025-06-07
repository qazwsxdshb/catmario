#include "App.hpp"
#include "Util/Logger.hpp"
#include "Util/Input.hpp"
#include "Util/BGM.hpp"



void App::Sec() {

    // 怪物
    AddMonster({
        "res/brock11.png", {-285, -315}, 48, {1.0f, 1.0f}, "box", {-9, 0},
        2, -1, 30, 32, 25
    });
    AddMonster({
        "res/brock14.png", {-285, -345}, 48, {1.0f, 1.0f}, "box", {-9, 0},
        2, -1, 30, 62, 25
    });
    AddMonster({"res/monster3.png", {-45.0f, -285.0f}, 51, {1.0f, 1.0f}, "", {0, -1}});
    AddMonster({"res/monster3.png", { 15.0f, -285.0f}, 51, {1.0f, 1.0f}, "", {0, -1}});

    AddMonster({
        "res/brock8.png", {195, -225}, 48, {1.0f, 1.0f}, "boxSpiked", {0, 0},
        2, -1, 30, 30, 30
    });

    AddMonster({"res/monster3.png", { 375.0f, -285.0f}, 51, {1.0f, 1.0f}, "", {0, -1}});

    AddMonster({
        "res/brock11.png", {375, -315}, 48, {1.0f, 1.0f}, "box", {-9, 0},
        2, -1, 30, 32, 25
    });
    AddMonster({
        "res/brock14.png", {370, -345}, 48, {1.0f, 1.0f}, "box", {-9, 0},
        2, -1, 30, 62, 25
    });

    AddMonster({
        "res/monster4.png", {515.0, -223.0f}, 51, {1.0f, 1.0f}, "tatle", {0, 1}
    });
    AddMonster({"res/monster3.png", { 735.0f, -285.0f}, 51, {1.0f, 1.0f}, "", {0, -1}});
    AddMonster({"res/monster3.png", { 765.0f, -285.0f}, 51, {1.0f, 1.0f}, "", {0, -1}});
    AddMonster({"res/monster3.png", { 795.0f, -285.0f}, 51, {1.0f, 1.0f}, "", {0, -1}});


    AddMonster({
        "res/monster7.png", { 975.0f, -330.0f}, 51, {1.0f, 1.0f}, "king", {15, -2},
        -1, 3, 31, 1024,90
    });

    AddMonster({
        "res/claude2.png", {1215.0f, 15.0f}, 51, {1.0f, 1.0f}, "claude", {0, 0}, -1, -1, 86
    });

    AddMonster({
        "res/catfront.png", { 1290.0f, -210.0f}, 51, {1.0f, 1.0f}, "king", {15, 0},
        -1, 3, 31, 1024,210,26,2,1
    });

    AddMonster({
        "res/brock11.png", {1635.0f ,15.0f}, 48, {1.0f, 1.0f}, "box", {-9, 0},
        2, -1, 30, 32, 25
    });

    AddMonster({
        "res/monster7.png", { 2175.0f, -165.0f}, 51, {1.0f, 1.0f}, "king2", {0, -1}
    });

    AddMonster({"res/greenball.png", {2535.0f, -225.0f}, 51, {1.0f, 1.0f}, "greenball", {0, 0}});

    AddMonster({
        "res/fireball.png", { 2725.0f, -163.0f}, 51, {1.0f, 1.0f}, "fireball", {20, -1},
        -1, 3, 31, 1024,210,26,1,2
    });

    AddMonster({
        "res/yellowbat2.png", {3025, 0.0f}, 51, {1.0f, 1.0f}, "state", {1, 0},
        -1, -1, 90, -1, -1, 20,1,2
    });

    AddMonster({
        "res/yellowbat2.png", {3025, -225.0f}, 51, {1.0f, 1.0f}, "state", {1, 0},
        -1, -1, 90, -1, -1, 20,1,2
    });

    AddMonster({
        "res/yellowbat2.png", {3175, 0.0f}, 51, {1.0f, 1.0f}, "state", {-1, 0},
        -1, -1, 90, 1024, 120, 20,1,2
    });

    AddMonster({
        "res/yellowbat2.png", {3175, -225.0f}, 51, {1.0f, 1.0f}, "state", {-1, 0},
        -1, -1, 90, 1024, 120, 20,1,2
    });


    for (int ii=0;ii<6;ii++) {
        AddMonster({
            "res/brock2.png", {3435.0f, -195-(30*ii)}, 48, {5.0f, 1.0f}, "box", {-10, 0},
            2, -1, 150, 150+(60*ii), 150
        });
    }

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
        {21,  {"res/brock5.png", 48, false}},

        {26, {"res/box.png", 49}},
        {27, {"res/flagpole.png", 48}},
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
