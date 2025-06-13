#ifndef PHASE_MANGER_HPP
#define PHASE_MANGER_HPP

#include "Util/GameObject.hpp"
#include "TaskText.hpp"
#include "BackgroundImage.hpp"

class PhaseResourceManger {
public:
    std::shared_ptr<TaskText> m_TaskText;

    PhaseResourceManger();

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
        // return {m_Background};
        return {m_TaskText, m_Background};
    }

    void NextPhase();

    void Select(int value);
    void BgZindex(int value);

private:
    std::shared_ptr<BackgroundImage> m_Background;

    int m_Phase = 1;
};


#endif //PHASE_MANGER_HPP
