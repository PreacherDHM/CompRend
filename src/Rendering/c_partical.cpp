#include "c_partical.h"

void cpartical_emmiter_create(cpartical_emmiter* cpe) {
    cpe->position = {0,0};
}
void cpartical_emmiter_start(cpartical_emmiter *cpe, float rate) {
    
}
void cpartical_emmiter_stop(cpartical_emmiter *cpe) {}
void cpartical_emmiter_set_direction(cpartical_emmiter *cpe, float direction, float margin) {}
void cpartical_emmiter_dispence(cpartical_emmiter *cpe, int partical_amount, float elaped_sec) {}
