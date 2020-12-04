#include QMK_KEYBOARD_H

#include "keymap.h"

// Create a global instance of the tapdance state type
static td_state_t td_state;
// Initialize variable holding the binary
// representation of active modifiers.
uint8_t current_mod;
// Tap dance states
typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD,
  DOUBLE_TAP,
  DOUBLE_HOLD,
  TRIPLE_TAP
} td_state_t;

// track the tapdance state to return
uint8_t cur_dance(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) {
        return SINGLE_TAP;
    } else {
        return SINGLE_HOLD;
    }
  }
  if (state->count == 2) {
    if (state->interrupted || !state->pressed) {
        return DOUBLE_TAP;
    } else {
        return DOUBLE_HOLD;
    }
  }
  if (state->count == 3) {
        return TRIPLE_TAP;
    }
  else {
      return 4; // any number higher than the maximum state value you return above
  }
}

void sentence_end(qk_tap_dance_state_t *state, void *user_data) {
      current_mod = get_mods();
      td_state = cur_dance(state);
  switch (td_state) {
      case SINGLE_TAP:
          tap_code(KC_M);
        break;

      case SINGLE_HOLD:
          tap_code(KC_DOT);
        break;

      case DOUBLE_TAP:
        // Double tapping TD_DOT produces
        // ". <one-shot-shift>" i.e. dot, space and capitalize next letter.
        // This helps to quickly end a sentence and begin another one
        // without having to hit shift.
        // Check that Shift is inactive
                tap_code(KC_M);
                tap_code(KC_SPC);
        // Internal code of OSM(MOD_LSFT)
                set_oneshot_mods(MOD_LSFT | get_oneshot_mods());
          break;
        case DOUBLE_HOLD:       // @   -> easy access to @ on same key as . for emails adress without having to go to symbols layer
          tap_code(KC_GRV);
        break;
        case TRIPLE_TAP:
          tap_code16(S(KC_DOT));   // …
        break;
      default:
      break;
  }
};

// handle the possible states for each tapdance keycode you define:

void coma_finished(qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:   // gives ,
      tap_code(KC_COMM);
      break;
    case SINGLE_HOLD:   // gives ;
      tap_code(KC_SLSH);
      break;
    case DOUBLE_TAP:    // sends !␣ +OS Shift
     if (get_mods () & MOD_MASK_SHIFT) {
      clear_mods();
      tap_code16(S(KC_COMM));
      tap_code(KC_SPC);
      set_oneshot_mods(MOD_LSFT | get_oneshot_mods());
     }
    break;
    default:
  break;
  }
}

void apo_acc_finished(qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      tap_code(KC_MINS); // ' "
      break;
    case SINGLE_HOLD: // -
      tap_code(KC_PMNS);
      break;
    case DOUBLE_TAP:  // ^ ¨
      tap_code(FR_EQL);
  break;
    default:
  break;
  }
}

void ACVX_finished(qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      tap_code16(C(KC_INS));
      break;
    case SINGLE_HOLD:
      tap_code16(C(KC_Q));
      break;
    case DOUBLE_TAP:
      tap_code16(S(KC_INS));
      break;
    case DOUBLE_HOLD:
      tap_code16(C(KC_X));
      break;
    default:
  break;
  }
}

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

// Initialize tap structure associated with example tap dance key
static tap ql_tap_state = {
    .is_press_action = true,
    .state = 0
};
static bool base_layer_on; // track the layer status to allow the one tap returning to default layer
                           // without returning it AND tapping the code of base layer.

// Functions that control what our tap dance key does

void eacc_finished(qk_tap_dance_state_t *state, void *user_data) {
  current_mod = get_mods();
  td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            if(get_mods() & MOD_MASK_SHIFT) {
              clear_mods();
              tap_code16(RALT(S(KC_2)));   //   É
              set_mods(current_mod);
            } else {         //  é
              tap_code (KC_2);
            }
          break;
        case SINGLE_HOLD:
            if(get_mods() & MOD_MASK_SHIFT) {
              clear_mods();
              tap_code16(RALT(S(KC_3)));   //  È
              set_mods(current_mod);
            } else {
              tap_code (KC_3);             //  è
            }
          break;
        default:
      break;
    }
  }

void esc_fn(qk_tap_dance_state_t *state, void *user_data) {
  ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
      case SINGLE_TAP:
        if (base_layer_on) {
            tap_code(KC_ESC);
        } else {
            layer_move(_BASE);
            base_layer_on = true;
        }
          break;
      case SINGLE_HOLD:
            layer_on (_FN);
            base_layer_on = false;
          break;
      case DOUBLE_TAP:
        if (layer_state_is (_FN)) {
            layer_off (_FN);
            base_layer_on = true;
        } else {
            layer_move (_FN);
            base_layer_on = false;
        }
      default:
    break;
  }
}

void ent_symb(qk_tap_dance_state_t *state, void *user_data) {
  ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
      case SINGLE_TAP:
            if (base_layer_on) {
               tap_code(KC_ENT);
            } else if (get_mods() & MOD_MASK_SHIFT) {   //Allows ENT on the previously chosen layer without returning to _BASE
              tap_code (KC_ENT);
            } else {
              layer_move(_BASE);
              base_layer_on = true;
            }
          break;
      case SINGLE_HOLD:
            if (base_layer_on) {
              layer_on(_SYMB);
              base_layer_on = false;
            }
          break;
      case DOUBLE_TAP:
            if (layer_state_is (_SYMB)) {
              layer_off (_SYMB);
              base_layer_on = true;
            } else {
              layer_move (_SYMB);
              base_layer_on = false;
            }
          break;
      default:
    break;
  }
}

