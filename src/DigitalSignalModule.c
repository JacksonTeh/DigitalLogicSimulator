#include <stdio.h>
#include <malloc.h>
#include "DigitalSignalModule.h"
#include "RedBlackTree.h"

/**
 * Series No.   Description                 Delay
 * ================================================
 * 74LS00       Quad 2-input NAND Gate      9.5ns
 * 74LS10       Triple 3-input NAND Gate    9.5ns
 * 74LS20       Dual 4-input NAND Gate      9.5ns
 * 74LS30       8-input NAND Gate           10.5ns
 *
 * 74LS02       Quad 2-input NOR Gate       10ns
 * 74LS27       Triple 3-input NOR Gate     10ns
 *
 * 74LS08       Quad 2-input AND Gate       9.0ns
 * 74LS11       Triple 3-input AND Gate     9.0ns
 * 74LS21       Dual 4-input AND Gate       9.0ns
 *
 * 74LS32       Quad 2-input OR Gate        14ns
 *
 * 74LS86       Quad 2-input XOR Gate       10ns
 *
 * 74LS04       Hex inverters               9.5ns
 * ================================================
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
    AND->event = andEvent;
    AND->set = setAnd;
    AND->configure = configureInputOutput;
    AND->totalPin = TOTAL_PIN;

    if(inputType == HEX_INV)
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

int andEvent(void *module)
{

}

void setAnd(void *pin, void *state)
{

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
    OR->event = andEvent;
    OR->set = setAnd;
    OR->configure = configureInputOutput;
    OR->totalPin = TOTAL_PIN;

    if(inputType == HEX_INV)
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

void setOr(void *pin, void *state)
{

}

/**
 * ========================
 * |       XOR Gate       |
 * ========================
 */
Module *createdXorModule(int numberOfPin)
{

}

int xorEvent(void *module)
{

}

void setXor(void *pin, void *state)
{

}

/**
 * ========================
 * |      NAND Gate       |
 * ========================
 */
Module *createdNandModule(int numberOfPin)
{

}

int nandEvent(void *module)
{

}

void setNand(void *pin, void *state)
{

}

/**
 * ========================
 * |       NOR Gate       |
 * ========================
 */
Module *createdNorModule(int numberOfPin)
{

}

int norEvent(void *module)
{

}

void setNor(void *pin, void *state)
{

}

/**
 * ========================
 * |       NOT Gate       |
 * ========================
 */
Module *createdNotModule(int numberOfPin)
{

}

int notEvent(void *module)
{

}

void setNot(void *pin, void *state)
{

}

void destroyModule(Module *module)
{
    int i;

    if(module != NULL)
    {
        for(i = 0; i < TOTAL_PIN; i++)
            destroyPipe((module->pin[i]).pipe);

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

int pipeEvent(void *module)
{

}

void setPipe(void *pin, void *state)
{

}

void addPipeModuleData(Pipe **pipe, Node *newNode)
{
    // Node *newNode;

    // newNode->dataPtr = (void *)moduleAndPin;

    genericAddRedBlackTree(&(*pipe)->data, newNode, compareModuleAndPin);
}

void destroyPipe(Pipe *pipe)
{
    if(pipe != NULL)
    {
        // if(pipe->moduleAndPin != NULL)
            // destroyModuleAndPin(pipe->moduleAndPin);

        // if(pipe->data != NULL)
            // free(pipe->data);

        // if(pipe->data != NULL)
            // free(pipe->data);

        free(pipe);
    }
}

// void destroyNode(Node *node)
// {
    // if(node != NULL)
        // free(node);
// }

ModuleAndPin *createdModuleAndPin(Module *module, int pinNum)
{
    ModuleAndPin *moduleAndPin;

    moduleAndPin = malloc(sizeof(ModuleAndPin));
    moduleAndPin->module = module;
    moduleAndPin->pin = &module->pin[pinNum-1];

    return moduleAndPin;
}

void destroyModuleAndPin(ModuleAndPin *moduleAndPin)
{
    if(moduleAndPin != NULL)
        free(moduleAndPin);
}

void configureInputOutput(void *thisModule, void *fromPin, void *nextModule, void *toPin)
{
    Module *fromModule = (Module *)thisModule;
    Module *toModule = (Module *)nextModule;
    Pipe *pipe;
    int outPin = (int)fromPin;
    int inPin = (int)toPin;

    // printf("outPin: %d\n", outPin - 1);
    // printf("(fromModule->pin[outPin-1]).type: %d\n", (fromModule->pin[outPin-1]).type);
    if((fromModule->pin[outPin-1]).type != OUTPUT_PIN)
        Throw(ERR_NOT_OUT_PIN);

    if((toModule->pin[inPin-1]).type != INPUT_PIN)
        Throw(ERR_NOT_IN_PIN);

    if((fromModule->pin[outPin-1]).pipe == NULL && (fromModule->pin[outPin-1]).type == OUTPUT_PIN)
    {
        printf("yes\n");
        pipe = createdPipeModule();
        (fromModule->pin[outPin-1]).pipe = pipe;
    }

    // addPipeModuleData(&pipe, &newNode);
    // pipeAttach(&(fromModule->pin[outPin-1]).pipe/* , &fromModule */, outPin, &toModule, inPin);
    // printf("outPin: %d\n", ++outPin);
    // printf("inPin: %d\n", inPin);
    // printf("fromModule->output[%d]: %d\n", outPin-1, fromModule->output[outPin-1]);
    // toModule->input[inPin-1] = fromModule->output[outPin-1];
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

void pipeAttach(Pipe **pipe/* , Module **fromModule , void *fromPin*/, Module *toModule, void *toPin)
{
    int inPin = (int)toPin;
    // ModuleAndPin *moduleAndPin = (*pipe)->moduleAndPin;

    // printf("pipe: %p\n", *pipe);
    // printf("(*pipe)->moduleAndPin: %p\n", (*pipe)->moduleAndPin);
    // printf("(*pipe)->moduleAndPin->module: %p\n", (*pipe)->moduleAndPin->module);
    // printf("\n(*pipe)->moduleAndPin->pin: %p\n", (*pipe)->moduleAndPin->pin);
    printf("toModule: %p\n", toModule);
    printf("toModule->pin[inPin-1]: %p\n", &toModule->pin[inPin-1]);
    // moduleAndPin->module = toModule;
    // moduleAndPin->pin = &toModule->pin[inPin-1];
    // printf("!!!(*pipe)->moduleAndPin->pin: %p\n", (*pipe)->moduleAndPin->pin);
}