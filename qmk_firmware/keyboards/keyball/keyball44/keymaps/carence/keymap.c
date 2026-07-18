/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_ESC   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_DEL   ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                        KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , S(KC_7)  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_INT1  ,
              KC_LALT,KC_LGUI,LCTL_T(KC_LNG2)     ,LT(1,KC_SPC),LT(3,KC_LNG1),                  KC_BSPC,LT(2,KC_ENT), RCTL_T(KC_LNG2),     KC_RALT  , KC_PSCR
  ),

  [1] = LAYOUT_universal(
    SSNP_FRE ,  KC_F1   , KC_F2    , KC_F3   , KC_F4    , KC_F5    ,                                         KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    SSNP_VRT ,  _______ , _______  , KC_UP   , KC_ENT   , KC_DEL   ,                                         KC_PGUP  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_BTN3  , KC_F12   ,
    SSNP_HOR ,  _______ , KC_LEFT  , KC_DOWN , KC_RGHT  , KC_BSPC  ,                                         KC_PGDN  , KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  , _______  ,
                  _______  , _______ , _______  ,         _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  ,S(KC_QUOT), KC_7     , KC_8    , KC_9     , S(KC_8)  ,                                         S(KC_9)  , S(KC_1)  , S(KC_6)  , KC_LBRC  , S(KC_4)  , _______  ,
    _______  ,S(KC_SCLN), KC_4     , KC_5    , KC_6     , KC_RBRC  ,                                         KC_NUHS  , KC_MINS  , S(KC_EQL), S(KC_3)  , KC_QUOT  , S(KC_2)  ,
    _______  ,S(KC_MINS), KC_1     , KC_2    , KC_3     ,S(KC_RBRC),                                        S(KC_NUHS),S(KC_INT1), KC_EQL   ,S(KC_LBRC),S(KC_SLSH),S(KC_INT3),
                  KC_0     , KC_DOT  , _______  ,         _______  , _______  ,                   KC_DEL   , _______  , _______       , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                        RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , SCRL_DVI ,                                        RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , SCRL_DVD ,                                        CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , _______  , KBC_SAVE ,
                  QK_BOOT  , KBC_RST  , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , KBC_RST  , QK_BOOT
  ),

  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
                  _______  , _______  , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);

    // LOWER + RAISE = ADJUST のようなTri Layersを使う場合
    // これを先に書いておかないと3の色がおかしくなる らしい
    // state = update_tri_layer_state(state, 1, 2, 3);

    // レイヤーごとにRGB色を変える
    uint8_t layer = biton32(state);
    switch (layer)
    {
    case 0:
      rgblight_sethsv_noeeprom(HSV_OFF); // 一旦完全に消灯
      wait_ms(10);
      rgblight_sethsv_noeeprom(106, 204, 80); // springgreen
      break;
    case 1:
      rgblight_sethsv_noeeprom(HSV_OFF); // 一旦完全に消灯
      wait_ms(10);
      rgblight_sethsv_noeeprom(255, 230, 177); // hotpink
      break;
    case 2:
      rgblight_sethsv_noeeprom(HSV_OFF); // 一旦完全に消灯
      wait_ms(10);
      rgblight_sethsv_noeeprom(177, 204, 40); // deepskyblue
      break;
    case 3:
      rgblight_sethsv_noeeprom(HSV_OFF); // 一旦完全に消灯
      wait_ms(10);
      rgblight_sethsv_noeeprom(4, 255, 177); // orange
      break;
    case 4:
      rgblight_sethsv_noeeprom(HSV_OFF); // 一旦完全に消灯
      wait_ms(10);
      rgblight_sethsv_noeeprom(39, 230, 102); // mintgreen
      break;
    default:
      rgblight_sethsv_noeeprom(HSV_OFF);
      break;
    }

    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

// combo setting
#ifdef COMBO_ENABLE
enum combos{
JQ_QUES,
JS_SING,
JW_DOUB,
JB_BOU,
FP_PER,
JD_DOL,
FU_UNDER,
JA_AND,
FH_HUSH,
JE_EXCL,
FN_NAMI,
FY_YAMA,

// command
WE_ESC,
JL_ESC,
JF_CAPS,
HJ_F5,

// Navigation
UI_UP,
MC_DOWN,
JK_LEFT,
KL_RIGHT,
YU_HOME,
NM_END,
};

