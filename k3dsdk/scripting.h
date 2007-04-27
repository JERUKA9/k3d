#ifndef K3DSDK_SCRIPTING_H
#define K3DSDK_SCRIPTING_H

// K-3D
// Copyright (c) 1995-2004, Timothy M. Shead
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
		\brief Declares convenience functions for working with scripts
		\author Tim Shead (tshead@k-3d.com)
*/

#include "iscript_engine.h"

#include <iosfwd>
#include <string>

namespace k3d
{

class iplugin_factory;
class uuid;

namespace script
{

/// Helper class that converts various forms of input into script code that can be executed
class code
{
public:
	/// Script code is stored as a string
	code(const std::string& Source);
	/// Script code is stored as an input stream
	code(std::istream& Source);
	/// Script code is stored in a string stream
	code(std::istringstream& Source);
	/// Script code is stored in a string stream
	code(std::stringstream& Source);

	/// Returns the stored script source code
	const std::string& source() const;

private:
	std::string m_buffer;
};

/// Helper class that converts various forms of input into an identifiable script language
class language
{
public:
	/// Determine the scripting language from a script source
	language(const code& Script);
	/// Specify the scripting language directly
	language(const uuid& Language);
	/// Specify the scripting language directly
	language(iplugin_factory* Language);

	/// Returns the plugin factory that corresponds with the given scripting language
	iplugin_factory* factory() const;

private:
	iplugin_factory* m_factory;
};

/// Executes a script using a specific language
bool execute(const code& Script, const std::string& ScriptName, iscript_engine::context_t& Context, const language& Language);
/// Executes a script, attempting to automatically recognize the language
void execute(const code& Script, const std::string& ScriptName, iscript_engine::context_t& Context, bool& Recognized, bool& Executed);

} // namespace script

} // namespace k3d

#endif // K3DSDK_SCRIPTING_H

