#include <stdio.h>
#include <malloc.h>
#include "DigitalSignalModule.h"
#include "RedBlackTree.h"
#include "InitNode.h"
#include "Node.h"
#include "EventInfo.h"

/**
 * Series No.   Description                 Delay, tpd
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

void andEvent(void *moduleAndPin, unsigned long long delay)
{
    ModuleAndPin *AND = (ModuleAndPin *)moduleAndPin;
    int outputPinNumber;

    if(AND->module->typeOfInput == QUAD_2_INPUT)
        outputPinNumber = outputConnectionForQuad2Input(AND->module, AND->pin->pinNumber, funcOfAND);
    else if(AND->module->typeOfInput == TRI_3_INPUT)
        outputPinNumber = outputConnectionForTri3Input(AND->module, AND->pin->pinNumber, funcOfAND);
    else if(AND->module->typeOfInput == DUAL_4_INPUT)
        outputPinNumber = outputConnectionForDual4Input(AND->module, AND->pin->pinNumber, funcOfAND);

    if(AND->module->pin[outputPinNumber].pipe != NULL)      //set pipe if pipe is connected
        AND->module->pin[outputPinNumber].pipe->set((void *)AND->module->pin[outputPinNumber].pipe, AND->module->pin[outputPinNumber].state, delay);
}

void setAnd(void *moduleAndPin, int state, unsigned long long delay)
{
    ModuleAndPin *AND = (ModuleAndPin *)moduleAndPin;

    if(AND->pin->type != INPUT_PIN)
        Throw(ERR_NOT_IN_PIN);

    delay = delay + AND_PROPAGATION_DELAY;

    if(state != AND->pin->state)
    {
        AND->pin->state = state;
        registerEvent(AND, NULL, delay);
    }
}

/**
 *
 * AND gate logic
 *
 */
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

    if(inputType == HEX_INV || (inputType != QUAD_2_INPUT && inputType != TRI_3_INPUT && inputType != DUAL_4_INPUT))
        Throw(ERR_INVALID_INPUT_TYPE);

    numberOfInPin = determineNumOfInputPin(inputType);
    numberOfOutPin = determineNumOfOutputPin(inputType);

    /* Initialise pin */
    for(i = 0; i < numberOfInPin; i++)
    {
        (OR->pin[i]).type = INPUT_PIN;
        (OR->pin[i]).pinNumber = i;
        (OR->pin[i]).state = LOW;
        (OR->pin[i]).pipe = NULL;
    }

    j = i + numberOfOutPin;

    for(; i < OR->totalPin; i++)
    {
        if(i < j)
            (OR->pin[i]).type = OUTPUT_PIN;
        else
            (OR->pin[i]).type = UNUSED_PIN;

        (OR->pin[i]).pinNumber = i;
        (OR->pin[i]).state = LOW;
        (OR->pin[i]).pipe = NULL;
    }

    return OR;
}

void orEvent(void *moduleAndPin, unsigned long long delay)
{
    ModuleAndPin *OR = (ModuleAndPin *)moduleAndPin;
    int outputPinNumber;

    if(OR->module->typeOfInput == QUAD_2_INPUT)
        outputPinNumber = outputConnectionForQuad2Input(OR->module, OR->pin->pinNumber, funcOfOR);
    else if(OR->module->typeOfInput == TRI_3_INPUT)
        outputPinNumber = outputConnectionForTri3Input(OR->module, OR->pin->pinNumber, funcOfOR);
    else if(OR->module->typeOfInput == DUAL_4_INPUT)
        outputPinNumber = outputConnectionForDual4Input(OR->module, OR->pin->pinNumber, funcOfOR);

    if(OR->module->pin[outputPinNumber].pipe != NULL)
        OR->module->pin[outputPinNumber].pipe->set((void *)OR->module->pin[outputPinNumber].pipe, OR->module->pin[outputPinNumber].state, delay);
}

void setOr(void *moduleAndPin, int state, unsigned long long delay)
{
    ModuleAndPin *OR = (ModuleAndPin *)moduleAndPin;

    if(OR->pin->type != INPUT_PIN)
        Throw(ERR_NOT_IN_PIN);

    delay = delay + OR_PROPAGATION_DELAY;

    if(state != OR->pin->state)
    {
        OR->pin->state = state;
        registerEvent(OR, NULL, delay);
    }
}

