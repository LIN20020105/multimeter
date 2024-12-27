#ifndef PHASE_H
#define PHASE_H
#include "main.h"

typedef enum {
    PHASE_ABC,
    PHASE_ACB,
    PHASE_BAC,
    PHASE_BCA,
    PHASE_CAB,
    PHASE_CBA,
    PHASE_UNKNOWN
} PhaseSequence;

PhaseSequence determine_phase_sequence(uint32_t zerocross_time_1, uint32_t zerocross_time_2, uint32_t zerocross_time_3);
void map_phase_sequence_to_order(PhaseSequence phase, int *o1, int *o2, int *o3);

#endif // PHASE_H