#include <states/state_load.hpp>
#include <compiler/tokenizer.hpp>

#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
/*
    try
    {
        App app(argc, argv);
        StateStack::push(new StateLoad(&app));
        app.run();
    }
    catch (exception::IException e)
    {
        std::cout << "Error : " << e.what() << std::endl;
    }
*/
    Tokenizer tokenizer;
    std::fstream file("projectos/teste/main.portugol");

    std::string line;
    while(file.good())
    {
        char c;

        file.get(c);
        if (file.good())
        {
            if (c != '\n')
                line += c;
            else
            {
                if (tokenizer.tokenize(line))
                {
                    std::cout << "tokens : ";

                    bool first = true;
                    auto list = tokenizer.getTokens();
                    for (auto it = list.begin(), end = list.end(); it != end; ++it)
                    {
                        if (first)
                            first = false;
                        else
                            std::cout << std::endl << "         ";

                        std::cout << it->toString();
                    }
                    std::cout << std::endl;
                }

                line = "";
            }
        }
    }

    system("PAUSE");

    return 0;
}
