/*
 *  tuioCursor.cpp
 *  oscReceiveForTuio
 *
 *  Created by Ranjit Bhatnagar on 1/30/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "tuioCursor.h"

bool tuioCursor::operator!=(tuioCursor a){
    return(this->s!=a.s);
}
bool tuioCursor::operator==(tuioCursor a){
    return(this->s==a.s);
}
bool tuioCursor::operator>(tuioCursor a){
    return(this->s>a.s);
}
bool tuioCursor::operator<(tuioCursor a){
    return(this->s<a.s);
}
