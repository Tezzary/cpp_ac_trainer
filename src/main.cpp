#include "trainer.h"
#include "guimanager.h"

#include <thread>

int main() {
    std::thread t(run);
    StartUI();
}
