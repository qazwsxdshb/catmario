#include "AppUtil.hpp"
#include "App.hpp"

#include "Util/Logger.hpp"

/**
 * @brief The function to validate the tasks.
 * @warning Do not modify this function.
 * @note See README.md for the task details.
 */
void App::ValidTask() {
    bool isBeeLooping;
    bool isBeePlaying;
    LOG_DEBUG("Validating the task {}", static_cast<int>(m_Phase));
    switch (m_Phase) {
        case Phase::zero:
            if (Phase::zero == m_Phase) {
                m_Phase=Phase::start;
                m_player->SetPosition({-112.5f, -140.5f});
                // m_PRM->NextPhase();
            } else {
                LOG_DEBUG("The image is not correct");
            }
        break;

        case Phase::start:
            if (Phase::start == m_Phase) {
                m_Phase=Phase::grassland1;

                m_player->SetPosition({-112.5f, -140.5f});
                m_PRM->NextPhase();
            } else {
                LOG_DEBUG("The image is not correct");
            }
            break;

        // case Phase::grassland1:
        //     if (isInsideTheSquare(*m_Giraffe)) {
        //         m_Phase = Phase::COLLIDE_DETECTION;
        //         m_Giraffe->SetPosition({-112.5f, -140.5f});
        //         m_Chest->SetVisible(true);
        //
        //         m_PRM->NextPhase();
        //     } else {
        //         LOG_DEBUG("The giraffe is not inside the square");
        //     }
        //     break;
    }
}
