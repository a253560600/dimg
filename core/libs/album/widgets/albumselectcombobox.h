/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2009-05-09
 * Description : A combo box for selecting albums
 *
 * Copyright (C) 2008-2011 by Marcel Wiesweg <marcel dot wiesweg at gmx dot de>
 * Copyright (C) 2010-2011 by Andi Clemens <andi dot clemens at gmail dot com>
 * Copyright (C) 2012-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef DIGIKAM_ALBUM_SELECT_COMBO_BOX_H
#define DIGIKAM_ALBUM_SELECT_COMBO_BOX_H

// Local includes

#include "comboboxutilities.h"

class QSortFilterProxyModel;

namespace Digikam
{

class AlbumFilterModel;
class AbstractCheckableAlbumModel;

class AlbumSelectComboBox : public TreeViewLineEditComboBox
{
    Q_OBJECT

public:

    explicit AlbumSelectComboBox(QWidget* const parent = nullptr);
    ~AlbumSelectComboBox()                              override;

    /**
     * Once after creation, call one of these three methods.
     * Use the first one if you want a standard combo box for PAlbums and
     *  the second one for tags, while the third allows you to provide
     *  custom source and filter models.
     *  The first two also set a default noSelectionText. Customize afterwards if required.
     */
    void setDefaultAlbumModel();
    void setDefaultTagModel();
    void setModel(AbstractCheckableAlbumModel* model,
                  AlbumFilterModel* filterModel = nullptr);

    /**
     * Enable checkboxes next to the items. Default: true
     */
    void setCheckable(bool checkable);
    bool isCheckable() const;

    /**
     * Enable closing when an item was activated (clicked). Default: false.
     */
    void setCloseOnActivate(bool close);

    /**
     * If the box is checkable, enable showing a resume a la "3 Albums checked"
     * in the combo box text. Default: True
     */
    void setShowCheckStateSummary(bool show);

    /**
     * Sets the text that is used to describe the state when no album is selected.
     * This may be something like "Any album" or "No tag selected".
     * Depends on the default line edit implementation of TreeViewLineEditComboBox.
     */
    void setNoSelectionText(const QString& text);

    /**
     * Returns the source model. Retrieve selection information from here.
     */
    AbstractCheckableAlbumModel* model() const;

    /**
     * Return the filter model in use.
     */
    QSortFilterProxyModel* filterModel() const;

public Q_SLOTS:

    void hidePopup()                                    override;

    /**
     * Updates the text describing the selection ("3 Albums selected").
     * Can be overridden to customize the default text.
     */
    virtual void updateText();

protected:

    void installView(QAbstractItemView* view = nullptr) override;

private:

    class Private;
    Private* const d;
};

// ------------------------------------------------------------------------------------

class AbstractAlbumTreeView;
class AlbumModel;
class AlbumTreeView;
class CheckableAlbumFilterModel;
class TagPropertiesFilterModel;
class TagModel;
class TagTreeView;

class AbstractAlbumTreeViewSelectComboBox : public AlbumSelectComboBox
{
    Q_OBJECT

public:

    /**
     * Abstract class.
     * This is an AlbumSelectComboBox which installs an AlbumTreeView,
     * not a plain QTreeView, as view.
     */

    explicit AbstractAlbumTreeViewSelectComboBox(QWidget* const parent = nullptr);

    /**
     * Set a tree view created by you instead of creating a default view
     * (in the subclasses).
     * Only takes effect before calling setModel.
     */
    void setTreeView(AbstractAlbumTreeView* const treeView);

    /**
     * Enables a context menu which contains options to
     * check or uncheck groups of albums, given you have a checkable model.
     * Call this method after setModel().
     */
    void addCheckUncheckContextMenuActions();

protected:

    void installView(QAbstractItemView* view = nullptr) override;
    void sendViewportEventToView(QEvent* e)             override;

protected:

    AbstractAlbumTreeView* m_treeView;
};

// ------------------------------------------------------------------------------------

class AlbumTreeViewSelectComboBox : public AbstractAlbumTreeViewSelectComboBox
{
    Q_OBJECT

public:

    explicit AlbumTreeViewSelectComboBox(QWidget* const parent = nullptr);

    void setDefaultModel();
    void setModel(AlbumModel* model,
                  CheckableAlbumFilterModel* filterModel = nullptr);
    AlbumTreeView* view() const;
};

// ------------------------------------------------------------------------------------

class TagTreeViewSelectComboBox : public AbstractAlbumTreeViewSelectComboBox
{
    Q_OBJECT

public:

    explicit TagTreeViewSelectComboBox(QWidget* const parent = nullptr);

    void setDefaultModel();
    void setModel(TagModel* model,
                  TagPropertiesFilterModel* filteredModel = nullptr,
                  CheckableAlbumFilterModel* filterModel = nullptr);
    TagTreeView* view() const;
};

} // namespace Digikam

#endif // DIGIKAM_ALBUM_SELECT_COMBO_BOX_H
