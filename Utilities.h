#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

// Common macros etc.

#define MAX(A,B)	((A)>(B)?(A):(B))
#define MIN(A,B)	((A)<(B)?(A):(B))

#define CLAMP(VAL,LO,HI)	(MAX(MIN(VAL,HI),LO))

#endif // !UTILITIES_H_INCLUDED
