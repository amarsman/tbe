/* The Butterfly Effect
 * This file copyright (C) 2012 Klaas van Gend
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA.
 */

#ifndef DUMMYUNDOCOMMAND_H
#define DUMMYUNDOCOMMAND_H

#include "AbstractUndoCommand.h"
#include "Position.h"
#include "ToolboxGroup.h"
#include "ViewObject.h"

/// Implementation of AbstractUndoCommand, base class to actions that do not
/// actually have something to undo/redo, just trigger a single (UI) action.
/// @note that this class THUS has significant different behavior:
///          * no body to undo()/redo()
///          * commit() will call deleteLater() on itself
class DummyUndoCommand : public QObject, public AbstractUndoCommand
{
    Q_OBJECT;

public:
    DummyUndoCommand(ViewObjectPtr anViewObjectPtr,
                     const QString &anUndoName);

    /// Overridden to just make sure not to push anything.
    virtual void commit(void) override;

    /// Mandatory, but we don't care - not used for any dummies
    /// @note that mouseReleaseEvent is not overridden - it will still call commit().
    bool mouseMoveEvent   (QGraphicsSceneMouseEvent *) override
    {
        return false;
    }

    /// Mandatory, but we don't care - not used for any dummies because we don't
    /// implement decorators either.
    /// @note that mouseReleaseEvent is not overridden - it will still call commit().
    bool mousePressEvent  (QGraphicsSceneMouseEvent *) override
    {
        return false;
    };

    /// Overridden because we don't have anything to do and need
    /// to prove this member is never called.
    void redo() override
    {
        Q_ASSERT(false);
    };

    /// Overridden because we don't have anything to do and need
    /// to prove this member is never called.
    void undo() override
    {
        Q_ASSERT(false);
    };
};

#endif // DUMMYUNDOCOMMAND_H
