#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <string>

#include "Util/GameObject.hpp"

class Monster : public Util::GameObject {
public:

    explicit Monster(const std::string& ImagePath);

    Monster(const Monster&) = delete;

    Monster(Monster&&) = delete;

    Monster& operator=(const Monster&) = delete;

    Monster& operator=(Monster&&) = delete;

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }


    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    // TODO: Implement the collision detection
    [[nodiscard]] bool IfCollides(const std::shared_ptr<Monster>& other) const {
        (void) other;
        return false;
    }

    // TODO: Add and implement more methods and properties as needed to finish Giraffe Adventure.

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    std::string m_ImagePath;
};


#endif //MONSTER_HPP
