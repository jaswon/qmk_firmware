RGB_MATRIX_EFFECT(FX)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

/* static HSV default_color = { 212, 255, 32 }; */

static bool FX (effect_params_t* params) {
	uint8_t led_i;
	for (int i = 0; i < MATRIX_ROWS; i++) {
		uint8_t row = matrix_get_row(i);
		for (int j = 0 ; j < MATRIX_COLS; j++) {
			led_i = g_led_config.matrix_co[i][j];
			if (led_i != NO_LED) {
				uint8_t hue = row & 1<<j ? 84 : rgb_matrix_config.hue;
				RGB rgb = hsv_to_rgb((HSV) { hue, 255, rgb_matrix_config.val });
				rgb_matrix_set_color(led_i, rgb.r, rgb.g, rgb.b);
			}
		}
	}
	return false;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// vim: ft=cpp
