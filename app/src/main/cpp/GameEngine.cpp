#include "GameEngine.h"
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <sstream>

GameEngine::GameEngine(int screenWidth, int screenHeight)
    : screenWidth_(screenWidth),
      screenHeight_(screenHeight),
      baseHealth_(20),
      gold_(250),
      lives_(5),
      wave_(0),
      score_(0),
      enemiesKilled_(0),
      gameState_(STATE_MENU),
      gamePhase_(PHASE_BUILDING),
      gameOver_(false),
      motionReductionEnabled_(false),
      colorblindModeEnabled_(false),
      waveSpawnTimer_(0.f),
      enemiesToSpawn_(0),
      spawnInterval_(1.0f),
      nextEnemyId_(0),
      enemiesLeakedThisWave_(0) {
    generateMapAndPath();
}

GameEngine::~GameEngine() = default;

void GameEngine::generateMapAndPath() {
    path_.clear();
    int numPoints = 12;
    float startY = 1.8f;
    float endY = -1.8f;
    float stepY = (startY - endY) / (numPoints - 1);

    for (int i = 0; i < numPoints; ++i) {
        float y = startY - i * stepY;
        float x = std::sin(i * 0.7f) * 1.2f;
        if (x < -1.3f) x = -1.3f;
        if (x > 1.3f) x = 1.3f;
        path_.push_back({x, y});
    }
}

void GameEngine::setGameState(GameState state) {
    gameState_ = state;
}

void GameEngine::startNextWave() {
    if (gameOver_) return;
    wave_++;
    gamePhase_ = PHASE_COMBAT;
    enemiesToSpawn_ = 6 + wave_ * 4;
    waveSpawnTimer_ = 0.f;
    spawnInterval_ = std::max(0.35f, 1.1f - wave_ * 0.04f);
    enemiesLeakedThisWave_ = 0;
}

void GameEngine::endWave() {
    gamePhase_ = PHASE_BUILDING;
    gold_ += 65 + wave_ * 30;
    score_ += wave_ * 150;

    int tilesToDelete = 1 + (enemiesLeakedThisWave_ > 1 ? 1 : 0);
    int deletedCount = 0;

    for (auto it = towers_.begin(); it != towers_.end(); ) {
        if (it->terrainType == TERRAIN_UPPER_GREEN && deletedCount < tilesToDelete) {
            int refund = static_cast<int>(it->totalCost * 0.75f);
            gold_ += refund;
            it = towers_.erase(it);
            deletedCount++;
        } else {
            ++it;
        }
    }
}

void GameEngine::watchAdForLives() {
    lives_ = 5;
    if (gameState_ == STATE_GAMEOVER) {
        gameOver_ = false;
        baseHealth_ = 10;
        gameState_ = STATE_PLAYING;
    }
}

void GameEngine::resetGame() {
    if (lives_ <= 0) return;
    baseHealth_ = 20;
    gold_ = 250;
    wave_ = 0;
    score_ = 0;
    enemiesKilled_ = 0;
    gamePhase_ = PHASE_BUILDING;
    gameOver_ = false;
    gameState_ = STATE_PLAYING;
    enemies_.clear();
    towers_.clear();
    projectiles_.clear();
    generateMapAndPath();
    lives_--;
}

void GameEngine::returnToMenu() {
    gameState_ = STATE_MENU;
    gameOver_ = false;
}

std::string GameEngine::serializeGameState() const {
    std::ostringstream oss;
    oss << wave_ << "," << gold_ << "," << baseHealth_ << "," << lives_ << "," << score_;
    return oss.str();
}

void GameEngine::deserializeGameState(const std::string& data) {
    std::istringstream iss(data);
    char comma;
    iss >> wave_ >> comma >> gold_ >> comma >> baseHealth_ >> comma >> lives_ >> comma >> score_;
}

void GameEngine::spawnEnemy() {
    if (enemiesToSpawn_ <= 0 || path_.empty()) return;

    EnemyDot enemy;
    enemy.id = nextEnemyId_++;
    enemy.x = path_[0].x;
    enemy.y = path_[0].y;
    enemy.maxHealth = 25.0f + wave_ * 12.0f;
    enemy.health = enemy.maxHealth;
    enemy.speed = 0.9f + wave_ * 0.05f;
    enemy.pathIndex = 0;
    enemy.pathProgress = 0.0f;
    enemy.active = true;

    enemies_.push_back(enemy);
    enemiesToSpawn_--;
}

