#include "phase.h"

extern uint32_t zerocross_time_1 ;
extern uint32_t zerocross_time_2 ;
extern uint32_t zerocross_time_3 ;

PhaseSequence determine_phase_sequence(uint32_t zerocross_time_1, uint32_t zerocross_time_2, uint32_t zerocross_time_3) {
    if (zerocross_time_1 < zerocross_time_2 && zerocross_time_2 < zerocross_time_3) {
        return PHASE_ABC;
    } else if (zerocross_time_1 < zerocross_time_3 && zerocross_time_3 < zerocross_time_2) {
        return PHASE_ACB;
    } else if (zerocross_time_2 < zerocross_time_1 && zerocross_time_1 < zerocross_time_3) {
        return PHASE_BAC;
    } else if (zerocross_time_2 < zerocross_time_3 && zerocross_time_3 < zerocross_time_1) {
        return PHASE_BCA;
    } else if (zerocross_time_3 < zerocross_time_1 && zerocross_time_1 < zerocross_time_2) {
        return PHASE_CAB;
    } else if (zerocross_time_3 < zerocross_time_2 && zerocross_time_2 < zerocross_time_1) {
        return PHASE_CBA;
    } 
}

void map_phase_sequence_to_order(PhaseSequence phase, int *o1, int *o2, int *o3) {
    switch (phase) {
        case PHASE_ABC:
            *o1 = 0;
            *o2 = 1;
            *o3 = 2;
            break;
        case PHASE_ACB:
            *o1 = 0;
            *o2 = 2;
            *o3 = 1;
            break;
        case PHASE_BAC:
            *o1 = 1;
            *o2 = 0;
            *o3 = 2;
            break;
        case PHASE_BCA:
            *o1 = 1;
            *o2 = 2;
            *o3 = 0;
            break;
        case PHASE_CAB:
            *o1 = 2;
            *o2 = 0;
            *o3 = 1;
            break;
        case PHASE_CBA:
            *o1 = 2;
            *o2 = 1;
            *o3 = 0;
            break;
    }
}