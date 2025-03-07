#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"
#include "Character.hpp"
#include "Util/Text.hpp"
#include "PhaseResourceManger.hpp"
#include "AnimatedCharacter.hpp"

class App {
public:
    enum class State {
        ZERO,
        ZEROUPDATE,
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Zero();

    void ZeroUpdate();

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

private:
    enum class Phase {
        zero,
        start,
        grassland1,
        grassland2,
    };


    State m_CurrentState = State::ZERO;
    Phase m_Phase = Phase::zero;


    Util::Renderer m_Root;
    std::shared_ptr<Character> m_player;
    std::vector<std::shared_ptr<Character>> tmp;
//    std::vector<std::shared_ptr<Character>> m_Doors;
//    std::shared_ptr<AnimatedCharacter> m_Bee;
    std::shared_ptr<PhaseResourceManger> m_PRM;

    bool m_EnterDown = false;
};

#endif