void spc_sft(qk_tap_dance_state_t *state, void *user_data) {
  ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
      case SINGLE_TAP:
            if (base_layer_on) {
               tap_code(KC_SPC);
            } else if (layer_state_is (_SYMB)) {
              tap_code16(A_UND);   // _
            } else if (layer_state_is (_NUM)) {
              tap_code (KC_P0);   // 0
            } else if (get_mods() & MOD_MASK_SHIFT) {   //Allows Space on the previously chosen layer without returning to _BASE layer
              tap_code (KC_SPC);
            } else {
              layer_move(_BASE);
              base_layer_on = true;
            }
          break;
      case SINGLE_HOLD:
            register_code (KC_LSFT);
          break;
      case DOUBLE_TAP:
          if (get_mods() & MOD_MASK_SHIFT) {    // CAPS LOCK
              unregister_code (KC_LSFT);
          } else {
            register_code (KC_LSFT);
          }
          break;
      case DOUBLE_HOLD:    // auto repeat
            register_code (KC_SPC);
          break;
      default:
    break;
  }
}

void tab_nav(qk_tap_dance_state_t *state, void *user_data) {
  current_mod = get_mods();
  ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case SINGLE_TAP:
            if (base_layer_on) {   // Shift + Tab is only possible on the _BASE layer
               tap_code(KC_TAB);
            } else if (get_mods() & MOD_MASK_SHIFT) {  //Allows TAB on the previously chosen layer without returning to _BASE
              clear_mods();
              tap_code (KC_TAB);
              set_mods(current_mod);
            } else {
              layer_move(_BASE);
              base_layer_on = true;
            }
          break;
        case SINGLE_HOLD:
                layer_on (_NAV);
                base_layer_on = false;
          break;
        case DOUBLE_TAP:
            if (layer_state_is (_NAV)) {
                layer_off (_NAV);
                base_layer_on = true;
            } else {
                layer_move (_NAV);
                base_layer_on = false;
            }
          break;
        default:
      break;
    }
  }

void del_num(qk_tap_dance_state_t *state, void *user_data) {
  ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case SINGLE_TAP:
            if (base_layer_on) {
               tap_code(KC_DEL);
            } else if (get_mods() & MOD_MASK_SHIFT) {    //Allows DEL on the previously chosen layer without returning to _BASE
              tap_code (KC_DEL);
            } else {
              layer_move(_BASE);
              base_layer_on = true;
            }
          break;
        case SINGLE_HOLD:
                del_mods(MOD_MASK_SHIFT);
                layer_on (_NUM);
                base_layer_on = false;
          break;
        case DOUBLE_TAP:
            if (layer_state_is (_SYMB)) {
                layer_off (_NUM);
                base_layer_on = true;
            } else {
                del_mods(MOD_MASK_SHIFT);
                layer_move (_NUM);
                base_layer_on = false;
            }
          break;
        default:
      break;
    }
  }

void spc_sft_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (ql_tap_state.state == SINGLE_HOLD) {
          unregister_code(KC_LSFT);
    } else if (ql_tap_state.state == DOUBLE_HOLD) {
          unregister_code(KC_SPC);
    }
}

void layer_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == SINGLE_HOLD) {
      if (layer_state_is (_NUM)) {
          layer_off (_NUM);
          base_layer_on = true;
      } else if (layer_state_is (_SYMB)) {
          layer_off (_SYMB);
          base_layer_on = true;
      } else if  (layer_state_is (_FN)) {
          layer_off (_FN);
          base_layer_on = true;
      } else if  (layer_state_is (_NAV)) {
          layer_off (_NAV);
          base_layer_on = true;
      }
    }
  ql_tap_state.state = 0;
};

qk_tap_dance_action_t tap_dance_actions[] = {

    [TD_COMA] = ACTION_TAP_DANCE_FN (coma_finished),
    [TD_APO_ACC] = ACTION_TAP_DANCE_FN (apo_acc_finished),
    [TD_DOT]  = ACTION_TAP_DANCE_FN (sentence_end),
    [TD_ACVX] = ACTION_TAP_DANCE_FN (ACVX_finished),
    [TD_EACC] = ACTION_TAP_DANCE_FN (eacc_finished),
    [TD_ENT_SYMB] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, ent_symb, layer_reset),
    [TD_SPC_SFT] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, spc_sft, spc_sft_reset),
    [TD_TAB_NAV] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, tab_nav, layer_reset),
    [TD_ESC_FN] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, esc_fn, layer_reset),
    [TD_DEL_NUM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, del_num, layer_reset)
};
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == SINGLE_HOLD) {
      if (layer_state_is (_NUM)) {
          layer_off (_NUM);
          base_layer_on = true;
      } else if (layer_state_is (_SYMB)) {
          layer_off (_SYMB);
          base_layer_on = true;
      } else if  (layer_state_is (_FN)) {
          layer_off (_FN);
          base_layer_on = true;
      } else if  (layer_state_is (_NAV)) {
          layer_off (_NAV);
          base_layer_on = true;
      }
    }
  ql_tap_state.state = 0;
};