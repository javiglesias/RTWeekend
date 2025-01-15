#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

static const uint32_t wayland_display_object_id = 1;
static const uint16_t wayland_wl_registry_event_global = 0;
static const uint16_t wayland_shm_pool_event_format = 0;
static const uint16_t wayland_wl_buffer_event_release = 0;
static const uint16_t wayland_xdg_wm_base_event_ping = 0;
static const uint16_t wayland_xdg_toplevel_event_configure = 0;
static const uint16_t wayland_xdg_toplevel_event_close = 1;
static const uint16_t wayland_xdg_surface_event_configure = 0;
static const uint16_t wayland_wl_display_get_registry_opcode = 1;
static const uint16_t wayland_wl_registry_bind_opcode = 0;
static const uint16_t wayland_wl_compositor_create_surface_opcode = 0;
static const uint16_t wayland_xdg_wm_base_pong_opcode = 3;
static const uint16_t wayland_xdg_surface_ack_configure_opcode = 4;
static const uint16_t wayland_wl_shm_create_pool_opcode = 0;
static const uint16_t wayland_xdg_wm_base_get_xdg_surface_opcode = 2;
static const uint16_t wayland_wl_shm_pool_create_buffer_opcode = 0;
static const uint16_t wayland_wl_surface_attach_opcode = 1;
static const uint16_t wayland_xdg_surface_get_toplevel_opcode = 1;
static const uint16_t wayland_wl_surface_commit_opcode = 6;
static const uint16_t wayland_wl_display_error_event = 0;
static const uint32_t wayland_format_xrgb8888 = 1;
static const uint32_t wayland_header_size = 8;
static const uint32_t color_channels = 4;

static int wayland_display_connect()
{
    char* xdg_runtime = getenv("XDG_RUNTIME_DIR");
    if(xdg_runtime == NULL)
        signal(SIGTRAP, NULL);
        
    uint64_t xdg_runtime_len = strlen(xdg_runtime );
    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    if(xdg_runtime_len > strlen(addr.sun_path))
        signal(SIGTRAP, NULL);
    uint64_t socket_path_len = 0;
    memcpy(addr.sun_path, xdg_runtime, xdg_runtime_len);
    socket_path_len += xdg_runtime_len;
    addr.sun_path[socket_path_len++] = '/';
    fprintf(stderr, "SUN PATH: %s\n", addr.sun_path);

    char* wayland_display = getenv("WAYLAND_DISPLAY");
    if(wayland_display == NULL)
    {
        char wayland_display_default[] = "wayland-0";
        uint64_t wayland_default_len = strlen(wayland_display_default);
        memcpy(addr.sun_path + socket_path_len, wayland_display_default, wayland_default_len);
        socket_path_len += wayland_default_len;

    } else {
        uint64_t wayland_display_len = strlen(wayland_display);
        memcpy(addr.sun_path + socket_path_len, wayland_display, wayland_display_len);
        socket_path_len += wayland_display_len;
    }
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(fd == -1 || connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
        exit(errno);
    return 0;
}