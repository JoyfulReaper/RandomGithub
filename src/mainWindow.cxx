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

#include <iostream>
#include <thread>
#include "mainWindow.hpp"

MainWindow::MainWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refGlade)
: Gtk::Window(cobject),
glade(refGlade),
pAboutDialog(0),
pPrevButton(0),
pNextButton(0),
pGetButton(0),
LID(0),
LOwner(0),
LName(0),
LDescription(0),
LRequests(0),
LCurrent(0),
LRepoHTML(0),
LOwnerHTML(0)
{   
  //Buttons
  glade->get_widget("bPrev", pPrevButton);
  if(pPrevButton)
  {
    pPrevButton->signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::prev_clicked) );
    pPrevButton->set_sensitive(false);
  }
  glade->get_widget("bNext", pNextButton);
  if(pNextButton)
  {
    pNextButton->signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::next_clicked) );
    pNextButton->set_sensitive(false);
  }
  glade->get_widget("bGet", pGetButton);
  if(pGetButton)
    pGetButton->signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::getRepos) );
  
  //Labels
  glade->get_widget("lID", LID);
  glade->get_widget("lOwner", LOwner);
  glade->get_widget("lName", LName);
  glade->get_widget("lCurrent", LCurrent);
  if (LCurrent)
  {
    LCurrent->set_label("Current: 0/0");
  }
  glade->get_widget("lDescription", LDescription);
  if(LDescription)
  {
    LDescription->set_line_wrap_mode(Pango::WRAP_WORD);
    LDescription->set_line_wrap(true);
  }
  glade->get_widget("lRequests", LRequests);
  
  //LinkButtons
  glade->get_widget("lRepoHTML", LRepoHTML);
  if(LRepoHTML)
  {
    LRepoHTML->set_label("Repo URL: ");
    LRepoHTML->set_uri("https://github.com");
  }
  glade->get_widget("lOwnerHTML", LOwnerHTML);
  if(LOwnerHTML)
  {
    LOwnerHTML->set_label("Owner URL: ");
    LOwnerHTML->set_uri("https://github.com");
  }
  
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
  
  Gtk::MenuItem *pGetItem = 0;
  glade->get_widget("getMenuItem", pGetItem);
  if(pGetItem)
    pGetItem->signal_activate().connect( sigc::mem_fun(*this, &MainWindow::getRepos) );
}

MainWindow::~MainWindow() {}

void MainWindow::getRepos()
{
  LCurrent->set_label("Working...");
  
  std::thread([this](){
    if(pPrevButton->get_sensitive())
      pPrevButton->set_sensitive(false);
    if(pNextButton->get_sensitive())
      pNextButton->set_sensitive(false);
    pGetButton->set_sensitive(false);
    
    repos = rg.getRandomRepos(MAX_REPOS, numRequests);
    auto rl = rg.github_getRateLimit();
    requests = rl.remaining;
    currentRepo = 0;
    
    pGetButton->set_sensitive(true);
    pPrevButton->set_sensitive(true);
    pNextButton->set_sensitive(true);
    
    update_labels();
  }).detach();
}

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

void MainWindow::prev_clicked()
{
  currentRepo--;
  update_labels();
  return;
}

void MainWindow::next_clicked()
{  
  currentRepo++;
  update_labels();
  return;
}

void MainWindow::update_labels()
{
  if(currentRepo == 0 || repos.empty())
  {
    pPrevButton->set_sensitive(false);
  } else {
    pPrevButton->set_sensitive(true);
  }
  
  if(currentRepo == repos.size() -1 || repos.empty())
  {
    pNextButton->set_sensitive(false);
  } else {
    pNextButton->set_sensitive(true);
  }
  
  if(repos.empty())
  {
    LCurrent->set_label("No projects found...");
    return;
  }
  
  LID->set_text("ID: " + std::to_string(repos[currentRepo].getRepoId()));
  LOwner->set_text("Owner: " + repos[currentRepo].getOwnerLogin());
  LName->set_text("Name: " + repos[currentRepo].getRepoName());
  LDescription->set_text("Description: " + repos[currentRepo].getRepoDescription());
  LRequests->set_text("API Requests Remaining: " + std::to_string(requests));
  
  LRepoHTML->set_label(repos[currentRepo].getRepoHtmlUrl());
  LRepoHTML->set_uri(repos[currentRepo].getRepoHtmlUrl());
  LOwnerHTML->set_label(repos[currentRepo].getOwnerHtmlUrl());
  LOwnerHTML->set_uri(repos[currentRepo].getOwnerHtmlUrl());
  LCurrent->set_label("Current Project: " + std::to_string((currentRepo +1)) + "/" + std::to_string(repos.size()));
  
  return;
}

void MainWindow::set_num_requests(size_t num)
{
  if (num > 50)
    num = 50;
  
  numRequests = num;
}