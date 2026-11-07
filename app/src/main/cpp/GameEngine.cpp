#include "GameEngine.h"
#include <cmath>
#include <algorithm>
#include <cstdlib>

GameEngine::GameEngine(int screenWidth, int screenHeight)
    : screenWidth_(screenWidth),
      screenHeight_(screenHeight),
      baseHealth_(20),
      gold_(200),
      wave_(0),
      gameOver_(false),
      waveInProgress_(false),
      waveSpawnTimer_(0.f),
      enemiesToSpawn_(0),
      spawnInterval_(1.0f),
      nextEnemyId_(0) {
    generatePath();
    startNextWave();
}

GameEngine::~GameEngine() = default;

void GameEngine::generatePath() {
    path_.clear();
    // Top-to-bottom meandering "Grand Canyon" path in normalized GL coordinates [-1.5, 1.5]
    int numPoints = 10;
    float startY = 1.8f;
    float endY = -1.8f;
    float stepY = (startY - endY) / (numPoints - 1);

    for (int i = 0; i < numPoints; ++i) {
        float y = startY - i * stepY;
        // Meander X using sin wave
        float x = std::sin(i * 0.8f) * 1.1f;
        // Clamp x within screen bounds
        if (x < -1.4f) x = -1.4f;
        if (x > 1.4f) x = 1.4f;
        path_.push_back({x, y});
    }
}

void GameEngine::startNextWave() {
    if (gameOver_) return;
    wave_++;
    enemiesToSpawn_ = 5 + wave_ * 3;
    waveSpawnTimer_ = 0.f;
    spawnInterval_ = std::max(0.4f, 1.2f - wave_ * 0.05f);
    waveInProgress_ = true;
}

void GameEngine::resetGame() {
    baseHealth_ = 20;
    gold_ = 200;
    wave_ = 0;
    gameOver_ = false;
    waveInProgress_ = false;
    enemies_.clear();
    towers_.clear();
    projectiles_.clear();
    generatePath();
    startNextWave();
}

void GameEngine::spawnEnemy() {
    if (enemiesToSpawn_ <= 0 || path_.empty()) return;

    EnemyDot enemy;
    enemy.id = nextEnemyId_++;
    enemy.x = path_[0].x;
    enemy.y = path_[0].y;
    enemy.maxHealth = 20.0f + wave_ * 10.0f;
    enemy.health = enemy.maxHealth;
    enemy.speed = 0.8f + wave_ * 0.05f;
    enemy.pathIndex = 0;
    enemy.pathProgress = 0.0f;
    enemy.active = true;

    enemies_.push_back(enemy);
    enemiesToSpawn_--;
}

void GameEngine::update(float deltaTime) {
    if (gameOver_) return;

    // Wave spawning
    if (waveInProgress_ && enemiesToSpawn_ > 0) {
        waveSpawnTimer_ += deltaTime;
        if (waveSpawnTimer_ >= spawnInterval_) {
            waveSpawnTimer_ = 0.f;
            spawnEnemy();
        }
    } else if (waveInProgress_ && enemiesToSpawn_ <= 0) {
        // Check if all enemies cleared
        bool activeEnemies = false;
        for (const auto& e : enemies_) {
            if (e.active) {
                activeEnemies = true;
                break;
            }
        }
        if (!activeEnemies) {
            waveInProgress_ = false;
            gold_ += 50 + wave_ * 20; // Wave bonus
            startNextWave();
        }
    }

    updateEnemies(deltaTime);
    updateTowers(deltaTime);
    updateProjectiles(deltaTime);
}

void GameEngine::updateEnemies(float deltaTime) {
    for (auto& enemy : enemies_) {
        if (!enemy.active) continue;

        if (enemy.pathIndex >= (int)path_.size() - 1) {
            // Reached the end!
            enemy.active = false;
            baseHealth_--;
            if (baseHealth_ <= 0) {
                gameOver_ = true;
            }
            continue;
        }

        const auto& p1 = path_[enemy.pathIndex];
        const auto& p2 = path_[enemy.pathIndex + 1];

        float dx = p2.x - p1.x;
        float dy = p2.y - p1.y;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dist > 0.0001f) {
            enemy.pathProgress += (enemy.speed * deltaTime) / dist;
            if (enemy.pathProgress >= 1.0f) {
                enemy.pathIndex++;
                enemy.pathProgress = 0.0f;
                if (enemy.pathIndex < (int)path_.size()) {
                    enemy.x = path_[enemy.pathIndex].x;
                    enemy.y = path_[enemy.pathIndex].y;
                }
            } else {
                enemy.x = p1.x + dx * enemy.pathProgress;
                enemy.y = p1.y + dy * enemy.pathProgress;
            }
        }
    }

    // Clean up inactive enemies
    enemies_.erase(
        std::remove_if(enemies_.begin(), enemies_.end(), [](const EnemyDot& e) { return !e.active; }),
        enemies_.end()
    );
}

