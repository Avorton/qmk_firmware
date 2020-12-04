#pragma once

#include QMK_KEYBOARD_H

#include "keymap_french.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
    _BASE,
    _NUM,
    _SYMB,
    _NAV,
    _FN,
};

// Initialize boolean variable which
// track the layer status to allow the one tap returning to default layer
// without returning it AND tapping the code of base layer.
static bool base_layer_on;
// representation of active modifiers.
uint8_t current_mod;

// Shortcut to make keymap more readable
#define A_SUB     RALT(KC_EQL) // dead key, combined with numbers gives subscripts
#define A_HYP     FR_EQL       // hyperscripts
#define A_LCBR    RALT(KC_T)   // {
#define A_RCBR    RALT(KC_Y)   // }
#define A_LBRK    RALT(KC_5)   // [
#define A_RBRK    RALT(KC_6)   // ]
#define A_AMP     RALT(KC_4)   // &
#define A_PCNT    RALT(KC_P)   // %
#define A_DOLR    RALT(KC_D)   // $
#define A_PIPE    RALT(KC_L)   // |
#define A_UND     RALT(KC_8)   // _
#define A_EQL     S(KC_SLSH)   // =
#define A_LABK    KC_NUBS      // <
#define A_RABK    S(KC_NUBS)   // >
#define A_BSLH    S(KC_QUOT)   // *\*
//Thumbs
#define DEL_NUM   TD(TD_DEL_NUM)
#define BSPC_SFT  LSFT_T(KC_BSPC)
#define TAB_NAV   TD(TD_TAB_NAV)
#define ESC_FN    TD(TD_ESC_FN)
#define SPC_SFT   TD(TD_SPC_SFT)
#define ENT_SYMB  TD(TD_ENT_SYMB)
// alphas & symbols
#define DOT       TD(TD_DOT)
#define COMA      TD(TD_COMA)
#define APO_ACC   TD(TD_APO_ACC)
#define EACC      TD(TD_EACC)
//functions
#define ACVX      TD(TD_ACVX) // CTRL+A, CTRL+C, CTRL+V, CTRL+X

// Left-hand home row mods
#define WIND_T   LGUI_T(KC_T)
#define ALT_N    LALT_T(KC_N)
#define CTRL_S   LCTL_T(KC_S)
#define AGR_R    RALT_T(KC_R)
#define GUI_AST  LGUI_T(KC_PAST)
#define ALT_MNS  LALT_T(KC_PMNS)
#define CTRL_SLH LCTL_T(KC_QUOT)
#define GUI_PRV  LGUI_T(KC_MPRV)
#define ALT_PLY  LALT_T(KC_MPLY)
#define CTRL_NXT LCTL_T(KC_MNXT)
#define GUI_HOME LGUI_T(KC_HOME)
#define ALT_PGDN LALT_T(KC_PGDN)
#define CTRL_END LCTL_T(KC_END)
#define AGR_PGUP RALT_T(KC_PGUP)

// Right-hand home row mods
#define CTRL_I   LCTL_T(KC_I)
#define ALT_E    LALT_T(KC_E)
#define GUI_A    LGUI_T(FR_A)
#define AGR_O    RALT_T(KC_O)
#define CTRL_4   LCTL_T(KC_P4)
#define ALT_5    LALT_T(KC_P5)
#define GUI_6    LGUI_T(KC_P6)
#define AGR_8    RALT_T(KC_P8)
#define CTRL_F4  LCTL_T(KC_F4)
#define ALT_F5   LALT_T(KC_F5)
#define GUI_F6   LGUI_T(KC_F6)
#define AGR_F8    RALT_T(KC_F8)

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTRL_S:
          return true;
        case ALT_N:
          return true;
        case WIND_T :
          return true;
        case CTRL_I:
          return true;
        case ALT_E:
          return true;
        default:
            return false;
    }
}

enum td_keycodes {
    TD_EACC,
    TD_COMA,
    TD_APO_ACC,
    TD_DOT,
    TD_ACVX,
    TD_UNRE,
    TD_ENT_SYMB,
    TD_TAB_NAV,
    TD_DEL_NUM,
    TD_ESC_FN,
    TD_SPC_SFT
};


uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTRL_I:
          return TAPPING_TERM +100;
        case AGR_O:
          return TAPPING_TERM +100;
        case AGR_R:
          return TAPPING_TERM +100;
        case ALT_E:
          return TAPPING_TERM +100;
        case GUI_A:
          return TAPPING_TERM +150;
        case WIND_T :
          return TAPPING_TERM +150;
        case ALT_N:
          return TAPPING_TERM +100;
        case CTRL_S:
          return TAPPING_TERM +100;
        case EACC:
          return TAPPING_TERM -125;
        case DOT:
          return TAPPING_TERM -100;
        case COMA:
          return TAPPING_TERM -100;
        case APO_ACC:
          return TAPPING_TERM -100;
        default:
            return TAPPING_TERM;
    }
};

enum my_keycodes {

    KC_QU,
    CALC,
    UNDO_REDO
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  current_mod = get_mods();
    switch (keycode) {
      case KC_QU:
        if (record->event.pressed) {
          if (get_mods() & MOD_MASK_SHIFT) {
          tap_code(KC_A);
          del_mods(MOD_MASK_SHIFT);
          tap_code(KC_U);
          set_mods(current_mod);
        } else if (get_mods() & MOD_MASK_ALT) {
          del_mods(MOD_MASK_ALT);
          tap_code(KC_A);
          set_mods(current_mod);
        } else {
          tap_code(FR_Q);
          tap_code(KC_U);
        return false;
        }
      return true;
    }

    case CALC:
      if (record->event.pressed) {
        tap_code16 (KC_CALC);
        layer_move(_NUM);
        base_layer_on = false;
      }
      return true;

    case UNDO_REDO:
    if (record->event.pressed) {
        if (get_mods() & MOD_MASK_SHIFT) {
          clear_mods();
          tap_code16(C(KC_Y));
          set_mods(current_mod);
        } else {
          tap_code16 (C(KC_W));
        }
      return false;
    }
  return true;
  }
return true;
};
