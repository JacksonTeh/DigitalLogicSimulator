#include <stdio.h>
#include <malloc.h>
#include "DigitalSignalModule.h"
#include "RedBlackTree.h"
#include "InitNode.h"

/**
 * Series No.   Description                 Delay
 * =========================================================
 * 74LS00       Quad 2-input NAND Gate      9.5ns
 * 74LS10       Triple 3-input NAND Gate    9.5ns   ==> NAND
 * 74LS20       Dual 4-input NAND Gate      9.5ns
 * 74LS30       8-input NAND Gate           10.5ns
 *
 * 74LS02       Quad 2-input NOR Gate       10ns    ==> NOR
 * 74LS27       Triple 3-input NOR Gate     10ns
 *
 * 74LS08       Quad 2-input AND Gate       9.0ns
 * 74LS11       Triple 3-input AND Gate     9.0ns   ==> AND
 * 74LS21       Dual 4-input AND Gate       9.0ns
 *
 * 74LS32       Quad 2-input OR Gate        14ns    ==> OR
 *
 * 74LS86       Quad 2-input XOR Gate       10ns    ==> XOR
 *
 * 74LS04       Hex inverters               9.5ns   ==> NOT
 * ========================================================
 */

/**
 * ========================
 * |       AND Gate       |
 * ========================
 */
Module *createdAndModule(int inputType)
{
    Module *AND;
    int i, j, numberOfInPin, numberOfOutPin;

    AND = malloc(sizeof(Module));
    AND->name = "AND";
    AND->event = andEvent;
    AND->set = setAnd;
    AND->configure = configureInputOutput;
    AND->typeOfInput = inputType;
    AND->totalPin = TOTAL_PIN;
    // AND->pipe = NULL;

    if(inputType == HEX_INV || (inputType != QUAD_2_INPUT && inputType != TRI_3_INPUT && inputType != DUAL_4_INPUT))
        Throw(ERR_INVALID_INPUT_TYPE);

    numberOfInPin = determineNumOfInputPin(inputType);
    numberOfOutPin = determineNumOfOutputPin(inputType);

    /* Initialise pin */
    for(i = 0; i < numberOfInPin; i++)
    {
        (AND->pin[i]).type = INPUT_PIN;
        (AND->pin[i]).pinNumber = i;
        (AND->pin[i]).pipe = NULL;
        // (AND->pin[i]).moduleConnected = NULL;
    }

    j = i + numberOfOutPin;

    for(; i < AND->totalPin; i++)
    {
        if(i < j)
            (AND->pin[i]).type = OUTPUT_PIN;
        else
            (AND->pin[i]).type = UNUSED_PIN;

        (AND->pin[i]).pinNumber = i;
        (AND->pin[i]).pipe = NULL;
    }

    return AND;
}

// int andEvent(void *module, void *pin)
int andEvent(void *moduleAndPin)
{
    ModuleAndPin *AND = (ModuleAndPin *)moduleAndPin;

    // if((AND->pin->pinNumber + 1) % 2 == 0)
    // {
        // if(AND->pin->pinNumber == 0 || AND->pin->pinNumber == 1)
        // {
            // if(isPipeNotNull(AND->pin->pipe))
                // AND->pin->pipe->set();
            // else
                // Throw();
        // }
    // }
}

// void setAnd(void *module, void *pin, int state, unsigned long long inputDelay)
void setAnd(void *moduleAndPin, int state, unsigned long long inputDelay)
{
    ModuleAndPin *AND = (ModuleAndPin *)moduleAndPin;
    // Pin *ANDpin = (Pin *)pin;
    // printf("!AND: %p\n", AND);
    if(AND->pin->type != INPUT_PIN)
        Throw(ERR_NOT_IN_PIN);

    AND->pin->state = state;
    registerEvent(AND, NULL, inputDelay);
}

/**
 * ========================
 * |       OR Gate        |
 * ========================
 */
