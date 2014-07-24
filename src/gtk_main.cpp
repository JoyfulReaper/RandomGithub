/*
 * RandomGithub: gtk_main.cpp
 * Copyright (C) 2014 Kyle Givler
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file gtk_main.cpp
 * @author Kyle Givler
 */

/*
 * Usage:
 * $ gtkRandomGithub [num api requests]
 */

#include "mainWindow.hpp"
#include <cstdlib>

int main(int argc, char **argv)
{  
  size_t numArgs = argc;
  argc = 1;
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "com.kgivler.randomgithub");
  Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
  
  try
  {
    refBuilder->add_from_file("gui.glade");
  }
  catch(const Glib::FileError& ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const Glib::MarkupError& ex)
  {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const Gtk::BuilderError& ex)
  {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return 1;
  }
  
  MainWindow *pWindow = 0;
  refBuilder->get_widget_derived("mainWindow", pWindow);
  
  unsigned int numRequests;
  if(numArgs == 2)
    numRequests = strtol(argv[1], NULL, 10);
  if (!numRequests)
    numRequests = 1;
  
  if(pWindow)
  {
    pWindow->set_num_requests(numRequests);
    app->run(*pWindow, argc, argv);
  }
  
  delete pWindow;
  return 0;
}