/**
 *
 * OR gate logic
 *
 */
int funcOfOR(Module *module, int pinNumber, int inputType)
{
    if(inputType == QUAD_2_INPUT)
    {
        if(module->pin[pinNumber].state == HIGH || module->pin[pinNumber+1].state == HIGH)
            return HIGH;
        else if(module->pin[pinNumber].state == LOW && module->pin[pinNumber+1].state == LOW)
            return LOW;
    }
    else if(inputType == TRI_3_INPUT)
    {
        if(module->pin[pinNumber].state == HIGH || module->pin[pinNumber+1].state == HIGH || module->pin[pinNumber+2].state == HIGH)
            return HIGH;
        else if(module->pin[pinNumber].state == LOW && module->pin[pinNumber+1].state == LOW && module->pin[pinNumber+2].state == LOW)
            return LOW;
    }
    else if(DUAL_4_INPUT)
    {
        if(module->pin[pinNumber].state == HIGH || module->pin[pinNumber+1].state == HIGH
            || module->pin[pinNumber+2].state == HIGH || module->pin[pinNumber+3].state == HIGH)
            return HIGH;
        else if(module->pin[pinNumber].state == LOW && module->pin[pinNumber+1].state == LOW
                && module->pin[pinNumber+2].state == LOW && module->pin[pinNumber+3].state == LOW)
            return LOW;
    }
}

/**
 * ========================
 * |       XOR Gate       |
 * ========================
 */
Module *createdXorModule(int inputType)
{
    Module *XOR;
    int i, j, numberOfInPin, numberOfOutPin;

    XOR = malloc(sizeof(Module));
    XOR->name = "XOR";
    XOR->event = xorEvent;
    XOR->set = setXor;
    XOR->configure = configureInputOutput;
    XOR->typeOfInput = inputType;
    XOR->totalPin = TOTAL_PIN;

    if(inputType == HEX_INV || inputType == DUAL_4_INPUT)
        Throw(ERR_INVALID_INPUT_TYPE);

    numberOfInPin = determineNumOfInputPin(inputType);
    numberOfOutPin = determineNumOfOutputPin(inputType);

    /* Initialise pin */
    for(i = 0; i < numberOfInPin; i++)
    {
        (XOR->pin[i]).type = INPUT_PIN;
        (XOR->pin[i]).pinNumber = i;
        (XOR->pin[i]).state = LOW;
        (XOR->pin[i]).pipe = NULL;
    }

    j = i + numberOfOutPin;

    for(; i < XOR->totalPin; i++)
    {
        if(i < j)
            (XOR->pin[i]).type = OUTPUT_PIN;
        else
            (XOR->pin[i]).type = UNUSED_PIN;

        (XOR->pin[i]).pinNumber = i;
        (XOR->pin[i]).state = LOW;
        (XOR->pin[i]).pipe = NULL;
    }

    return XOR;
}

void xorEvent(void *moduleAndPin, unsigned long long delay)
{
    ModuleAndPin *XOR = (ModuleAndPin *)moduleAndPin;
    int outputPinNumber;

    if(XOR->module->typeOfInput == QUAD_2_INPUT)
        outputPinNumber = outputConnectionForQuad2Input(XOR->module, XOR->pin->pinNumber, funcOfXOR);
    else if(XOR->module->typeOfInput == TRI_3_INPUT)
        outputPinNumber = outputConnectionForTri3Input(XOR->module, XOR->pin->pinNumber, funcOfXOR);

    if(XOR->module->pin[outputPinNumber].pipe != NULL)
        XOR->module->pin[outputPinNumber].pipe->set((void *)XOR->module->pin[outputPinNumber].pipe, XOR->module->pin[outputPinNumber].state, delay);
}

void setXor(void *moduleAndPin, int state, unsigned long long delay)
{
    ModuleAndPin *XOR = (ModuleAndPin *)moduleAndPin;

    if(XOR->pin->type != INPUT_PIN)
        Throw(ERR_NOT_IN_PIN);

    delay = delay + XOR_PROPAGATION_DELAY;

    if(state != XOR->pin->state)
    {
        XOR->pin->state = state;
        registerEvent(XOR, NULL, delay);
    }
}

