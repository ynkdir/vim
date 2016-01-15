#include <windows.h>
#include <stdio.h>
#include <scheme.h>

#define RACKET_DLL "libracket3m_9z0ds0.dll"

extern void **getfs();
extern void **getgs();
extern void **getfs2c();
extern void **getgs58();
extern void **get_tls_vars_ptr(uintptr_t delta);

extern int _tls_index;

static __declspec(thread) void *tls_space;

uintptr_t *p_scheme_tls_delta;
void (*p_scheme_register_tls_space)(void *tls_space, int _tls_index);
int (*p_scheme_main_setup)(int no_auto_statics, Scheme_Env_Main _main, int argc, char **argv);
void *(*p_scheme_external_get_thread_local_variables)(void);

void load() {
    HINSTANCE h = LoadLibrary(RACKET_DLL);
    *(void **)&p_scheme_register_tls_space = (void *)GetProcAddress(h, "scheme_register_tls_space");
    *(void **)&p_scheme_main_setup = (void *)GetProcAddress(h, "scheme_main_setup");
    *(void **)&p_scheme_external_get_thread_local_variables = (void *)GetProcAddress(h, "scheme_external_get_thread_local_variables");
    *(void **)&p_scheme_tls_delta = (void *)GetProcAddress(h, "scheme_tls_delta");
}

static int run(Scheme_Env *e, int argc, char *argv[])
{
    void **base;

    base = getgs58();

    printf("getfs() = %p\n", getfs());
    printf("getgs() = %p\n", getgs());
    //printf("getfs2c() = %p\n", getfs2c());
    printf("getgs58() = %p\n", getgs58());
    printf("get_tls_vars_ptr() = %p\n", get_tls_vars_ptr(*p_scheme_tls_delta));
    printf("*get_tls_vars_ptr() = %p\n", *get_tls_vars_ptr(*p_scheme_tls_delta));
    printf("&tls_space - base[tls_index] = %lld\n", (uintptr_t)&tls_space - (uintptr_t)base[_tls_index]);
    printf("scheme_tls_delta = %lld\n", *p_scheme_tls_delta);
    //printf("scheme_get_thread_local_variables() = %p\n", scheme_get_thread_local_variables());
    printf("scheme_external_get_thread_local_variables() = %p\n", p_scheme_external_get_thread_local_variables());

    return 0;
}

int main(int argc, char *argv[])
{
    load();
    Sleep(1000);
    p_scheme_register_tls_space(&tls_space, _tls_index);
    Sleep(1000);
    return p_scheme_main_setup(1, run, argc, argv);
}

