//
//  Rect.h
//  createBoxFromLines
//
//  Created by Satoshi Ohtani on 12/6/14.
//  Copyright (c) 2014 Satoshi Ohtani. All rights reserved.
//

#ifndef __createBoxFromLines__Rect__
#define __createBoxFromLines__Rect__

#include <stdio.h>

class Rect {
protected:
    long x1;
    long y1;
    long x2;
    long y2;
public:
    Rect(long x1, long y1, long x2, long y2);
    long getX1();
    long getY1();
    long getX2();
    long getY2();
};

#endif /* defined(__createBoxFromLines__Rect__) */
