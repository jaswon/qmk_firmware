#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

extern uint8_t is_master;

enum layers {
	_QWERTY,
	_LOWER,
	_RAISE,
	_ADJUST,
};

enum { LSFT_CAPS };

// tap dance actions
qk_tap_dance_action_t tap_dance_actions[] = {
	[LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER MO(_LOWER)
#define KC_RAISE MO(_RAISE)
#define KC_CENT  CTL_T(KC_ENT)
#define KC_SSFT  TD(LSFT_CAPS)
#define KC_LMOD  RGB_MOD

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        ESC,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  CENT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LALT, LOWER,  SSFT,      SPC, RAISE,  RGUI \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        GRV,     1,     2,     3,     4,     5,                   BSLS,  LCBR,  RCBR,  PIPE, XXXXX,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX,     6,     7,     8,     9,     0,                   MINS,  LPRN,  RPRN,  UNDS, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                    EQL,  LBRC,  RBRC,  PLUS, XXXXX,  RCTL,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LALT, LOWER,  LSFT,      SPC, RAISE,  RGUI \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       LMOD, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                   PGUP,  HOME,    UP,   END, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                   PGDN,  LEFT,  DOWN, RIGHT, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  RCTL,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LALT, LOWER,  LSFT,      SPC, RAISE,  RGUI \
                              //`--------------------'  `--------------------'
  ),

	// ADJUST = SHIFTED LOWER
  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       TILD,  EXLM,    AT,  HASH,   DLR,  PERC,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX,  CIRC,  AMPR,  ASTR, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  RCTL,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LALT, LOWER,  LSFT,      SPC, RAISE,  RGUI \
                              //`--------------------'  `--------------------'
  )
};

void matrix_init_user(void) {
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
		#ifdef SSD1306OLED
		iota_gfx_init(!has_usb());   // turns on the display
		#endif
}

void keyboard_post_init_user(void) {
	rgb_matrix_enable_noeeprom();
	/* rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_FX); */
	rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS);
}

#ifdef RGB_MATRIX_ENABLE
void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}
#endif

void led_set_user(uint8_t usb_led) {
	rgb_matrix_sethsv_noeeprom(IS_LED_ON(usb_led, USB_LED_CAPS_LOCK) ? 236 : 212 , 255, 192);
}

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) { iota_gfx_task(); }

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
		set_keylog(keycode, record);
#endif
	}
  return true;
}
