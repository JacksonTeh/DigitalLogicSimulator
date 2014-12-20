#ifndef DigitalSignalModule_H
#define DigitalSignalModule_H

// #include "Node.h"

#define TOTAL_PIN       14
#define ONE_PICO_SEC    1
#define ONE_NANO_SEC    1000 * ONE_PICO_SEC
#define NAND_PROPAGATION_DELAY  9.5 * ONE_NANO_SEC
#define NOR_PROPAGATION_DELAY   10 * ONE_NANO_SEC
#define AND_PROPAGATION_DELAY   9 * ONE_NANO_SEC
#define OR_PROPAGATION_DELAY    14 * ONE_NANO_SEC
#define XOR_PROPAGATION_DELAY   10 * ONE_NANO_SEC
#define NOT_PROPAGATION_DELAY   9.5 * ONE_NANO_SEC

typedef enum {QUAD_2_INPUT, TRI_3_INPUT, DUAL_4_INPUT, HEX_INV} InputType;
typedef enum {LOW, HIGH, UNKNOWN} State;
typedef enum {INPUT_PIN, OUTPUT_PIN, UNUSED_PIN} TypeOfPin;
typedef enum {ERR_NO_ERROR, ERR_INVALID_INPUT_TYPE, ERR_INVALID_NUM_OF_PIN, ERR_NOT_OUT_PIN, ERR_NOT_IN_PIN} Error;

typedef int PinType;

typedef struct Module Module;
typedef struct Pipe Pipe;
typedef struct ModuleAndPin ModuleAndPin;
typedef struct Pin Pin;

#include "Node.h"

struct ModuleAndPin
{
    Module *module;
    Pin *pin;
};

struct Pin
{
    // void *moduleConnected;    //module that is connected to
    Pipe *pipe;
    int pinNumber;              //pin of the module connected to
    int state;
    PinType type;
};

struct Module
{
    char *name;
    void (*event)(void *moduleAndPin, unsigned long long delay);
    void (*set)(void *moduleAndPin, int state, unsigned long long delay);
    void (*configure)(void *thisModule, void *fromPin, void *nextModule, void *toPin);
    int typeOfInput;
    int totalPin;
    Pin pin[TOTAL_PIN];
};

struct Pipe
{
    void (*event)(void *object, void *node, unsigned long long inputDelay);
    void (*set)(void *pipe, int state, unsigned long long inputDelay);
    void (*configure)(void *thisModule, void *fromPin, void *nextModule, void *toPin);
    Node *data;         //data to contain module and pin
    int stateToFire;
};

Pipe *createdPipeModule();
void pipeEvent(void *pipe, void *node, unsigned long long inputDelay);
void setPipe(void *pipe, int state, unsigned long long inputDelay);
void destroyPipe(Pipe *pipe);
void destroyPipeData(Pipe *pipe);

// void storedModuleAndPin(ModuleAndPin *moduleAndPin, Module *module, int pinNum);
ModuleAndPin *createdModuleAndPin(Module *module, int pinNum);
void destroyModuleAndPin(ModuleAndPin *moduleAndPin);

Module *createdAndModule(int inputType);
Module *createdOrModule(int inputType);
Module *createdXorModule(int inputType);
Module *createdNandModule(int inputType);
Module *createdNorModule(int inputType);
Module *createdNotModule(int inputType);
void destroyModule(Module *module);

void andEvent(void *moduleAndPin, unsigned long long delay);
void setAnd(void *moduleAndPin, int state, unsigned long long delay);
int funcOfAND(Module *module, int pinNumber, int inputType);

void orEvent(void *moduleAndPin, unsigned long long delay);
void setOr(void *moduleAndPin, int state, unsigned long long delay);
int funcOfOR(Module *module, int pinNumber, int inputType);

void xorEvent(void *moduleAndPin, unsigned long long delay);
void setXor(void *moduleAndPin, int state, unsigned long long delay);
int funcOfXOR(Module *module, int pinNumber, int inputType);

void nandEvent(void *moduleAndPin, unsigned long long delay);
void setNand(void *moduleAndPin, int state, unsigned long long delay);
int funcOfNAND(Module *module, int pinNumber, int inputType);

void norEvent(void *moduleAndPin, unsigned long long delay);
void setNor(void *moduleAndPin, int state, unsigned long long delay);
int funcOfNOR(Module *module, int pinNumber, int inputType);

void notEvent(void *moduleAndPin, unsigned long long delay);
void setNot(void *moduleAndPin, int state, unsigned long long delay);
int funcOfNOT(Module *module, int pinNumber);

void configureInputOutput(void *thisModule, void *fromPin, void *nextModule, void *toPin);

// void pipeAttach(Pipe **pipe/*, Module **fromModule , void *fromPin*/, Module *toModule, void *toPin);

int determineNumOfInputPin(int inputType);
int determineNumOfOutputPin(int inputType);

int outputConnectionForQuad2Input(Module *module, int pinNumber, int (*gateFunction)(Module *module, int pinNumber, int inputType));
int outputConnectionForTri3Input(Module *module, int pinNumber, int (*gateFunction)(Module *module, int pinNumber, int inputType));
int outputConnectionForDual4Input(Module *module, int pinNumber, int (*gateFunction)(Module *module, int pinNumber, int inputType));
int outputConnectionForHexInv(Module *module, int pinNumber, int (*gateFunction)(Module *module, int pinNumber));

#endif // DigitalSignalModule_H
