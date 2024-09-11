
#include "../../inc/cub.h"
#include <math.h>

typedef struct s_dvector{
    double x;
    double y;
}t_dvector;

double vector_norm(t_dvector a)
{
    double norm;

    norm = sqrt(pow(a.x,2) + pow(a.y,2));
    return (norm);
}

t_dvector vector_rot(t_vector a, double rotation)
{
    /*
        cosx     sin(rotatiom)y
        sinx     cos()y
    */
   t_dvector rotated;

    rotated.x = (cos(rotation * a.x) - sin(rotation * a.y));
    rotated.y = (sin(rotation * a.x) + cos(rotation * a.y));
    return (rotated);
}


