//
// Created by Travis Milton on 12/10/15.
//

#include <iosfwd>
#include "Agent.h"

#include "Simple.h"

namespace Gaming {
    const char Simple::SIMPLE_ID = 'S';
    Simple::Simple(const Game &g, const Position &p, double energy): Agent( g, p, energy)
             {

    }

    Simple::~Simple() {

    }

    void Simple::print(std::ostream &os) const {//TODO
        os << SIMPLE_ID;

        
    }

    ActionType Simple::takeTurn(const Surroundings &s) const {
        auto it = s.array.begin();
        int index = 0;

        for (; it != s.array.end(); ++it) {
            if (*it == ADVANTAGE || *it == FOOD) {
                switch (index) {
                    case 0:
                        return NW;
                        break;
                    case 1:
                        return N;
                        break;
                    case 2:
                        return NE;
                        break;
                    case 3:
                        return W;
                        break;
                    case 4:
                        return STAY;
                        break;
                    case 5:
                        return E;
                        break;
                    case 6:
                        return SW;
                        break;
                    case 7:
                        return S;
                        break;
                    case 8:
                        return SE;
                        break;
                }
            }
            if (*it == EMPTY) {
                switch (index) {
                    case 0:
                        return NW;
                        break;
                    case 1:
                        return N;
                        break;
                    case 2:
                        return NE;
                        break;
                    case 3:
                        return W;
                        break;
                    case 4:
                        return STAY;
                        break;
                    case 5:
                        return E;
                        break;
                    case 6:
                        return SW;
                        break;
                    case 7:
                        return S;
                        break;
                    case 8:
                        return SE;
                        break;
                }
            }
            index++;
        }
        return STAY;
    }



    /*
     bool good = false;
     bool n = false, ss = false, sw = false, se = false, ne = false, nw = false, w = false, e = false;
     bool empty = false;
     bool n1 = false, ss1 = false, sw1 = false, se1 = false, ne1 = false, nw1 = false, w1 = false, e1 = false;
     Position P, O;
     O.x = 0;
     O.y = 0;
     ActionType A;
     std::vector<int> index{9, 8, 7, 6, 5, 4, 3, 2, 1};
     while (!good) {
         // if (n1 || n){if(ss1 || ss){if(sw1 || sw){
         //              if(se1 || se){if(ne1 || ne){if(nw1 || nw){
         //                        if(w1 || w){if(e1 || e){good = true;}}}}}}}}

         P = __game.randomPosition((const std::vector<int> &) index);
         A = __game.reachSurroundings(O, P);
         switch (A) {
             case N: {
                 if (!n) {
                     if (s.array[1] == ADVANTAGE) { good = true; }
                     if (s.array[1] == FOOD) { good = true; }
                     if (s.array[1] == STRATEGIC) {
                         good = false;
                         n = true;
                     }
                     if (s.array[1] == SIMPLE) {
                         good = false;
                         n = true;
                     }
                     if (s.array[1] == EMPTY) { //if(empty)
                         good = true;
                     }
                     break;
                 }
             }
             case NE: {
                 if (!ne) {
                     if (s.array[2] == ADVANTAGE) { good = true; }
                     if (s.array[2] == FOOD) { good = true; }
                     if (s.array[2] == STRATEGIC) {
                         good = false;
                         ne = true;
                     }
                     if (s.array[2] == SIMPLE) {
                         good = false;
                         ne = true;
                     }
                     if (s.array[2] == EMPTY) { good = true; }
                 }
                 break;
             }
             case NW: {
                 if (!nw) {
                     if (s.array[0] == ADVANTAGE) { good = true; }
                     if (s.array[0] == FOOD) { good = true; }
                     if (s.array[0] == STRATEGIC) {
                         good = false;
                         nw = true;
                     }
                     if (s.array[0] == SIMPLE) {
                         good = false;
                         nw = true;
                     }
                     if (s.array[0] == EMPTY) { good = true; }
                 }
                 break;

             }
             case E: {
                 if (!e) {
                     if (s.array[5] == ADVANTAGE) { good = true; }
                     if (s.array[5] == FOOD) { good = true; }
                     if (s.array[5] == STRATEGIC) {
                         good = false;
                         e = true;
                     }
                     if (s.array[5] == SIMPLE) {
                         good = false;
                         e = true;
                     }
                     if (s.array[5] == EMPTY) { good = true; }
                 }
                 break;
             }
             case W: {
                 if (!w) {
                     if (s.array[3] == ADVANTAGE) { good = true; }
                     if (s.array[3] == FOOD) { good = true; }
                     if (s.array[3] == STRATEGIC) {
                         good = false;
                         w = true;
                     }
                     if (s.array[3] == SIMPLE) {
                         good = false;
                         w = true;
                     }
                     if (s.array[3] == EMPTY) { good = true; }
                 }
                 break;
             }
             case SE: {
                 if (!se) {
                     if (s.array[8] == ADVANTAGE) { good = true; }
                     if (s.array[8] == FOOD) { good = true; }
                     if (s.array[8] == STRATEGIC) {
                         good = false;
                         se = true;
                     }
                     if (s.array[8] == SIMPLE) {
                         good = false;
                         se = true;
                     }
                     if (s.array[8] == EMPTY) { good = true; }
                     break;
                 }
                 case SW:
                     if (!sw) {
                         if (s.array[6] == ADVANTAGE) { good = true; }
                         if (s.array[6] == FOOD) { good = true; }
                         if (s.array[6] == STRATEGIC) {
                             good = false;
                             sw = true;
                         }
                         if (s.array[6] == SIMPLE) {
                             good = false;
                             sw = true;
                         }
                         if (s.array[6] == EMPTY) { good = true; }
                     }
                 break;
             }
             case S: {
                 if (!ss) {
                     if (s.array[7] == ADVANTAGE) { good = true; }
                     if (s.array[7] == FOOD) { good = true; }
                     if (s.array[7] == STRATEGIC) {
                         good = false;
                         ss = true;
                     }
                     if (s.array[7] == SIMPLE) {
                         good = false;
                         ss = true;
                     }
                     if (s.array[7] == EMPTY) { good = true; }
                 }
                 break;
             }

             case STAY: {
                 if (ss) {
                     if (se) {
                         if (sw) {
                             if (e) {
                                 if (w) {
                                     if (ne) {
                                         if (nw) {
                                             if (n) { good = true; }
                                         }
                                     }
                                 }
                             }

                         }
                     }
                 }
                 break;
             }
         }

     }
     return A;
 }*/
}
