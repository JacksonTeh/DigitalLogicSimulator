#ifndef DigitalEventSimulator_H
#define DigitalEventSimulator_H

#include "DigitalSignalModule.h"

// void registerEvent(Module *module, unsigned long long expiredPeriod);
void registerEvent(ModuleAndPin *moduleAndPin, Pipe *pipe, unsigned long long expiredPeriod);

#endif // DigitalEventSimulator_H
