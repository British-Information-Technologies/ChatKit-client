#include <stdio.h>

#include "MainApplication.h"

/*
 *
 */
MainApplication::MainApplication()
	: Application() {

	Window* mainWindow = nullptr;

	auto builder = Builder::create();
	builder->add_from_file("resource/mickyb18-chat-client.glade");
	builder->get_widget("main_window", mainWindow);

	this->mainWindow = mainWindow;
	this->mainWindow->show();
}

MainApplication::~MainApplication() {
	this->release();
}