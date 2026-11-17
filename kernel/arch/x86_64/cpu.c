#include "cpu.h"
#include "../../drivers/serial.h"
void cpu_init(void) {
    serial_write("CPU: entered x86_64 kernel entry point\r\n");
}
