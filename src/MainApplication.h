#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <gtkmm-3.0/gtkmm.h>

using namespace Gtk;

/**
 * Author: @michael-bailey
 * # MainApplication 
 * This class defines the main application of the client
 * It handles all application level events like activation and opening files
 */
class MainApplication : public Application
{
private:
	Window* mainWindow;
public:
	MainApplication();
	~MainApplication();
	
};

#endif