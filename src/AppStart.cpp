#include "App.hpp"
#include "Util/Logger.hpp"
#include "Util/Input.hpp"
#include "Util/BGM.hpp"

// test
void App::AddObstacle(const ObstacleInfo& info, glm::vec2 basePos) {
    auto obstacle = std::make_shared<Obstacle>(GA_RESOURCE_DIR "/" + info.path);
    obstacle->SetPosition(basePos + info.offset);
    obstacle->SetZIndex(info.zIndex);
    obstacle->SetVisible(info.visible);
    obstacle->m_Transform.scale = info.scale;
    m_Root.AddChild(obstacle);
    tmp.push_back(obstacle);
}

void App::Start() {
    // Util::BGM bgm(GA_RESOURCE_DIR"/sound/field.mp3");
    // bgm.Play(-1);
    // LOG_TRACE("Start");

    // 初始化怪物
    auto monster = std::make_shared<Monster>(GA_RESOURCE_DIR"/res/monster3.png");
    monster->SetPosition({-112.5f, 0.0f});
    monster->SetZIndex(51);
    monster->SetOrigin({100, -280});
    m_Root.AddChild(monster);
    m_monster.push_back(monster);
    monsterAcceleration.push_back({0, 1});

    // box
    monster = std::make_shared<Monster>(GA_RESOURCE_DIR"/res/brock1.png");
    monster->name="box";
    monster->SetPosition({1700-574.5,-75});
    monster->SetZIndex(51);
    monster->SetOrigin({1700-574.5,-75});
    m_Root.AddChild(monster);
    m_monster.push_back(monster);
    monsterAcceleration.push_back({-10, 0});

    monster = std::make_shared<Monster>(GA_RESOURCE_DIR"/res/brock1.png");
    monster->name="box";
    monster->SetPosition({1700-574.5+30,-75});
    monster->SetZIndex(51);
    monster->SetOrigin({1700-574.5+30,-75});
    m_Root.AddChild(monster);
    m_monster.push_back(monster);
    monsterAcceleration.push_back({-10, 0});

    monster = std::make_shared<Monster>(GA_RESOURCE_DIR"/res/brock1.png");
    monster->name="box";
    monster->SetPosition({1700-574.5+60,-75});
    monster->SetZIndex(51);
    monster->SetOrigin({1700-574.5+60,-75});
    m_Root.AddChild(monster);
    m_monster.push_back(monster);
    monsterAcceleration.push_back({-10, 0});


    //fish
    monster = std::make_shared<Monster>(GA_RESOURCE_DIR"/res/monster6.png");
    monster->name="fish";
    monster->SetPosition({-112.5f, 0.0f});
    monster->SetZIndex(51);
    monster->SetOrigin({100, -280});
    m_Root.AddChild(monster);
    m_monster.push_back(monster);
    monsterAcceleration.push_back({10, 0});

    //fish
    monster = std::make_shared<Monster>(GA_RESOURCE_DIR"/res/monster6.png");
    monster->name="fish";
    monster->m_Transform.scale = glm::vec2(1.0f, -1.0f);
    monster->SetPosition({-112.5f+1611, 0.0f});
    monster->SetZIndex(51);
    monster->SetOrigin({100+1611, -280});
    m_Root.AddChild(monster);
    m_monster.push_back(monster);
    monsterAcceleration.push_back({-10, 0});

    // fish
    monster = std::make_shared<Monster>(GA_RESOURCE_DIR"/res/monster3.png");
    monster->SetPosition({-112.5f+1611, 0.0f});
    monster->SetZIndex(51);
    monster->SetOrigin({100+1611, -280});
    m_Root.AddChild(monster);
    m_monster.push_back(monster);
    monsterAcceleration.push_back({0, 1});

    // fish
    monster = std::make_shared<Monster>(GA_RESOURCE_DIR"/res/yellowbat.png");
    monster->SetPosition({-112.5f+1611, 0.0f});
    monster->SetZIndex(51);
    monster->SetOrigin({100+1611, -280});
    m_Root.AddChild(monster);
    m_monster.push_back(monster);
    monsterAcceleration.push_back({0, -1});


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
        {14, {"res/brock7.png", 49}},
        {15, {"res/brock4.png", 48, false}},
        {16, {"res/flag.png", 49, true, {7.0f, 12.0f}}},
        {17, {"res/brock4.png", 48, false}},
        {18, {"res/brock10.png", 49}},
        {19, {"res/brock13.png", 49}},
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

    m_CurrentState = State::UPDATE;
}

