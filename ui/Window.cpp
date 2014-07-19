#include "GUIWindow.h"
#include <iostream>
using namespace std;

GUIWindow::GUIWindow() :
    m_button("test")
{
	set_border_width( 10 );
	
	m_button.signal_clicked().connect( sigc::mem_fun( *this, &GUIWindow::onButtonClicked ) );
	
	// This packs the button into the GUIWindow (a container).
	add( m_button );
	
	// The final step is to display this newly created widget.
	m_button.show();
}

GUIWindow::~GUIWindow() {}

void GUIWindow::onButtonClicked() {
    cout << "thanks it worked" << endl; 
}
