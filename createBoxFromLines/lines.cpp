//
//  lines.cpp
//  createBoxFromLines
//
//  Created by Satoshi Ohtani on 12/6/14.
//  Copyright (c) 2014 Satoshi Ohtani. All rights reserved.
//

#include "lines.h"

Line::Line(long x1, long y1, long x2, long y2) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}

long Line::getX1() {
    return x1;
}

long Line::getY1() {
    return y1;
}

long Line::getX2() {
    return x2;
}

long Line::getY2() {
    return y2;
}

