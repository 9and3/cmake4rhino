#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

const char* logo =
R"(            [38;5;252m______   ____                       [38;5;33m! [38;5;1m,                
            [38;5;7mzummms  ammmmm                     [38;5;33m@g [38;5;1m[L               
            [38;5;251mB@BBB  :@B@BBBN                  [38;5;33m_@@@ [38;5;1m[@g              
     [38;5;250m____  @@@@F  g@@@@@B"                  [38;5;33m/@@@@ [38;5;1m'@@@             
   [38;5;249m4=PT0=M4=9P  +9f#="  .+D9               [38;5;33m@@@@W   [38;5;1m@@@@_           
           [38;5;248m~wwg    ,_aagypgpa_           [38;5;33m_@@@P  [38;5;248m_  [38;5;1m@@@@@h          
              [38;5;247m+g_  gg>'-4qgggW@g__      [38;5;33m/@P  [38;5;247m_gg  [38;5;1m0@@@@@@@         
                [38;5;246mB, @@@F  , "==>          _o@WWW  [38;5;2mw_ [38;5;1m"B@@@@@,       
                 [38;5;245m" """"[38;5;102m_  .[38;5;245m' [38;5;102m..[38;5;245m"""`[38;5;102m. .[38;5;245m"""""""" [38;5;2m_@@@@g_ [38;5;1m"@@@@h      
                   [38;5;244m'"""""""""""""""""[38;5;243m,[38;5;244m"""""  [38;5;2m_@@@@@@@@@g_ [38;5;1m"@@@     
                       [38;5;242m">[38;5;241m_[38;5;242m`+====="""T= "" [38;5;2m_g@@@@@@@@@@@@@@g_ [38;5;1m"@,   
                           [38;5;240m~[38;5;239m_  [38;5;240m~~+~  ~  [38;5;2m+BBBBBBBBBBBBBBBBBBBB+.    
                              [38;5;238m`  ^[38;5;237m-[38;5;236m_[38;5;237m-[0m
)";

int main() {
    // Info lines to print
    std::vector<std::string> info = { 
        "\033[90mProject:\033[0m       cmake4rhino",
        "\033[90mAuthor:\033[0m        Andrea Settimi (9and3)",
        "\033[90mDescription:\033[0m   Rhino C++ Plugin in CMake template",
        "\033[90mYear:\033[0m          July  2025",
        "\033[90mVersion:\033[0m       1.2.0",
        "\033[90mWebsite:\033[0m       https://github.com/9and3/cmake4rhino",
        "\033[90mLicense:\033[0m       MIT",
        "\033[90mC++ Standard:\033[0m  17",
        "\033[90mCMake Min Ver:\033[0m 3.15",
        "\033[90mSDK:\033[0m           Rhino 8/7",
        "\033[90mTemplate:\033[0m      cookiecutter gh:9and3/cmake4rhino",
        "\033\033[0m               --checkout cookietemplate"
    };

    // Split logo into lines
    std::vector<std::string> logo_lines;
    std::istringstream logo_stream(logo);
    std::string line;
    while (std::getline(logo_stream, line)) {
        logo_lines.push_back(line);
    }

    // Calculate padding for info alignment
    size_t logo_width = 0;
    for (const auto& l : logo_lines) {
        if (l.length() > logo_width) logo_width = l.length();
    }
    size_t pad = 4; // space between logo and info

    // Print logo and info side by side
    size_t max_lines = std::max(logo_lines.size(), info.size());
    for (size_t i = 0; i < max_lines; ++i) {
        if (i < logo_lines.size())
            std::cout << logo_lines[i];
        else
            std::cout << std::string(logo_width, ' ');

        std::cout << std::string(pad, ' ');

        if (i < info.size())
            std::cout << info[i];

        std::cout << std::endl;
    }

    return 0;
}