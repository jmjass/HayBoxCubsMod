#ifndef _MODES_MELEETOPHOMEROW_HPP
#define _MODES_MELEETOPHOMEROW_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

typedef struct {
    bool crouch_walk_os = false;
} MeleeTopHomeRowOptions;

class MeleeTopHomeRow : public ControllerMode {
  public:
    MeleeTopHomeRow(socd::SocdType socd_type, MeleeTopHomeRowOptions options = {});

  protected:
    void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);

  private:
    MeleeTopHomeRowOptions _options;
    bool _horizontal_socd;

    void HandleSocd(InputState &inputs);
};

#endif
