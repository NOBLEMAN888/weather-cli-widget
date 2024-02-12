#include "event_listener.h"

bool ListenKeyPressed(int key){
  if (GetKeyState(key) & 0x8000) {
    if (!(GetKeyState(key) & 0x8000)) {
      std::cout << "Pressed!";
      return true;
    }
  }
  return false;
}
