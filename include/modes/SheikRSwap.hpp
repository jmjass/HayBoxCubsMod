#ifndef _MODES_SHEIKRSWAP_HPP
#define _MODES_SHEIKRSWAP_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

typedef struct {
    bool crouch_walk_os = true;
} SheikRSwapOptions;

class SheikRSwap : public ControllerMode {
  public:
    SheikRSwap(socd::SocdType socd_type, SheikRSwapOptions options = {});

  protected:
    void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);

  private:
    SheikRSwapOptions _options;
    bool _horizontal_socd;

    void HandleSocd(InputState &inputs);
};

#endif
