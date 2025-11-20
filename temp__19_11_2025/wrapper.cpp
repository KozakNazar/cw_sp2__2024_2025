extern int main_spirit(int argc, char* argv[]);

extern "C" int call_main_spirit(int argc, char* argv[]) {
    return main_spirit(argc, argv);

}