Module *createdOrModule(int inputType)
{
    Module *OR;
    int i, j, numberOfInPin, numberOfOutPin;

    OR = malloc(sizeof(Module));
    OR->name = "OR";
    OR->event = andEvent;
    OR->set = setAnd;
    OR->configure = configureInputOutput;
    OR->typeOfInput = inputType;
    OR->totalPin = TOTAL_PIN;
    // OR->pipe = NULL;

    if(inputType == HEX_INV || (inputType != QUAD_2_INPUT && inputType != TRI_3_INPUT && inputType != DUAL_4_INPUT))
        Throw(ERR_INVALID_INPUT_TYPE);

    numberOfInPin = determineNumOfInputPin(inputType);
    numberOfOutPin = determineNumOfOutputPin(inputType);

    /* Initialise pin */
    for(i = 0; i < numberOfInPin; i++)
    {
        (OR->pin[i]).type = INPUT_PIN;
        (OR->pin[i]).pinNumber = i;
        (OR->pin[i]).pipe = NULL;
        // (OR->pin[i]).moduleConnected = NULL;
    }

    j = i + numberOfOutPin;

    for(; i < OR->totalPin; i++)
    {
        if(i < j)
            (OR->pin[i]).type = OUTPUT_PIN;
        else
            (OR->pin[i]).type = UNUSED_PIN;

        (OR->pin[i]).pinNumber = i;
        (OR->pin[i]).pipe = NULL;
    }

    return OR;
}

int orEvent(void *module)
{

}

void setOr(void *module, void *pin, int state, unsigned long long inputDelay)
{

}

/**
 * ========================
 * |       XOR Gate       |
 * ========================
 */
// Module *createdXorModule(int numberOfPin)
// {

// }

// int xorEvent(void *module)
// {

// }

// void setXor(void *module, void *pin, int state, unsigned long long inputDelay)
// {

// }

/**
 * ========================
 * |      NAND Gate       |
 * ========================
 */
// Module *createdNandModule(int numberOfPin)
// {

// }

// int nandEvent(void *module)
// {

// }

// void setNand(void *module, void *pin, int state, unsigned long long inputDelay)
// {

// }

/**
 * ========================
 * |       NOR Gate       |
 * ========================
 */
// Module *createdNorModule(int numberOfPin)
// {

// }

// int norEvent(void *module)
// {

// }

// void setNor(void *module, void *pin, int state, unsigned long long inputDelay)
// {

// }

/**
 * ========================
 * |       NOT Gate       |
 * ========================
 */
// Module *createdNotModule(int numberOfPin)
// {

// }

// int notEvent(void *module)
// {

// }

// void setNot(void *module, void *pin, int state, unsigned long long inputDelay)
// {

// }

void destroyModule(Module *module)
{
    int i;

    if(module != NULL)
    {
        // printf("module: %p\n", module);

        for(i = 0; i < TOTAL_PIN; i++)
        {
            if((module->pin[i]).type == OUTPUT_PIN)
                destroyPipe((module->pin[i]).pipe);
        }

        free(module);
    }
}

Pipe *createdPipeModule()
{
    Pipe *pipe;

    pipe = malloc(sizeof(Pipe));
    pipe->event = pipeEvent;
    pipe->set = setPipe;
    pipe->configure = configureInputOutput;
    // pipe->data = malloc(sizeof(Node));
    // pipe->moduleAndPin = malloc(sizeof(ModuleAndPin));
    pipe->data = NULL;
    // pipe->moduleAndPin->module = NULL;
    // pipe->moduleAndPin->pin = NULL;
    // pipe->moduleAndPin->left = NULL;
    // pipe->moduleAndPin->right = NULL;
    pipe->stateToFire = UNKNOWN;

    return pipe;
}

int pipeEvent(void *pipe)
{

}

void setPipe(void *pipe, void *node, int state, unsigned long long inputDelay)
{
    Pipe *pipeWithData = (Pipe *)pipe;
    Node *data = (Node *)node;
    ModuleAndPin *moduleAndPin = (ModuleAndPin *)data->dataPtr;

    pipeWithData->stateToFire = state;

    if(data->left != NULL)
        pipeWithData->set((void *)pipeWithData, (void *)data->left, HIGH, ONE_NANO_SEC);

    if(data->right != NULL)
        pipeWithData->set((void *)pipeWithData, (void *)data->right, HIGH, ONE_NANO_SEC);

    registerEvent(moduleAndPin, pipeWithData, inputDelay);
}

// void addPipeModuleData(Pipe **pipe, Node *newNode)
// {
    // genericAddRedBlackTree(&(*pipe)->data, newNode, compareModuleAndPin);
// }

