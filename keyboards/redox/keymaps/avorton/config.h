#pragma once

#define USE_SERIAL
#define MASTER_LEFT
// Use custom magic number so that when switching branches, EEPROM always gets reset
#define EECONFIG_MAGIC_NUMBER (uint16_t)0x1338

/* Set Polling rate to 1000Hz */
#define USB_POLLING_INTERVAL_MS 1

#ifndef ONESHOT_TAP_TOGGLE
#    define ONESHOT_TAP_TOGGLE 2
#endif  // !ONESHOT_TAP_TOGGLE
#ifndef ONESHOT_TIMEOUT
#    define ONESHOT_TIMEOUT 5000
#endif  // !ONESHOT_TIMEOUT

#ifndef QMK_KEYS_PER_SCAN
#    define QMK_KEYS_PER_SCAN 4
#endif  // !QMK_KEYS_PER_SCAN

// this makes it possible to do rolling combos (zx) with keys that
// convert to other keys on hold (z becomes ctrl when you hold it,
// and when this option isn't enabled, z rapidly followed by x
// actually sends Ctrl-x. That's bad.)
#define IGNORE_MOD_TAP_INTERRUPT
// This prevents short hold periods to be interpreted as individual taps when typing quickly.
#undef PERMISSIVE_HOLD
#define RETRO_TAPPING

#ifndef TAPPING_TOGGLE
#    define TAPPING_TOGGLE 2
#endif

#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

#define TAP_CODE_DELAY 5

/* Disable unused and unneeded features to reduce on firmware size */
#ifdef LOCKING_SUPPORT_ENABLE
#    undef LOCKING_SUPPORT_ENABLE
#endif
#ifdef LOCKING_RESYNC_ENABLE
#    undef LOCKING_RESYNC_ENABLE
#endif
#define COMBO_VARIABLE_LEN
#define COMBO_COUNT COMBO_VARIABLE_LEN
#define COMBO_TERM 70
#define TAPPING_FORCE_HOLD_PER_KEY
