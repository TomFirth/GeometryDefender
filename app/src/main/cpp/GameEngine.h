#ifndef GEOMETRY_DEFENDER_GAME_ENGINE_H
#define GEOMETRY_DEFENDER_GAME_ENGINE_H

#include <vector>
#include <string>
#include <memory>

enum ShapeType {
    SHAPE_NONE = 0,
    SHAPE_SQUARE = 1,
    SHAPE_CIRCLE = 2,
    SHAPE_TRIANGLE = 3
};

struct Vector2D {
    float x, y;
};

struct PathNode {
    float x, y;
};

struct EnemyDot {
    int id;
    float x, y;
    float maxHealth;
    float health;
    float speed;
    int pathIndex;
    float pathProgress; // 0.0 to 1.0 between current and next node
    bool active;
};

struct Tower {
    int gridX, gridY;
    std::vector<ShapeType> shapes; // stacked shapes (up to 3)
    int level; // 1 to 10
    float range;
    float fireRate;
    float fireCooldown;
    float damage;
    float rotation;
    int targetEnemyId;
};

struct Projectile {
    float x, y;
    float targetX, targetY;
    float speed;
    float damage;
    int targetEnemyId;
    bool active;
};

class GameEngine {
public:
    GameEngine(int screenWidth, int screenHeight);
    ~GameEngine();

    void update(float deltaTime);
    void handleTouch(float x, float y, bool down);

    // Getters for rendering
    int getBaseHealth() const { return baseHealth_; }
    int getGold() const { return gold_; }
    int getWave() const { return wave_; }
    bool isGameOver() const { return gameOver_; }

    const std::vector<PathNode>& getPath() const { return path_; }
    const std::vector<EnemyDot>& getEnemies() const { return enemies_; }
    const std::vector<Tower>& getTowers() const { return towers_; }
    const std::vector<Projectile>& getProjectiles() const { return projectiles_; }

    void startNextWave();
    void resetGame();

private:
    int screenWidth_;
    int screenHeight_;

    int baseHealth_;
    int gold_;
    int wave_;
    bool gameOver_;
    bool waveInProgress_;

    std::vector<PathNode> path_;
    std::vector<EnemyDot> enemies_;
    std::vector<Tower> towers_;
    std::vector<Projectile> projectiles_;

    float waveSpawnTimer_;
    int enemiesToSpawn_;
    float spawnInterval_;
    int nextEnemyId_;

    void generatePath();
    void spawnEnemy();
    void updateTowers(float deltaTime);
    void updateProjectiles(float deltaTime);
    void updateEnemies(float deltaTime);
};

#endif // GEOMETRY_DEFENDER_GAME_ENGINE_H
