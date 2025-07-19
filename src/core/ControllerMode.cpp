#include "core/ControllerMode.hpp"
#include "input/GamecubeControllerInput.hpp"

ControllerMode::ControllerMode() {
    // Set up initial state.
    ResetDirections();
}

void ControllerMode::UpdateOutputs(InputState &inputs, OutputState &outputs) {
    HandleSocd(inputs);
    UpdateDigitalOutputs(inputs, outputs);
    UpdateAnalogOutputs(inputs, outputs);
    ResetController(inputs, outputs);
}

void ControllerMode::ResetDirections() {
    directions = {
        .horizontal = false,
        .vertical = false,
        .diagonal = false,
        .x = 0,
        .y = 0,
        .cx = 0,
        .cy = 0,
    };
}

void ControllerMode::UpdateDirections(
    bool lsLeft,
    bool lsRight,
    bool lsDown,
    bool lsUp,
    bool rsLeft,
    bool rsRight,
    bool rsDown,
    bool rsUp,
    uint8_t analogStickMin,
    uint8_t analogStickNeutral,
    uint8_t analogStickMax,
    OutputState &outputs
) {
    ResetDirections();

    outputs.leftStickX = analogStickNeutral;
    outputs.leftStickY = analogStickNeutral;
    outputs.rightStickX = analogStickNeutral;
    outputs.rightStickY = analogStickNeutral;

    // Coordinate calculations to make modifier handling simpler.
    if (lsLeft || lsRight) {
        directions.horizontal = true;
        if (lsLeft) {
            directions.x = -1;
            outputs.leftStickX = analogStickMin;
        } else {
            directions.x = 1;
            outputs.leftStickX = analogStickMax;
        }
    }
    if (lsDown || lsUp) {
        directions.vertical = true;
        if (lsDown) {
            directions.y = -1;
            outputs.leftStickY = analogStickMin;
        } else {
            directions.y = 1;
            outputs.leftStickY = analogStickMax;
        }
    }
    if (directions.horizontal && directions.vertical)
        directions.diagonal = true;

    if (rsLeft || rsRight) {
        if (rsLeft) {
            directions.cx = -1;
            outputs.rightStickX = analogStickMin;
        } else {
            directions.cx = 1;
            outputs.rightStickX = analogStickMax;
        }
    }
    if (rsDown || rsUp) {
        if (rsDown) {
            directions.cy = -1;
            outputs.rightStickY = analogStickMin;
        } else {
            directions.cy = 1;
            outputs.rightStickY = analogStickMax;
        }
    }
}

bool ResetCall();
int resetDelay = 0;
void ControllerMode::ResetController(InputState &inputs, OutputState &outputs){
    //if user holds x + y + start
    if(outputs.x && outputs.y && outputs.start){
        //add delay to reset to ensure it doesnt spam the console/doesnt happpen by accident
        resetDelay++;
        if(resetDelay >= 100){
            //call for origin reset and reset counter
            ResetCall();
            resetDelay = 0;
        }
    }
}
