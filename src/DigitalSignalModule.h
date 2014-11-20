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

Module *createdAndModule(Module **module);
Module *createdOrModule(Module **module);
Module *createdXorModule(Module **module);
Module *createdNandModule(Module **module);
Module *createdNorModule(Module **module);
Module *createdNotModule(Module **module);

void pipeAttach(Pipe **pipe, Module **fromModule, void *fromPin, Module **toModule, void *toPin);

#endif // DigitalSignalModule_H