/**
 *
 * XOR gate logic
 *
 */
int funcOfXOR(Module *module, int pinNumber, int inputType)
{
    int i, odd = 0;

    if(inputType == QUAD_2_INPUT)
    {
        if((module->pin[pinNumber].state == HIGH && module->pin[pinNumber+1].state == LOW)
            || (module->pin[pinNumber].state == LOW && module->pin[pinNumber+1].state == HIGH))
            return HIGH;
        else if((module->pin[pinNumber].state == LOW && module->pin[pinNumber+1].state == LOW)
                || (module->pin[pinNumber].state == HIGH && module->pin[pinNumber+1].state == HIGH))
            return LOW;
    }
    else if(inputType == TRI_3_INPUT)
    {
        for(i = pinNumber; i < pinNumber + 3; i++)
        {
            if(module->pin[i].state == HIGH)
                odd++;
        }

        if(odd % 2 != 0)
            return HIGH;
        else
            return LOW;
    }
}

/**
 * ========================
 * |      NAND Gate       |
 * ========================
 */
Module *createdNandModule(int inputType)
{
    Module *NAND;
    int i, j, numberOfInPin, numberOfOutPin;

    NAND = malloc(sizeof(Module));
    NAND->name = "NAND";
    NAND->event = nandEvent;
    NAND->set = setNand;
    NAND->configure = configureInputOutput;
    NAND->typeOfInput = inputType;
    NAND->totalPin = TOTAL_PIN;

    if(inputType == HEX_INV || (inputType != QUAD_2_INPUT && inputType != TRI_3_INPUT && inputType != DUAL_4_INPUT))
        Throw(ERR_INVALID_INPUT_TYPE);

    numberOfInPin = determineNumOfInputPin(inputType);
    numberOfOutPin = determineNumOfOutputPin(inputType);

    /* Initialise pin */
    for(i = 0; i < numberOfInPin; i++)
    {
        (NAND->pin[i]).type = INPUT_PIN;
        (NAND->pin[i]).pinNumber = i;
        (NAND->pin[i]).state = LOW;
        (NAND->pin[i]).pipe = NULL;
    }

    j = i + numberOfOutPin;

    for(; i < NAND->totalPin; i++)
    {
        if(i < j)
            (NAND->pin[i]).type = OUTPUT_PIN;
        else
            (NAND->pin[i]).type = UNUSED_PIN;

        (NAND->pin[i]).pinNumber = i;
        (NAND->pin[i]).state = LOW;
        (NAND->pin[i]).pipe = NULL;
    }

    return NAND;
}

void nandEvent(void *moduleAndPin, unsigned long long delay)
{
    ModuleAndPin *NAND = (ModuleAndPin *)moduleAndPin;
    int outputPinNumber;

    if(NAND->module->typeOfInput == QUAD_2_INPUT)
        outputPinNumber = outputConnectionForQuad2Input(NAND->module, NAND->pin->pinNumber, funcOfNAND);
    else if(NAND->module->typeOfInput == TRI_3_INPUT)
        outputPinNumber = outputConnectionForTri3Input(NAND->module, NAND->pin->pinNumber, funcOfNAND);
    else if(NAND->module->typeOfInput == DUAL_4_INPUT)
        outputPinNumber = outputConnectionForDual4Input(NAND->module, NAND->pin->pinNumber, funcOfNAND);

    if(NAND->module->pin[outputPinNumber].pipe != NULL)
        NAND->module->pin[outputPinNumber].pipe->set((void *)NAND->module->pin[outputPinNumber].pipe, NAND->module->pin[outputPinNumber].state, delay);
}

void setNand(void *moduleAndPin, int state, unsigned long long delay)
{
    ModuleAndPin *NAND = (ModuleAndPin *)moduleAndPin;

    if(NAND->pin->type != INPUT_PIN)
        Throw(ERR_NOT_IN_PIN);

    delay = delay + NAND_PROPAGATION_DELAY;

    if(state != NAND->pin->state)
    {
        NAND->pin->state = state;
        registerEvent(NAND, NULL, delay);
    }
}

/**
 *
 * NAND gate logic
 *
 */
