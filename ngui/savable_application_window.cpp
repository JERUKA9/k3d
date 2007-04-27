// K-3D
// Copyright (c) 1995-2005, Timothy M. Shead
//
// Contact: tshead@k-3d.com
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

/** \file
		\author Tim Shead (tshead@k-3d.com)
*/

#include "application_state.h"
#include "safe_close_dialog.h"
#include "savable_application_window.h"

#include <k3dsdk/iapplication.h>
#include <k3dsdk/application.h>

#include <gtkmm/dialog.h>
#include <gdk/gdkkeysyms.h>

namespace libk3dngui
{

/////////////////////////////////////////////////////////////////////////////
// savable_application_window

savable_application_window::savable_application_window(const std::string& Name, k3d::icommand_node* const Parent) :
	base(Gtk::WINDOW_TOPLEVEL),
	ui_component(Name, Parent)
{
	application_state::instance().connect_safe_close_signal(sigc::mem_fun(*this, &savable_application_window::on_safe_close));
	k3d::application().connect_close_signal(sigc::mem_fun(*this, &savable_application_window::close));
}

savable_application_window::~savable_application_window()
{
}

bool savable_application_window::on_key_press_event(GdkEventKey* event)
{
	if(event->keyval == GDK_Escape)
	{
		safe_close();
		return true;
	}

	return base::on_key_press_event(event);
}

bool savable_application_window::on_delete_event(GdkEventAny* event)
{
	safe_close();
	return true;
}

unsaved_document* savable_application_window::on_safe_close()
{
	return this;
}

const bool savable_application_window::save_changes()
{
	if(application_state::instance().batch_mode() || !unsaved_changes())
		return true;

	switch(safe_close_dialog::run(*this, unsaved_document_title()))
	{
		case Gtk::RESPONSE_NONE:
		case Gtk::RESPONSE_CANCEL:
		case Gtk::RESPONSE_DELETE_EVENT:
			return false;
		case Gtk::RESPONSE_CLOSE:
			return true;
		case Gtk::RESPONSE_OK:
			return save_unsaved_changes();
	}

	assert_not_reached();
	return false;
}

void savable_application_window::safe_close()
{
	if(application_state::instance().batch_mode() || !unsaved_changes())
	{
		close();
		return;
	}

	switch(safe_close_dialog::run(*this, unsaved_document_title()))
	{
		case Gtk::RESPONSE_NONE:
		case Gtk::RESPONSE_CANCEL:
		case Gtk::RESPONSE_DELETE_EVENT:
			return;
		case Gtk::RESPONSE_CLOSE:
			close();
			return;
		case Gtk::RESPONSE_OK:
			if(save_unsaved_changes())
				close();
	}
}

void savable_application_window::close()
{
	on_close();
	delete this;
}

void savable_application_window::on_close()
{
}

} // namespace libk3dngui
