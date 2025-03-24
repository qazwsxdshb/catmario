#include "PhaseResourceManger.hpp"
#include "Textt.hpp"

#include "Util/Logger.hpp"

PhaseResourceManger::PhaseResourceManger() {
    m_TaskText = std::make_shared<TaskText>();
    m_Background = std::make_shared<BackgroundImage>();
    m_Background->m_Transform.scale = glm::vec2(5.0f, 7.0f);
}

void PhaseResourceManger::NextPhase() {
    if (m_Phase == 3) return;
    LOG_DEBUG("Passed! Next phase: {}", m_Phase);
    m_Background->NextPhase(m_Phase);
    m_TaskText->NextPhase(m_Phase++);
}

void PhaseResourceManger::Select(int value) {
    m_Background->NextPhase(value);
    m_TaskText->NextPhase(value);
}

void PhaseResourceManger::BgZindex(int value) {
    m_Background->SetZIndex(value);
}