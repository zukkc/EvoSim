#include "app/Application.h"

int main() {
  evosim::Application app;

  app.setup();
  app.loop();
  app.end();

  return 0;
}