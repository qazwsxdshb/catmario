#include "Obstacle.hpp"
#include "Util/Image.hpp"


Obstacle::Obstacle(const std::string& ImagePath) {
    SetImage(ImagePath);
    ResetPosition();
}

void Obstacle::SetImage(const std::string& ImagePath) {
    m_ImagePath = ImagePath;
    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}