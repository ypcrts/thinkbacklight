#include "thinkbacklight.h"

/* ./thinkbacklight.c */
void print_help(void);
uint_fast8_t set_backlight(const uint_fast16_t val);
void print_current_backlight(void);
void print_max_backlight(void);
uint_fast16_t get_max_backlight(void);
uint_fast16_t get_current_backlight(void);
uint_fast16_t get_backlight_value(const char *filepath);

static int fade_flag = 0;
/* static struct option long_options[] = {{ */
/* "check-current", */
/* }, */
/* { */
/* "check-max", */
/* }, */
/* { */
/* "set", */
/* }, */
/* { */
/* "up", */
/* }, */
/* { */
/* "down", */
/* }, */
/* { */
/* "fade", */
/* }}; */

int main(int argc, char **argv, char **envp) {
  /* int c, option_index; */


  /*
   * if (argc == 0) {
   *   print_help();
   *   exit(0);
   * }
   */

  /*
   * while (c == getopt_long(argc, argv, "-cxsud", long_options, &option_index))
   * {
   *   if (c == -1) break;
   *   switch (c) {
   *     case 0:
   *       [> set a flag <]
   *       break;
   *     case 'c':
   *       break;
   *     case 'x':
   *       break;
   *     case 's':
   *       break;
   *     case 'u':
   *       break;
   *     case 'd':
   *       break;
   *       return 0;
   *   }
   * }
   */
}

void print_help(void) {}

uint_fast8_t set_backlight_to_percentage() {
  set_backlight(get_max_backlight());
}

uint_fast8_t set_backlight_to_max() {
  set_backlight(get_max_backlight());
}

uint_fast8_t set_backlight(const uint_fast16_t val) {
  FILE *f;
  char s[MAX_STR];
  int ret;

  snprintf(s, MAX_STR, "%ld", val);

  f = fopen(BACKLIGHT_FILE, "w");
  if (f == NULL) {
    perror(BACKLIGHT_FILE);
    exit(1);
  }

  ret = fputs(s, f);
  if (!(ret > 0)) {
    perror(BACKLIGHT_FILE);
    exit(1);
  }

  ret = fclose(f);
  if (ret != 0) perror(NULL);

  return 0;
}

void print_current_backlight(void) { printf("%ld\n", get_current_backlight()); }

void print_max_backlight(void) { printf("%ld\n", get_max_backlight()); }

uint_fast16_t get_max_backlight(void) {
  return get_backlight_value(BACKLIGHT_MAX_FILE);
}
uint_fast16_t get_current_backlight(void) {
  return get_backlight_value(BACKLIGHT_FILE);
}

uint_fast16_t get_backlight_value(const char *filepath) {
  FILE *f;
  size_t chunk_size, num_chunks;
  char buf[MAX_STR], *buftest;
  int ret;
  uint_fast16_t result;

  f = fopen(filepath, "r");
  if (f == NULL) {
    perror(filepath);
    exit(1);
  }

  buftest = fgets(buf, MAX_STR, f);
  if (buf != buftest) {
    perror(filepath);
    exit(1);
  }

  result = (uint_fast16_t)atoi(buf);

  ret = fclose(f);
  if (ret != 0) perror(NULL);

  return result;
}
