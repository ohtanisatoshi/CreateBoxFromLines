//
//  main.cpp
//  createBoxFromLines
//
//  Created by Satoshi Ohtani on 12/6/14.
//  Copyright (c) 2014 Satoshi Ohtani. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include "lines.h"
#include "Rect.h"

using namespace std;

void createBox(vector<Line> hlines, vector<Line> vlines, vector<Rect> *rect);

bool getCrossPoint(Line hline, Line vline, long *x, long *y) {
    *x = -1;
    *y = -1;
    if (hline.getX1() <= vline.getX1() && vline.getX1() <= hline.getX2()) {
        *x = vline.getX1();
    }
    if (vline.getY1() <= hline.getY1() && hline.getY1() <= vline.getY2()) {
        *y = hline.getY1();
    }
    
    if (*x != -1 && *y != -1) {
        return true;
    } else {
        return false;
    }
}

void createBox(vector<Line> hlines, vector<Line> vlines, vector<Rect> *rect) {
    if (hlines.size() < 2 || vlines.size() < 2) {
        return;
    }
    
    Line hline1 = hlines[0];
    for (int h1 = 0; h1 < hlines.size()-1; h1 ++) {
        hline1 = hlines[h1];
        map<int, int> match_vlines;
        for(int h2 = h1+1; h2 < hlines.size(); h2++) {
            // loop of horizontal lines
            Line hline2 = hlines[h2];
            
            for (int v1 = 0; v1 < vlines.size()-1; v1++) {
                Line vline1 = vlines[v1];
                for (int v2 = v1+1; v2 < vlines.size(); v2++) {
                    map<int, int>::iterator it = match_vlines.find(v1);
                    if (it != match_vlines.end() && it->second == v2) {
                        // to avoid duplicate
                        continue;
                    }
                    
                    Line vline2 = vlines[v2];
                    long x1;
                    long y1;
                    long x2;
                    long y2;
                    long x3;
                    long y3;
                    long x4;
                    long y4;
                    bool r1 = getCrossPoint(hline1, vline1, &x1, &y1);
                    bool r2 = getCrossPoint(hline1, vline2, &x2, &y2);
                    bool r3 = getCrossPoint(hline2, vline1, &x3, &y3);
                    bool r4 = getCrossPoint(hline2, vline2, &x4, &y4);
                    
                    if (r1 == true && r2 == true && r3 == true && r4 == true) {
                        bool unnecessary = false;
                        if (v2-v1 > 1) {
                            // to avoid duplicate rect
                            int i;
                            for (i = v1; v1 < v2-1; i ++) {
                                map<int, int>::iterator it = match_vlines.find(i);
                                if (it == match_vlines.end() || it->second != i+1) {
                                    break;
                                }
                            }
                            if (i == v2) {
                                unnecessary = true;
                            }
                        }
                        
                        if (unnecessary == false) {
                            // create rect
                            Rect r(x1, y1, x4, y4);
                            rect->push_back(r);
                        }
                        match_vlines[v1] = v2;
                        v1 = v2 - 1;
                        break;                        
                    }
                }
            }
        }
    }
    
    return;
}

int main(int argc, const char * argv[]) {
    vector<Line> hlines;
    vector<Line> vlines;
    
    Line hline1 = Line(10,100,110,100);
    hlines.push_back(hline1);
    Line hline2(10,200,110,200);
    hlines.push_back(hline2);
    Line hline3(10,210,110,210);
    hlines.push_back(hline3);
    
    Line vline1(20,80,20,220);
    vlines.push_back(vline1);
    Line vline2(90,80,90,220);
    vlines.push_back(vline2);
    Line vline3(100,80,100,220);
    vlines.push_back(vline3);
    
    vector<Rect> rects;
    createBox(hlines, vlines, &rects);
    for (std::vector<Rect>::iterator it=rects.begin(); it != rects.end(); it ++) {
        cout << (*it).getX1() << "," << (*it).getY1() << "," << (*it).getX2() << "," << (*it).getY2() << endl;
    }
    return 0;
}
