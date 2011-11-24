/* The Butterfly Effect
 * This file copyright (C) 2009,2010  Klaas van Gend
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

#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include <QString>
#include <QList>
#include <QDomDocument>
#include "tbe_global.h"
#include "AbstractObject.h"
#include "LocalString.h"

// Forward Declarations:
class MainWindow;
class World;

/**
  * class Level
  *
  * the level reads the objects from a file and creates the world containing
  * the various objects
  *
  * Level inherits QObject to make i18n of error messages easier
  */

class Level :  public QObject
{
	Q_OBJECT

	// Constructors/Destructors
	//
public:

	/**
	 * Empty Constructor
	 */
	Level ( );

	/**
	 * Empty Destructor
	 */
	virtual ~Level ( );

public:
	// Public accessor methods
	//

	/// returns the Level's title
	virtual QString getName ( ) const
		{ return theLevelName.result(); }

	World* getTheWorldPtr(void)
		{ return theWorldPtr; }

	/** open file containing a level definition, parse it, build the Level
	 *  if run into a <toolbox> section, keep a reference to that so the toolbox
	 *  can benefit later...
	 *
	 * @param aFileName file to parse and populate Level with.
	 * @return empty string is returned if loading was successful, otherwise
	 *			the return will contain the i18n'ed error message
	 */
	QString load(const QString& aFileName);

	/** save the Level to a file
	 *  the file name must be unique - overwriting is not allowed here
	 *
	 * @param aFileName file to serialize the Level/World to.
	 * @return false if saving failed - error message will be set.
	 */
	bool save(const QString& aFileName);

	/// @returns the path to the file that describes the current level
	static QString getPathToLevelFile(void);

	/// @returns the name of the file that describes the current level
	static QString getLevelFileName(void);

	/// @returns a reference to the QDomNode containing the toolbox description
	const QDomNode& getToolboxDomNode(void) const
	{ return theToolboxDomNode; }

	/// sets the name of the file that describes the current level
	void setLevelFileName(const QString& aName);

protected:
	// TODO FIXME: move these two somewhere else so we no longer need the #include for QDomElement here
	void addTextElement(QDomElement aParent, const QString& anElementName, const QString& aText) const;
	void addTextElement(QDomElement aParent, const QString& anElementName, const LocalString& anLS) const;
	void addAbstractObject(QDomElement aParent, const AbstractObject& anObjectRef) const;

private:
	World* theWorldPtr;

	LocalString theLevelName;
	QString theLevelAuthor;
	QString theLevelLicense;
	LocalString theLevelDescription;
	QString theLevelDate;

	/** populated during load(), this DomNode contains the contents for the toolbox
	 *  if no load() has happened, this is empty.
	 */
	QDomNode theToolboxDomNode;

	friend class SaveLevelInfo;
	friend class LevelInfoDialog;
	friend class EditLevelProperties;

	// prevent copy constructor / assignment operator
	Level(const Level&);
	const Level& operator= (const Level&);
};

#endif // LEVEL_H