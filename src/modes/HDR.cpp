/* HDR profile by Faye */
#include "modes/HDR.hpp"

#define ANALOG_STICK_MIN 28
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 228

HDR::HDR(socd::SocdType socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::left,    &InputState::right  },
        socd::SocdPair{ &InputState::down,   &InputState::up     },
        socd::SocdPair{ &InputState::c_left, &InputState::c_right},
        socd::SocdPair{ &InputState::c_down, &InputState::c_up   },
    };
}

void HDR::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    outputs.a = inputs.a;
    outputs.b = inputs.r;
    outputs.x = inputs.x;
    outputs.y = inputs.y;
    outputs.buttonR = inputs.z;
    outputs.triggerLDigital = inputs.l;
    outputs.triggerRDigital = inputs.b;
    outputs.start = inputs.start;
    outputs.select = inputs.select;
    outputs.home = inputs.home;

    // Turn on D-Pad layer by holding Mod X + Mod Y or Nunchuk C button.
    if ((inputs.mod_x && inputs.mod_y) || inputs.nunchuk_c) {
        outputs.dpadUp = inputs.c_up;
        outputs.dpadDown = inputs.c_down;
        outputs.dpadLeft = inputs.c_left;
        outputs.dpadRight = inputs.c_right;
    }
}