void destroyPipe(Pipe *pipe)
{
    if(pipe != NULL)
    {
        // if(pipe->moduleAndPin != NULL)
            // destroyModuleAndPin(pipe->moduleAndPin);

        // printf("pipe: %p\n", pipe);
        // destroyNodeDataPtr(pipe->data);
        free(pipe);
    }
}
/*
void destroyNodeDataPtr(Node *node)
{
    if(node != NULL)
    {
        if(node->left != NULL)
            // printf("node->left: %p\n", node->left);
            destroyNodeDataPtr(node->left);

        if(node->right != NULL)
            // printf("node->right: %p\n", node->right);
            destroyNodeDataPtr(node->right);

        // ModuleAndPin *moduleAndPin = (ModuleAndPin *)node->dataPtr;
        // destroyModuleAndPin(moduleAndPin);
    }
} */

// ModuleAndPin *storedModuleAndPin(Module *module, int pinNum)
void storedModuleAndPin(ModuleAndPin *moduleAndPin, Module *module, int pinNum)
{
    // ModuleAndPin *moduleAndPin;

    // moduleAndPin = malloc(sizeof(ModuleAndPin));
    moduleAndPin->module = module;
    moduleAndPin->pin = &module->pin[pinNum];

    // return moduleAndPin;
}
/*
void destroyModuleAndPin(ModuleAndPin *moduleAndPin)
{
    // printf("moduleAndPin: %p\n", moduleAndPin);
    if(moduleAndPin != NULL)
        free(moduleAndPin);
} */

void configureInputOutput(void *thisModule, void *fromPin, void *nextModule, void *toPin, void *pipeData)
{
    Module *sourceModule = (Module *)thisModule;
    Module *destModule = (Module *)nextModule;
    Pin *sourcePin = (Pin *)fromPin;
    Pin *destPin = (Pin *)toPin;
    Node *newNode = (Node *)pipeData;
    Pipe *pipe;
    // ModuleAndPin pipeData = {destModule, destPin};
    // Node newNode;

    if(sourcePin->type != OUTPUT_PIN)
        Throw(ERR_NOT_OUT_PIN);

    if(destPin->type != INPUT_PIN)
        Throw(ERR_NOT_IN_PIN);

    if((sourceModule->pin[sourcePin->pinNumber]).pipe == NULL)
    {
        pipe = createdPipeModule();
        (sourceModule->pin[sourcePin->pinNumber]).pipe = pipe;
    }
    else
    {
        (destModule->pin[destPin->pinNumber]).pipe = (sourceModule->pin[sourcePin->pinNumber]).pipe;
        // destPin->state = ((sourceModule->pin[sourcePin->pinNumber]).pipe)->stateToFire;
        // nextModuleAndPin = createdModuleAndPin(destModule, destPin->pinNumber);
        // genericResetNode(&newNode, (void *)&pipeData);
        // setNode(&newNode, NULL, NULL, 'r');
        genericAddRedBlackTree(&((sourceModule->pin[sourcePin->pinNumber]).pipe)->data, newNode, compareModuleAndPin);
    }
}

int determineNumOfInputPin(int inputType)
{
     if(inputType == QUAD_2_INPUT || inputType == DUAL_4_INPUT)
        return 8;
    else if(inputType == TRI_3_INPUT)
        return 9;
    else if(inputType == HEX_INV)
        return 6;
    else
        return 0;
}

int determineNumOfOutputPin(int inputType)
{
    if(inputType == QUAD_2_INPUT)
        return 4;
    else if(inputType == DUAL_4_INPUT)
        return 2;
    else if(inputType == TRI_3_INPUT)
        return 3;
    else if(inputType == HEX_INV)
        return 6;
    else
        return 0;
}

// void pipeAttach(Pipe **pipe, Module **fromModule , void *fromPin, Module *toModule, void *toPin)
// {
    // int inPin = (int)toPin;
    // ModuleAndPin *moduleAndPin = (*pipe)->moduleAndPin;

    // printf("pipe: %p\n", *pipe);
    // printf("(*pipe)->moduleAndPin: %p\n", (*pipe)->moduleAndPin);
    // printf("(*pipe)->moduleAndPin->module: %p\n", (*pipe)->moduleAndPin->module);
    // printf("\n(*pipe)->moduleAndPin->pin: %p\n", (*pipe)->moduleAndPin->pin);
    // printf("toModule: %p\n", toModule);
    // printf("toModule->pin[inPin-1]: %p\n", &toModule->pin[inPin-1]);
    // moduleAndPin->module = toModule;
    // moduleAndPin->pin = &toModule->pin[inPin-1];
    // printf("!!!(*pipe)->moduleAndPin->pin: %p\n", (*pipe)->moduleAndPin->pin);
// }