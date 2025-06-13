#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "Textt.hpp"
#include "Util/Renderer.hpp"
#include "Character.hpp"
#include "Monster.hpp"
#include "Coin.hpp"
#include "Obstacle.hpp"
#include "PhaseResourceManger.hpp"
#include "Util/BGM.hpp"
#include "Util/SFX.hpp"
#include <vector>

class App {
public:
    float Acceleration = 1;

    enum class State {
        ZERO,
        ZEROUPDATE,
        START,
        DIE,
        UPDATE,
        UPDATE2,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Zero();
    void ZeroUpdate();
    void Start();
    int playerwidth = 20;

    struct ObstacleInfo {
        std::string path;
        int zIndex;
        bool visible = true;
        glm::vec2 offset = {0.0f, 0.0f};
        glm::vec2 scale = {1.0f, 1.0f};
    };
    void AddObstacle(const ObstacleInfo& info, glm::vec2 basePos);

    void Update();
    void Update2();
    void Sec();
    void Tre();
    void UpdateTimers();
    void HandleGlobalInput();

    void ChangeMap(int ttmp[24][200]);
    void ResetLevel();
    void ResetAll();

    void Monsteract(glm::vec2 monsterpos, int value, glm::vec2 playerpos, std::vector<std::shared_ptr<Monster>> mon);

    bool Collision(int Ax, int Ay, int Awidth, int Aheight, int Bx, int By, int Bwidth, int Bheight);
    bool RLCollision(int xx, int yy, glm::vec2 playerpos, int rl, int height, int weight);
    bool UDCollision(int xx, int yy, glm::vec2 playerpos, int ud, int speedd, int height, int weight);

    void Die();
    void End();

private:
    void ValidTask();

    enum class Phase {
        zero,
        start,
        grassland1,
        grassland2,
    };

    enum class PlayerState {
        Normal = 0,
        OP = 1,
        Die = 3,
        Falling = 4,
        FinalForm = 5,
    };

public:
    PlayerState playerstate = PlayerState::Normal;
    int sec = 0;
    int opsec = 0;
    int life = 2;
    int zerox = 0;
    int zeroy = 0;
    int rlsec = 0;
    int checkpoint = 0;
    int speed = 4;
    int boxsize = 30;
    int playerheight = 34;
    int WINDOW_WIDTH = 720;
    int WINDOW_HEIGHT = 720;
    int windows[6] = {0, 7300, 0, 8130, 1200, 8130};
    int level = 1;
    int fireball = -1;
    int dropdrop = -1;
    int dietime = 0;
    int texttime = -1;
    int texttttt = 0;

    Util::BGM bgm;
    Util::SFX SFX;
    glm::vec2 ofsetzero = {0, 0};

    State m_CurrentState = State::ZERO;
    Phase m_Phase = Phase::zero;

    std::shared_ptr<Textt> text;
    Util::Renderer m_Root;
    std::shared_ptr<Character> m_player;

    std::vector<std::shared_ptr<Obstacle>> tmp;
    std::vector<std::vector<int>> reset;
    std::vector<int> tube;

    const std::shared_ptr<Util::GameObject> tmptext;
    std::shared_ptr<PhaseResourceManger> m_PRM;

    std::vector<std::shared_ptr<Monster>> m_monster;
    std::vector<std::shared_ptr<Coin>> m_coin;
    int tmp_monster = 0;

    struct MonsterInfo {
        std::string path;
        glm::vec2 pos;
        int zIndex;
        glm::vec2 scale = {1.0f, 1.0f};
        std::string name = "";
        glm::ivec2 acceleration = {0, 0};
        int type = -1;
        int act = -1;
        int mon_wei = -1;
        int mon_traget = -1;
        int mon_tragetrl = -1;
        int mon_hei = -1;
        int mon_mul = -1; // 修正：使用 mon_mul 而非 mon_ml
        int life = 0;
        bool visible = true;
    };
    void AddMonster(const MonsterInfo& info);

    bool m_EnterDown = false;

    int position[24][200] = {};

    // 地圖陣列聲明（無硬編碼初始化）
    int zerostart[24][200];
    int onestart[24][200];
    int twostart[24][200];
    int twoend[24][200];
    int threestart[24][200];

    // 從 CSV 讀取地圖的函數
    bool LoadMapFromCSV(const std::string& filename, int map[24][200]);

    // 初始化所有地圖
    void LoadAllMaps();
};

#endif