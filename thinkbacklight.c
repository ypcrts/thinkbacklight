#include "thinkbacklight.h"

/* thinkbacklight.c */
int main(int argc, char **argv, char **envp);
void print_help(void);
void set_backlight_step_up(void);
void set_backlight_step_down(void);
uint_fast16_t find_step_size(void);
uint_fast16_t find_percentage_of_max(const uint_fast16_t p);
void set_backlight(const uint_fast8_t p);
void set_backlight_raw(const uint_fast16_t p);
void print_current_backlight(void);
void print_max_backlight(void);
uint_fast16_t get_max_backlight(void);
uint_fast16_t get_current_backlight(void);
uint_fast16_t get_backlight_value(const char *filepath);

// TODO
static int fade_flag = 0;

static struct option long_options[] = {{"check", no_argument,       0,          'c'},
                                       {"set",   required_argument, 0,          's'},
                                       {"up",    optional_argument, 0,          'u'},
                                       {"down",  optional_argument, 0,          'd'},
                                       {"fade",  no_argument,       &fade_flag, 0},
                                       {0,       0,                 0,          0}};

int main(int argc, char **argv, char **envp) {
  int c, option_index;

  if (argc <= 1) {
    print_help();
    exit(0);
  }

  while ((c = getopt_long(argc, argv, "-cs:udh", long_options, &option_index))) {
    if (c == -1) break;

    switch (c) {
      case 0:
        /* if(optarg) {}  */
        break;
      case 'c':
        print_current_backlight();
        break;
      case 's':
        if (!optarg) errno = EINVAL, perror(0), exit(1);

        set_backlight((uint_fast8_t)atoi(optarg));
        break;
      case 'u':
        set_backlight_step_up();
        break;
      case 'd':
        set_backlight_step_down();
        break;
      case 'h':
        print_help();
        exit(0);
        break;
    }
    return 0;
  }
}

void print_help(void) { errno = ENOSYS, perror(0); }

void set_backlight_step_up(void) {
  uint_fast16_t s, c;

  s = find_step_size(), c = get_current_backlight();
  set_backlight_raw(s + c);
}

void set_backlight_step_down(void) {
  uint_fast16_t s, c;

  s = find_step_size(), c = get_current_backlight();
  set_backlight_raw(c - s);
}

uint_fast16_t find_step_size(void) {
  uint_fast16_t s;
  return s = get_max_backlight() / 20;
}

uint_fast16_t find_percentage_of_max(const uint_fast16_t p) {
  uint_fast16_t v, x;
  v = get_max_backlight() * (p / 100.0);
  if (v == 0) return 1;
  return v;
}

void set_backlight(const uint_fast8_t p) {
  uint_fast16_t val;

  if (p > 100 || p == 0) errno = EINVAL, perror(0), exit(1);

  val = find_percentage_of_max(p);

  set_backlight_raw(val);
}

void set_backlight_raw(const uint_fast16_t val) {
  FILE *f;
  char s[MAX_STR];
  int ret;

  snprintf(s, MAX_STR, "%lu", val);

  f = fopen(BACKLIGHT_FILE, "w" /* truncate me, daddy */);
  if (f == NULL) perror(BACKLIGHT_FILE), exit(1);

  ret = fputs(s, f);
  if (!(ret > 0)) perror(BACKLIGHT_FILE), exit(1);

  ret = fclose(f);
  if (ret != 0) perror(NULL), exit(1);
}

void print_current_backlight(void) {
  float p, c, x;
  c = get_current_backlight(), x = get_max_backlight();
  p = c/x * 100;
  printf("%1.0f / %1.0f → %1.1f%% \n", c, x, p ); }


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
  if (f == NULL) perror(filepath), exit(1);

  buftest = fgets(buf, MAX_STR, f);
  if (buf != buftest) perror(filepath), exit(1);

  result = (uint_fast16_t)atoi(buf);

  ret = fclose(f);
  if (ret != 0) perror(NULL), exit(1);

  return result;
}
