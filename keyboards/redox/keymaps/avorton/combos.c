#include QMK_KEYBOARD_H
#include "keymap.h"
#include "action_tapping.h"

enum combo_events {

    UI_Y,
    IEACC_J,
    DS_B,
    SC_V,
    TNS_P,
    IEA_COM,
    HV_HAVE,
    BSPCN_NOT,
    BSPCM_MENT,
    BSPCG_ING,
    BSPCO_OUGH,
    BSPCI_IGHT,
    BSPCQ_QUE,
    BSPCT_TION,
    BSPCS_SION
    };

int COMBO_LEN = COMBO_LENGHT;

const uint16_t PROGMEM U_I_COMBO[] = {KC_U,HOME_I , COMBO_END};
const uint16_t PROGMEM I_EACC_COMBO[] = {HOME_I, EACC, COMBO_END};
const uint16_t PROGMEM D_V_COMBO[] = {KC_D, HOME_S, COMBO_END};
const uint16_t PROGMEM S_C_COMBO[] = {HOME_S, KC_C, COMBO_END};
const uint16_t PROGMEM T_N_S_COMBO[] = {HOME_T, HOME_N, HOME_S, COMBO_END};
const uint16_t PROGMEM I_E_A_COMBO[] = {HOME_I, HOME_E, HOME_A, COMBO_END};
const uint16_t PROGMEM H_V_COMBO[] = {HOME_H, KC_V, COMBO_END};
const uint16_t PROGMEM BSPC_N_COMBO[] = {KC_BSPC, HOME_N, COMBO_END};
const uint16_t PROGMEM BSPC_M_COMBO[] = {KC_BSPC, FR_M, COMBO_END};
const uint16_t PROGMEM BSPC_G_COMBO[] = {KC_BSPC, KC_G, COMBO_END};
const uint16_t PROGMEM BSPC_O_COMBO[] = {KC_BSPC, KC_O, COMBO_END};
const uint16_t PROGMEM BSPC_I_COMBO[] = {KC_BSPC, HOME_I, COMBO_END};
const uint16_t PROGMEM BSPC_Q_COMBO[] = {KC_BSPC, FR_Q, COMBO_END};
const uint16_t PROGMEM BSPC_T_COMBO[] = {KC_BSPC, KC_T, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {

    [UI_Y] = COMBO_ACTION(U_I_COMBO),
    [IEACC_J] = COMBO_ACTION(I_EACC_COMBO),
    [IEA_COM] = COMBO_ACTION(I_E_A_COMBO),
    [DS_B] = COMBO_ACTION(D_S_COMBO),
    [SC_V] = COMBO_ACTION(S_C_COMBO),
    [TNS_P] = COMBO_ACTION(T_N_S_COMBO),
    [HV_HAVE] = COMBO_ACTION(H_V_COMBO),
    [BSPCN_NOT] = COMBO_ACTION(BSPC_N_COMBO),
    [BSPCM_MENT] = COMBO_ACTION(BSPC_M_COMBO),
    [BSPCG_ING] = COMBO_ACTION(BSPC_G_COMBO),
    [BSPCO_OUGH] = COMBO_ACTION(BSPC_O_COMBO),
    [BSPCI_IGHT] = COMBO_ACTION(BSPC_I_COMBO),
    [BSPCQ_QUE] = COMBO_ACTION(BSPC_Q_COMBO),
    [BSPCT_TION] = COMBO_ACTION(BSPC_T_COMBO)
};


void process_combo_event(uint16_t combo_index, bool pressed) {
    // Process mod-taps before the combo is fired,
    // this helps making modifier-aware combos, 
    // like UY_PRN or BSPCN_NOT, more fluid
    // when I use them with home row mods.
    action_tapping_process((keyrecord_t){});
    mod_state = get_mods();
    switch(combo_index) {

        case UI_Y:
            if (pressed) {
                tap_code(KC_Y);
            }
        break;
        
        case IEACC_J:
            if (pressed) {
                tap_code(KC_J);
            }
        break;
        
        case DS_B:
            if (pressed) {
                tap_code(KC_B);
            }
        break;
        
        case SC_V:
            if (pressed) {
                tap_code(KC_V);
            }
        break;
        
        case TNS_P:
            if (pressed) {
                tap_code(KC_P);
            }
        break;

        case IEA_COM:
            if (pressed) {
                tap_code(COMA);
            }
        break;

        case HV_HAVE:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    send_string("Hqve");
                    set_mods(mod_state);

                    } else if (mod_state & MOD_MASK_CTRL) {
                    del_mods(MOD_MASK_CTRL);
                    send_string("-ve");
                    set_mods(mod_state);
                } else {
                    send_string("hqve");
                }
        }
        break;

        case BSPCN_NOT:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    send_string("Not");
                    set_mods(mod_state);
                }
                else if (mod_state & MOD_MASK_CTRL) {
                    del_mods(MOD_MASK_CTRL);
                    send_string("n-t");
                    set_mods(mod_state);
                }
                else {
                    send_string("not");
                }
        }
        break;

        case BSPCM_MENT:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    send_string("<ent");
                    set_mods(mod_state);
                }
                else {
                    send_string(".ent");
                }
        }
        break;

        case BSPCG_ING:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    send_string("Ing");
                    set_mods(mod_state);
                }
                else {
                    send_string("ing");
                }
        }
        break;

        case BSPCO_OUGH:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    send_string("Ough ");
                    set_mods(mod_state);
                }
                else {
                    send_string("ough ");
                }
        }
        break;

        case BSPCI_ION:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    send_string("Ion");
                    set_mods(mod_state);
                }
                else {
                    send_string("ion");
                }
        }
        break;

        case BSPCQ_QUE:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    send_string("Aue");
                    set_mods(mod_state);
                }
                else {
                    send_string("aue");
                }
        }
        break;
        
    }
};