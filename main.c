#include <unistd.h>
#include <stdio.h>

#include "lv_8ms.h"
#include "qm_ui_entry.h"

static void lv_8ms_handle_signal(int signo)
{
    lv_8ms_stop();
}

static void lv_8ms_setup_signals(void)
{
    struct sigaction s;

    memset(&s, 0, sizeof(s));
    s.sa_handler = lv_8ms_handle_signal;
    sigemptyset(&s.sa_mask);
    s.sa_flags = 0;
    sigaction(SIGTERM, &s, NULL);

    s.sa_handler = SIG_IGN;
    sigaction(SIGPIPE, &s, NULL);
}

int main(int argc, char *argv[])
{
    lv_8ms_setup_signals();

    lv_8ms_init();
    lv_8ms_set_loop_cb(lv_qm_ui_loop);

    lv_qm_ui_entry();

    lv_8ms_start();

    lv_8ms_deinit();

    return 0;
}
