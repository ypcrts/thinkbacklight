#include "thinkbacklight.h"

/* thinkbacklight.c */
void print_help(void);
void print_current_backlight(void);
void print_max_backlight(void);
uint_fast16_t get_max_backlight(void);
uint_fast16_t get_current_backlight(void);
uint_fast16_t get_backlight_value(const char *filepath);

static int fade_flag = 0;

int main(int argc, char **argv, char **envp) {
  static struct option long_options[] = {{"check-current", no_argument, 0, 'c'},
                                         {"check-max", no_argument, 0, 'x'},
                                         {"set", required_argument, 0, 's'},
                                         {"up", no_argument, 0, 'u'},
                                         {"down", no_argument, 0, 'd'},
                                         {"fade", no_argument, &fade_flag, 1}};
  int c, option_index;

  if (argc == 0) {
    print_help();
    exit(0);
  }
  while (c == getopt_long(argc, argv, "-cxsud", long_options, &option_index)) {

    switch (c) {
    case -1:
      break;
    case 0
        /* set a flag */
        break;
        case 'c':
      break;
    case 'x':
      break;
    case 's':
      break;
    case 'u':
      break;
    case 'd':
      break;
      return 0;
    }

    void print_help(void) {}

    void print_current_backlight(void) {
      printf("%ld\n", get_current_backlight());
    }

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
      if (ret != 0)
        perror(NULL);

      return result;
    }
