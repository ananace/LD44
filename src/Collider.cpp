#include "Collider.hpp"
#include "Application.hpp"

Collider::~Collider()
{
    Application::getApplication().getCollisionManager().removeCollider(this);
}
