#include <scheme.h>
#include <stdio.h>

extern void **getfs();
extern void **getgs();
extern void **getfs2c();
extern void **getgs58();
extern void **get_tls_vars_ptr(uintptr_t delta);

extern int _tls_index;

static __declspec(thread) void *tls_space;

__declspec(dllimport) uintptr_t scheme_tls_delta;

static int run(Scheme_Env *e, int argc, char *argv[])
{
    void **base;

    base = getgs58();

    printf("getfs() = %p\n", getfs());
    printf("getgs() = %p\n", getgs());
    //printf("getfs2c() = %p\n", getfs2c());
    printf("getgs58() = %p\n", getgs58());
    printf("get_tls_vars_ptr() = %p\n", get_tls_vars_ptr(scheme_tls_delta));
    printf("*get_tls_vars_ptr() = %p\n", *get_tls_vars_ptr(scheme_tls_delta));
    printf("&tls_space - base[tls_index] = %zd\n", (uintptr_t)&tls_space - (uintptr_t)base[_tls_index]);
    printf("scheme_tls_delta = %zd\n", scheme_tls_delta);
    printf("scheme_get_thread_local_variables() = %p\n", scheme_get_thread_local_variables());

    return 0;
}

int main(int argc, char *argv[])
{
    scheme_register_tls_space(&tls_space, _tls_index);
    return scheme_main_setup(1, run, argc, argv);
}

