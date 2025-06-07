#include "AppUtil.hpp"
#include "App.hpp"

#include "Util/Logger.hpp"

void App::ValidTask() {
    LOG_DEBUG("Validating the task {}", static_cast<int>(m_Phase));
    switch (m_Phase) {
        case Phase::zero:
            if (Phase::zero == m_Phase) {
                m_Phase=Phase::start;
                m_player->SetPosition({-112.5f, -140.5f});
            } else {
                LOG_DEBUG("The image is not correct");
            }
        break;

        case Phase::start:
            if (Phase::start == m_Phase) {
                m_Phase=Phase::grassland1;
                m_player->SetPosition({-112.5f, -140.5f});
                m_PRM->NextPhase();
            } else {
                LOG_DEBUG("The image is not correct");
            }
            break;

        // case Phase::grassland1:
        //     if (isInsideTheSquare(*m_Giraffe)) {
        //         m_Phase = Phase::COLLIDE_DETECTION;
        //         m_Giraffe->SetPosition({-112.5f, -140.5f});
        //         m_Chest->SetVisible(true);
        //
        //         m_PRM->NextPhase();
        //     } else {
        //         LOG_DEBUG("The giraffe is not inside the square");
        //     }
        //     break;
    }
}


void App::AddObstacle(const ObstacleInfo& info, glm::vec2 basePos) {
    auto obstacle = std::make_shared<Obstacle>(GA_RESOURCE_DIR "/" + info.path);
    obstacle->SetPosition(basePos + info.offset);
    obstacle->SetZIndex(info.zIndex);
    obstacle->SetVisible(info.visible);
    obstacle->m_Transform.scale = info.scale;
    m_Root.AddChild(obstacle);
    tmp.push_back(obstacle);
}

void App::AddMonster(const MonsterInfo& info) {
    auto monster = std::make_shared<Monster>(GA_RESOURCE_DIR "/" + info.path);
    monster->SetPosition(info.pos);
    monster->SetOrigin(info.pos);
    monster->SetZIndex(info.zIndex);
    monster->m_Transform.scale = info.scale;
    monster->SetVisible(info.visible);
    if (!info.name.empty()) monster->name = info.name;
    if (info.type != -1) monster->type = info.type;
    if (info.act != -1) monster->act = info.act;
    if (info.mon_wei != -1) monster->mon_wei = info.mon_wei;
    if (info.mon_traget != -1) monster->mon_traget = info.mon_traget;
    if (info.mon_tragetrl != -1) monster->mon_tragetrl = info.mon_tragetrl;
    if (info.mon_hei != -1) monster->mon_hei = info.mon_hei;
    if (info.mon_mul != -1) monster->mon_mul = info.mon_mul;
    if (info.life != -1) monster->life = info.life;

    m_Root.AddChild(monster);
    m_monster.push_back(monster);
    monster->acceleration=info.acceleration;
    monster->oriacceleration=info.acceleration;
}

void App::ChangeMap(int ttmp[24][200]) {
    //copy
    for (int x = std::size(zerostart[0]) - 1; x >= 0; --x) {
        for (int y = std::size(zerostart) - 1; y >= 0; --y) {
            zerostart[y][x]=ttmp[y][x];
        }
    }
}

void App::ResetLevel() {
    playerstate= PlayerState::Normal;
    zerox=-110;
    checkpoint=-110;
    tmp_monster=0;
    tmp.clear();
    tube.clear();
    reset.clear();
    m_monster.clear();
    m_Root.Clear();

    m_player = std::make_shared<Character>(GA_RESOURCE_DIR"/res/player1.png");
    m_player->SetPosition({-285.0f, 60.0f});
    m_player->position={-175.0f, 60.0f};
    m_player->SetZIndex(48);
    m_Root.AddChild(m_player);

    text = std::make_shared<Textt>();
    text->SetPosition({0, 0});
    text->SetZIndex(70);
    text->Settext(" ");
    m_Root.AddChild(text);
}