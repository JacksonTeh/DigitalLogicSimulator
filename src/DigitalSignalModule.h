#ifndef DigitalSignalModule_H
#define DigitalSignalModule_H

#include "Node.h"

#define TOTAL_PIN       14

typedef enum {QUAD_2_INPUT, TRI_3_INPUT, DUAL_4_INPUT, HEX_INV} InputType;
typedef enum {LOW, HIGH, UNKNOWN} State;
typedef enum {INPUT_PIN, OUTPUT_PIN, UNUSED_PIN} TypeOfPin;
typedef enum {ERR_NO_ERROR, ERR_INVALID_INPUT_TYPE, ERR_INVALID_NUM_OF_PIN, ERR_NOT_OUT_PIN, ERR_NOT_IN_PIN} Error;

typedef int PinType;

typedef struct Module Module;
typedef struct Pipe Pipe;
typedef struct ModuleAndPin ModuleAndPin;
typedef struct Pin Pin;

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

struct Module
{
    int (*event)(void *object);
    void (*set)(void *pin, void *state);
    void (*configure)(void *thisModule, void *fromPin, void *nextModule, void *toPin);
    int totalPin;
    Pipe *pipe;
    Pin pin[TOTAL_PIN];
    // Inbit clk;
};

struct Pipe
{
    int (*event)(void *object);
    void (*set)(void *pin, void *state);
    void (*configure)(void *thisModule, void *fromPin, void *nextModule, void *toPin);
    Node *data;
    // ModuleAndPin *moduleAndPin;
    int stateToFire;
};

Pipe *createdPipeModule();
int pipeEvent(void *module);
void setPipe(void *pin, void *state);
void destroyPipe(Pipe *pipe);
void addPipeModuleData(Pipe **pipe, Node *newNode);

void destroyNodeDataPtr(Node *node);

ModuleAndPin *createdModuleAndPin(Module *module, int pinNum);
void destroyModuleAndPin(ModuleAndPin *moduleAndPin);

Module *createdAndModule(int inputType);
Module *createdOrModule(int inputType);
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
// Module *configureInputOutput(void *thisModule, void *fromPin, void *nextModule, void *toPin);
void configureInputOutput(void *thisModule, void *fromPin, void *nextModule, void *toPin);

void pipeAttach(Pipe **pipe/*, Module **fromModule , void *fromPin*/, Module *toModule, void *toPin);

int determineNumOfInputPin(int inputType);
int determineNumOfOutputPin(int inputType);

#endif // DigitalSignalModule_H
