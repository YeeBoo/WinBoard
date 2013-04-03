/*
 * xboard.h -- Parameter definitions for X front end
 * $Id: xboard.h,v 2.1 2003/10/27 19:21:00 mann Exp $
 *
 * Copyright 1991 by Digital Equipment Corporation, Maynard, Massachusetts.
 * Enhancements Copyright 1992-95 Free Software Foundation, Inc.
 *
 * The following terms apply to Digital Equipment Corporation's copyright
 * interest in XBoard:
 * ------------------------------------------------------------------------
 * All Rights Reserved
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies and that
 * both that copyright notice and this permission notice appear in
 * supporting documentation, and that the name of Digital not be
 * used in advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.
 *
 * DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
 * DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
 * ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 * ------------------------------------------------------------------------
 *
 * The following terms apply to the enhanced version of XBoard distributed
 * by the Free Software Foundation:
 * ------------------------------------------------------------------------
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * ------------------------------------------------------------------------
 */

#include <stdio.h>

#define ICS_LOGON    ".icsrc"
#define INFOFILE     "xboard.info"
#define MANPAGE      "xboard.6"
#define CLOCK_FONT   "-*-helvetica-bold-r-normal--*-*-*-*-*-*-*-*"
#define COORD_FONT   "-*-helvetica-bold-r-normal--*-*-*-*-*-*-*-*"
#define DEFAULT_FONT "-*-helvetica-medium-r-normal--*-*-*-*-*-*-*-*"
#define COLOR_SHOUT             "green"
#define COLOR_SSHOUT            "green,black,1"
#define COLOR_CHANNEL1          "cyan"
#define COLOR_CHANNEL           "cyan,black,1"
#define COLOR_KIBITZ            "magenta,black,1"
#define COLOR_TELL              "yellow,black,1"
#define COLOR_CHALLENGE         "red,black,1"
#define COLOR_REQUEST           "red"
#define COLOR_SEEK              "blue"
#define COLOR_NORMAL            "default"

typedef struct {
    char *name;
    int squareSize;
    int lineGap;
    int clockFontPxlSize;
    int coordFontPxlSize;
    int fontPxlSize;
    int smallLayout;
    int tinyLayout;
    int minScreenSize;
} SizeDefaults;

#define SIZE_DEFAULTS \
{ { "Titanic",  129, 4, 34, 14, 14, 0, 0, 1200 }, \
  { "Colossal", 116, 4, 34, 14, 14, 0, 0, 1200 }, \
  { "Giant",    108, 3, 34, 14, 14, 0, 0, 1024 }, \
  { "Huge",     95, 3, 34, 14, 14, 0, 0, 1024 }, \
  { "Big",      87, 3, 34, 14, 14, 0, 0, 864 }, \
  { "Large",    80, 3, 34, 14, 14, 0, 0, 864 }, \
  { "Bulky",    72, 3, 34, 12, 14, 0, 0, 864 }, \
  { "Medium",   64, 3, 34, 12, 14, 0, 0, 768 }, \
  { "Moderate", 58, 3, 34, 12, 14, 0, 0, 768 }, \
  { "Average",  54, 2, 30, 11, 12, 0, 0, 600 }, \
  { "Middling", 49, 2, 24, 10, 12, 0, 0, 600 }, \
  { "Mediocre", 45, 2, 20, 10, 12, 1, 0, 600 }, \
  { "Small",    40, 2, 20, 10, 12, 1, 0, 480 }, \
  { "Slim",     37, 2, 20, 10, 12, 1, 0, 480 }, \
  { "Petite",   33, 1, 15, 9,  11, 1, 0, 480 }, \
  { "Dinky",    29, 1, 15, 9,  11, 1, 0, 480 }, \
  { "Teeny",    25, 1, 12, 8,  11, 1, 1, 480 }, \
  { "Tiny",     21, 1, 12, 8,  11, 1, 1, 0 }, \
  { NULL, 0, 0, 0, 0, 0, 0 } }

#define BORDER_X_OFFSET 3
#define BORDER_Y_OFFSET 27
#define FIRST_CHESS_PROGRAM	"gnuchessx"
#define SECOND_CHESS_PROGRAM	"gnuchessx"

/* Default to no flashing (the "usual" XBoard behavior) */
#define FLASH_COUNT	0		/* Number of times to flash */
#define FLASH_RATE	5		/* Flashes per second */

/* Default delay per character (in msec) while sending login script */
#define MS_LOGIN_DELAY  0

typedef int (*FileProc) P((FILE *f, int n, char *title));
void CatchDeleteWindow(Widget w, String procname);

#define TOPLEVEL 1 /* preference item; 1 = make popup windows toplevel */

