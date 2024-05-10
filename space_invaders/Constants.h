#pragma once
#include <chrono>

constexpr unsigned char BASE_SIZE = 16; // величина определ€юща€ размеры всех объектов игры

constexpr unsigned char ENEMY_BULLET_SPEED = 2; 
const unsigned char ENEMY_HIT_TIMER_DURATION = 5; // врем€ подсветки инвайдера белым
const unsigned char ENEMY_MOVE_PAUSE_DECREASE = 1; // дельта скорости
constexpr unsigned char ENEMY_MOVE_PAUSE_MIN = 3;
constexpr unsigned char ENEMY_MOVE_PAUSE_START = 54; // начальный интервал движени€
constexpr unsigned char ENEMY_MOVE_PAUSE_START_MIN = 32;
constexpr unsigned char ENEMY_MOVE_SPEED = 2;
constexpr unsigned char ENEMY_TYPES = 3;

constexpr unsigned char EXPLOSION_ANIMATION_SPEED = 2;

constexpr unsigned char NEXT_LEVEL_TRANSITION = 64; // интервал ожидани€ дл€ перехода на следующий уровень

constexpr unsigned char PLAYER_BULLET_SPEED = 4;
constexpr unsigned char PLAYER_MOVE_SPEED = 2;

constexpr unsigned char RELOAD_DURATION = 31;
constexpr unsigned char SCREEN_RESIZE = 4;

constexpr unsigned char TOTAL_LEVELS = 5;

constexpr unsigned short ENEMY_SHOOT_CHANCE = 3025;

constexpr unsigned short SCREEN_HEIGHT = 200;
constexpr unsigned short SCREEN_WIDTH = 400;

constexpr std::chrono::microseconds FRAME_DURATION(16667);
