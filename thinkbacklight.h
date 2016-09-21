#include <assert.h>
#include <errno.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BACKLIGHT_DIR
#define BACKLIGHT_DIR "/sys/class/backlight/intel_backlight/"
#endif

#ifndef BACKLIGHT_FILE_NAME
#define BACKLIGHT_FILE_NAME "brightness"
#endif

#ifndef BACKLIGHT_MAX_FILE_NAME
#define BACKLIGHT_MAX_FILE_NAME "max_brightness"
#endif

#ifndef BACKLIGHT_FILE
#define BACKLIGHT_FILE BACKLIGHT_DIR BACKLIGHT_FILE_NAME
#endif

#ifndef BACKLIGHT_MAX_FILE
#define BACKLIGHT_MAX_FILE BACKLIGHT_DIR BACKLIGHT_MAX_FILE_NAME
#endif

#define MAX_STR 16
