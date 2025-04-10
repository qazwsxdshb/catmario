#include "Coin.hpp"
#include "Util/Image.hpp"


Coin::Coin(const std::string& ImagePath) {
    SetImage(ImagePath);
}

void Coin::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;
    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}