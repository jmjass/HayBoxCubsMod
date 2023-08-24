#include "modes/WingmanFgcMode.hpp"

WingmanFgcMode::WingmanFgcMode(socd::SocdType horizontal_socd, socd::SocdType vertical_socd) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::left,   &InputState::right, horizontal_socd         },
 /* Mod X override C-Up input if both are pressed. Without this, neutral SOCD doesn't work
  properly if Down and both Up buttons are pressed, because it first resolves Down + Mod X
  to set both as unpressed, and then it sees C-Up as pressed but not Down, so you get an up
  input instead of neutral. */
        socd::SocdPair{ &InputState::mod_x, &InputState::c_up,  socd::SOCD_DIR1_PRIORITY},
        socd::SocdPair{ &InputState::down,  &InputState::mod_x, vertical_socd           },
        socd::SocdPair{ &InputState::down,  &InputState::c_up,  vertical_socd           },
    };
}

void WingmanFgcMode::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    // Directions
    outputs.dpadLeft = inputs.left;
    outputs.dpadRight = inputs.right;
    outputs.dpadDown = inputs.down;
    outputs.dpadUp = inputs.mod_x;
    outputs.leftStickClick = inputs.l;
    outputs.rightStickClick = inputs.a;

    // Menu keys
    outputs.start = inputs.start;
    outputs.select = inputs.c_left;
    outputs.home = inputs.c_down;

    // Right hand bottom row    
    outputs.a = inputs.x;
    outputs.b = inputs.b;
    outputs.triggerRDigital = inputs.z;
    outputs.triggerLDigital = inputs.up;

    // Right hand top row
    outputs.x = inputs.y;
    outputs.y = inputs.r;
    outputs.buttonR = inputs.lightshield;
    outputs.buttonL = inputs.midshield;
}

void WingmanFgcMode::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    outputs.leftStickX = 128;
    outputs.leftStickY = 128;
    outputs.rightStickX = 128;
    outputs.rightStickY = 128;
    outputs.triggerLAnalog = outputs.triggerLDigital ? 255 : 0;
    outputs.triggerRAnalog = outputs.triggerRDigital ? 255 : 0;
}
