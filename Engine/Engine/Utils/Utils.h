#ifndef _UTILS_H
#define _UTILS_H

#define SAFE_DELETE_PTR(ptr) if(ptr){ delete ptr; ptr = NULL; }
#define SAFE_DELETE_ARY(ary) if(ary){ delete[] ary; ary = NULL;}

#endif
