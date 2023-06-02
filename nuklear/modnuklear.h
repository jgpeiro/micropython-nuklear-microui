/****************************************************************************
 * File:	modnuklear.h
 * Brief:		

integration steps:
1.
file: mpconfigport.h
line: // extra built in modules to add to the list
add : extern const struct _mp_obj_module_t nuklear_module;
2.
file: mpconfigport.h
line: // #define MICROPY_PORT_BUILTIN_MODULES
add : { MP_ROM_QSTR(MP_QSTR_nuklear), (mp_obj_t)&nuklear_module }, 
3.
file: makefile.mk
line: // SRC_C =  
add : modnuklear.c 

 * Author:		
 ****************************************************************************/
#ifndef	_MODNUKLEAR_H_
#define	_MODNUKLEAR_H_
/****************************************************************************
 * Public Includes.
 ****************************************************************************/

/****************************************************************************
 * Public Defines.
 ****************************************************************************/

/****************************************************************************
 * Public Types.
 ****************************************************************************/

/****************************************************************************
 * Public Variables.
 ****************************************************************************/

/****************************************************************************
 * Public Functions.
 ****************************************************************************/

#endif	//#ifndef	_MODNUKLEAR_H_
