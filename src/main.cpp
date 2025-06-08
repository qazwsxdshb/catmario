#include "App.hpp"

#include "Core/Context.hpp"

int main(int, char**) {
    auto context = Core::Context::GetInstance();
    App app;

    while (!context->GetExit()) {
        switch (app.GetCurrentState()) {
            case App::State::ZERO:
                app.Zero();
            break;

            case App::State::ZEROUPDATE:
                app.ZeroUpdate();
                break;

            case App::State::START:
                app.Start();
                break;

            case App::State::UPDATE:
                app.Update();
                break;

            case App::State::DIE:
                app.Die();
                break;

            case App::State::UPDATE2:
                app.ResetLevel();
                app.level++;
                if (app.level==2) {
                    app.ChangeMap(app.onestart);
                    printf("cccc %d",app.level);
                    app.Start();
                }
                else if(app.level==3){
                    app.ChangeMap(app.twostart);
                    app.Sec();
                }
                else if(app.level==4) {
                    app.ChangeMap(app.twoend);
                    app.Start();
                }
                else if(app.level==5) {
                    app.ChangeMap(app.threestart);
                    app.Tre();
                }
                break;

            case App::State::END:
                app.End();
                context->SetExit(true);
                break;
        }
        context->Update();
    }
    return 0;
}
