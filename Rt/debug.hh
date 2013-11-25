#ifndef __Rt_debug_hh
#define __Rt_debug_hh

#define E_DEBUG(X) std::cerr << "  " << __FILE__ << ":" << __LINE__ << "  " << #X << " = " << (X) << "\n"

#endif
