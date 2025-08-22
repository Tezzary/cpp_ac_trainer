#include "trainer.h"
#include "guimanager.h"

#include <thread>
#include <atomic>

int main() {

    std::atomic<bool> aimbotEnabled {true};
    std::atomic<char> aimbotKey {};
    std::thread t(run);
    StartUI();
}
