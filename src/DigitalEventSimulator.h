#ifndef DigitalEventSimulator_H
#define DigitalEventSimulator_H

#include "EventTime.h"
#include "DigitalSignalModule.h"

// void registerEvent(Module *module, unsigned long long expiredPeriod);
Node *registerEvent(ModuleAndPin *moduleAndPin, Pipe *pipe, unsigned long long expiredPeriod);
void storedEventTimeData(EventTime *eventTime, ModuleAndPin *moduleAndPin, Pipe *pipe);
unsigned long long determinePropagationDelay(Module *module);
int eventSimulator();

#endif // DigitalEventSimulator_H
