#pragma once

#include <iostream>

inline void PHEM_Bind_CPU_Thread() {}
inline void PHEM_Unbind_CPU_Thread() {}

inline void PHEM_Begin_Vibration() {}
inline void PHEM_End_Vibration() {}
inline void PHEM_Enable_LED(int) {}

#if defined(DONT_DEBUG_THIS)
#define PHEM_Log_Msg(msg)
#define PHEM_Log_Place(val)
#define PHEM_Log_Hex(val)
#else
#define PHEM_Log_Msg(msg) std::cerr << __PRETTY_FUNCTION__ << " " << msg << std::endl
#define PHEM_Log_Place(val) std::cerr << __FILE__ << ":" << __LINE__ << " " << val << std::endl
#define PHEM_Log_Hex(val) fprintf(stderr, "%x\n", val)
#endif
