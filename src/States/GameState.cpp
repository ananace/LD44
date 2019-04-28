#include "GameState.hpp"
#include "../Util.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include <random>
#include <cstdio>

using Game::States::GameState;

enum
{
    kWorldSize = 6000
};

GameState::GameState()
{
    generateStarfields();

    startEncounter();
}

void GameState::handleEvent(const sf::Event& aEvent)
{
}
void GameState::update(float aDt)
{
    m_player.update(aDt);
    for (auto& enemy : m_enemies)
        enemy.update(aDt);

    auto hvsize = m_gameView.getSize() / 4.f;
    auto lsize = sf::Vector2f(kWorldSize, kWorldSize);
    sf::FloatRect viewLimit((kWorldSize / -2) + hvsize.x + 16, (kWorldSize / -2) + hvsize.y * 2 + 16, lsize.x - hvsize.x * 4 - 32, lsize.y - hvsize.y * 4 - 32);
    auto& playerPosition = m_player.getShip().getPosition();

    m_gameView.setCenter(constrain(viewLimit, playerPosition - sf::Vector2f(hvsize.x, 0)) + sf::Vector2f(m_gameView.getSize().x / 4.f, 0));
}

void GameState::preDraw(sf::RenderTarget& aTarget)
{
    aTarget.clear(sf::Color::Black);

    m_gameView.setSize(aTarget.getView().getSize());
    aTarget.setView(m_gameView);

    sf::RenderStates parallaxstate;
    aTarget.draw(m_starfield1, parallaxstate);
    parallaxstate.transform.translate(m_gameView.getCenter() / 4.f);
    aTarget.draw(m_starfield2, parallaxstate);
}
void GameState::draw(sf::RenderTarget& aTarget)
{
    aTarget.draw(m_player);
    for (auto& enemy : m_enemies)
        aTarget.draw(enemy);
}
void GameState::postDraw(sf::RenderTarget& aTarget)
{

}

void GameState::generateStarfields()
{
    std::random_device dev;
    std::uniform_real_distribution<float> size(kWorldSize / -2, kWorldSize / 2);

    m_starfield1.clear();
    m_starfield1.resize(2000);
    for (size_t i = 0; i < m_starfield1.getVertexCount(); ++i)
        m_starfield1[i] = sf::Vertex({ size(dev), size(dev) });

    m_starfield2.clear();
    m_starfield2.resize(1000);
    for (size_t i = 0; i < m_starfield2.getVertexCount(); ++i)
    m_starfield2[i] = sf::Vertex({ size(dev), size(dev) }, { 90, 90, 90 });
}

void GameState::startEncounter()
{
    std::random_device dev;
    std::uniform_real_distribution<float> position(kWorldSize / -2, kWorldSize / 2);
    std::uniform_int_distribution<int> encounter(0, 1);

    sf::Vector2f encounterPosition(position(dev), position(dev));
    // auto& encounterPosition = m_player.getShip().getPosition();
    sf::Vector2f targetPosition(position(dev), position(dev));

    switch (encounter(dev))
    {
    case 0:
        { // Single aggressive enemy, coming after the player
            printf("Game: Spawning encounter %i\n", 0);
            m_enemies.emplace_back(encounter(dev) + 1);
            auto& enemy = m_enemies.back();

            enemy.getShip().setPosition(encounterPosition);
            enemy.setTarget(&m_player.getShip());
            enemy.setFlag(EnemyFlags_Aggressive);
            enemy.setState(EnemyState_Attacking);
        }; break;

    case 1:
        { // Triple ship convoy
            printf("Game: Spawning encounter %i\n", 1);
            m_enemies.emplace_back(encounter(dev) + 1);
            auto& lead = m_enemies.back();

            auto& ship = lead.getShip();
            ship.setPosition(encounterPosition);
            ship.setRotation(getDirection(ship.getPosition(), targetPosition) * Rad2Deg());
            ship.setVelocity(ship.getMaxSpeed() * 0.5f);

            {
            m_enemies.emplace_back(encounter(dev) + 1);
            auto& enemy = m_enemies.back();

            enemy.getShip().setPosition(encounterPosition);
            enemy.setTarget(&lead.getShip());
            enemy.setState(EnemyState_Escorting);
            }

            {
            m_enemies.emplace_back(encounter(dev) + 1);
            auto& enemy = m_enemies.back();

            enemy.setFlag(EnemyFlags_Offset);
            enemy.getShip().setPosition(encounterPosition);
            enemy.setTarget(&lead.getShip());
            enemy.setState(EnemyState_Escorting);
            }
        }; break;

    default:
        printf("Game: TODO|Unfinished encounter\n");
        break;
    }
}
