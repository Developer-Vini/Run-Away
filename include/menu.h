#ifndef MENU_H
#define MENU_H

typedef  enum {
    MENU_ACTION_NONE,
    MENU_ACTION_PLAY,
    MENU_ACTION_QUIT
} MenuAction;

MenuAction updateMenu(void);
void drawMenu(void);

void initMenu(void);
void unloadMenu(void);

#endif