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
        (AND->pin[i]).state = LOW;
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
        (AND->pin[i]).state = LOW;
        (AND->pin[i]).pipe = NULL;
    }

    return AND;
}

// int andEvent(void *module, void *pin)
void andEvent(void *moduleAndPin)
{
    ModuleAndPin *AND = (ModuleAndPin *)moduleAndPin;
    int outputPinNumber;

    if(AND->module->typeOfInput == QUAD_2_INPUT)
    {
        outputPinNumber = outputConnectionForQuad2Input(AND->module, AND->pin->pinNumber, funcOfAND);
    }
    else if(AND->module->typeOfInput == TRI_3_INPUT)
    {
        outputPinNumber = outputConnectionForTri3Input(AND->module, AND->pin->pinNumber, funcOfAND);
    }
    else if(AND->module->typeOfInput == DUAL_4_INPUT)
    {
        outputPinNumber = outputConnectionForDual4Input(AND->module, AND->pin->pinNumber, funcOfAND);
    }

    if(AND->module->pin[outputPinNumber].pipe != NULL)
        AND->module->pin[outputPinNumber].pipe->set((void *)AND->module->pin[outputPinNumber].pipe, AND->module->pin[outputPinNumber].state, ONE_NANO_SEC);
}

int outputConnectionForQuad2Input(Module *module, int pinNumber, int (*gateFunction)(Module *module, int pinNumber, int inputType))
{
    if(pinNumber < 2)
    {
        if((pinNumber + 1) %2 == 0)
            (module->pin[8]).state = gateFunction(module, pinNumber-1, module->typeOfInput);
        else
            (module->pin[8]).state = gateFunction(module, pinNumber, module->typeOfInput);

        return 8;
    }
    else if(pinNumber > 1 && pinNumber < 4)
    {
        if((pinNumber + 1) %2 == 0)
            (module->pin[9]).state = gateFunction(module, pinNumber-1, module->typeOfInput);
        else
            (module->pin[9]).state = gateFunction(module, pinNumber, module->typeOfInput);

        return 9;
    }
    else if(pinNumber > 3 && pinNumber < 6)
    {
        if((pinNumber + 1) %2 == 0)
            (module->pin[10]).state = gateFunction(module, pinNumber-1, module->typeOfInput);
        else
            (module->pin[10]).state = gateFunction(module, pinNumber, module->typeOfInput);

        return 10;
    }
    else if(pinNumber > 5 && pinNumber < 8)
    {
        if((pinNumber + 1) %2 == 0)
            (module->pin[11]).state = gateFunction(module, pinNumber-1, module->typeOfInput);
        else
            (module->pin[11]).state = gateFunction(module, pinNumber, module->typeOfInput);

        return 11;
    }
}

int outputConnectionForTri3Input(Module *module, int pinNumber, int (*gateFunction)(Module *module, int pinNumber, int inputType))
{
    if(pinNumber < 3)
    {
        switch(pinNumber)
        {
            case 0: 
                (module->pin[9]).state = gateFunction(module, pinNumber, module->typeOfInput);
                break;
            case 1:
                (module->pin[9]).state = gateFunction(module, pinNumber-1, module->typeOfInput);
                break;
            case 2:
                (module->pin[9]).state = gateFunction(module, pinNumber-2, module->typeOfInput);
                break;
        }

        return 9;
    }
    else if(pinNumber > 2 && pinNumber < 6)
    {
        switch(pinNumber)
        {
            case 3:
                (module->pin[10]).state = gateFunction(module, pinNumber, module->typeOfInput);
                break;
            case 4:
                (module->pin[10]).state = gateFunction(module, pinNumber-1, module->typeOfInput);
                break;
            case 5:
                (module->pin[10]).state = gateFunction(module, pinNumber-2, module->typeOfInput);
                break;
        }

        return 10;
    }
    else if(pinNumber > 5 && pinNumber < 9)
    {
        switch(pinNumber)
        {
            case 6:
                (module->pin[11]).state = gateFunction(module, pinNumber, module->typeOfInput);
                break;
            case 7:
                (module->pin[11]).state = gateFunction(module, pinNumber-1, module->typeOfInput);
                break;
            case 8:
                (module->pin[11]).state = gateFunction(module, pinNumber-2, module->typeOfInput);
                break;
        }

        return 11;
    }
}

