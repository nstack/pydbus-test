#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
#include <systemd/sd-bus.h>

int main(int argc, char *argv[]) {
        sd_bus_error error = SD_BUS_ERROR_NULL;
        sd_bus_message *out_msg = NULL;
        sd_bus_message *in_msg = NULL;
        sd_bus *bus = NULL;
        double result;
        int r;
        
        
        if (argc < 2) {
                fprintf(stderr, "Usage: sdbus-client SIZE");
                return EXIT_FAILURE;
        }

        uint64_t in_arr_size = strtoul(argv[1], NULL, 0);
        uint8_t in_arr[in_arr_size];
        fprintf(stdout, "Sending PING - %" PRIu64 "\n", in_arr_size);


        /* Connect to the user bus */
        r = sd_bus_open_user(&bus);
        if (r < 0) {
                fprintf(stderr, "Failed to connect to user bus: %s\n", strerror(-r));
                goto finish;
        }

        r = sd_bus_message_new_method_call(bus, &in_msg, 
                               "com.nstack.DbusTest",           /* service to contact */
                               "/com/nstack/DbusTest",          /* object path */
                               "com.nstack.DbusTest",   /* interface name */
                               "Ping");                          /* method name */

        if (r < 0) {
                fprintf(stderr, "Failed to create new method call: %s\n", error.message);
                goto finish;
        }

        r = sd_bus_message_append_array(in_msg, 'y', in_arr, sizeof(uint8_t) * in_arr_size);
        if (r < 0) {
                fprintf(stderr, "Failed to add to message: %s\n", error.message);
                goto finish;
        }

        sd_bus_call(bus, in_msg, 0, &error, &out_msg);

        if (r < 0) {
                fprintf(stderr, "Failed to issue method call: %s\n", error.message);
                goto finish;
        }


        /* Parse the in_msg message */
        r = sd_bus_message_read(out_msg, "d", &result);
        if (r < 0) {
                fprintf(stderr, "Failed to parse in_msg message: %s\n", strerror(-r));
                goto finish;
        }

        printf("PONG - %lg\n", result);

finish:
        sd_bus_error_free(&error);
        sd_bus_message_unref(in_msg);
        sd_bus_message_unref(out_msg);
        sd_bus_unref(bus);

        return r < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
