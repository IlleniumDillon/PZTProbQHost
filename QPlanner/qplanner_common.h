#ifndef QPLANNER_COMMON_H
#define QPLANNER_COMMON_H

#include <opencv.hpp>
#include <iostream>
#include <vector>

using cv::Mat;

class Point2d
{
public:
    Point2d(int _x = 0,int _y = 0)
    {
        x = _x, y = _y;
    }
    Point2d operator+(const Point2d& b)
    {
        Point2d ret;
        ret.x = this->x + b.x;
        ret.y = this->y + b.y;
        return ret;
    }
    Point2d operator-(const Point2d& b)
    {
        Point2d ret;
        ret.x = this->x - b.x;
        ret.y = this->y - b.y;
        return ret;
    }
    bool operator==(const Point2d& b)
    {
        return (this->x == b.x && this->y == b.y);
    }
    bool operator!=(const Point2d& b)
    {
        return !(this->x == b.x && this->y == b.y);
    }

    int manhattanLength()
    {
        return abs(x)+abs(y);
    }

    int x,y;
};


#endif // QPLANNER_COMMON_H
