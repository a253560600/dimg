/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2011-01-24
 * Description : Tags Action Manager
 *
 * Copyright (C) 2011-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#ifndef DIGIKAM_TAGS_ACTION_MNGR_H
#define DIGIKAM_TAGS_ACTION_MNGR_H

// Qt includes

#include <QObject>
#include <QWidget>

class KActionCollection;

namespace Digikam
{

class Album;
class ImageTagChangeset;

class TagsActionMngr : public QObject
{
    Q_OBJECT

public:

    explicit TagsActionMngr(QWidget* const parent);
    ~TagsActionMngr() override;

    /**
     * Register all tag actions to collections managed with keyboard shortcuts.
     * Because Tags shortcuts are stored in database this method must be called after
     * database initialization and after that all root window instances have been created.
     */
    void registerTagsActionCollections();

    /**
     * Register all labels actions to collections managed with keyboard shortcuts.
     * Unlike tags actions, labels shortcuts are stored in XML GUI file of each root windows,
     * to be able to customize it through KDE keyboards shortcuts config panel.
     * This method must be called before to DXmlGuiWindow::createGUI(), typically
     * when window actions are registered to ActionCollection instance.
     */
    void registerLabelsActions(KActionCollection* const ac);

    void registerActionsToWidget(QWidget* const wdg);

    /**
     * Return the list of whole action collections managed.
     */
    QList<KActionCollection*> actionCollections()   const;

    /**
     * Updates the shortcut action for a tag. Call this when a shortcut was
     * added, removed or changed.
     */
    void updateTagShortcut(int tagId, const QKeySequence& ks, bool delAction = true);

    QString ratingShortcutPrefix()                  const;
    QString tagShortcutPrefix()                     const;
    QString pickShortcutPrefix()                    const;
    QString colorShortcutPrefix()                   const;

    static TagsActionMngr* defaultManager();

Q_SIGNALS:

    void signalShortcutPressed(const QString& shortcut, int val);

private Q_SLOTS:

    /**
     * Removes the shortcut actions associated with a tag.
     */
    void slotAlbumDeleted(Album*);

    /**
     * Wrapper around windows to run relevant code about keyboard shortcuts in GUI.
     */
    void slotAssignFromShortcut();

    /**
     * Called by config shortcuts dialog, when user change action properties.
     */
    void slotTagActionChanged();

private:

    bool createTagActionShortcut(int tagId);
    bool removeTagActionShortcut(int tagId, bool delAction = true);

    bool createRatingActionShortcut(KActionCollection* const ac, int rating);
    bool createPickLabelActionShortcut(KActionCollection* const ac, int pickId);
    bool createColorLabelActionShortcut(KActionCollection* const ac, int colorId);

private:

    static TagsActionMngr* m_defaultManager;

    class Private;
    Private* const d;
};

} // namespace Digikam

#endif // DIGIKAM_TAGS_ACTION_MNGR_H
