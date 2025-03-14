//
// Created by 何益森 on 2025/3/14.
//

#ifndef TEXTT_H
#define TEXTT_H

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include "Util/Color.hpp"

class Textt : public Util::GameObject {
public:
    std::string texte="aaaa";

    Textt() : GameObject(
            std::make_unique<Util::Text>(GA_RESOURCE_DIR"/Font/Inkfree.ttf", 40,
                                         append_string_views("aaa",""),
                                         Util::Color::FromName(Util::Colors::WHITE)),
                                         100) {
            m_Transform.translation = {0, 0};
    }
private:
    inline static std::string append_string_views(std::string_view sv1, std::string_view sv2) {
        return std::string(sv1) + "\n" + std::string(sv2);
    }
};

#endif //TEXTT_H
