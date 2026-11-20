#include "zvm.h"
#include "../types.h"
#include "../console/console.h"

#define MAXVARS 64
static int strcmpz(const char *a, const char *b) {
    while (*a && *b && *a==*b){a++;b++;}
    return (unsigned char)*a - (unsigned char)*b;
}
typedef struct { char name[32]; int value; int isstr; char str[128]; } var_t;
static var_t vars[MAXVARS];
static int nvars = 0;

static var_t *getvar(const char *name) {
    for (int i = 0; i < nvars; i++) if (strcmpz(vars[i].name, name) == 0) return &vars[i];
    if (nvars < MAXVARS) { vars[nvars].name[0]=0; int i=0; while (name[i] && i<31) { vars[nvars].name[i]=name[i]; i++; } vars[nvars].name[i]=0; vars[nvars].value=0; vars[nvars].isstr=0; vars[nvars].str[0]=0; return &vars[nvars++]; }
    return NULL;
}



/* trim trailing spaces */
static void trim(char *s){ int i=0; while(s[i]) i++; while(i>0 && (s[i-1]==' '||s[i-1]=='\t'||s[i-1]=='\r')) s[--i]=0; }

static int eval_int(const char *e) {
    /* very simple: integer literal or variable */
    while (*e==' ') e++;
    if (*e>='0' && *e<='9') { int v=0; while(*e>='0'&&*e<='9'){v=v*10+(*e-'0');e++;} return v; }
    char name[32]; int i=0; while (e[i] && e[i]!=' ' && i<31){name[i]=e[i];i++;} name[i]=0;
    var_t *v=getvar(name); return v?v->value:0;
}

static void do_say(const char *e) {
    while (*e==' ') e++;
    if (*e=='"') {
        e++; char buf[256]; int i=0;
        while (*e && *e!='"' && i<255) buf[i++]=*e++;
        buf[i]=0; console_write(buf); console_write("\n");
    } else {
        /* expression: str(var) or var or concat with + */
        /* handle + concatenation minimally */
        console_write("[expr]"); console_write(e); console_write("\n");
    }
}

static void do_let(const char *line) {
    /* let name = expr */
    const char *p=line+4; while(*p==' ')p++;
    char name[32]; int i=0; while(*p && *p!=' ' && *p!='=' && i<31){name[i++]=*p;p++;}
    name[i]=0;
    while(*p==' '||*p=='=')p++;
    var_t *v=getvar(name);
    if (!v) return;
    if (*p=='"') { v->isstr=1; p++; int j=0; while(*p && *p!='"' && j<127) v->str[j++]=*p++; v->str[j]=0; }
    else { v->isstr=0; v->value=eval_int(p); }
}

static void exec_script(const char *src) {
    char line[512]; int li=0;
    const char *p=src;
    /* We'll process line by line; handle when/otherwise/loop minimally by direct eval */
    while (1) {
        /* read next line */
        li=0;
        while (*p && *p!='\n') { if (li<511) line[li++]=*p; p++; }
        if (*p=='\n') p++;
        line[li]=0;
        trim(line);
        /* skip empty */
        int k=0; while(line[k]==' ')k++;
        if (line[k]==0) { if (*p==0) break; continue; }
        if (starts(line+k, "let ")) do_let(line+k);
        else if (starts(line+k, "say ")) do_say(line+k+4);
        else { /* ignore other constructs for now */ }
        if (*p==0) break;
    }
}

int zvm_run(const char *src) {
    nvars=0;
    console_write("ZVM: executing\n");
    exec_script(src);
    console_write("ZVM: done\n");
    return 0;
}
EOF