int outputConnectionForDual4Input(Module *module, int pinNumber, int (*gateFunction)(Module *module, int pinNumber, int inputType))
{
    if(pinNumber < 4)
    {
        switch(pinNumber)
        {
            case 0:
                (module->pin[8]).state = gateFunction(module, pinNumber, module->typeOfInput);
                break;
            case 1:
                (module->pin[8]).state = gateFunction(module, pinNumber-1, module->typeOfInput);
                break;
            case 2:
                (module->pin[8]).state = gateFunction(module, pinNumber-2, module->typeOfInput);
                break;
            case 3:
                (module->pin[8]).state = gateFunction(module, pinNumber-3, module->typeOfInput);
                break;
        }

        return 8;
    }
    else if(pinNumber > 3 && pinNumber < 8)
    {
        switch(pinNumber)
        {
            case 4:
                (module->pin[9]).state = gateFunction(module, pinNumber, module->typeOfInput);
                break;
            case 5:
                (module->pin[9]).state = gateFunction(module, pinNumber-1, module->typeOfInput);
                break;
            case 6:
                (module->pin[9]).state = gateFunction(module, pinNumber-2, module->typeOfInput);
                break;
            case 7:
                (module->pin[9]).state = gateFunction(module, pinNumber-3, module->typeOfInput);
                break;
        }

        return 9;
    }
}

int funcOfAND(Module *module, int pinNumber, int inputType)
{
    if(inputType == QUAD_2_INPUT)
    {
        if(module->pin[pinNumber].state == HIGH && module->pin[pinNumber+1].state == HIGH)
            return HIGH;
        else if(module->pin[pinNumber].state == LOW || module->pin[pinNumber+1].state == LOW)
            return LOW;
    }
    else if(inputType == TRI_3_INPUT)
    {
        if(module->pin[pinNumber].state == HIGH && module->pin[pinNumber+1].state == HIGH && module->pin[pinNumber+2].state == HIGH)
            return HIGH;
        else if(module->pin[pinNumber].state == LOW || module->pin[pinNumber+1].state == LOW || module->pin[pinNumber+2].state == LOW)
            return LOW;
    }
    else if(DUAL_4_INPUT)
    {
        if(module->pin[pinNumber].state == HIGH && module->pin[pinNumber+1].state == HIGH
            && module->pin[pinNumber+2].state == HIGH && module->pin[pinNumber+3].state == HIGH)
            return HIGH;
        else if(module->pin[pinNumber].state == LOW || module->pin[pinNumber+1].state == LOW
                || module->pin[pinNumber+2].state == LOW || module->pin[pinNumber+3].state == LOW)
            return LOW;
    }
}

// void setAnd(void *module, void *pin, int state, unsigned long long inputDelay)
void setAnd(void *moduleAndPin, int state, unsigned long long inputDelay)
{
    ModuleAndPin *AND = (ModuleAndPin *)moduleAndPin;
    // Pin *ANDpin = (Pin *)pin;
    // printf("!AND: %p\n", AND);
    if(AND->pin->type != INPUT_PIN)
        Throw(ERR_NOT_IN_PIN);

    if(state != AND->pin->state)
    {
        AND->pin->state = state;
        registerEvent(AND, NULL, inputDelay);
    }
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
    OR->event = orEvent;
    OR->set = setOr;
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

void orEvent(void *moduleAndPin)
{

}

void setOr(void *moduleAndPin, int state, unsigned long long inputDelay)
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

void pipeEvent(void *pipe, void *node, unsigned long long inputDelay)
{
    Pipe *pipeWithData = (Pipe *)pipe;
    Node *data = (Node *)node;
    ModuleAndPin *moduleAndPin = (ModuleAndPin *)data->dataPtr;

    if(data->left != NULL)
        pipeWithData->event((void *)pipeWithData, (void *)data->left, ONE_NANO_SEC);

    if(data->right != NULL)
        pipeWithData->event((void *)pipeWithData, (void *)data->right, ONE_NANO_SEC);

    moduleAndPin->module->set((void *)moduleAndPin, pipeWithData->stateToFire, inputDelay);
}

void setPipe(void *pipe, int state, unsigned long long inputDelay)
{
    Pipe *pipeWithData = (Pipe *)pipe;

    if(pipeWithData->stateToFire != state)
        pipeWithData->stateToFire = state;

    registerEvent(NULL, pipeWithData, inputDelay);
}

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