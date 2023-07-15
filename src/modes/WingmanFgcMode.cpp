#include "modes/WingmanFgcMode.hpp"

WingmanFgcMode::WingmanFgcMode(socd::SocdType socd_type) : ControllerMode(socd_type) {
    _socd_pair_count = 1;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::left, &InputState::right},
    };
}

void WingmanFgcMode::HandleSocd(InputState &inputs) {
    if (inputs.down && (inputs.mod_x)) {
        inputs.down = false;
        inputs.mod_x = false;
    }
    InputMode::HandleSocd(inputs);
}

void WingmanFgcMode::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    // Directions
    outputs.dpadLeft = inputs.left;
    outputs.dpadRight = inputs.right;
    outputs.dpadDown = inputs.down;
    outputs.dpadUp = inputs.mod_x;
    outputs.leftStickClick = inputs.a;
    outputs.rightStickClick = inputs.c_up;

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
