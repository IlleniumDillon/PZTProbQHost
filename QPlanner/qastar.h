#ifndef QASTAR_H
#define QASTAR_H

#include "qplanner_common.h"

class Cell2d
{
public:
    Cell2d(void)
    {
        this->pos.x = 0; this->pos.y = 0;
        this->f = 0; this->g = 0; this->h = 0;
        this->parent = NULL;
    }
    Cell2d(int x, int y)
    {
        this->pos.x = x; this->pos.y = y;
        this->f = 0; this->g = 0; this->h = 0;
        this->parent = NULL;
    }
    Cell2d(int x, int y, Cell2d* parent)
    {
        this->pos.x = x; this->pos.y = y;
        this->f = 0; this->g = 0; this->h = 0;
        this->parent = parent;
    }

    void evaluate(Cell2d* goal)
    {
        double dx, dy;
        // 已有路径代价计算
        if (this->parent != NULL)
        {
            dx = (this->pos.x - this->parent->pos.x);
            dy = (this->pos.y - this->parent->pos.y);
            this->g = this->parent->g + sqrt(dx * dx + dy * dy);
        }
        else
        {
            this->g = 0;
        }
        // 启发代价计算
        dx = (this->pos.x - goal->pos.x);
        dy = (this->pos.y - goal->pos.y);
        if (this->heuristic_function == 1)
            // 欧氏距离
            this->h = sqrt(dx * dx + dy * dy);
        else if (this->heuristic_function == 2)
            // 曼哈顿距离
            this->h = fabs(dx) + fabs(dy);
        this->h *= 10;
        // 求和
        this->f = this->g + this->h;
    }

public:
    Point2d pos;
    double f;
    double g;
    double h;
    Cell2d* parent;

    int heuristic_function = 2;
};

class QAStar
{
public:
    QAStar();
};

#endif // QASTAR_H
