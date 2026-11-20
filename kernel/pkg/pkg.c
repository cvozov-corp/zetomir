#include "pkg.h"
#include "../../types.h"
#include "../../console/console.h"

static char packages[16][32];
static int npkg = 0;

void pkg_init(void) { npkg = 0; }

int pkg_install(const char *name) {
    if (npkg >= 16) return -1;
    int i=0; while (name[i] && i<31) { packages[npkg][i]=name[i]; i++; } packages[npkg][i]=0;
    npkg++;
    console_write("installed: "); console_write(name); console_write("\n");
    return 0;
}

int pkg_remove(const char *name) {
    for (int i=0;i<npkg;i++) {
        int eq=1,k=0;
        while (name[k]||packages[i][k]) { if (name[k]!=packages[i][k]){eq=0;break;} k++; }
        if (eq) {
            for (int j=i;j<npkg-1;j++) for (int k=0;k<32;k++) packages[j][k]=packages[j+1][k];
            npkg--;
            console_write("removed: "); console_write(name); console_write("\n");
            return 0;
        }
    }
    return -1;
}

void pkg_list(void) {
    for (int i=0;i<npkg;i++) { console_write(packages[i]); console_write("\n"); }
}
EOF