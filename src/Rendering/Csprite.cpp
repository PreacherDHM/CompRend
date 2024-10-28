#include "Csprite.h"

sprite sprite_create() {
    sprite s;
    s.bounds.x = 3;
    s.bounds.y = 3;
    s.position.x = 0;
    s.position.y = 0;
    s.data = "#*#***#*#";
    s.data_size = s.bounds.x * s.bounds.y;
    return s;
}

sprite sprite_create(int boundsX,int boundsY, const char* data) {
    sprite s;
    s.bounds.x = boundsX;
    s.bounds.y = boundsY;
    s.position.x = 0;
    s.position.y = 0;
    s.data = data;
    s.data_size = s.bounds.x * s.bounds.y;
    return sprite();
}

sprite sprite_create(int boundsX,int boundsY, int positionX, int positionY, const char* data) {
    sprite s;
    s.bounds.x = boundsX;
    s.bounds.y = boundsY;
    s.position.x = positionX;
    s.position.y = positionY;
    s.data = data;
    s.data_size = s.bounds.x * s.bounds.y;
    return sprite();
}
