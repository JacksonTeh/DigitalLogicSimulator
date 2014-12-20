#ifndef DigitalEventSimulator_H
#define DigitalEventSimulator_H

#include "DigitalSignalModule.h"
#include "Node.h"

// Node *registerEvent(ModuleAndPin *moduleAndPin, Pipe *pipe, unsigned long long expiredPeriod);
// void registerEvent(Node **eventRoot, ModuleAndPin *moduleAndPin, Pipe *pipe, unsigned long long expiredPeriod);
void registerEvent(ModuleAndPin *moduleAndPin, Pipe *pipe, unsigned long long expiredPeriod);
// void storedEventInfoData(EventInfo *eventInfo, ModuleAndPin *moduleAndPin, Pipe *pipe);
// unsigned long long determinePropagationDelay(Module *module);
// int eventSimulator(Node *eventRoot);
int eventSimulator();

#endif // DigitalEventSimulator_H
