#ifdef _MSC_VER
#pragma warning(disable: 4996 4477)
#endif
#ifdef NDEBUG
#undef NDEBUG
#endif

#define main main_example
#include "./example.c"
#undef main

#define try try_
#define main main_infcover
#include "./infcover.c"
#undef main

int main(int argc, char *argv[])
{
    int ret = 0;
    ret += main_example(argc, argv);
    ret += main_infcover();

    if (ret == 0)
        printf("\ntests passed. OK!\n\n");
    return ret;
}
