#ifndef CASTUTIL_H
#define CASTUTIL_H

#define N_CAST(c, v) (v)
#define D_CAST(c, v) dynamic_cast<c>(v)
#define R_CAST(c, v) reinterpret_cast<c>(v)
#define S_CAST(c, v) static_cast<c>(v)

#endif
