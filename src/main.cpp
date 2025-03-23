#include "ECS.h"

int main()
{
    static snx::ECS ecs{};
    auto hero = ecs.createEntity();
    ecs.assignComponent<int>(hero, 1);
    return 0;
}