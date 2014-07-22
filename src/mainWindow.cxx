/*
 * RandomGithub: mainWindow.cxx
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
 * @file mainWindow.cxx
 * @author Kyle Givler
 */

#include "mainWindow.hpp"

MainWindow::MainWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refGlade)
 : Gtk::Window(cobject),
   glade(refGlade),
   pAboutDialog(0)
{
  
  //About stuff
  glade->get_widget("aboutDialog", pAboutDialog);
  if(pAboutDialog)
    pAboutDialog->signal_response().connect( sigc::mem_fun(*this, &MainWindow::on_about_response) );
  
  //Menu stuff
  Gtk::MenuItem *pAboutItem = 0;
  glade->get_widget("aboutMenuItem", pAboutItem);
  if(pAboutItem)
    pAboutItem->signal_activate().connect( sigc::mem_fun(*this, &MainWindow::show_about) );
  
  Gtk::MenuItem *pQuitItem = 0;
  glade->get_widget("quitMenuItem", pQuitItem);
  if(pAboutItem)
    pQuitItem->signal_activate().connect( sigc::mem_fun(*this, &MainWindow::quit) );
}

MainWindow::~MainWindow() {}

void MainWindow::quit()
{
  this->hide();
  return;
}

void MainWindow::show_about()
{
  pAboutDialog->show();
  pAboutDialog->present();
  return;
}

void MainWindow::on_about_response(int response_id)
{
  if( (response_id == Gtk::RESPONSE_CLOSE) || (response_id == Gtk::RESPONSE_CANCEL) )
  {
    pAboutDialog->hide();
  }
  return;
}