#include <malloc.h>
#include "DigitalSignalModule.h"

Module *createdAndModule(Inbit idata1, Inbit idata2)
{
    Module *andModule;

    andModule = malloc(sizeof(Module));
    andModule->input1a = idata1;
    andModule->input2a = idata2;
    andModule->event = andEvent;
    andModule->set = set;
    andModule->configure = configureInputOutput;

    return andModule;
}

Module *createdOrModule(Module **module)
{

}

Module *createdXorModule(Module **module)
{

}

Module *createdNandModule(Module **module)
{

}

Module *createdNorModule(Module **module)
{

}

Module *createdNotModule(Module **module)
{

}

void destroyModule(Module *module)
{
    if(module != NULL)
        free(module);
}

int andEvent(Module **module)
{

}

void set(int pin, int state)
{
    
}

void configureInputOutput(Module *nextModuleConnected, int *fromPin, int *toPin)
{
    
}

void pipeAttach(Pipe **pipe, Module **fromModule, void *fromPin, Module **toModule, void *toPin)
{

}