void GameEngine::update(float deltaTime) {
    if (gameState_ != STATE_PLAYING || gameOver_) return;

    if (gamePhase_ == PHASE_COMBAT) {
        if (enemiesToSpawn_ > 0) {
            waveSpawnTimer_ += deltaTime;
            if (waveSpawnTimer_ >= spawnInterval_) {
                waveSpawnTimer_ = 0.f;
                spawnEnemy();
            }
        } else {
            bool activeEnemies = false;
            for (const auto& e : enemies_) {
                if (e.active) {
                    activeEnemies = true;
                    break;
                }
            }
            if (!activeEnemies) {
                endWave();
            }
        }

        updateEnemies(deltaTime);
        updateTowers(deltaTime);
        updateProjectiles(deltaTime);
    }
}

void GameEngine::updateEnemies(float deltaTime) {
    for (auto& enemy : enemies_) {
        if (!enemy.active) continue;

        if (enemy.pathIndex >= (int)path_.size() - 1) {
            enemy.active = false;
            baseHealth_--;
            enemiesLeakedThisWave_++;
            if (baseHealth_ <= 0) {
                gameOver_ = true;
                gameState_ = STATE_GAMEOVER;
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

        for (auto& tower : towers_) {
            if (tower.terrainType == TERRAIN_LOWER_BROWN) {
                float tdx = enemy.x - ((tower.gridX - 5.0f) * 0.35f);
                float tdy = enemy.y - ((tower.gridY - 7.5f) * 0.35f);
                if (std::sqrt(tdx * tdx + tdy * tdy) < 0.25f) {
                    float defenseFactor = 1.0f + (tower.level * 0.15f);
                    tower.hp -= ((6.0f + wave_ * 1.5f) / defenseFactor) * deltaTime;
                    if (tower.hp <= 0.0f) {
                        int refund = static_cast<int>(tower.totalCost * 0.50f);
                        gold_ += refund;
                        tower.gridX = -999;
                    }
                }
            }
        }
    }

    towers_.erase(
        std::remove_if(towers_.begin(), towers_.end(), [](const Tower& t) { return t.gridX == -999; }),
        towers_.end()
    );

    enemies_.erase(
        std::remove_if(enemies_.begin(), enemies_.end(), [](const EnemyDot& e) { return !e.active; }),
        enemies_.end()
    );
}

void GameEngine::updateTowers(float deltaTime) {
    for (auto& tower : towers_) {
        tower.fireCooldown -= deltaTime;

        // If motion reduction is enabled, skip extra rotation animations or speed up cooling
        float effectiveFireRate = motionReductionEnabled_ ? tower.fireRate * 0.8f : tower.fireRate;

        float closestDist = tower.range;
        int targetId = -1;

        for (const auto& enemy : enemies_) {
            if (!enemy.active) continue;
            float dx = enemy.x - ((tower.gridX - 5.0f) * 0.35f);
            float dy = enemy.y - ((tower.gridY - 7.5f) * 0.35f);
            float dist = std::sqrt(dx * dx + dy * dy);

            if (dist <= closestDist) {
                closestDist = dist;
                targetId = enemy.id;
            }
        }

        tower.targetEnemyId = targetId;

        if (targetId != -1) {
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

            if (tower.fireCooldown <= 0.0f) {
                tower.fireCooldown = effectiveFireRate;

                Projectile proj;
                proj.x = (tower.gridX - 5.0f) * 0.35f;
                proj.y = (tower.gridY - 7.5f) * 0.35f;
                proj.targetEnemyId = targetId;
                proj.speed = 4.0f;
                proj.damage = tower.damage;
                proj.active = true;

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
            proj.active = false;
            if (targetFound) {
                for (auto& enemy : enemies_) {
                    if (enemy.id == proj.targetEnemyId && enemy.active) {
                        enemy.health -= proj.damage;
                        if (enemy.health <= 0.0f) {
                            enemy.active = false;
                            gold_ += 25;
                            score_ += 50;
                            enemiesKilled_++;
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
    if (!down) return;

    if (gameState_ == STATE_MENU) {
        // Play button: x in [-0.6, 0.6], y in [0.1, 0.5]
        if (touchX >= -0.6f && touchX <= 0.6f && touchY >= 0.1f && touchY <= 0.5f) {
            resetGame();
        }
        // Settings button: x in [-0.6, 0.6], y in [-0.4, 0.0]
        else if (touchX >= -0.6f && touchX <= 0.6f && touchY >= -0.4f && touchY <= 0.0f) {
            gameState_ = STATE_SETTINGS;
        }
        return;
    }

    if (gameState_ == STATE_SETTINGS) {
        // Toggle Motion Reduction: x in [-0.8, 0.8], y in [0.2, 0.5]
        if (touchX >= -0.8f && touchX <= 0.8f && touchY >= 0.2f && touchY <= 0.5f) {
            toggleMotionReduction();
        }
        // Toggle Colorblind Mode: x in [-0.8, 0.8], y in [-0.2, 0.1]
        else if (touchX >= -0.8f && touchX <= 0.8f && touchY >= -0.2f && touchY <= 0.1f) {
            toggleColorblindMode();
        }
        // Back button: x in [-0.6, 0.6], y in [-0.8, -0.4]
        else if (touchX >= -0.6f && touchX <= 0.6f && touchY >= -0.8f && touchY <= -0.4f) {
            gameState_ = STATE_MENU;
        }
        return;
    }

    if (gameState_ == STATE_GAMEOVER) {
        // Restart button: x in [-0.8, -0.1], y in [-0.3, 0.1]
        if (touchX >= -0.8f && touchX <= -0.1f && touchY >= -0.3f && touchY <= 0.1f) {
            resetGame();
        }
        // Watch Ad button: x in [0.1, 0.8], y in [-0.3, 0.1]
        else if (touchX >= 0.1f && touchX <= 0.8f && touchY >= -0.3f && touchY <= 0.1f) {
            watchAdForLives();
        }
        // Menu button: x in [-0.4, 0.4], y in [-0.7, -0.4]
        else if (touchX >= -0.4f && touchX <= 0.4f && touchY >= -0.7f && touchY <= -0.4f) {
            returnToMenu();
        }
        return;
    }

    if (gameState_ == STATE_PLAYING) {
        // Top-right Menu button check: x > 0.75, y > 0.85
        if (touchX >= 0.75f && touchY >= 0.85f) {
            gameState_ = STATE_MENU;
            return;
        }

        int gridX = static_cast<int>((touchX + 1.0f) * 5.0f);
        int gridY = static_cast<int>((touchY + 1.0f) * 7.5f);

        if (gridX < 0 || gridX > 9 || gridY < 0 || gridY > 14) return;

        float worldX = (gridX - 5.0f) * 0.35f;
        float worldY = (gridY - 7.5f) * 0.35f;

        bool isOnPath = false;
        for (const auto& node : path_) {
            float dx = node.x - worldX;
            float dy = node.y - worldY;
            if (std::sqrt(dx * dx + dy * dy) < 0.35f) {
                isOnPath = true;
                break;
            }
        }

        auto it = std::find_if(towers_.begin(), towers_.end(), [gridX, gridY](const Tower& t) {
            return t.gridX == gridX && t.gridY == gridY;
        });

        if (it != towers_.end()) {
            if (gamePhase_ == PHASE_COMBAT && gold_ >= 50 && it->level < 10) {
                gold_ -= 50;
                it->totalCost += 50;
                it->level++;
                it->damage += 8.0f;
                it->range += 0.05f;
                if (it->shapes.size() < 3) {
                    ShapeType nextShape = (it->shapes.size() == 1) ? SHAPE_CIRCLE : SHAPE_TRIANGLE;
                    it->shapes.push_back(nextShape);
                }
                float shapeBonus = 0.0f;
                for (auto s : it->shapes) {
                    if (s == SHAPE_TRIANGLE) shapeBonus += 15.0f;
                    else if (s == SHAPE_SQUARE) shapeBonus += 30.0f;
                    else if (s == SHAPE_CIRCLE) shapeBonus += 60.0f;
                }
                it->maxHp = (isOnPath ? 40.0f : 80.0f) + shapeBonus + (it->level * 15.0f);
                it->hp = it->maxHp;
            }
        } else {
            if (gamePhase_ == PHASE_BUILDING && gold_ >= 60) {
                gold_ -= 60;
                Tower tower;
                tower.gridX = gridX;
                tower.gridY = gridY;
                tower.terrainType = isOnPath ? TERRAIN_LOWER_BROWN : TERRAIN_UPPER_GREEN;
                tower.shapes.push_back(SHAPE_SQUARE);
                tower.level = 1;
                tower.range = 0.8f;
                tower.fireRate = 0.5f;
                tower.fireCooldown = 0.0f;
                tower.damage = 12.0f;
                tower.maxHp = isOnPath ? 50.0f : 100.0f;
                tower.hp = tower.maxHp;
                tower.rotation = 0.0f;
                tower.targetEnemyId = -1;
                tower.totalCost = 60;
                towers_.push_back(tower);
            }
        }
    }
}
