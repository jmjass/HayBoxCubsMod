#ifndef _MODES_WINGMANFGCMODE_HPP
#define _MODES_WINGMANFGCMODE_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

class WingmanFgcMode : public ControllerMode {
  public:
    WingmanFgcMode(socd::SocdType horizontal_socd, socd::SocdType vertical_socd);

  private:
    void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);
};

#endif
