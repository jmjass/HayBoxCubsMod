#ifndef _MODES_FALCOMODE_HPP
#define _MODES_FALCOMODE_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

typedef struct {
    bool crouch_walk_os = false;
} FalcoModeOptions;

class FalcoMode : public ControllerMode {
  public:
    FalcoMode(socd::SocdType socd_type, FalcoModeOptions options = {});

  protected:
    void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);

  private:
    FalcoModeOptions _options;
    bool _horizontal_socd;

    void HandleSocd(InputState &inputs);
};

#endif
