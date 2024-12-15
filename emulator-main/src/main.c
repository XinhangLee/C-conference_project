#include <emulator.h>

static char* imgfile = NULL;

static void parse_args(int argc, char* argv[]) {
  if (argc > 1) imgfile = argv[1];
}

int main(int argc, char* argv[]) {
  parse_args(argc, argv);

  emulator_init(imgfile);

  emulator_run();

  return is_exit_status_bad();
}