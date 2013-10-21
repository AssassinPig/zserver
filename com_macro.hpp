#ifndef _COM_MACRO_H__
#define _COM_MACRO_H__

#ifndef FUN_NEEDS_RET
#define FUN_NEEDS_RET(type)\
        type ret;\
        return ret;
#endif  //FUN_NEEDS_RET(type)


#ifndef FUN_NEEDS_RET_WITH_DEFAULT
#define FUN_NEEDS_RET_WITH_DEFAULT(type, default_value)\
        type ret = default_value;\
        return ret;
#endif  //FUN_NEEDS_RET(type)

#endif  //_COM_MACRO_H_
