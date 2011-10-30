/* The Butterfly Effect
 * This file copyright (C) 2011 Klaas van Gend
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation
 * applicable version is GPL version 2 only.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef UNDOSINGLETON_H
#define UNDOSINGLETON_H

#include "AbstractObject.h"
#include "PieMenu.h"

#include <QUndoCommand>

// forward declarations
class QUndoStack;
class AbstractUndoCommand;

class UndoSingleton
{
public:
	/// Factory method for AbstractUndoCommands
	/// @param anObject
	/// @param anUndoType
	/// @returns Pointer to a newly created AbstractUndoCommand.
	/// @note The newly created command is not put on the stack yet.
	///       If you want it to, call commit() on the Command.
	///       The object is now owned by the ViewObject anObject.
	static AbstractUndoCommand* createUndoCommand(ViewObject* anObject,
										ActionIcon::ActionType anUndoType);

	/// Clean up the stack (i.e. start a new level)
	/// this removes all UndoObjects from the stack
	static void clear();

	static void push(AbstractUndoCommand* anAUCPtr);

	static QAction * createRedoAction ( QObject* parent, const QString & prefix = QString() );
	static QAction * createUndoAction ( QObject* parent, const QString & prefix = QString() );

public slots:
	static void setClean();

private:
	/// private constructor - this is a singleton class!
	explicit UndoSingleton(void);

	/// @returns pointer to the existing singleton.
	static UndoSingleton* me(void);

	// no copy constructor or assignment operators here!
	Q_DISABLE_COPY ( UndoSingleton )

	QUndoStack theUndoStack;

	friend class UndoObject;
};

#endif // UNDOSINGLETON_H
