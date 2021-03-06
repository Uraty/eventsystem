#ifndef RUN_SYSTEM_ENGINE_H
#define RUN_SYSTEM_ENGINE_H

#ifdef SYSTEM_LIFECYCLE
    int _evs_handleSystemStart();
    int _evs_handleSystemTick();
    int _evs_handleSystemStop();
#endif

void _evs_systemStep();

int _evs_isEventSystemStopped;
int _evs_isSystemStart;
int _evs_systemStepId;

void runEventSystem()
{
    _evs_isEventSystemStopped = 0;
    _evs_isSystemStart = 1;
    
    #ifdef SYSTEM_LIFECYCLE
	   _evs_handleSystemStart();
    #endif
    
	while(!_evs_isEventSystemStopped)
	{
        #ifdef SYSTEM_LIFECYCLE
            _evs_handleSystemTick();
        #endif
        
		_evs_systemStepId++;
		_evs_systemStep();
	}
    
    #ifdef SYSTEM_LIFECYCLE
        _evs_handleSystemStop();
    #endif
}

#endif
