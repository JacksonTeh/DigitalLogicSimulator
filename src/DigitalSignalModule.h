#ifndef DigitalSignalModule_H
#define DigitalSignalModule_H

#include "Node.h"

#define TOTAL_PIN       14
#define ONE_PICO_SEC    1
#define ONE_NANO_SEC    1000 * ONE_PICO_SEC

typedef enum {QUAD_2_INPUT, TRI_3_INPUT, DUAL_4_INPUT, HEX_INV} InputType;
typedef enum {LOW, HIGH, UNKNOWN} State;
typedef enum {INPUT_PIN, OUTPUT_PIN, UNUSED_PIN} TypeOfPin;
typedef enum {ERR_NO_ERROR, ERR_INVALID_INPUT_TYPE, ERR_INVALID_NUM_OF_PIN, ERR_NOT_OUT_PIN, ERR_NOT_IN_PIN} Error;

typedef int PinType;

typedef struct Module Module;
typedef struct Pipe Pipe;
typedef struct ModuleAndPin ModuleAndPin;
typedef struct Pin Pin;
typedef struct Switch Switch;

struct ModuleAndPin
{
    /* RBT */
    // ModuleAndPin *left;
    // ModuleAndPin *right;
    // char colour;
    /* data */
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

struct Switch
{
    void (*event)(void *moduleAndPin);
    void (*set)(void *moduleAndPin, int state, unsigned long long inputDelay);
    void (*configure)(void *thisModule, void *fromPin, void *nextModule, void *toPin, void *pipeData);
};

struct Module
{
    char *name;
    void (*event)(void *moduleAndPin);
    // int (*event)(void *object, void *pin);
    void (*set)(void *moduleAndPin, int state, unsigned long long inputDelay);
    // void (*set)(void *module, void *pin, int state, unsigned long long inputDelay);
    void (*configure)(void *thisModule, void *fromPin, void *nextModule, void *toPin, void *pipeData);
    int typeOfInput;
    int totalPin;
    Pin pin[TOTAL_PIN];
    // Inbit clk;
};

struct Pipe
{
    void (*event)(void *object, void *node, unsigned long long inputDelay);
    void (*set)(void *pipe, int state, unsigned long long inputDelay);
    void (*configure)(void *thisModule, void *fromPin, void *nextModule, void *toPin, void *pipeData);
    Node *data;
    // ModuleAndPin *moduleAndPin;
    int stateToFire;
};

Pipe *createdPipeModule();
void pipeEvent(void *pipe, void *node, unsigned long long inputDelay);
void setPipe(void *pipe, int state, unsigned long long inputDelay);
void destroyPipe(Pipe *pipe);

// void destroyNodeDataPtr(Node *node);

void storedModuleAndPin(ModuleAndPin *moduleAndPin, Module *module, int pinNum);
// ModuleAndPin *storedModuleAndPin(Module *module, int pinNum);
// void destroyModuleAndPin(ModuleAndPin *moduleAndPin);

Module *createdAndModule(int inputType);
Module *createdOrModule(int inputType);
Module *createdXorModule(int numberOfPin);
Module *createdNandModule(int numberOfPin);
Module *createdNorModule(int numberOfPin);
Module *createdNotModule(int numberOfPin);
void destroyModule(Module *module);

void andEvent(void *moduleAndPin);
void setAnd(void *moduleAndPin, int state, unsigned long long inputDelay);
int outputConnectionForQuad2Input(Module *module, int pinNumber, int (*gateFunction)(Module *module, int pinNumber, int inputType));
int outputConnectionForTri3Input(Module *module, int pinNumber, int (*gateFunction)(Module *module, int pinNumber, int inputType));
int outputConnectionForDual4Input(Module *module, int pinNumber, int (*gateFunction)(Module *module, int pinNumber, int inputType));
int funcOfAND(Module *module, int pinNumber, int inputType);
// void setAnd(void *module, void *pin, int state, unsigned long long inputDelay);
void orEvent(void *moduleAndPin);
void setOr(void *moduleAndPin, int state, unsigned long long inputDelay);
// int xorEvent(void *module);
// void setXor(void *module, void *pin, int state, unsigned long long inputDelay);
// int nandEvent(void *module);
// void setNand(void *module, void *pin, int state, unsigned long long inputDelay);
// int norEvent(void *module);
// void setNor(void *module, void *pin, int state, unsigned long long inputDelay);
// int notEvent(void *module);
// void setNot(void *module, void *pin, int state, unsigned long long inputDelay);
// Module *configureInputOutput(void *thisModule, void *fromPin, void *nextModule, void *toPin);
void configureInputOutput(void *thisModule, void *fromPin, void *nextModule, void *toPin, void *pipeData);

// void pipeAttach(Pipe **pipe/*, Module **fromModule , void *fromPin*/, Module *toModule, void *toPin);

int determineNumOfInputPin(int inputType);
int determineNumOfOutputPin(int inputType);

#endif // DigitalSignalModule_H
