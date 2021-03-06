/* 
 *   Creation Date: <2000/12/09 16:24:56 samuel>
 *   Time-stamp: <2003/03/01 15:58:57 samuel>
 *   
 *	<keycodes.h>
 *	
 *	Handles different keyboard layout and user customization
 *   
 *   Copyright (C) 2000, 2001, 2002, 2003 Samuel Rydh (samuel@ibrium.se)
 *   
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License
 *   as published by the Free Software Foundation
 *   
 */

#ifndef _H_KEYCODES
#define _H_KEYCODES

#include "kbd_sh.h"

static inline int uses_linux_keycodes( void ) { 
	extern int _uses_linux_keycodes; return _uses_linux_keycodes;
}

/* API for key sources  */
extern int	register_key_table( int ktype, int min, int max );
extern int	user_kbd_customize( int ktype );

extern void	key_event( int keycode_type, int keycode, int is_keypress );
extern void	zap_keyboard( void );
extern void	set_keycode( int keycode_type, int keycode, int adbcode );

/* MOL keyboard shortcuts */
typedef struct key_action {
	int 	mod1, mod2, key;
	int	(*action)( int key, int usr_val );
	int	usr_val;

	/* internal to keycodes.c */
	struct	key_action *next;
	int	fire;
} key_action_t;

extern void	add_key_actions( key_action_t *, int size );
extern void	remove_key_actions( key_action_t *, int size );

/* Some ADB keycodes used by mol */
#define KEY_F1			0x7a
#define KEY_F2			0x78
#define KEY_F3			0x63
#define KEY_F4			0x76
#define KEY_F5			0x60
#define KEY_F6			0x61
#define KEY_F7			0x62
#define KEY_F8			0x64
#define KEY_F9			0x65
#define KEY_F10	 		0x6d
#define KEY_F11			0x67
#define KEY_F12			0x6f

#define KEY_TAB			0x30
#define KEY_SPACE		0x31	/* FIXME */
#define KEY_RETURN		0x24
#define KEY_ENTER		0x4c
#define KEY_CAPSLOCK		0x39

#define KEY_CTRL		0x36
#define KEY_SHIFT		0x38
#define KEY_ALT			0x3a
#define KEY_COMMAND		0x37

#define KEY_SET2(a,b)		(((a)<<8) | b)
#define KEY_SET3(a,b,c)		(((a)<<16) | ((b)<<8) | (c))
#define KEY_SET4(a,b,c,d)	(((a)<<24) | ((b)<<16) | ((c)<<8) | (d))

/* #define KEY_RIGHT_OPTION	0x7c */
/* #define KEY_RIGHT_CTRL	0x7d */


#endif   /* _H_KEYCODES */
