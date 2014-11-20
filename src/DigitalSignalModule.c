#include <malloc.h>
#include "DigitalSignalModule.h"

/**
 *
 * ========================
 * |       AND Gate       |
 * ========================
 *
 */ 
Module *createdAndModule(Module *module, Inbit idata1, Inbit idata2)
{
    Module *andModule;

    andModule = malloc(sizeof(Module));
    andModule->input1a = idata1;
    andModule->input2a = idata2;
    andModule->event = andEvent;
    andModule->set = setAnd;
    andModule->configure = configureInputOutput;
    // andModule->output->module = module;

    return andModule;
}

int andEvent(void *module)
{

}

void setAnd(void *pin, void *state)
{
    
}

/**
 *
 * ========================
 * |       OR Gate        |
 * ========================
 *
 */ 
Module *createdOrModule(Module *module, Inbit idata1, Inbit idata2)
{
    Module *orModule;

    orModule = malloc(sizeof(Module));
    orModule->input1a = idata1;
    orModule->input2a = idata2;
    orModule->event = orEvent;
    orModule->set = setOr;
    orModule->configure = configureInputOutput;
    // andModule->output->module = module;

    return orModule;
}

int orEvent(void *module)
{

}

void setOr(void *pin, void *state)
{
    
}

/**
 *
 * ========================
 * |       XOR Gate       |
 * ========================
 *
 */ 
Module *createdXorModule(Module *module, Inbit idata1, Inbit idata2)
{
    Module *xorModule;

    xorModule = malloc(sizeof(Module));
    xorModule->input1a = idata1;
    xorModule->input2a = idata2;
    xorModule->event = xorEvent;
    xorModule->set = setXor;
    xorModule->configure = configureInputOutput;
    // andModule->output->module = module;

    return xorModule;
}

int xorEvent(void *module)
{

}

void setXor(void *pin, void *state)
{
    
}

/**
 *
 * ========================
 * |      NAND Gate       |
 * ========================
 *
 */ 
Module *createdNandModule(Module *module, Inbit idata1, Inbit idata2)
{
    Module *nandModule;

    nandModule = malloc(sizeof(Module));
    nandModule->input1a = idata1;
    nandModule->input2a = idata2;
    nandModule->event = nandEvent;
    nandModule->set = setNand;
    nandModule->configure = configureInputOutput;
    // andModule->output->module = module;

    return nandModule;
}

int nandEvent(void *module)
{

}

void setNand(void *pin, void *state)
{
    
}

/**
 *
 * ========================
 * |       NOR Gate       |
 * ========================
 *
 */ 
Module *createdNorModule(Module *module, Inbit idata1, Inbit idata2)
{
    Module *norModule;

    norModule = malloc(sizeof(Module));
    norModule->input1a = idata1;
    norModule->input2a = idata2;
    norModule->event = norEvent;
    norModule->set = setNor;
    norModule->configure = configureInputOutput;
    // andModule->output->module = module;

    return norModule;
}

int norEvent(void *module)
{

}

void setNor(void *pin, void *state)
{
    
}

/**
 *
 * ========================
 * |       NOT Gate       |
 * ========================
 *
 */
Module *createdNotModule(Module *module, Inbit idata1, Inbit idata2)
{
    Module *notModule;

    notModule = malloc(sizeof(Module));
    notModule->input1a = idata1;
    notModule->input2a = idata2;
    notModule->event = notEvent;
    notModule->set = setNot;
    notModule->configure = configureInputOutput;
    // andModule->output->module = module;

    return notModule;
}

int notEvent(void *module)
{

}

void setNot(void *pin, void *state)
{
    
}

void destroyModule(Module *module)
{
    if(module != NULL)
        free(module);
}

void configureInputOutput(void *nextModuleConnected, void *fromPin, void *toPin)
{
    
}

void pipeAttach(Pipe **pipe, Module **fromModule, void *fromPin, Module **toModule, void *toPin)
{

}