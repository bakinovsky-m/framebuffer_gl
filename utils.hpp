#ifndef UTILS_HPP
#define UTILS_HPP

struct Color{
    Color(const double r_, const double g_, const double b_, const double a_) : r(r_), g(g_), b(b_), a(a_) {}
    Color(const double r_, const double g_, const double b_) : r(r_), g(g_), b(b_), a(0) {}

    double r;
    double g;
    double b;
    double a;
};

struct Kvadrat{
    Kvadrat(const double tl_x_, const double tl_y_, const double br_x_, const double br_y_) :
        tl_x(tl_x_),
        tl_y(tl_y_),
        br_x(br_x_),
        br_y(br_y_),
        depth(0),
        color{0,0,0,0}
    {}
    Kvadrat(const double tl_x_, const double tl_y_, const double br_x_, const double br_y_, const Color color_) :
        tl_x(tl_x_),
        tl_y(tl_y_),
        br_x(br_x_),
        br_y(br_y_),
        depth(0),
        color(color_)
    {}
    Kvadrat(const double tl_x_, const double tl_y_, const double br_x_, const double br_y_, const double depth_, const Color color_) :
        tl_x(tl_x_),
        tl_y(tl_y_),
        br_x(br_x_),
        br_y(br_y_),
        depth(depth_),
        color(color_)
    {}
    // top left corner
    double tl_x;
    double tl_y;
    // bottom right corner
    double br_x;
    double br_y;
    double depth;
    Color color;
};

#endif // UTILS_HPP
