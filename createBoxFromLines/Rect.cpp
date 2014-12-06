//
//  Rect.cpp
//  createBoxFromLines
//
//  Created by Satoshi Ohtani on 12/6/14.
//  Copyright (c) 2014 Satoshi Ohtani. All rights reserved.
//

#include "Rect.h"

Rect::Rect (long x1, long y1, long x2, long y2) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}

long Rect::getX1() {
    return x1;
}

long Rect::getY1() {
    return y1;
}

long Rect::getX2() {
    return x2;
}

long Rect::getY2() {
    return y2;
}

