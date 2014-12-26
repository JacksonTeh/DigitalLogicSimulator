#ifndef DigitalEventSimulator_H
#define DigitalEventSimulator_H

#include "DigitalSignalModule.h"
#include "Node.h"

void registerEvent(ModuleAndPin *moduleAndPin, Pipe *pipe, unsigned long long expiredPeriod);
int eventSimulator();

#endif // DigitalEventSimulator_H
