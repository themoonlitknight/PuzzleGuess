//
//  settings.h
//  PuzzleGuess
//
//  Created by Francesco on 25/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PuzzleGuess_settings_h
#define PuzzleGuess_settings_h

#define MENUMARGIN 40	// space in points at the top of the screen left for in-game menu

#define dimX 20			// width of the cell in points
#define dimY 20			// height of the cell in points
#define MAXCELLS 10		// max number of cells to draw simultaneously. all of these are statically allocated

#define ATTEMPTS 3		// number of attempts to guess
#define NUMALT 4		// number of choices among which to guess

#define CATEGORIES 4	// number of categories
#define LEVELS 12		// number of levels for each category

/***** menu items *****/
#define MENUITEM_BACK "menuitem_back.png"
#define MENUITEM_BACK_SEL "menuitem_back_sel.png"

// gameplay
#define MENUITEM_GUESS		"menuitem_guess.png"
#define MENUITEM_GUESS_SEL	"menuitem_guess_sel.png"
#define MENUITEM_MENU		"menuitem_menu.png"
#define MENUITEM_MENU_SEL	"menuitem_menu_sel.png"

// guess
#define MENUITEM_FILL		"menuitem_fill.png"
#define MENUITEM_FILL_SEL	"menuitem_fill_sel.png"

// levels
#define MENUITEM_UNLOCKED		"levelunlocked.png"
#define MENUITEM_UNLOCKED_SEL	"levelunlocked_sel.png"
#define MENUITEM_LOCKED		"levellocked.png"
#define MENUITEM_LOCKED_SEL	"levellocked_sel.png"

// category
#define MENUITEM_CATEGORY		"levelunlocked.png"
#define MENUITEM_CATEGORY_SEL	"levelunlocked.png"

// mainmenu
#define MENUITEM_PLAY		"menuitem_play.png"
#define MENUITEM_PLAY_SEL	"menuitem_play.png"
#define MENUITEM_OPTIONS		"menuitem_options.png"
#define MENUITEM_OPTIONS_SEL	"menuitem_options.png"

// result
#define MENUITEM_NEXTLEVEL "menuitem_nextlevel.png"
#define MENUITEM_NEXTLEVEL_SEL "menuitem_nextlevel_sel.png"
#define MENUITEM_RETRYLEVEL "menuitem_retrylevel.png"
#define MENUITEM_RETRYLEVEL_SEL "menuitem_retrylevel_sel.png"
#define MENUITEM_RETURNLEVELS "menuitem_returnlevels.png"
#define MENUITEM_RETURNLEVELS_SEL "menuitem_returnlevels_sel.png"
#define MENUITEM_RETURNMAIN "menuitem_returnmain.png"
#define MENUITEM_RETURNMAIN_SEL "menuitem_returnmain_sel.png"

/**********************/

#define IMG_LEVELCOMPLETED "level_completed.png"
#define IMG_LEVELFAILED "level_failed.png"

#endif
