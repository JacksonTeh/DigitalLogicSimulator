#ifndef DigitalSignalModule_H
#define DigitalSignalModule_H

typedef enum {LOW, HIGH} State;

typedef int Inbit;

typedef struct Module Module;
typedef struct Pipe Pipe;
typedef struct ModulePin ModulePin;
typedef struct Outbit Outbit;

struct ModulePin
{
    Module *module;
    int pinNumber;
};

struct Outbit
{
    Module *module;
};

struct Module
{
    int (*event)(void *object);
    void (*set)(void *pin, void *state);
    void (*configure)(void *nextModuleConnected, void *fromPin, void *toPin);
    Inbit clk;
    Inbit input1a;
    Inbit input2a;
    Outbit output;
    int state;
};

struct Pipe
{
    int (*event)(void *object);
    void (*set)(void *pin, void *state);
    void (*configure)(void *nextModuleConnected, void *fromPin, void *toPin);
    ModulePin *modulePin;
    int stateToFire;
};

Module *createdAndModule(Module *module, Inbit idata1, Inbit idata2);
Module *createdOrModule(Module *module, Inbit idata1, Inbit idata2);
Module *createdXorModule(Module *module, Inbit idata1, Inbit idata2);
Module *createdNandModule(Module *module, Inbit idata1, Inbit idata2);
Module *createdNorModule(Module *module, Inbit idata1, Inbit idata2);
Module *createdNotModule(Module *module, Inbit idata1, Inbit idata2);
void destroyModule(Module *module);

int andEvent(void *module);
void setAnd(void *pin, void *state);
int orEvent(void *module);
void setOr(void *pin, void *state);
int xorEvent(void *module);
void setXor(void *pin, void *state);
int nandEvent(void *module);
void setNand(void *pin, void *state);
int norEvent(void *module);
void setNor(void *pin, void *state);
int notEvent(void *module);
void setNot(void *pin, void *state);
void configureInputOutput(void *nextModuleConnected, void *fromPin, void *toPin);

void pipeAttach(Pipe **pipe, Module **fromModule, void *fromPin, Module **toModule, void *toPin);

#endif // DigitalSignalModule_H