void GameEngine::updateTowers(float deltaTime) {
    for (auto& tower : towers_) {
        tower.fireCooldown -= deltaTime;

        // Find target enemy in range
        float closestDist = tower.range;
        int targetId = -1;

        for (const auto& enemy : enemies_) {
            if (!enemy.active) continue;
            float dx = enemy.x - ((tower.gridX - 5.0f) * 0.35f); // map grid to world coords
            float dy = enemy.y - ((tower.gridY - 7.5f) * 0.35f);
            float dist = std::sqrt(dx * dx + dy * dy);

            if (dist <= closestDist) {
                closestDist = dist;
                targetId = enemy.id;
            }
        }

        tower.targetEnemyId = targetId;

        if (targetId != -1) {
            // Rotate towards target
            for (const auto& enemy : enemies_) {
                if (enemy.id == targetId) {
                    float tx = enemy.x;
                    float ty = enemy.y;
                    float wx = (tower.gridX - 5.0f) * 0.35f;
                    float wy = (tower.gridY - 7.5f) * 0.35f;
                    tower.rotation = std::atan2(ty - wy, tx - wx);
                    break;
                }
            }

            // Fire if cooldown ready
            if (tower.fireCooldown <= 0.0f) {
                tower.fireCooldown = tower.fireRate;

                // Spawn projectile
                Projectile proj;
                proj.x = (tower.gridX - 5.0f) * 0.35f;
                proj.y = (tower.gridY - 7.5f) * 0.35f;
                proj.targetEnemyId = targetId;
                proj.speed = 3.5f;
                proj.damage = tower.damage;
                proj.active = true;

                // Find target pos initially
                for (const auto& enemy : enemies_) {
                    if (enemy.id == targetId) {
                        proj.targetX = enemy.x;
                        proj.targetY = enemy.y;
                        break;
                    }
                }

                projectiles_.push_back(proj);
            }
        }
    }
}

void GameEngine::updateProjectiles(float deltaTime) {
    for (auto& proj : projectiles_) {
        if (!proj.active) continue;

        // Track target enemy if still active
        bool targetFound = false;
        for (auto& enemy : enemies_) {
            if (enemy.id == proj.targetEnemyId && enemy.active) {
                proj.targetX = enemy.x;
                proj.targetY = enemy.y;
                targetFound = true;
                break;
            }
        }

        float dx = proj.targetX - proj.x;
        float dy = proj.targetY - proj.y;
        float dist = std::sqrt(dx * dx + dy * dy);

        float moveDist = proj.speed * deltaTime;
        if (dist <= moveDist) {
            // Hit!
            proj.active = false;
            if (targetFound) {
                for (auto& enemy : enemies_) {
                    if (enemy.id == proj.targetEnemyId && enemy.active) {
                        enemy.health -= proj.damage;
                        if (enemy.health <= 0.0f) {
                            enemy.active = false;
                            gold_ += 15; // Reward per kill
                        }
                        break;
                    }
                }
            }
        } else {
            proj.x += (dx / dist) * moveDist;
            proj.y += (dy / dist) * moveDist;
        }
    }

    projectiles_.erase(
        std::remove_if(projectiles_.begin(), projectiles_.end(), [](const Projectile& p) { return !p.active; }),
        projectiles_.end()
    );
}

void GameEngine::handleTouch(float touchX, float touchY, bool down) {
    if (!down || gameOver_) return;

    // Convert screen touch normalized [-1, 1] to grid coordinates (10 cols, 15 rows)
    // touchX from [-1, 1], touchY from [-1, 1]
    int gridX = static_cast<int>((touchX + 1.0f) * 5.0f); // 0 to 10
    int gridY = static_cast<int>((touchY + 1.0f) * 7.5f); // 0 to 15

    if (gridX < 0 || gridX > 9 || gridY < 0 || gridY > 14) return;

    // Check if tile is on or near path (don't allow towers on path)
    float worldX = (gridX - 5.0f) * 0.35f;
    float worldY = (gridY - 7.5f) * 0.35f;

    for (const auto& node : path_) {
        float dx = node.x - worldX;
        float dy = node.y - worldY;
        if (std::sqrt(dx * dx + dy * dy) < 0.35f) {
            // Too close to path, cannot build
            return;
        }
    }

    // Check if tower already exists at grid pos
    auto it = std::find_if(towers_.begin(), towers_.end(), [gridX, gridY](const Tower& t) {
        return t.gridX == gridX && t.gridY == gridY;
    });

    if (it != towers_.end()) {
        // Upgrade tower or add shape stack
        if (gold_ >= 50 && it->level < 10) {
            gold_ -= 50;
            it->level++;
            it->damage += 5.0f;
            it->range += 0.05f;
            if (it->shapes.size() < 3) {
                // Add next shape in rotation: Square -> Circle -> Triangle
                ShapeType nextShape = (it->shapes.size() == 1) ? SHAPE_CIRCLE : SHAPE_TRIANGLE;
                it->shapes.push_back(nextShape);
            }
        }
    } else {
        // Build new tower if enough gold
        if (gold_ >= 60) {
            gold_ -= 60;
            Tower tower;
            tower.gridX = gridX;
            tower.gridY = gridY;
            tower.shapes.push_back(SHAPE_SQUARE); // Start with square machine gun
            tower.level = 1;
            tower.range = 0.8f;
            tower.fireRate = 0.5f;
            tower.fireCooldown = 0.0f;
            tower.damage = 10.0f;
            tower.rotation = 0.0f;
            tower.targetEnemyId = -1;
            towers_.push_back(tower);
        }
    }
}
