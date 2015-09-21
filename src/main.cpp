#include <portugol/code/code_file.hpp>
#include <portugol/code/code_string.hpp>
#include <portugol/code/environment.hpp>
using namespace portugol::code;

#include <cstdio>

int main(int argc, char** argv)
{
    try
    {
        Environment::clear();

        if (argc < 2)
            Environment::loadFile("main.portugol");
        else
            Environment::loadFile(argv[1]);

        auto result = Environment::get("programa").m_node->execute();
        printf("program result : %d\n", result.getInt32());
    }
    catch (std::string e)
    {
        printf("ERROR : %s\n", e.c_str());
    }

    system("PAUSE");
    return 0;
}