void HDR::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
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

    bool shield_button_pressed = inputs.l || inputs.b;
    
    //imported from PM code
    outputs.dpadUp = outputs.dpadUp || inputs.midshield || inputs.leftmidshield;

        //imported from PM code
    outputs.dpadDown = outputs.dpadDown || inputs.lightshield;

    if (inputs.mod_x) {
        // MX + Horizontal = 6625 = 53
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 53);
            // Horizontal Shield tilt = 51
            if (shield_button_pressed) {
                outputs.leftStickX = 128 + (directions.x * 51);
            }
            // Horizontal Tilts = 36
            if (inputs.a) {
                outputs.leftStickX = 128 + (directions.x * 36);
            }
        }
        // MX + Vertical = 44
        if (directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 44);
            // Vertical Shield Tilt = 51
            if (shield_button_pressed) {
                outputs.leftStickY = 128 + (directions.y * 51);
            }
        }
        if (directions.diagonal) {
            // MX + q1/2/3/4 = 53 35
            outputs.leftStickX = 128 + (directions.x * 53);
            outputs.leftStickY = 128 + (directions.y * 35);
            if (shield_button_pressed) {
                // MX + L, R, LS, and MS + q1/2/3/4 = 6375 3750 = 51 30
                outputs.leftStickX = 128 + (directions.x * 51);
                outputs.leftStickY = 128 + (directions.y * 30);
            }
        }

        // Angled fsmash/ftilt with C-Stick + MX
        if (directions.cx != 0) {
            outputs.rightStickX = 128 + (directions.cx * 127);
            outputs.rightStickY = 128 + (directions.y * 59);
        }

        /* Up B angles */
        if (directions.diagonal && !shield_button_pressed) {
            // (33.44) = 53 35
                outputs.leftStickX = 128 + (directions.x * 73);
                outputs.leftStickY = 128 + (directions.y * 31);
            // (39.05) = 53 43
            if (inputs.c_down) {
                outputs.leftStickX = 128 + (directions.x * 49);
                outputs.leftStickY = 128 + (directions.y * 42);
            }
            // (36.35) = 53 39
            if (inputs.c_left) {
                outputs.leftStickX = 128 + (directions.x * 49);
                outputs.leftStickY = 128 + (directions.y * 42);
            }
            // (30.32) = 56 41
            if (inputs.c_up) {
                outputs.leftStickX = 128 + (directions.x * 49);
                outputs.leftStickY = 128 + (directions.y * 42);
            }
            // (27.85) = 49 42
            if (inputs.c_right) {
                outputs.leftStickX = 128 + (directions.x * 49);
                outputs.leftStickY = 128 + (directions.y * 42);
            }

            /* Extended Up B Angles */
            if (inputs.r) {
                // (33.29) = 67 44
                outputs.leftStickX = 128 + (directions.x * 73);
                outputs.leftStickY = 128 + (directions.y * 31);
                // (39.38) = 67 55
                if (inputs.c_down) {
                    outputs.leftStickX = 128 + (directions.x * 70);
                    outputs.leftStickY = 128 + (directions.y * 36);
                }
                // 31.77828 - 8500 5250 (31.7) = 68 42
                if (inputs.c_left) {
                    outputs.leftStickX = 128 + (directions.x * 68);
                    outputs.leftStickY = 128 + (directions.y * 42);
                }
                // 36.18552 - 7375 5375 (36.1) = 59 43
                if (inputs.c_up) {
                    outputs.leftStickX = 128 + (directions.x * 59);
                    outputs.leftStickY = 128 + (directions.y * 43);
                }
                // 40.59276 - 6375 5375 (40.1) = 51 43
                if (inputs.c_right) {
                    outputs.leftStickX = 128 + (directions.x * 51);
                    outputs.leftStickY = 128 + (directions.y * 43);
                }
            }

            // Angled Ftilts
            if (inputs.a) {
                outputs.leftStickX = 128 + (directions.x * 36);
                outputs.leftStickY = 128 + (directions.y * 26);
            }
        }
    }

    if (inputs.mod_y) {
        // MY + Horizontal (even if shield is held) = 3375 = 27
        if (directions.horizontal) {
            outputs.leftStickX = 128 + (directions.x * 27);
        }
        // MY + Vertical (even if shield is held) = 7375 = 59
        if (directions.vertical) {
            outputs.leftStickY = 128 + (directions.y * 59);
        }
        if (directions.diagonal) {
            // MY + q1/2/3/4 = 3125 7375 = 25 59
            outputs.leftStickX = 128 + (directions.x * 25);
            outputs.leftStickY = 128 + (directions.y * 59);
            if (shield_button_pressed) {
                // MY + L, R, LS, and MS + q1/2 = 4750 8750 = 38 70
                outputs.leftStickX = 128 + (directions.x * 38);
                outputs.leftStickY = 128 + (directions.y * 70);
                // MY + L, R, LS, and MS + q3/4 = 5000 8500 = 40 68
                if (directions.y == -1) {
                    outputs.leftStickX = 128 + (directions.x * 40);
                    outputs.leftStickY = 128 + (directions.y * 68);
                }
            }
        }

        // Turnaround neutral B nerf
        if (inputs.r) {
            outputs.leftStickX = 128 + (directions.x * 80);
        }

        /* Up B angles */
        if (directions.diagonal && !shield_button_pressed) {
            // 67.0362 - 3125 7375 = 25 59
            outputs.leftStickX = 128 + (directions.x * 25);
            outputs.leftStickY = 128 + (directions.y * 59);
            // 62.62896 - 3625 7000 (62.62) = 29 56
            if (inputs.c_down) {
                outputs.leftStickX = 128 + (directions.x * 29);
                outputs.leftStickY = 128 + (directions.y * 56);
            }
            // 58.22172 - 4875 7875 (58.24) = 39 63
            if (inputs.c_left) {
                outputs.leftStickX = 128 + (directions.x * 39);
                outputs.leftStickY = 128 + (directions.y * 63);
            }
            // 53.81448 - 5125 7000 (53.79) = 41 56
            if (inputs.c_up) {
                outputs.leftStickX = 128 + (directions.x * 41);
                outputs.leftStickY = 128 + (directions.y * 56);
            }
            // 49.40724 - 6375 7625 (50.10) = 51 61
            if (inputs.c_right) {
                outputs.leftStickX = 128 + (directions.x * 51);
                outputs.leftStickY = 128 + (directions.y * 61);
            }

            /* Extended Up B Angles */
            if (inputs.r) {
                // 67.0362 - 3875 9125 = 31 73
                outputs.leftStickX = 128 + (directions.x * 31);
                outputs.leftStickY = 128 + (directions.y * 73);
                // 62.62896 - 4500 8750 (62.8) = 36 70
                if (inputs.c_down) {
                    outputs.leftStickX = 128 + (directions.x * 36);
                    outputs.leftStickY = 128 + (directions.y * 70);
                }
                // 58.22172 - 5250 8500 (58.3) = 42 68
                if (inputs.c_left) {
                    outputs.leftStickX = 128 + (directions.x * 42);
                    outputs.leftStickY = 128 + (directions.y * 68);
                }
                // 53.81448 - 5875 8000 (53.7) = 47 64
                if (inputs.c_up) {
                    outputs.leftStickX = 128 + (directions.x * 47);
                    outputs.leftStickY = 128 + (directions.y * 64);
                }
                // 49.40724 - 5875 7125 (50.49) = 47 57
                if (inputs.c_right) {
                    outputs.leftStickX = 128 + (directions.x * 47);
                    outputs.leftStickY = 128 + (directions.y * 57);
                }
            }
        }
    }

    // C-stick ASDI Slideoff angle overrides any other C-stick modifiers (such as
    // angled fsmash).
    if (directions.cx != 0 && directions.cy != 0) {
        // 5250 8500 = 42 68
        outputs.rightStickX = 128 + (directions.cx * 42);
        outputs.rightStickY = 128 + (directions.cy * 68);
    }

    if (inputs.l) {
        outputs.triggerLAnalog = 140;
    }

    if (inputs.b) {
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