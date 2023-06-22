#ifndef _MODES_MELEEPUFF_HPP
#define _MODES_MELEEPUFF_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

typedef struct {
    bool crouch_walk_os = false;
} MeleePuffOptions;

class MeleePuff : public ControllerMode {
  public:
    MeleePuff(socd::SocdType socd_type, MeleePuffOptions options = {});

  protected:
    void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);

  private:
    MeleePuffOptions _options;
    bool _horizontal_socd;

    void HandleSocd(InputState &inputs);
};

#endif
