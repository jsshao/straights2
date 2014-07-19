#ifndef GUIWINDOW_H
#define GUIWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/table.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/frame.h>
#include <vector>
#include "DeckGUI.h"

class GUIWindow : public Gtk::Window {
public:
    GUIWindow();
    virtual ~GUIWindow();
protected:
    Gtk::Image* cards[52];
    Gtk::Image* hand_cards[13];
    DeckGUI card_manager;
    Gtk::Frame tableFrame;
	Gtk::Frame playerFrame[4];
	Gtk::VBox player[4];
	Gtk::Button switchButton[4];
	Gtk::Label points[4];
	Gtk::Label discards[4];
	Gtk::VBox layout;
	Gtk::HBox players;
    Gtk::HBox header;
	Gtk::Table table;
	Gtk::Button start_;
	Gtk::Button end_;
	Gtk::Entry seed_;
	Gtk::Frame handFrame_;
	Gtk::HBox hand_;	
    Gtk::Button handButtons_[13];	
};

#endif
