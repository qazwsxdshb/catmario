#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <string>
#include <App.hpp>
#include <CollisionUtil.hpp>
#include "Util/GameObject.hpp"

class Monster : public Util::GameObject , public App ,public CollisionUtil{
public:
    std::string name="bun";
    glm::vec2 acceleration={0,0};
    glm::vec2 oriacceleration={0,0};
    int talk=0;
    int time=0;
    int act=0;
    int move=0;
    int type=1;
    int mon_hei=26;
    int mon_tragetrl=30;
    int mon_traget=1024;
    int mon_wei=24;
    explicit Monster(const std::string& ImagePath);

    Monster(const Monster&) = delete;

    Monster(Monster&&) = delete;

    Monster& operator=(const Monster&) = delete;

    Monster& operator=(Monster&&) = delete;

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    // void SetName(std::string name){ name = name; }

    std::string GetName() const { return name; }


    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    void SetOrigin(const glm::vec2& Position) {pos=Position;}

    void Reset(int zerox);
    void Update(glm::vec2 monsterpos,int value,glm::vec2 playerpos,std::vector<std::shared_ptr<Monster>> mon);

private:
    glm::vec2 pos={0,0};
    std::string m_ImagePath;
};


#endif //MONSTER_HPP
