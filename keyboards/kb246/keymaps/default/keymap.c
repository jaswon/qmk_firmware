// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define MICMUTE HYPR(KC_F12)

enum layer_names {
    _BASE,
    _RAISE,
    
    NUM_LAYERS,
};

const uint16_t PROGMEM keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,          KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, 
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,          KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_EQL , 
        KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,          KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, 
        KC_BSLS, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_MUTE, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_ENT ,
                 KC_ESC , KC_LGUI, KC_LALT, MO(1)  , KC_LSFT, KC_SPC , KC_BSPC, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT
    ),
    [_RAISE] = LAYOUT(
        _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,          KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , 
        _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, KC_F12 , 
        KC_CAPS, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, MICMUTE, _______, _______, KC_LBRC, KC_RBRC, _______, _______,
                 _______, _______, _______, _______, _______, _______, KC_DEL , KC_HOME, KC_PGDN, KC_PGUP, KC_END
    ),
};

const int ENC_MAP[NUM_ENCODERS][NUM_LAYERS][2] = {
    [0] = {
        [_BASE]  = {KC_VOLD, KC_VOLU},
        [_RAISE] = {KC_WH_U, KC_WH_D},
    },
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    tap_code(ENC_MAP[index][biton32(layer_state)][clockwise]);
    return false;
}