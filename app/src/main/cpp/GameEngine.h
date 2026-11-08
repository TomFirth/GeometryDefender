#ifndef GEOMETRY_DEFENDER_GAME_ENGINE_H
#define GEOMETRY_DEFENDER_GAME_ENGINE_H

#include <vector>
#include <string>
#include <memory>
#include "ObjectPool.h"

enum ShapeType {
    SHAPE_NONE = 0,
    SHAPE_SQUARE = 1,
    SHAPE_CIRCLE = 2,
    SHAPE_TRIANGLE = 3
};

enum TerrainType {
    TERRAIN_UPPER_GREEN = 1,
    TERRAIN_LOWER_BROWN = 2
};

enum GamePhase {
    PHASE_BUILDING = 1,
    PHASE_COMBAT = 2
};

enum GameState {
    STATE_MENU = 1,
    STATE_PLAYING = 2,
    STATE_SETTINGS = 3,
    STATE_GAMEOVER = 4
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
    float pathProgress;
    bool active;
};

struct Tower {
    int gridX, gridY;
    TerrainType terrainType;
    std::vector<ShapeType> shapes;
    int level;
    float range;
    float fireRate;
    float fireCooldown;
    float damage;
    float hp;
    float maxHp;
    float rotation;
    int targetEnemyId;
    int totalCost;
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

    // Getters
    int getBaseHealth() const { return baseHealth_; }
    int getGold() const { return gold_; }
    int getLives() const { return lives_; }
    int getWave() const { return wave_; }
    int getScore() const { return score_; }
    GameState getGameState() const { return gameState_; }
    GamePhase getGamePhase() const { return gamePhase_; }
    bool isGameOver() const { return gameOver_; }

    // Accessibility & Settings (Phase 6.2)
    bool isMotionReductionEnabled() const { return motionReductionEnabled_; }
    void toggleMotionReduction() { motionReductionEnabled_ = !motionReductionEnabled_; }
    bool isColorblindModeEnabled() const { return colorblindModeEnabled_; }
    void toggleColorblindMode() { colorblindModeEnabled_ = !colorblindModeEnabled_; }

    const std::vector<PathNode>& getPath() const { return path_; }
    const std::vector<EnemyDot>& getEnemies() const { return enemies_; }
    const std::vector<Tower>& getTowers() const { return towers_; }
    const std::vector<Projectile>& getProjectiles() const { return projectiles_; }

    void setGameState(GameState state);
    void startNextWave();
    void watchAdForLives();
    void resetGame();
    void returnToMenu();

    // Session Persistence (Phase 7.2)
    std::string serializeGameState() const;
    void deserializeGameState(const std::string& data);

private:
    int screenWidth_;
    int screenHeight_;

    int baseHealth_;
    int gold_;
    int lives_;
    int wave_;
    int score_;
    int enemiesKilled_;
    GameState gameState_;
    GamePhase gamePhase_;
    bool gameOver_;

    bool motionReductionEnabled_;
    bool colorblindModeEnabled_;

    std::vector<PathNode> path_;
    std::vector<EnemyDot> enemies_;
    std::vector<Tower> towers_;
    std::vector<Projectile> projectiles_;

    float waveSpawnTimer_;
    int enemiesToSpawn_;
    float spawnInterval_;
    int nextEnemyId_;
    int enemiesLeakedThisWave_;

    void generateMapAndPath();
    void spawnEnemy();
    void updateTowers(float deltaTime);
    void updateProjectiles(float deltaTime);
    void updateEnemies(float deltaTime);
    void endWave();
};

#endif // GEOMETRY_DEFENDER_GAME_ENGINE_H
