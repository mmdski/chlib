int main(int argc, char **argv)
{
    int k = 0x7fffffff;
    k += argc;

    // suppress unused parameter errors
    (void)k;
    (void)argv;

    return 0;
}
