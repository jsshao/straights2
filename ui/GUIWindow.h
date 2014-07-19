#ifndef GUIWINDOW_H
#define GUIWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/table.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <vector>
#include "DeckGUI.h"

class GUIWindow : public Gtk::Window {
public:
    GUIWindow();
    virtual ~GUIWindow();
protected:
    Gtk::Image* cards[52];
    DeckGUI card_manager;
    Gtk::VBox layout;
    Gtk::HBox header;
	Gtk::Table table;
	Gtk::Button start_;
	Gtk::Button end_;
	Gtk::Entry seed_;
};

#endif
