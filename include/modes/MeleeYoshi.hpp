#ifndef _MODES_MELEEYOSHI_HPP
#define _MODES_MELEEYOSHI_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

typedef struct {
    bool crouch_walk_os = false;
} MeleeYoshiOptions;

class MeleeYoshi : public ControllerMode {
  public:
    MeleeYoshi(socd::SocdType socd_type, MeleeYoshiOptions options = {});

  protected:
    void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);

  private:
    MeleeYoshiOptions _options;
    bool _horizontal_socd;

    void HandleSocd(InputState &inputs);
};

#endif
