#include "event_listener.h"

bool ListenKeyPressed(int key) {
  if (GetKeyState(key) & 0x8000) {
    return true;
  }
  return false;
}
