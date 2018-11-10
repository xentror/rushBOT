#ifndef GET_INPUT_H
#define GET_INPUT_H

enum event
{
    J1_LEFT = 0,
    J1_RIGHT,
    J1_FORWARD,
    J1_BACK,
    J1_SHOT,
    J2_LEFT,
    J2_RIGHT,
    J2_FORWARD,
    J2_BACK,
    J2_SHOT,
    NOTHING,
    QUIT
};

enum event get_input(void);


#endif /*  !GET_INPUT_H */
