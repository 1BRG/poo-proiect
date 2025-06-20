//
// Created by Gabriel on 5/3/2025.
//

#include "../../include/Entities/Environment/QuestionBlock.h"
#include "../../include/game/gameFunction.h"
#include "../../include/Entities/EntityFactory.h"
// Load level file into entity list using factory and exceptions
void game::setLevel(int k) {
    std::string filename = "../Code/Levels/level" + std::to_string(k) + ".txt";
    std::ifstream f(filename);
    std::string line;
    level.clear();
    try {
        if (!f.is_open()) {
            throw FileException(filename);
        }
    } catch (const FileException &txt) {
        std::cout << txt.what() << std::endl;
        exit(0);
    }
    // 0 empty
    // 1 brick
    // P player
    // 2 tortoise
    //3 question block
    int n = 1;

    while (std::getline(f, line)) {
        for (long long unsigned int i = 0; i < line.length(); i++) {
            std::shared_ptr<Entity> a;
            try {
                if (line[i] == '1') {
                    a = EntityFactory::createEntity(EntityFactory::Type::groundBlock, i * 16, n * 16);
                    throw(a);
                }
                if (line[i] == '2') {
                    a = EntityFactory::createEntity(EntityFactory::Type::turtle, (i) * 16, n * 16);
                    throw(a);
                }
                if (line[i] == 'P') {
                    a = EntityFactory::createEntity(EntityFactory::Type::player, i * 16, n * 16);
                    auto c = std::dynamic_pointer_cast<Player>(a);
                    c->setScore(score);
                    throw(a);
                }
                if (line[i] == '3') {
                    a = EntityFactory::createEntity(EntityFactory::Type::questionBlock, i * 16, n * 16);
                    throw(a);
                }
                if (line[i] == '4') {
                    a = EntityFactory::createEntity(EntityFactory::Type::brickBlock, i * 16, n * 16);
                    throw(a);
                }
                if (line[i] != '0')
                    throw(BaseException("This entity does not exist!"));
            } catch (const BaseException &txt) {
                std::cout << txt.what() << std::endl;
                exit(0);
            }
            catch (...) {
                level.push_back(a);
            }
        }
        n++;
    }
    f.close();
    level.sort([](const std::shared_ptr<Entity> &a, const std::shared_ptr<Entity> &b) -> bool {
        return a->coord_x() < b->coord_x();
    });
}

// Categorize entities into lists and attach observers
void game::setEntities() {
    entities.clear();
    environment.clear();
    /*
    for (int i = 0; i < screenHeight; i ++)
        for (int j = 0; j < screenWidth; j ++)
            grid[i][j] = nullptr;
            */
    for (const auto &entity: level) {
        if (std::dynamic_pointer_cast<Living>(entity) != nullptr) {
            try {
                entities.push_back(std::dynamic_pointer_cast<Living>(entity));
            } catch (TextureException &txt) {
                std::cout << txt.what() << std::endl;
                exit(0);
            }
        } else if (std::dynamic_pointer_cast<MovebleEnvironment>(entity) != nullptr) {
            try {
                movEnv.push_back(std::dynamic_pointer_cast<MovebleEnvironment>(entity));
            } catch (TextureException &txt) {
                std::cout << txt.what() << std::endl;
                exit(0);
            }
        } else {
            try {
                environment.push_back(std::dynamic_pointer_cast<Environment>(entity));
            } catch (TextureException &txt) {
                std::cout << txt.what() << std::endl;
                exit(0);
            }
        }
        //  insertEntity(entity);
    }
    for (auto &env: movEnv) {
        auto qb = std::dynamic_pointer_cast<QuestionBlock>(env);
        if (qb) {
            qb->setWorld(this);
            qb->attach(score);
        }
    }
}