int funcOfNAND(Module *module, int pinNumber, int inputType)
{
    if(inputType == QUAD_2_INPUT)
    {
        if(module->pin[pinNumber].state == HIGH && module->pin[pinNumber+1].state == HIGH)
            return LOW;
        else if(module->pin[pinNumber].state == LOW || module->pin[pinNumber+1].state == LOW)
            return HIGH;
    }
    else if(inputType == TRI_3_INPUT)
    {
        if(module->pin[pinNumber].state == HIGH && module->pin[pinNumber+1].state == HIGH && module->pin[pinNumber+2].state == HIGH)
            return LOW;
        else if(module->pin[pinNumber].state == LOW || module->pin[pinNumber+1].state == LOW || module->pin[pinNumber+2].state == LOW)
            return HIGH;
    }
    else if(DUAL_4_INPUT)
    {
        if(module->pin[pinNumber].state == HIGH && module->pin[pinNumber+1].state == HIGH
            && module->pin[pinNumber+2].state == HIGH && module->pin[pinNumber+3].state == HIGH)
            return LOW;
        else if(module->pin[pinNumber].state == LOW || module->pin[pinNumber+1].state == LOW
                || module->pin[pinNumber+2].state == LOW || module->pin[pinNumber+3].state == LOW)
            return HIGH;
    }
}

/**
 * ========================
 * |       NOR Gate       |
 * ========================
 */
Module *createdNorModule(int inputType)
{
    Module *NOR;
    int i, j, numberOfInPin, numberOfOutPin;

    NOR = malloc(sizeof(Module));
    NOR->name = "NOR";
    NOR->event = norEvent;
    NOR->set = setNor;
    NOR->configure = configureInputOutput;
    NOR->typeOfInput = inputType;
    NOR->totalPin = TOTAL_PIN;

    if(inputType == HEX_INV || (inputType != QUAD_2_INPUT && inputType != TRI_3_INPUT && inputType != DUAL_4_INPUT))
        Throw(ERR_INVALID_INPUT_TYPE);

    numberOfInPin = determineNumOfInputPin(inputType);
    numberOfOutPin = determineNumOfOutputPin(inputType);

    /* Initialise pin */
    for(i = 0; i < numberOfInPin; i++)
    {
        (NOR->pin[i]).type = INPUT_PIN;
        (NOR->pin[i]).pinNumber = i;
        (NOR->pin[i]).state = LOW;
        (NOR->pin[i]).pipe = NULL;
    }

    j = i + numberOfOutPin;

    for(; i < NOR->totalPin; i++)
    {
        if(i < j)
            (NOR->pin[i]).type = OUTPUT_PIN;
        else
            (NOR->pin[i]).type = UNUSED_PIN;

        (NOR->pin[i]).pinNumber = i;
        (NOR->pin[i]).state = LOW;
        (NOR->pin[i]).pipe = NULL;
    }

    return NOR;
}

void norEvent(void *moduleAndPin, unsigned long long delay)
{
    ModuleAndPin *NOR = (ModuleAndPin *)moduleAndPin;
    int outputPinNumber;

    if(NOR->module->typeOfInput == QUAD_2_INPUT)
        outputPinNumber = outputConnectionForQuad2Input(NOR->module, NOR->pin->pinNumber, funcOfNOR);
    else if(NOR->module->typeOfInput == TRI_3_INPUT)
        outputPinNumber = outputConnectionForTri3Input(NOR->module, NOR->pin->pinNumber, funcOfNOR);
    else if(NOR->module->typeOfInput == DUAL_4_INPUT)
        outputPinNumber = outputConnectionForDual4Input(NOR->module, NOR->pin->pinNumber, funcOfNOR);

    if(NOR->module->pin[outputPinNumber].pipe != NULL)
        NOR->module->pin[outputPinNumber].pipe->set((void *)NOR->module->pin[outputPinNumber].pipe, NOR->module->pin[outputPinNumber].state, delay);
}

void setNor(void *moduleAndPin, int state, unsigned long long delay)
{
    ModuleAndPin *NOR = (ModuleAndPin *)moduleAndPin;

    if(NOR->pin->type != INPUT_PIN)
        Throw(ERR_NOT_IN_PIN);

    delay = delay + NOR_PROPAGATION_DELAY;

    if(state != NOR->pin->state)
    {
        NOR->pin->state = state;
        registerEvent(NOR, NULL, delay);
    }
}

