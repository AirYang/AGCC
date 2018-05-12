#include "../include/agcc.h"

void MacroTest() {
  printf("------Macro Test Begin------\n");
#ifdef DEBUG
  printf("  DEBUG Macro Open\n");
#endif  // DEBUG
  printf("------Macro Test End------\n");
}

int main(int argc, char** argv) {
  MacroTest();

  AGCC agcc(argc, argv);
  agcc.run();
  return 0;
}
