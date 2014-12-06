//
//  lines.h
//  createBoxFromLines
//
//  Created by Satoshi Ohtani on 12/6/14.
//  Copyright (c) 2014 Satoshi Ohtani. All rights reserved.
//

#ifndef __createBoxFromLines__lines__
#define __createBoxFromLines__lines__

#include <stdio.h>

class Line {
protected:
    long x1;
    long y1;
    long x2;
    long y2;

public:
    long getX1();
    long getY1();
    long getX2();
    long getY2();
    
    Line (long x1, long y1, long x2, long y2);
};

#endif /* defined(__createBoxFromLines__lines__) */
