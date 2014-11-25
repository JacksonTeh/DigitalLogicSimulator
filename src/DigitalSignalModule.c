#include <stdio.h>
#include <malloc.h>
#include "DigitalSignalModule.h"

/**
 * ========================
 * |       AND Gate       |
 * ========================
 */
Module *createdAndModule(int numberOfPin)
{
    Module *AND;
    int i, j = 0;
    int input[numberOfPin];
    int output[numberOfPin / 2];

    if(numberOfPin <= 1)                    //no of input must more than 2
        Throw(ERR_INVALID_PIN_NUMBER);

    AND = malloc(sizeof(Module));
    AND->input = input;
    AND->output = output;
    AND->event = andEvent;
    AND->set = setAnd;
    AND->configure = configureInputOutput;

    /* Initialise to UNKNOWN state */
    for(i = 0; i < numberOfPin; i++)
    {
        AND->input[i] = UNKNOWN;

        if(i % 2 != 0)
        {
            AND->output[j] = UNKNOWN;
            j++;
        }
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
Module *createdOrModule(int numberOfPin)
{
    Module *OR;
    int i, j = 0;
    int input[numberOfPin];
    int output[numberOfPin / 2];

    if(numberOfPin <= 1)                    //no of input must more than 2
        Throw(ERR_INVALID_PIN_NUMBER);

    OR = malloc(sizeof(Module));
    OR->input = input;
    OR->output = output;
    OR->event = orEvent;
    OR->set = setOr;
    OR->configure = configureInputOutput;

    /* Initialise to UNKNOWN state */
    for(i = 0; i < numberOfPin; i++)
    {
        OR->input[i] = UNKNOWN;

        if(i % 2 != 0)
        {
            OR->output[j] = UNKNOWN;
            j++;
        }
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
    Module *XOR;
    int i, j = 0;
    int input[numberOfPin];
    int output[numberOfPin / 2];

    if(numberOfPin <= 1)                    //no of input must more than 2
        Throw(ERR_INVALID_PIN_NUMBER);

    XOR = malloc(sizeof(Module));
    XOR->input = input;
    XOR->output = output;
    XOR->event = xorEvent;
    XOR->set = setXor;
    XOR->configure = configureInputOutput;

    /* Initialise to UNKNOWN state */
    for(i = 0; i < numberOfPin; i++)
    {
        XOR->input[i] = UNKNOWN;

        if(i % 2 != 0)
        {
            XOR->output[j] = UNKNOWN;
            j++;
        }
    }

    return XOR;
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
    Module *NAND;
    int i, j = 0;
    int input[numberOfPin];
    int output[numberOfPin / 2];

    if(numberOfPin <= 1)                    //no of input must more than 2
        Throw(ERR_INVALID_PIN_NUMBER);

    NAND = malloc(sizeof(Module));
    NAND->input = input;
    NAND->output = output;
    NAND->event = nandEvent;
    NAND->set = setNand;
    NAND->configure = configureInputOutput;

    /* Initialise to UNKNOWN state */
    for(i = 0; i < numberOfPin; i++)
    {
        NAND->input[i] = UNKNOWN;

        if(i % 2 != 0)
        {
            NAND->output[j] = UNKNOWN;
            j++;
        }
    }

    return NAND;
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
    Module *NOR;
    int i, j = 0;
    int input[numberOfPin];
    int output[numberOfPin / 2];

    if(numberOfPin <= 1)                    //no of input must more than 2
        Throw(ERR_INVALID_PIN_NUMBER);

    NOR = malloc(sizeof(Module));
    NOR->input = input;
    NOR->output = output;
    NOR->event = norEvent;
    NOR->set = setNor;
    NOR->configure = configureInputOutput;

    /* Initialise to UNKNOWN state */
    for(i = 0; i < numberOfPin; i++)
    {
        NOR->input[i] = UNKNOWN;

        if(i % 2 != 0)
        {
            NOR->output[j] = UNKNOWN;
            j++;
        }
    }

    return NOR;
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
    Module *NOT;
    int i;
    int input[numberOfPin];
    int output[numberOfPin];

    if(numberOfPin < 1)                    //no of input must not 0
        Throw(ERR_INVALID_PIN_NUMBER);

    NOT = malloc(sizeof(Module));
    NOT->input = input;
    NOT->output = output;
    NOT->event = notEvent;
    NOT->set = setNot;
    NOT->configure = configureInputOutput;

    /* Initialise to UNKNOWN state */
    for(i = 0; i < numberOfPin; i++)
    {
        NOT->input[i] = UNKNOWN;
        NOT->output[i] = UNKNOWN;
    }

    return NOT;
}

int notEvent(void *module)
{

}

void setNot(void *pin, void *state)
{

}

void destroyModule(Module *module)
{
    if(module != NULL)
        free(module);
}

void configureInputOutput(void *thisModule, void *fromPin, void *nextModule, void *toPin)
{
    Module *fromModule = (Module *)thisModule;
    Module *toModule = (Module *)nextModule;
    int *outPin = (int *)fromPin;
    int *inPin = (int *)toPin;
    // int num = *outPin;

    // outPin = outPin - 1;
    // *outPin = num + 1;
    printf("outPin: %d\n", outPin);
    printf("inPin: %d\n", inPin);
    // printf("fromModule->output[%d]: %d\n", (outPin)-1, fromModule->output[0]);
    // toModule->input[inPin-1] = fromModule->output[outPin-1];
}

void pipeAttach(Pipe **pipe, Module **fromModule, void *fromPin, Module **toModule, void *toPin)
{

}