const uint16_t PROGMEM my_jq[] = {KC_J, KC_Q, COMBO_END};
const uint16_t PROGMEM my_js[] = {KC_J, KC_S, COMBO_END};
const uint16_t PROGMEM my_jw[] = {KC_J, KC_W, COMBO_END};
const uint16_t PROGMEM my_jb[] = {KC_J, KC_B, COMBO_END};
const uint16_t PROGMEM my_fp[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM my_jd[] = {KC_J, KC_D, COMBO_END};
const uint16_t PROGMEM my_fu[] = {KC_F, KC_U, COMBO_END};
const uint16_t PROGMEM my_ja[] = {KC_J, KC_A, COMBO_END};
const uint16_t PROGMEM my_fh[] = {KC_F, KC_H, COMBO_END};
const uint16_t PROGMEM my_je[] = {KC_J, KC_E, COMBO_END};
const uint16_t PROGMEM my_fn[] = {KC_F, KC_N, COMBO_END};
const uint16_t PROGMEM my_fy[] = {KC_F, KC_Y, COMBO_END};

// command
const uint16_t PROGMEM my_we[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM my_jl[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM my_jf[] = {KC_J, KC_F, COMBO_END};
const uint16_t PROGMEM my_hj[] = {KC_H, KC_J, COMBO_END};

// Navigation
const uint16_t PROGMEM my_ui[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM my_mco[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM my_jk[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM my_kl[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM my_yu[] = {KC_Y, KC_U, COMBO_END};
const uint16_t PROGMEM my_nm[] = {KC_N, KC_M, COMBO_END};

combo_t key_combos[] = {
[JQ_QUES] = COMBO(my_jq, KC_QUES), //[J][Q] の同時押しで?を入力
[JS_SING] = COMBO(my_js, KC_AMPR), //[J][S] の同時押しでシングルクォーテーションを入力　 (JIS変換用)
[JW_DOUB] = COMBO(my_jw, KC_AT), //[J][W] の同時押しでダブルクォーテーションを入力　 (JIS変換用)
[JB_BOU] = COMBO(my_jb, LSFT(KC_INT3)), //[J][B] の同時押しで縦棒を入力　 (JIS変換用)
[FP_PER] = COMBO(my_fp, KC_PERC), //[F][P] の同時押しで％を入力　
[JD_DOL] = COMBO(my_jd, KC_DLR), //[J][D] の同時押しで＄を入力
[FU_UNDER] = COMBO(my_fu, LSFT(KC_INT1)), //[F][U] の同時押しでアンダースコアを入力 (JIS変換用)
[JA_AND] = COMBO(my_ja, KC_CIRC), //[J][A] の同時押しでアンドを入力  (JIS変換用)
[FH_HUSH] = COMBO(my_fh, KC_HASH), //[F][H] の同時押しで＃を入力
[JE_EXCL] = COMBO(my_je, KC_EXLM), //[J][E] の同時押しで！を入力
[FN_NAMI] = COMBO(my_fn, KC_PLUS), //[F][N] の同時押しでチルダを入力 (JIS変換用)
[FY_YAMA] = COMBO(my_fy, KC_PEQL), //[F][Y] の同時押しでハットを入力 (JIS変換用)

// command
[WE_ESC] = COMBO(my_we, KC_ESC),
[JL_ESC] = COMBO(my_jl, KC_ESC),
[JF_CAPS] = COMBO(my_jf, QK_CAPS_WORD_TOGGLE),
[HJ_F5] = COMBO(my_hj, KC_F5),

// Navigation
[UI_UP] = COMBO(my_ui, KC_UP),
[MC_DOWN] = COMBO(my_mco, KC_DOWN),
[JK_LEFT] = COMBO(my_jk, KC_LEFT),
[KL_RIGHT] = COMBO(my_kl, KC_RGHT),
[YU_HOME] = COMBO(my_yu, KC_HOME),
[NM_END] = COMBO(my_nm, KC_END),
};
#endif


// AUTO_MOUSE_THRESHOLDの独自実装。keyballの最新FWでは当該QMKの機能が未実装のため
// https://github.com/Yowkees/keyball/issues/596
// 参考にした資料

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
bool auto_mouse_activation(report_mouse_t mouse_report) {
    static int16_t accum_x = 0;
    static int16_t accum_y = 0;
    static int16_t accum_h = 0;
    static int16_t accum_v = 0;
    static uint16_t last_move_time = 0;

    // トラックボールに動きがあった場合のみ累積と時間更新を行う
    if (mouse_report.x != 0 || mouse_report.y != 0 || mouse_report.h != 0 || mouse_report.v != 0) {
        // 最後の動作から 200ms 以上経過していたら、過去の微小な累積をリセット
        if (timer_elapsed(last_move_time) > 200) {
            accum_x = 0;
            accum_y = 0;
            accum_h = 0;
            accum_v = 0;
        }
        last_move_time = timer_read();

        accum_x += mouse_report.x;
        accum_y += mouse_report.y;
        accum_h += mouse_report.h;
        accum_v += mouse_report.v;
    }

    // しきい値（config.h の AUTO_MOUSE_THRESHOLD）と比較、またはボタンクリック時に即時判定
    if (abs(accum_x) > AUTO_MOUSE_THRESHOLD || 
        abs(accum_y) > AUTO_MOUSE_THRESHOLD || 
        abs(accum_h) > AUTO_MOUSE_THRESHOLD || 
        abs(accum_v) > AUTO_MOUSE_THRESHOLD || 
        mouse_report.buttons) {
        
        // トリガー成立時は累積をクリア
        accum_x = 0;
        accum_y = 0;
        accum_h = 0;
        accum_v = 0;
        return true;
    }
    return false;
}
#endif


// 一時的にCPIを変更するキーを定義（KB18）
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t prev_cpi_value;
    switch (keycode) {
    case QK_KB_18:
        if (record->event.pressed) {
            prev_cpi_value = keyball_get_cpi();
            keyball_set_cpi(4); // 一時的に使うCPIを100で割った値を指定
        } else {
            keyball_set_cpi(prev_cpi_value);
        }
        return false;
    case QK_KB_19:
        if (record->event.pressed) {
            rgblight_sethsv_noeeprom(HSV_OFF); // 消灯（黒に設定）
        }
        return false;
    default:
        break;
    }
    return true;
}
