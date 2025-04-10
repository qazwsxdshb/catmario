#ifndef COIN_HPP
#define COIN_HPP

#include <string>

#include "Util/GameObject.hpp"

class Coin : public Util::GameObject {
public:
    int time=0;
    explicit Coin(const std::string& ImagePath);

    Coin(const Coin&) = delete;

    Coin(Coin&&) = delete;

    Coin& operator=(const Coin&) = delete;

    Coin& operator=(Coin&&) = delete;

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }


    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

private:
    std::string m_ImagePath;
};


#endif //COIN_HPP