// test

//
//
// void App::Start() {
//
//     // Util::BGM bgm(GA_RESOURCE_DIR"/sound/field.mp3");
//     // bgm.Play(-1);
//     // LOG_TRACE("Start");
//
//     m_monster.push_back(std::make_shared<Monster>(GA_RESOURCE_DIR"/res/monster3.png"));
//     m_monster[m_monster.size()-1]->SetPosition({-112.5f, 0.0f});
//     m_monster[m_monster.size()-1]->SetZIndex(51);
//     m_monster[m_monster.size()-1]->SetOrigin({100,-280});
//     m_Root.AddChild(m_monster[m_monster.size()-1]);
//
//     monsterAcceleration.push_back({0,1});
//
//     for (int x=std::size(zerostart[0]); x>=0; x--) {
//         for (int y=std::size(zerostart); y>=0; y--) {
//             if(zerostart[y][x] == 1) {
//                 tmp.push_back(std::make_shared<Obstacle>(GA_RESOURCE_DIR"/res/brock10.png"));
//                 tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
//                 tmp[tmp.size()-1]->SetZIndex(49);
//                 m_Root.AddChild(tmp[tmp.size()-1]);
//             }
//             else if(zerostart[y][x] == 2) {
//                 tmp.push_back(std::make_shared<Obstacle>(GA_RESOURCE_DIR"/res/brock13.png"));
//                 tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
//                 tmp[tmp.size()-1]->SetZIndex(49);
//                 m_Root.AddChild(tmp[tmp.size()-1]);
//             }
//             else if(zerostart[y][x] == 3) {
//                 tmp.push_back(std::make_shared<Obstacle>(GA_RESOURCE_DIR"/res/brock1.png"));
//                 tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
//                 tmp[tmp.size()-1]->SetZIndex(49);
//                 m_Root.AddChild(tmp[tmp.size()-1]);
//             }
//             else if(zerostart[y][x] == 4) {
//                 tmp.push_back(std::make_shared<Obstacle>(GA_RESOURCE_DIR"/res/box.png"));
//                 tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
//                 tmp[tmp.size()-1]->SetZIndex(50);
//                 m_Root.AddChild(tmp[tmp.size()-1]);
//             }//饅頭
//             else if(zerostart[y][x] == 5) {
//                 tmp.push_back(std::make_shared<Obstacle>(GA_RESOURCE_DIR"/res/brock4.png"));
//                 tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
//                 tmp[tmp.size()-1]->SetZIndex(49);
//                 m_Root.AddChild(tmp[tmp.size()-1]);
//             }
//             else if(zerostart[y][x] == 6) {
//                 tmp.push_back(std::make_shared<Obstacle>(GA_RESOURCE_DIR"/res/shorttube.png"));
//                 tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2) - 15, ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
//                 tmp[tmp.size()-1]->SetZIndex(-22);
//                 tmp[tmp.size()-1]->m_Transform.scale = glm::vec2(0.8f, 1.0f);
//                 m_Root.AddChild(tmp[tmp.size()-1]);
//             }
//             else if(zerostart[y][x] == 7) {
//                 tmp.push_back(std::make_shared<Obstacle>(GA_RESOURCE_DIR"/res/longtube.png"));
//                 tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2) - 15, ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2) - 2});
//                 tmp[tmp.size()-1]->SetZIndex(48);
//                 tube.push_back((tmp.size()-1));
//                 m_Root.AddChild(tmp[tmp.size()-1]);
//             }
//             else if(zerostart[y][x] == 8) {
//                 tmp.push_back(std::make_shared<Obstacle>(GA_RESOURCE_DIR"/res/brock4.png"));
//                 tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
//                 tmp[tmp.size()-1]->SetZIndex(48);
//                 tmp[tmp.size()-1]->SetVisible(0);
//                 m_Root.AddChild(tmp[tmp.size()-1]);
//             }
//             else if(zerostart[y][x] == 9) {
//                 tmp.push_back(std::make_shared<Obstacle>(GA_RESOURCE_DIR"/res/longtube_rotate90.png"));
//                 tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2) - 16, ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2) - 1});
//                 tmp[tmp.size()-1]->SetZIndex(48);
//                 m_Root.AddChild(tmp[tmp.size()-1]);
//             }
//             else if(zerostart[y][x] == 10) {
//                 tmp.push_back(std::make_shared<Obstacle>(GA_RESOURCE_DIR"/res/box.png"));
//                 tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
//                 tmp[tmp.size()-1]->SetZIndex(48);
//                 m_Root.AddChild(tmp[tmp.size()-1]);
//             }//會移動
//             else if(zerostart[y][x] == 11) {
//                 tmp.push_back(std::make_shared<Obstacle>(GA_RESOURCE_DIR"/res/brock1.png"));
//                 tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
//                 tmp[tmp.size()-1]->SetZIndex(49);
//                 m_Root.AddChild(tmp[tmp.size()-1]);
//             }//星星
//             else if(zerostart[y][x] == 12) {
//                 tmp.push_back(std::make_shared<Obstacle>(GA_RESOURCE_DIR"/res/box.png"));
//                 tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
//                 tmp[tmp.size()-1]->SetZIndex(49);
//                 m_Root.AddChild(tmp[tmp.size()-1]);
//             }//金幣
//             else if(zerostart[y][x] == 14) {
//                 tmp.push_back(std::make_shared<Obstacle>(GA_RESOURCE_DIR"/res/brock7.png"));
//                 tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
//                 tmp[tmp.size()-1]->SetZIndex(49);
//                 m_Root.AddChild(tmp[tmp.size()-1]);
//             }
//             else if(zerostart[y][x] == 15) {
//                 tmp.push_back(std::make_shared<Obstacle>(GA_RESOURCE_DIR"/res/brock4.png"));
//                 tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
//                 tmp[tmp.size()-1]->SetZIndex(48);
//                 tmp[tmp.size()-1]->SetVisible(0);
//                 m_Root.AddChild(tmp[tmp.size()-1]);
//             }//ㄅㄥ金幣
//             else if(zerostart[y][x] == 16) {
//                 tmp.push_back(std::make_shared<Obstacle>(GA_RESOURCE_DIR"/res/flag.png"));
//                 tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2) + 7, ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2) + 12});
//                 tmp[tmp.size()-1]->SetZIndex(49);
//                 m_Root.AddChild(tmp[tmp.size()-1]);
//             }
//             else if(zerostart[y][x] == 17) {
//                 tmp.push_back(std::make_shared<Obstacle>(GA_RESOURCE_DIR"/res/brock4.png"));
//                 tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
//                 tmp[tmp.size()-1]->SetZIndex(48);
//                 tmp[tmp.size()-1]->SetVisible(0);
//                 m_Root.AddChild(tmp[tmp.size()-1]);
//             }
//             else if(zerostart[y][x] == 18) {
//                 tmp.push_back(std::make_shared<Obstacle>(GA_RESOURCE_DIR"/res/brock10.png"));
//                 tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
//                 tmp[tmp.size()-1]->SetZIndex(49);
//                 m_Root.AddChild(tmp[tmp.size()-1]);
//             }
//             else if(zerostart[y][x] == 19) {
//                 tmp.push_back(std::make_shared<Obstacle>(GA_RESOURCE_DIR"/res/brock13.png"));
//                 tmp[tmp.size()-1]->SetPosition({(x*boxsize)-((WINDOW_WIDTH-boxsize)/2), ((23-y)*boxsize)-((WINDOW_HEIGHT-boxsize)/2)});
//                 tmp[tmp.size()-1]->SetZIndex(49);
//                 m_Root.AddChild(tmp[tmp.size()-1]);
//             }
//
//
//
//             position[y][x]=tmp.size()-1;
//
//         }
//     }
//
//     m_PRM = std::make_shared<PhaseResourceManger>();
//     m_Root.AddChildren(m_PRM->GetChildren());
//
//     m_CurrentState = State::UPDATE;
// }