/**
 *
 * NOR gate logic
 *
 */
int funcOfNOR(Module *module, int pinNumber, int inputType)
{
    if(inputType == QUAD_2_INPUT)
    {
        if(module->pin[pinNumber].state == HIGH || module->pin[pinNumber+1].state == HIGH)
            return LOW;
        else if(module->pin[pinNumber].state == LOW && module->pin[pinNumber+1].state == LOW)
            return HIGH;
    }
    else if(inputType == TRI_3_INPUT)
    {
        if(module->pin[pinNumber].state == HIGH || module->pin[pinNumber+1].state == HIGH || module->pin[pinNumber+2].state == HIGH)
            return LOW;
        else if(module->pin[pinNumber].state == LOW && module->pin[pinNumber+1].state == LOW && module->pin[pinNumber+2].state == LOW)
            return HIGH;
    }
    else if(DUAL_4_INPUT)
    {
        if(module->pin[pinNumber].state == HIGH || module->pin[pinNumber+1].state == HIGH
            || module->pin[pinNumber+2].state == HIGH || module->pin[pinNumber+3].state == HIGH)
            return LOW;
        else if(module->pin[pinNumber].state == LOW && module->pin[pinNumber+1].state == LOW
                && module->pin[pinNumber+2].state == LOW && module->pin[pinNumber+3].state == LOW)
            return HIGH;
    }
}

/**
 * ========================
 * |       NOT Gate       |
 * ========================
 */
Module *createdNotModule(int inputType)
{
    Module *NOT;
    int i, j, numberOfInPin, numberOfOutPin;

    NOT = malloc(sizeof(Module));
    NOT->name = "NOT";
    NOT->event = notEvent;
    NOT->set = setNot;
    NOT->configure = configureInputOutput;
    NOT->typeOfInput = inputType;
    NOT->totalPin = TOTAL_PIN;

    if(inputType != HEX_INV)
        Throw(ERR_INVALID_INPUT_TYPE);

    numberOfInPin = determineNumOfInputPin(inputType);
    numberOfOutPin = determineNumOfOutputPin(inputType);

    /* Initialise pin */
    for(i = 0; i < numberOfInPin; i++)
    {
        (NOT->pin[i]).type = INPUT_PIN;
        (NOT->pin[i]).pinNumber = i;
        (NOT->pin[i]).state = LOW;
        (NOT->pin[i]).pipe = NULL;
    }

    j = i + numberOfOutPin;

    for(; i < NOT->totalPin; i++)
    {
        if(i < j)
            (NOT->pin[i]).type = OUTPUT_PIN;
        else
            (NOT->pin[i]).type = UNUSED_PIN;

        (NOT->pin[i]).pinNumber = i;
        (NOT->pin[i]).state = LOW;
        (NOT->pin[i]).pipe = NULL;
    }

    return NOT;
}

void notEvent(void *moduleAndPin, unsigned long long delay)
{
    ModuleAndPin *NOT = (ModuleAndPin *)moduleAndPin;
    int outputPinNumber;

    outputPinNumber = outputConnectionForHexInv(NOT->module, NOT->pin->pinNumber, funcOfNOT);

    if(NOT->module->pin[outputPinNumber].pipe != NULL)
        NOT->module->pin[outputPinNumber].pipe->set((void *)NOT->module->pin[outputPinNumber].pipe, NOT->module->pin[outputPinNumber].state, delay);
}

void setNot(void *moduleAndPin, int state, unsigned long long delay)
{
    ModuleAndPin *NOT = (ModuleAndPin *)moduleAndPin;

    if(NOT->pin->type != INPUT_PIN)
        Throw(ERR_NOT_IN_PIN);

    delay = delay + NOT_PROPAGATION_DELAY;

    if(state != NOT->pin->state)
    {
        NOT->pin->state = state;
        registerEvent(NOT, NULL, delay);
    }
}

/**
 *
 * NOT gate logic
 *
 */
int funcOfNOT(Module *module, int pinNumber)
{
    if(module->pin[pinNumber].state == HIGH)
        return LOW;
    else if(module->pin[pinNumber].state == LOW)
        return HIGH;
}

