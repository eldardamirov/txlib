//{===========================================================================
//! @file       Examples\Demo\Shaker.cpp
//              (C) ������� ��������, 7 �����, 2009
//!
//! @brief      ���� "������������� �������"
//!
//! @author     ������� ��������, 7 �����
//! @date       2009
//}===========================================================================

#include "TXLib.h"

//============================================================================

unsigned long Time = 0;

//============================================================================

struct Ball_t
    {
    double   x_;
    double   y_;
    double   vx_;
    double   vy_;
    double   r_;
    COLORREF color_;

    Ball_t();

    void draw (bool shading) const;
    void move (const POINT& d);
    };

//----------------------------------------------------------------------------

Ball_t::Ball_t() :
    x_     (random (100, txGetExtentX() - 100)),
    y_     (random (100, txGetExtentY() - 100)),
    vx_    (random (  5, 15)),
    vy_    (random (  5, 15)),
    r_     (random ( 10, 30)),
    color_ (RGB (random (50, 255), random (50, 255), random (50, 255)))
    {}

//----------------------------------------------------------------------------

void Ball_t::draw (bool shading) const
    {
    if (shading)
        {
        double r = txExtractColor (color_, TX_RED)   / 255.0,
               g = txExtractColor (color_, TX_GREEN) / 255.0,
               b = txExtractColor (color_, TX_BLUE)  / 255.0;

        for (double t = 0; t <= 1; t += 1.0/10)
            {
            double c = pow (t + 0.05, 0.25);
            txColor     (r*c, g*c, b*c);
            txFillColor (r*c, g*c, b*c);
            txCircle ((int)x_, (int)y_, (int) (r_ * (1-t) + 0.5));

            if (GetTickCount() > Time) break;
            }
        }
    else
        {
        txSetColor     (color_);
        txSetFillColor (color_);
        txCircle ((int)x_, (int)y_, (int)r_);
        }
    }

//----------------------------------------------------------------------------

#define AY         ( 0.7 )
#define DT         ( 1.0 )
#define ELASTICITY ( 0.6 + random (-0.2, +0.1) )

void Ball_t::move (const POINT& d)
    {
    x_  -= d.x;
    y_  -= d.y;

    y_  += vy_ * DT;
    x_  += vx_ * DT;

    vy_ += AY;

    if (x_ < 0              + r_) { x_ = 0              + r_; vx_ = -vx_ * ELASTICITY + d.x; }
    if (y_ < 0              + r_) { y_ = 0              + r_; vy_ = -vy_ * ELASTICITY + d.y; }
    if (x_ > txGetExtentX() - r_) { x_ = txGetExtentX() - r_; vx_ = -vx_ * ELASTICITY + d.x; }
    if (y_ > txGetExtentY() - r_) { y_ = txGetExtentY() - r_; vy_ = -vy_ * ELASTICITY + d.y; }
    }

//============================================================================

POINT TxGetWindowOrg()
    {
    RECT r = {0, 0, 0, 0};
    GetWindowRect (txWindow(), &r);
    POINT org = { r.left, r.top };
    return org;
    }

//============================================================================

#define SLEEP_TIME 20

int main()
    {
    srand ((unsigned) time (NULL));

    txCreateWindow (700, 500);

    POINT org1 = TxGetWindowOrg();

    Ball_t balls[20];

    txBegin();

    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        Time = GetTickCount() + SLEEP_TIME;

        txSetFillColor (TX_BLACK);
        txClear();

        txSetTextAlign();
        txTextOut (txGetExtentX()/2, txGetExtentY()/2, "Move window, shake the balls. [Esc] exits");

        POINT org0 = org1; org1 = TxGetWindowOrg();
        POINT d = { org1.x - org0.x, org1.y - org0.y };

        for (unsigned i = 0; i < sizearr (balls); i++) balls[i].move (d);
        for (unsigned i = 0; i < sizearr (balls); i++) balls[i].draw (true);

        txSleep (0);

        char s[100] = ""; sprintf (s, "%+03ld ms free", Time - GetTickCount());
        SetWindowText (txWindow(), s);

        while (GetTickCount() < Time) Sleep (0);
        }

    txEnd();

    _txExit = true;
    return 0;
    }
