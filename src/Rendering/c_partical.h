#ifndef C_PARTICAL_H
#define C_PARTICAL_H

#define C_PARTICAL_COUNT_MAX 100

struct cposition {
    float x;
    float y;
};

struct cvelocity {
    float direction;
    float velocity;
};

typedef struct {
    struct cposition position;
    int render_index;
    float time;
    int id;
    
} cpartical;

typedef struct {
    int partical_count;
    int render_data_size;
    float min_angle;
    float max_angle;
    const char* render_data;
    const char* cpartical_script;
    cposition position;
    cpartical particals[C_PARTICAL_COUNT_MAX];

} cpartical_emmiter;


/*==============================
 *  functions
 *============================== */

/// **cpartical emmiter create**
///
/// This creates a emmiter.
void cpartical_emmiter_create(cpartical_emmiter*);
/// **Cpartical emmiter start**
///
/// cpartical emmiter start takes a partical emmiter and a rate 
/// *particals per second*
void cpartical_emmiter_start(cpartical_emmiter*, float);
/// **cpartical emmiter stop**
///
/// stops the emmition of particals.
void cpartical_emmiter_stop(cpartical_emmiter*);
/// **cpartical emmiter dispance**
///
/// Takes amount of partical to dispance and dispences 
/// them over a piread of time.
void cpartical_emmiter_dispence(cpartical_emmiter*, int, float);
/// **cpartical emmiter update**
///
/// Updates partical behavier
void cpartical_emmiter_update(cpartical_emmiter*);

/*==============================
 *  Setters
 *============================== */

/// **cpartical emmiter set direction**
///
/// sets the direction of the emmiter with a direction and a margin in degries.
/// *this makes a cone*
void cpartical_emmiter_set_direction(cpartical_emmiter*, float, float);


#endif
