#ifndef _MODES_MARTHRSWAP_HPP
#define _MODES_MARTHRSWAP_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

typedef struct {
    bool crouch_walk_os = true;
} MarthRSwapOptions;

class MarthRSwap : public ControllerMode {
  public:
    MarthRSwap(socd::SocdType socd_type, MarthRSwapOptions options = {});

  protected:
    void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);

  private:
    MarthRSwapOptions _options;
    bool _horizontal_socd;

    void HandleSocd(InputState &inputs);
};

#endif
