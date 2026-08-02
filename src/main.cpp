#include "app/Application.h"

int main() {
  Application app;

  app.setup();
  app.loop();
  app.end();

  return 0;
}