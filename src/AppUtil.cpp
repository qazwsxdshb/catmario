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
        case Phase::start:
            if (m_Giraffe->GetImagePath() == GA_RESOURCE_DIR"/Image/Character/giraffe.png") {
                m_Phase = Phase::ABLE_TO_MOVE;
                m_Giraffe->SetPosition({-112.5f, -140.5f});

                m_PRM->NextPhase();
            } else {
                LOG_DEBUG("The image is not correct");
                LOG_DEBUG("The image path is {} instead.", m_Giraffe->GetImagePath());
            }
            break;

        case Phase::ABLE_TO_MOVE:
            if (isInsideTheSquare(*m_Giraffe)) {
                m_Phase = Phase::COLLIDE_DETECTION;
                m_Giraffe->SetPosition({-112.5f, -140.5f});
                m_Chest->SetVisible(true);

                m_PRM->NextPhase();
            } else {
                LOG_DEBUG("The giraffe is not inside the square");
            }
            break;

        case Phase::COUNTDOWN:
            if (m_Ball->IfAnimationEnds()) {
                LOG_DEBUG("Congratulations! You have completed Giraffe Adventure!");
                m_CurrentState = State::END;
            } else{
                LOG_DEBUG("The ball animation is not ended");
            }
            break;
    }
}
