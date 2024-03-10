#include <math.h>
#include <stdint.h>
#include "structdef.h"
#include "utility.h"

unsigned long dedaf_solve_injection_delay(
    struct table_cell *table_CELLS,
    unsigned int cell_count,
    float throttle,
    float rpm)
{
    // Don't do anything if table is empty
    if (!cell_count)
        return 0;
    // We want closest cell to current coordinate, as possible.
    // Let's find out the constraints
    float min_throttle_constraint = -INFINITY;
    float min_rpm_constraint = -INFINITY;
    float max_throttle_constraint = INFINITY;
    float max_rpm_constraint = INFINITY;
    // ...so we have to solve 4 closest cell based on
    // throttle and RPM value
    for (int i = 0; i < cell_count; i++)
    {
        struct table_cell *current_cell = &(table_CELLS[i]);
        if (current_cell->throttle <= throttle && current_cell->throttle >= min_throttle_constraint)
            min_throttle_constraint = current_cell->throttle;
        if (current_cell->throttle >= throttle && current_cell->throttle <= max_throttle_constraint)
            max_throttle_constraint = current_cell->throttle;
        if (current_cell->rpm <= rpm && current_cell->rpm >= min_rpm_constraint)
            min_rpm_constraint = current_cell->rpm;
        if (current_cell->rpm >= rpm && current_cell->rpm <= max_rpm_constraint)
            max_rpm_constraint = current_cell->rpm;
    }
    /*
    Mathematically, we map those variable names to be:
      min_throttle_constraint -> x1
           min_rpm_constraint -> y1
      max_throttle_constraint -> x2
           max_rpm_constraint -> y2
    */
    // Throttle is horizontal, RPM is vertical
    struct table_cell *top_left = NULL;
    struct table_cell *top_right = NULL;
    struct table_cell *bottom_left = NULL;
    struct table_cell *bottom_right = NULL;
    for (int i = 0; i < cell_count; i++)
    {
        struct table_cell *current_cell = &(table_CELLS[i]);
        if (!top_left || (current_cell->throttle <= throttle && current_cell->throttle >= min_throttle_constraint && current_cell->rpm <= rpm && current_cell->rpm >= min_rpm_constraint))
        {
            top_left = current_cell;
        }
        if (!top_right || (current_cell->throttle >= throttle && current_cell->throttle <= max_throttle_constraint && current_cell->rpm <= rpm && current_cell->rpm >= min_rpm_constraint))
        {
            top_right = current_cell;
        }
        if (!bottom_left || (current_cell->throttle <= throttle && current_cell->throttle >= min_throttle_constraint && current_cell->rpm >= rpm && current_cell->rpm <= max_rpm_constraint))
        {
            bottom_left = current_cell;
        }
        if (!bottom_right || (current_cell->throttle >= throttle && current_cell->throttle <= max_throttle_constraint && current_cell->rpm >= rpm && current_cell->rpm <= max_rpm_constraint))
        {
            bottom_right = current_cell;
        }
    }
    /*
    Those CELLS are now transpose of a matrix. Thus, we got:
         __                         __     __       __
        |   top_left     bottom_left  |   | Q11   Q12 |
    Q = |                             | = |           |
        |   top_right    bottom_right |   | Q21   Q22 |
         ‾‾                         ‾‾     ‾‾       ‾‾
    See Bilinear Interpolation:
      https://en.wikipedia.org/wiki/Bilinear_interpolation#Repeated_linear_interpolation
    */
    return (
        (1 / ((max_throttle_constraint - min_throttle_constraint) * (max_rpm_constraint - min_rpm_constraint))) * ((top_left->injection * (max_throttle_constraint - throttle) * (max_rpm_constraint - rpm)) + (top_right->injection * (throttle - min_throttle_constraint) * (max_rpm_constraint - rpm)) + (bottom_left->injection * (max_throttle_constraint - throttle) * (rpm - min_rpm_constraint)) + (bottom_right->injection * (throttle - min_throttle_constraint) * (rpm - min_rpm_constraint))));
}