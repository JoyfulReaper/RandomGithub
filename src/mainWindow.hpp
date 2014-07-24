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
#include <vector>
#include "randomGithub.hpp"

class MainWindow : public Gtk::Window 
{
public:
  MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
  virtual ~MainWindow();
  
  void set_num_requests(size_t num);
  
protected:
  void getRepos();
  void quit();
  void show_about();
  void on_about_response(int response_it);
  void next_clicked();
  void prev_clicked();
  void update_labels();
  
  RandomGithub rg;
  std::vector<GitRepo> repos;
  size_t currentRepo = 0;
  size_t requests = 0; // API Requests remaining
  size_t numRequests = 1; // Number of API requests to issues (Larger numbers take longer, but produce more random results)
  
  Glib::RefPtr<Gtk::Builder> glade;
  Gtk::AboutDialog *pAboutDialog;
  Gtk::Button *pPrevButton;
  Gtk::Button *pNextButton;
  Gtk::Button *pGetButton;
  Gtk::Label *LID;
  Gtk::Label *LOwner;
  Gtk::Label *LName;
  Gtk::Label *LDescription;
  Gtk::Label *LRequests;
  Gtk::Label *LCurrent;
  Gtk::LinkButton *LRepoHTML;
  Gtk::LinkButton *LOwnerHTML;
};

#endif