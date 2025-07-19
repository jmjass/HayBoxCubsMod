#include "modes/MeleeRSwap.hpp"

#define ANALOG_STICK_MIN 48
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 208

MeleeRSwap::MeleeRSwap(socd::SocdType socd_type, MeleeRSwapOptions options) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::left,    &InputState::right  },
        socd::SocdPair{ &InputState::down,   &InputState::up     },
        socd::SocdPair{ &InputState::c_left, &InputState::c_right},
        socd::SocdPair{ &InputState::c_down, &InputState::c_up   },
    };

    _options = options;
    _horizontal_socd = false;
}

void MeleeRSwap::HandleSocd(InputState &inputs) {
    _horizontal_socd = inputs.left && inputs.right;
    InputMode::HandleSocd(inputs);
}

void MeleeRSwap::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    outputs.a = inputs.a;
    outputs.b = inputs.r;
    outputs.x = inputs.x;
    outputs.y = inputs.y;
    outputs.buttonR = inputs.z;
    if (inputs.nunchuk_connected) {
        outputs.triggerLDigital = inputs.nunchuk_z;
    } else {
        outputs.triggerLDigital = inputs.l;
    }
    outputs.triggerRDigital = inputs.b;
    outputs.start = inputs.start;

    if (inputs.nunchuk_connected) {
        outputs.start = inputs.nunchuk_start;
        outputs.dpadLeft = inputs.nunchuk_dleft;
        outputs.dpadRight = inputs.nunchuk_dright;
        outputs.dpadUp = inputs.nunchuk_dup;
        outputs.dpadDown = inputs.nunchuk_ddown;
     }


    if (inputs.select)
        outputs.dpadLeft = true;
    if (inputs.home)
        outputs.dpadRight = true;
}

void MeleeRSwap::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    // Coordinate calculations to make modifier handling simpler.
    UpdateDirections(
        inputs.left,
        inputs.right,
        inputs.down,
        inputs.up,
        inputs.c_left,
        inputs.c_right,
        inputs.c_down,
        inputs.c_up,
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );
    //Output L analog from controller along with Right side LSMS
    outputs.triggerLAnalog = inputs.l_analog;

    // C-stick ASDI Slideoff angle overrides any other C-stick modifiers (such as
    // angled fsmash).
    if (directions.cx != 0 && directions.cy != 0) {
        // 5250 8500 = 42 68
        outputs.rightStickX = 128 + (directions.cx * 42);
        outputs.rightStickY = 128 + (directions.cy * 68);
    }

    //rotational c stick modifier for angled smashes
    //c right = down right fsmash
    /*if (inputs.z && directions.cx == 1) {
        // 5250 8500 = 42 68
        outputs.rightStickX = 128 + (1 * 68);
        outputs.rightStickY = 128 + (-1 * 47);
    }
    //c up = up right fsmash
    if (inputs.z && directions.cy == 1) {
        // 5250 8500 = 42 68
        outputs.rightStickX = 128 + (1 * 68);
        outputs.rightStickY = 128 + (1 * 47);
    }
    //c left = up left fsmash
    if (inputs.z && directions.cx == -1) {
        // 5250 8500 = 42 68
        outputs.rightStickX = 128 + (-1 * 68);
        outputs.rightStickY = 128 + (1 * 47);
    }
    //c down = down left fsmash
    if (inputs.z && directions.cy == -1) {
        // 5250 8500 = 42 68
        outputs.rightStickX = 128 + (-1 * 68);
        outputs.rightStickY = 128 + (-1 * 47);
    }*/

    if (inputs.lightshield || inputs.up) {
        outputs.triggerRAnalog = 49;
    }
    if (inputs.midshield) {
        outputs.triggerRAnalog = 94;
    }

    if (outputs.triggerLDigital) {
        outputs.triggerLAnalog = 140;
    }

    if (outputs.triggerRDigital) {
        outputs.triggerRAnalog = 140;
    }

    // Shut off C-stick when using D-Pad layer.
    if ((inputs.mod_x && inputs.mod_y) || inputs.nunchuk_c) {
        outputs.rightStickX = 128;
        outputs.rightStickY = 128;
    }

    // Nunchuk overrides left stick.
    if (inputs.nunchuk_connected) {
        outputs.leftStickX = inputs.nunchuk_x;
        outputs.leftStickY = inputs.nunchuk_y;
        
    }
}
