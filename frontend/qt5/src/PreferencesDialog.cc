// PreferencesDialog.cc --- base class for the break windows
//
// Copyright (C) 2001 - 2013 Rob Caelers & Raymond Penners
// All rights reserved.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "PreferencesDialog.hh"

#include <QtGui>
#include <QStyle>

#include "debug.hh"
#include "nls.h"

#include "TimerPreferencesPanel.hh"

// #include "System.hh"
#include "Util.hh"
#include "ICore.hh"
// #include "CoreFactory.hh"

using namespace workrave;

PreferencesDialog::PreferencesDialog()
  : QDialog(),
    notebook(NULL),
    hsize_group(NULL),
    vsize_group(NULL)
{
  TRACE_ENTER("PreferencesDialog::PreferencesDialog");

  QVBoxLayout* layout = new QVBoxLayout();
  layout->setContentsMargins(1, 1, 1, 1);
  setLayout(layout);
  
  notebook = new QTabWidget();
  layout->addWidget(notebook);

  notebook->setTabPosition(QTabWidget::West);
  notebook->setIconSize(QSize(100,100));
  
  QWidget *timer_page = create_timer_page();
  add_page(_("Timers"), "time.png", timer_page);

  QWidget *gui_page = create_ui_page();
  add_page(_("User interface"), "display.png", gui_page);

  QDialogButtonBox *buttonBox =  new QDialogButtonBox(QDialogButtonBox::Close);
  layout->addWidget(buttonBox);

  connect(buttonBox, SIGNAL(rejected()), this, SLOT(accept()));
  TRACE_EXIT();
}


//! Destructor.
PreferencesDialog::~PreferencesDialog()
{
  TRACE_ENTER("PreferencesDialog::~PreferencesDialog");
  delete hsize_group;
  delete vsize_group;
  TRACE_EXIT();
}


QWidget *
PreferencesDialog::create_timer_page()
{
  QWidget *ret;
  
  QTabWidget *timer_tab = new QTabWidget;
  timer_tab->setTabPosition(QTabWidget::North);

  hsize_group = new SizeGroup(Qt::Horizontal);
  vsize_group = new SizeGroup(Qt::Horizontal);
  
  for (int i = 0; i < BREAK_ID_SIZEOF; i++)
    {
      TimerPreferencesPanel *panel = new TimerPreferencesPanel(BreakId(i), hsize_group, vsize_group);

      // FIXME: duplicate:
      const char *icons[] = { "timer-micro-break.png", "timer-rest-break.png", "timer-daily.png" };
      const char *labels[] = { _("Micro-break"), _("Rest break"), _("Daily limit") };

      std::string file = Util::complete_directory(string(icons[i]), Util::SEARCH_PATH_IMAGES);
      QPixmap pixmap(file.c_str());
      QIcon icon(pixmap);

      timer_tab->addTab(panel, icon, labels[i]);
    }

  ret = timer_tab;
  return ret;
}


QWidget *
PreferencesDialog::create_ui_page()
{
  QWidget *ret = new QWidget;

  return ret;
}


void
PreferencesDialog::add_page(const char *label, const char *image, QWidget *page)
{
  std::string file = Util::complete_directory(image, Util::SEARCH_PATH_IMAGES);
  QPixmap pixmap(file.c_str());
  QIcon icon(pixmap);

  notebook->addTab(page, icon, label);
}
