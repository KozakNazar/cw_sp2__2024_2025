extern int main_spirit(int argc, char* argv[]);
extern int main_syntax(int argc, char* argv[]);

extern "C" int call_main_spirit(int argc, char* argv[]) {
    return main_spirit(argc, argv);
}

extern "C" int call_main_syntax(int argc, char* argv[]) {
    return main_syntax(argc, argv);
}