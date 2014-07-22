/*
 * RandomGithub: mainWindow.hpp
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
 * @file mainWindow.hpp
 * @author Kyle Givler
 */

#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <gtkmm.h>
#include "randomGithub.hpp"

class MainWindow : public Gtk::window 
{
  MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder> &refGlade);
  virtual ~MainWindow();
  
protected:
  RandomGithub rg;
  Glib::RefPtr<Gtk::Builder> glade;
  
  Gtk::AboutDialog *pAboutDialog;
};

#endif