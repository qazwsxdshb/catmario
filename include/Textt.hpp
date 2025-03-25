#ifndef TEXTT_HPP
#define TEXTT_HPP

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include "Util/Color.hpp"

class Textt : public Util::GameObject {
public:
    inline static std::string texte="test";

    Textt() : GameObject(std::make_unique<Util::Text>(GA_RESOURCE_DIR"/Font/Inkfree.ttf", 40,
    texte,Util::Color::FromName(Util::Colors::WHITE)),60) {}

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    void Settext(std::string value) {
        auto temp = std::dynamic_pointer_cast<Util::Text>(m_Drawable);
        temp->SetText(append_string_views(value));
    }

    inline static std::string append_string_views(std::string_view sv1) {
        return std::string(sv1);
    }


};


#endif //TEXTT_HPP
