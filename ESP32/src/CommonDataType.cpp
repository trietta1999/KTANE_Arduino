/**
 * @brief Common data type
 */

#include "CommonDataType.h"

using namespace std::string_literals;

MAP_ENUM_STR(LABEL_INDICATOR, DEF_LABEL_INDICATOR)
MAP_ENUM_STR(BATTERY_TYPE, DEF_BATTERY_TYPE)
MAP_ENUM_STR(COMPORT_TYPE, DEF_COMPORT_TYPE)
MAP_ENUM_STR(MODULE_NAME, DEF_MODULE_NAME)

#ifdef _WIN64
MAP_ENUM_WSTR(MODULE_NAME, DEF_MODULE_NAME)
#endif

MAP_ENUM_STR(MOVE_TYPE, DEF_MOVE_TYPE)

std::unordered_map<MOVE_TYPE, char> mapMoveTypeChar = {
    { MOVE_TYPE::LEFT, 'L' },
    { MOVE_TYPE::RIGHT, 'R' },
    { MOVE_TYPE::UP, 'U' },
    { MOVE_TYPE::DOWN, 'D' },
};

// Create moving rule base on direction: start from bottom-left, column by column from down to up
// Create indicator coordinate base on direction: start from bottom-left, column by column from down to up
// Point next to edge can still move in any direction, unless it is a wall.
// Follow these letter mark, no order requirement:
// L: can be moved left
// R: can be moved right
// U: can be moved up
// D: can be moved down
// X: can not be moved
std::vector<std::pair<LIST_IND_T, ROW_T>> listMazeType = {
    // Sheet1
    {
        {
            { 1, 5 }, { 6, 4 },
        },
        {{
            { "LURD", "LUR", "LUD", "URD", "LUR", "LUR" },
            { "LUD", "RD", "LU", "UR", "LR", "LRD" },
            { "LUD", "UR", "LD", "RD", "LR", "LURD" },
            { "LUD", "R", "LUR", "LU", "R", "LURD" },
            { "LURD", "LR", "LD", "RD", "L", "URD" },
            { "LURD", "LD", "URD", "LUD", "RD", "LURD" },
        }},
    },
    // Sheet2
    {
        {
            { 2, 3 }, { 5, 5 },
        },
        {{
            { "LUR", "LURD", "LU", "URD", "LURD", "LUR" },
            { "LRD", "LU", "RD", "LU", "UR", "LRD" },
            { "LUD", "RD", "LU", "RD", "LR", "LURD" },
            { "LURD", "LU", "RD", "LU", "D", "URD" },
            { "LUD", "D", "UD", "RD", "LU", "URD" },
            { "LUD", "URD", "LUD", "URD", "LRD", "LURD" },
        }},
    },
    // Sheet3
    {
        {
            { 4, 3 }, { 6, 3 },
        },
        {{
            { "LURD", "LUR", "LUD", "UD", "URD", "LURD" },
            { "LU", "D", "UD", "UR", "LU", "URD" },
            { "RD", "LUD", "UD", "RD", "LD", "URD" },
            { "LUD", "UD", "UD", "UD", "UD", "URD" },
            { "LUD", "UR", "LU", "UD", "UD", "URD" },
            { "LURD", "LRD", "LRD", "LUD", "URD", "LURD" },
        }},
    },
    // Sheet4
    {
        {
            { 1, 3 }, { 1, 6 },
        },
        {{
            { "LURD", "LUD", "UR", "LUR", "LUR", "LURD" },
            { "LUD", "UD", "RD", "LR", "LR", "LURD" },
            { "LUD", "UR", "LU", "RD", "L", "URD" },
            { "LUD", "R", "LR", "LUR", "LR", "LURD" },
            { "LURD", "LR", "LR", "LR", "LD", "URD" },
            { "LURD", "LRD", "LD", "RD", "LUD", "URD" },
        }},
    },
    // Sheet5
    {
        {
            { 4, 1 }, { 5, 4 },
        },
        {{
            { "LUR", "LUR", "LUR", "LUR", "LURD", "LURD" },
            { "LRD", "LR", "LR", "LRD", "LU", "UR" },
            { "LURD", "LD", "R", "LU", "RD", "LRD" },
            { "LUD", "UR", "LR", "LD", "U", "URD" },
            { "LUD", "RD", "LR", "LUR", "L", "URD" },
            { "LUD", "URD", "LRD", "LRD", "LRD", "LURD" },
        }},
    },
    // Sheet6
    {
        {
            { 3, 2 }, { 5, 6 },
        },
        {{
            { "LUD", "URD", "LUD", "UR", "LURD", "LURD" },
            { "LUD", "UD", "UD", "RD", "LU", "URD" },
            { "LURD", "LU", "U", "UD", "RD", "LUR" },
            { "LUR", "LD", "RD", "LUD", "UD", "RD" },
            { "LRD", "LU", "U", "UD", "UR", "LURD" },
            { "LURD", "LRD", "LRD", "LUD", "RD", "LURD" },
        }},
    },
    // Sheet7
    {
        {
            { 2, 1 }, { 2, 6 },
        },
        {{
            { "LURD", "LUR", "LUR", "LUD", "URD", "LURD" },
            { "LUD", "RD", "L", "UR", "LU", "URD" },
            { "LUR", "LU", "RD", "L", "RD", "LUR" },
            { "LRD", "LD", "URD", "LR", "LU", "RD" },
            { "LUD", "U", "UR", "LR", "LD", "URD" },
            { "LURD", "LRD", "LRD", "LRD", "LURD", "LURD" },
        }},
    },
    // Sheet8
    {
        {
            { 3, 3 }, { 4, 6 },
        },
        {{
            { "LUD", "URD", "LUR", "LUD", "URD", "LURD" },
            { "LURD", "LUR", "L", "UR", "LU", "URD" },
            { "LUD", "RD", "LR", "LR", "LD", "URD" },
            { "LUD", "UR", "LD", "R", "LUR", "LUR" },
            { "LUD", "D", "UR", "LR", "LR", "LR" },
            { "LURD", "LURD", "LRD", "LRD", "LRD", "LRD" },
        }},
    },
    // Sheet9
    {
        {
            { 1, 2 }, { 3, 5 },
        },
        {{
            { "LUD", "URD", "LUR", "LUR", "LURD", "LURD" },
            { "LUD", "UD", "RD", "L", "UD", "URD" },
            { "LURD", "LUR", "LU", "RD", "LU", "URD" },
            { "LUD", "D", "RD", "LU", "R", "LURD" },
            { "LUD", "UD", "UD", "RD", "LD", "UR" },
            { "LURD", "LUD", "URD", "LUD", "URD", "LRD" },
        }},
    },
};
