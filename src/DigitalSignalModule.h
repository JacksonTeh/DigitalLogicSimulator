#ifndef DigitalSignalModule_H
#define DigitalSignalModule_H

// #define NO_OF_PIN   6

typedef enum {LOW, HIGH, UNKNOWN} State;
typedef enum {ERR_NO_ERROR, ERR_INVALID_PIN_NUMBER} Error;

typedef int Inbit;
typedef int Outbit;

typedef struct Module Module;
typedef struct Pipe Pipe;
typedef struct ModuleAndPin ModuleAndPin;
typedef struct Pin Pin;
// typedef struct Outbit Outbit;

struct ModuleAndPin
{
    //RBT node here to be include
    Module *module;
    int pinNumber;
};

struct Pin
{
    Module *moduleConnected;    //module that is connected to
    int pinNumber;              //pin of the module connected to
    int state;
};

// struct Outbit
// {
    // Module *module;
// };

struct Module
{
    int (*event)(void *object);
    void (*set)(void *pin, void *state);
    void (*configure)(void *thisModule, void *fromPin, void *nextModule, void *toPin);
    // Inbit clk;
    Inbit *input;
    Outbit *output;
    int state;
};

struct Pipe
{
    int (*event)(void *object);
    void (*set)(void *pin, void *state);
    void (*configure)(void *nextModuleConnected, void *fromPin, void *toPin);
    ModuleAndPin *moduleAndPin;
    int stateToFire;
};

Module *createdAndModule(int numberOfPin);
Module *createdOrModule(int numberOfPin);
Module *createdXorModule(int numberOfPin);
Module *createdNandModule(int numberOfPin);
Module *createdNorModule(int numberOfPin);
Module *createdNotModule(int numberOfPin);
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
void configureInputOutput(void *thisModule, void *fromPin, void *nextModule, void *toPin);

void pipeAttach(Pipe **pipe, Module **fromModule, void *fromPin, Module **toModule, void *toPin);
void registerEvent(Module *module, unsigned long long expiredPeriod);

#endif // DigitalSignalModule_H
