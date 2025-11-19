#include "framebufApp.h"
#include "mcore.h"

#include <iostream>


//----------------------------------------------------------------------------------------------

void guardedMain()
{
    FramebufApp app("mos1062", 1024, 600);
    app.mainLoop();
}


int main()
{
    try
    {
        guardedMain();
    }
    catch (const std::string msg)
    {
        std::cerr << "Catastophe: " << msg << std::endl;
        return 1;
    }
}

//----------------------------------------------------------------------------------------------

