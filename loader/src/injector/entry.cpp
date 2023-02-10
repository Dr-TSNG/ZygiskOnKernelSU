#include "daemon.h"
#include "logging.h"
#include "zygisk.hpp"
#include "module.hpp"

using namespace std;

void *self_handle = nullptr;

[[gnu::destructor]] [[maybe_unused]]
static void zygisk_cleanup_wait() {
    if (self_handle) {
        // Wait 10us to make sure none of our code is executing
        timespec ts = { .tv_sec = 0, .tv_nsec = 10000L };
        nanosleep(&ts, nullptr);
    }
}

extern "C" [[gnu::visibility("default")]]
void entry(void *handle) {
#ifdef NDEBUG
    logging::setfd(zygiskd::RequestLogcatFd());
#endif
    self_handle = handle;

    LOGD("Load injector successfully");
    hook_functions();
}

// The following code runs in zygote/app process

static inline bool should_load_modules(uint32_t flags) {
    return (flags & UNMOUNT_MASK) != UNMOUNT_MASK &&
           (flags & PROCESS_IS_MAGISK_APP) != PROCESS_IS_MAGISK_APP;
}
