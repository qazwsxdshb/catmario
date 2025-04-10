#include "Character.hpp"
#include "Util/Image.hpp"


Character::Character(const std::string& ImagePath) {
    SetImage(ImagePath);
}

void Character::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;
    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}