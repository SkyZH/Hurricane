//
// Created by Alex Chi on 2018/11/22.
//

#ifndef HURRICANE_ARMBASE_H
#define HURRICANE_ARMBASE_H

#include "CAHRR/src/PIDAccumulator.h"
#include "CAHRR/src/RampAccumulator.h"
#include "CAHRR/src/RotateAccumulator.h"
#include "CAHRR/src/DeltaAccumulator.h"
#include "CAHRR/src/AvgAccumulator.h"
#include "hal.h"

class ArmBase {
private:
    PIDDisplacementAccumulator pid_position;
    PIDRateAccumulator pid_rate;
    RampAccumulator<double> ramp;
    RotateAccumulator accumulator;
    AvgAccumulator<double> speed;
    const double spd_limit, cur_limit, Kf;

protected:
    double target_pos;
    int16_t target_output;
    double current_pos, target_spd, current_spd, target_current;
public:
    ArmBase(double spd_p, double spd_i, double spd_d, double cur_limit, double pos_p, double pos_i, double pos_d,
            double spd_limit, double ramp_limit, double feed_forward);

    double real_angle();

    double expected_pos(double angle);

    bool initialize();

    bool destroy();

    bool update();

    bool feed(int16_t ang, int16_t spd);

    int16_t output();

    bool set_pos(double pos);

    virtual double feed_forward() { return 0; }
};


#endif //HURRICANE_ARMBASE_H
