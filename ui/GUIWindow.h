#ifndef GUIWINDOW_H
#define GUIWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/table.h>
#include <vector>
#include "DeckGUI.h"

class GUIWindow : public Gtk::Window {
public:
    GUIWindow();
    virtual ~GUIWindow();
protected:
    Gtk::Image* *cards[4];
    DeckGUI card_manager;
    Gtk::VBox layout;
    Gtk::Table table;
};

#endif
