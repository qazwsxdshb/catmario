#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <string>

#include "Util/GameObject.hpp"

class Obstacle : public Util::GameObject {
public:
    int posup=0;

    explicit Obstacle(const std::string& ImagePath);

    Obstacle(const Obstacle&) = delete;

    Obstacle(Obstacle&&) = delete;

    Obstacle& operator=(const Obstacle&) = delete;

    Obstacle& operator=(Obstacle&&) = delete;

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }


    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    void ResetPosition() { m_Transform.translation = {0, 0}; }

private:

    std::string m_ImagePath;
};


#endif //OBSTACLE_HPP
