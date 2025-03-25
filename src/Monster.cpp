#include "Monster.hpp"
#include "Util/Image.hpp"


Monster::Monster(const std::string& ImagePath) {
    SetImage(ImagePath);
    ResetPosition();
}

void Monster::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;
    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}