void destroyModule(Module *module)
{
    int i;

    if(module != NULL)
    {

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
    pipe->data = NULL;
    pipe->stateToFire = UNKNOWN;

    return pipe;
}

void pipeEvent(void *pipe, void *node, unsigned long long delay)
{
    Pipe *pipeWithData = (Pipe *)pipe;
    Node *data = (Node *)node;
    ModuleAndPin *moduleAndPin = (ModuleAndPin *)data->dataPtr;

    if(data->left != NULL)
        pipeWithData->event((void *)pipeWithData, (void *)data->left, delay);


    if(data->right != NULL)
        pipeWithData->event((void *)pipeWithData, (void *)data->right, delay);

    moduleAndPin->module->set((void *)moduleAndPin, pipeWithData->stateToFire, delay);
}

void setPipe(void *pipe, int state, unsigned long long delay)
{
    Pipe *pipeWithData = (Pipe *)pipe;

    if(pipeWithData->stateToFire != state)
        pipeWithData->stateToFire = state;

    registerEvent(NULL, pipeWithData, delay);
}

void destroyPipe(Pipe *pipe)
{
    if(pipe != NULL)
        free(pipe);
}

void destroyPipeData(Pipe *pipe)
{    
    if(pipe != NULL)
    {
        if(pipe->data != NULL)
        {
            ModuleAndPin *moduleAndPin = (ModuleAndPin *)pipe->data->dataPtr;
            destroyModuleAndPin(moduleAndPin);
            destroyNode(pipe->data);
        }

        free(pipe);
    }
}

void storedModuleAndPin(ModuleAndPin *moduleAndPin, Module *module, int pinNum)
{
    moduleAndPin->module = module;
    moduleAndPin->pin = &module->pin[pinNum];
}

ModuleAndPin *createdModuleAndPin(Module *module, int pinNum)
{
    ModuleAndPin *moduleAndPin;

    moduleAndPin = malloc(sizeof(ModuleAndPin));
    moduleAndPin->module = module;
    moduleAndPin->pin = &module->pin[pinNum];

    return moduleAndPin;
}

void destroyModuleAndPin(ModuleAndPin *moduleAndPin)
{
    if(moduleAndPin != NULL)
        free(moduleAndPin);
}

/**
 *
 * To configure the output of thisModule to a pipe and pipe to nextModule
 *
 */
void configureInputOutput(void *thisModule, void *fromPin, void *nextModule, void *toPin)
{
    Module *sourceModule = (Module *)thisModule;
    Module *destModule = (Module *)nextModule;
    Pin *sourcePin = (Pin *)fromPin;
    Pin *destPin = (Pin *)toPin;
    ModuleAndPin *moduleAndPin;
    Node *newPipeNode;
    Pipe *pipe;

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
        moduleAndPin = createdModuleAndPin(destModule, destPin->pinNumber);
        newPipeNode = createdNewPipeDataNode(moduleAndPin);
        genericAddRedBlackTree(&((sourceModule->pin[sourcePin->pinNumber]).pipe)->data, newPipeNode, compareModuleAndPin);
    }
}

/**
 *
 * To determine the number of input according to the type of input
 *
 */
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

/**
 *
 * To determine the number of output according to the type of input
 *
 */
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

/**
 *
 * To determine the connection of output according to the Quad 2 input
 * type of input and return the pin number of output
 *
 */
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

/**
 *
 * To determine the connection of output according to the Tri 3 input
 * type of input and return the pin number of output
 *
 */
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

/**
 *
 * To determine the connection of output according to the Dual 4 input
 * type of input and return the pin number of output
 *
 */
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

/**
 *
 * To determine the connection of output according to the Hex Inv
 * input and return the pin number of output
 *
 */
int outputConnectionForHexInv(Module *module, int pinNumber, int (*gateFunction)(Module *module, int pinNumber))
{
    int outputPinNumber;

    switch(pinNumber)
    {
        case 0:
            outputPinNumber = 6;
            break;
        case 1:
            outputPinNumber = 7;
            break;
        case 2:
            outputPinNumber = 8;
            break;
        case 3:
            outputPinNumber = 9;
            break;
        case 4:
            outputPinNumber = 10;
            break;
        case 5:
            outputPinNumber = 11;
            break;
    }

    module->pin[outputPinNumber].state = gateFunction(module, pinNumber);

    return outputPinNumber;
}
