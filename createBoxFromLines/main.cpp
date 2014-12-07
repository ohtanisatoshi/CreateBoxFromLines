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
            // if there has been a longer line than hline2, end the loop and proceed to nect hlines.
            Line hline2 = hlines[h2];
            int i;
            for (i = h1+1; i < h2; i++) {
                Line hLineToCheck = hlines[i];
                if (hLineToCheck.getX1() <= hline2.getX1() && hline2.getX2() <= hLineToCheck.getX2()) {
                    break;
                }
            }
            if (i < h2) {
                break;
            }
            
            for (int v1 = 0; v1 < vlines.size()-1; v1++) {
                Line vline1 = vlines[v1];
                for (int v2 = v1+1; v2 < vlines.size(); v2++) {
                    Line vline2 = vlines[v2];
                    map<int, int>::iterator it = match_vlines.find(v1);
                    if (it != match_vlines.end() && it->second == v2) {
                        // to avoid duplicate
                        // if the pair of vertical lines has been already used
                        //    and the vline2 crosses over hlies, go to next vline1
                        // if the pair of vertical lines has been already used
                        //    and the vline2 does not cross over hlies, go to next vline2
                        long x, y;
                        if (getCrossPoint(hline2, vline2, &x, &y)) {
                            break;
                        } else {
                            continue;
                        }
                    }
                    
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
//                        bool unnecessary = false;
//                        if (v2-v1 > 1) {
//                            // to avoid duplicate rect
//                            int i;
//                            for (i = v1; v1 < v2-1; i ++) {
//                                map<int, int>::iterator it = match_vlines.find(i);
//                                if (it == match_vlines.end() || it->second != i+1) {
//                                    break;
//                                } else {
//                                    long x, y;
//                                    Line vLineToCheck = vlines[i+1];
//                                    if (getCrossPoint(hline2, vLineToCheck, &x, &y) == false) {
//                                        break;
//                                    }
//                                }
//                            }
//                            if (i == v2) {
//                                unnecessary = true;
//                            }
//                        }
//                        
//                        if (unnecessary == false) {
                            // create rect
                            Rect r(x1, y1, x4, y4);
                            rect->push_back(r);
//                        }
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
    {
        vector<Line> hlines;
        vector<Line> vlines;
        
        Line hline1(10,10,60,10);
        hlines.push_back(hline1);
        Line hline2(10,20,20,20);
        hlines.push_back(hline2);
        Line hline3(50,20,60,20);
        hlines.push_back(hline3);
        Line hline4(30,30,40,30);
        hlines.push_back(hline4);
        Line hline5(10,40,60,40);
        hlines.push_back(hline5);
        
        Line vline1(10,10,10,40);
        vlines.push_back(vline1);
        Line vline2(20,10,20,20);
        vlines.push_back(vline2);
        Line vline3(30,30,30,40);
        vlines.push_back(vline3);
        Line vline4(40,30,40,40);
        vlines.push_back(vline4);
        Line vline5(50,10,50,20);
        vlines.push_back(vline5);
        Line vline6(60,10,60,40);
        vlines.push_back(vline6);
        
        vector<Rect> rects;
        createBox(hlines, vlines, &rects);
        // 10,10,20,20
        // 50,10,60,20
        // 10,10,60,40
        // 30,30,40,40
        cout << "*** Test 1 ***" << endl;
        for (std::vector<Rect>::iterator it=rects.begin(); it != rects.end(); it ++) {
            cout << (*it).getX1() << "," << (*it).getY1() << "," << (*it).getX2() << "," << (*it).getY2() << endl;
        }
    }
    {
        vector<Line> hlines;
        vector<Line> vlines;
        
        Line hline1(10,10,30,10);
        hlines.push_back(hline1);
        Line hline2(10,20,30,20);
        hlines.push_back(hline2);
        Line hline3(10,30,30,30);
        hlines.push_back(hline3);
        
        Line vline1(10,10,10,30);
        vlines.push_back(vline1);
        Line vline2(20,10,20,30);
        vlines.push_back(vline2);
        Line vline3(30,10,30,30);
        vlines.push_back(vline3);
        
        vector<Rect> rects;
        createBox(hlines, vlines, &rects);
        // 10,10,20,20
        // 20,10,30,20
        // 10,20,20,30
        // 20,20,30,30
        cout << "*** Test 2 ***" << endl;
        for (std::vector<Rect>::iterator it=rects.begin(); it != rects.end(); it ++) {
            cout << (*it).getX1() << "," << (*it).getY1() << "," << (*it).getX2() << "," << (*it).getY2() << endl;
        }
    }
    {
        vector<Line> hlines;
        vector<Line> vlines;
        
        Line hline1(10,10,30,10);
        hlines.push_back(hline1);
        Line hline2(10,20,30,20);
        hlines.push_back(hline2);
        Line hline3(10,30,30,30);
        hlines.push_back(hline3);
        
        Line vline1(10,10,10,30);
        vlines.push_back(vline1);
        Line vline2(20,10,20,20);
        vlines.push_back(vline2);
        Line vline3(30,10,30,30);
        vlines.push_back(vline3);
        
        vector<Rect> rects;
        createBox(hlines, vlines, &rects);
        // 10,10,20,20
        // 20,10,30,20
        // 10,20,30,30
        cout << "*** Test 3 ***" << endl;
        for (std::vector<Rect>::iterator it=rects.begin(); it != rects.end(); it ++) {
            cout << (*it).getX1() << "," << (*it).getY1() << "," << (*it).getX2() << "," << (*it).getY2() << endl;
        }
    }
    {
        vector<Line> hlines;
        vector<Line> vlines;
        
        Line hline1(10,10,30,10);
        hlines.push_back(hline1);
        Line hline2(10,20,30,20);
        hlines.push_back(hline2);
        Line hline3(10,30,30,30);
        hlines.push_back(hline3);
        
        Line vline1(10,10,10,30);
        vlines.push_back(vline1);
        Line vline2(20,20,20,30);
        vlines.push_back(vline2);
        Line vline3(30,10,30,30);
        vlines.push_back(vline3);
        
        vector<Rect> rects;
        createBox(hlines, vlines, &rects);
        // 10,10,30,20
        // 10,20,20,30
        // 20,20,30,30
        cout << "*** Test 4 ***" << endl;
        for (std::vector<Rect>::iterator it=rects.begin(); it != rects.end(); it ++) {
            cout << (*it).getX1() << "," << (*it).getY1() << "," << (*it).getX2() << "," << (*it).getY2() << endl;
        }
    }
    {
        vector<Line> hlines;
        vector<Line> vlines;
        
        Line hline1(10,10,30,10);
        hlines.push_back(hline1);
        Line hline2(10,20,20,20);
        hlines.push_back(hline2);
        Line hline3(10,30,30,30);
        hlines.push_back(hline3);
        
        Line vline1(10,10,10,30);
        vlines.push_back(vline1);
        Line vline2(20,10,20,30);
        vlines.push_back(vline2);
        Line vline3(30,10,30,30);
        vlines.push_back(vline3);
        
        vector<Rect> rects;
        createBox(hlines, vlines, &rects);
        // 10,10,20,20
        // 20,10,30,30
        // 10,20,20,30
        cout << "*** Test 5 ***" << endl;
        for (std::vector<Rect>::iterator it=rects.begin(); it != rects.end(); it ++) {
            cout << (*it).getX1() << "," << (*it).getY1() << "," << (*it).getX2() << "," << (*it).getY2() << endl;
        }
    }
    {
        vector<Line> hlines;
        vector<Line> vlines;
        
        Line hline1(10,10,30,10);
        hlines.push_back(hline1);
        Line hline2(20,20,30,20);
        hlines.push_back(hline2);
        Line hline3(10,30,30,30);
        hlines.push_back(hline3);
        
        Line vline1(10,10,10,30);
        vlines.push_back(vline1);
        Line vline2(20,10,20,30);
        vlines.push_back(vline2);
        Line vline3(30,10,30,30);
        vlines.push_back(vline3);
        
        vector<Rect> rects;
        createBox(hlines, vlines, &rects);
        // 20,10,30,20
        // 10,10,20,30
        // 20,20,30,30
        cout << "*** Test 6 ***" << endl;
        for (std::vector<Rect>::iterator it=rects.begin(); it != rects.end(); it ++) {
            cout << (*it).getX1() << "," << (*it).getY1() << "," << (*it).getX2() << "," << (*it).getY2() << endl;
        }
    }
    {
        vector<Line> hlines;
        vector<Line> vlines;
        
        Line hline1(10,10,30,10);
        hlines.push_back(hline1);
        Line hline2(10,20,20,20);
        hlines.push_back(hline2);
        Line hline3(10,30,30,30);
        hlines.push_back(hline3);
        
        Line vline1(10,10,10,30);
        vlines.push_back(vline1);
        Line vline2(20,10,20,20);
        vlines.push_back(vline2);
        Line vline3(30,10,30,30);
        vlines.push_back(vline3);
        
        vector<Rect> rects;
        createBox(hlines, vlines, &rects);
        // 10,10,20,20
        // 10,10,30,30
        cout << "*** Test 7 ***" << endl;
        for (std::vector<Rect>::iterator it=rects.begin(); it != rects.end(); it ++) {
            cout << (*it).getX1() << "," << (*it).getY1() << "," << (*it).getX2() << "," << (*it).getY2() << endl;
        }
    }
    {
        vector<Line> hlines;
        vector<Line> vlines;
        
        Line hline1(10,10,30,10);
        hlines.push_back(hline1);
        Line hline2(20,20,30,20);
        hlines.push_back(hline2);
        Line hline3(10,30,30,30);
        hlines.push_back(hline3);
        
        Line vline1(10,10,10,30);
        vlines.push_back(vline1);
        Line vline2(20,10,20,20);
        vlines.push_back(vline2);
        Line vline3(30,10,30,30);
        vlines.push_back(vline3);
        
        vector<Rect> rects;
        createBox(hlines, vlines, &rects);
        // 20,10,30,20
        // 10,10,30,30
        cout << "*** Test 8 ***" << endl;
        for (std::vector<Rect>::iterator it=rects.begin(); it != rects.end(); it ++) {
            cout << (*it).getX1() << "," << (*it).getY1() << "," << (*it).getX2() << "," << (*it).getY2() << endl;
        }
    }
    {
        vector<Line> hlines;
        vector<Line> vlines;
        
        Line hline1(10,10,30,10);
        hlines.push_back(hline1);
        Line hline2(10,20,20,20);
        hlines.push_back(hline2);
        Line hline3(10,30,30,30);
        hlines.push_back(hline3);
        
        Line vline1(10,10,10,30);
        vlines.push_back(vline1);
        Line vline2(20,20,20,30);
        vlines.push_back(vline2);
        Line vline3(30,10,30,30);
        vlines.push_back(vline3);
        
        vector<Rect> rects;
        createBox(hlines, vlines, &rects);
        // 10,10,30,30
        // 10,20,20,30
        cout << "*** Test 9 ***" << endl;
        for (std::vector<Rect>::iterator it=rects.begin(); it != rects.end(); it ++) {
            cout << (*it).getX1() << "," << (*it).getY1() << "," << (*it).getX2() << "," << (*it).getY2() << endl;
        }
    }
    {
        vector<Line> hlines;
        vector<Line> vlines;
        
        Line hline1(10,10,30,10);
        hlines.push_back(hline1);
        Line hline2(20,20,30,20);
        hlines.push_back(hline2);
        Line hline3(10,30,30,30);
        hlines.push_back(hline3);
        
        Line vline1(10,10,10,30);
        vlines.push_back(vline1);
        Line vline2(20,20,20,30);
        vlines.push_back(vline2);
        Line vline3(30,10,30,30);
        vlines.push_back(vline3);
        
        vector<Rect> rects;
        createBox(hlines, vlines, &rects);
        // 10,10,30,30
        // 20,20,30,30
        cout << "*** Test 10 ***" << endl;
        for (std::vector<Rect>::iterator it=rects.begin(); it != rects.end(); it ++) {
            cout << (*it).getX1() << "," << (*it).getY1() << "," << (*it).getX2() << "," << (*it).getY2() << endl;
        }
    }
    {
        vector<Line> hlines;
        vector<Line> vlines;
        
        Line hline1(10,10,50,10);
        hlines.push_back(hline1);
        Line hline2(10,20,50,20);
        hlines.push_back(hline2);
        Line hline3(10,30,50,30);
        hlines.push_back(hline3);
        
        Line vline1(10,10,10,30);
        vlines.push_back(vline1);
        Line vline2(20,10,20,20);
        vlines.push_back(vline2);
        Line vline3(30,10,30,20);
        vlines.push_back(vline3);
        Line vline4(40,10,40,20);
        vlines.push_back(vline4);
        Line vline5(50,10,50,30);
        vlines.push_back(vline5);
        
        vector<Rect> rects;
        createBox(hlines, vlines, &rects);
        // 10,10,20,20
        // 20,10,30,20
        // 30,10,40,20
        // 40,10,50,20
        // 10,20,50,30
        cout << "*** Test 11 ***" << endl;
        for (std::vector<Rect>::iterator it=rects.begin(); it != rects.end(); it ++) {
            cout << (*it).getX1() << "," << (*it).getY1() << "," << (*it).getX2() << "," << (*it).getY2() << endl;
        }
    }

    return 0;
}
