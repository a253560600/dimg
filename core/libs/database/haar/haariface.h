/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2003-01-17
 * Description : Haar Database interface
 *
 * Copyright (C) 2016-2018 by Mario Frank <mario dot frank at uni minus potsdam dot de>
 * Copyright (C) 2003      by Ricardo Niederberger Cabral <nieder at mail dot ru>
 * Copyright (C) 2009-2021 by Gilles Caulier <caulier dot gilles at gmail dot com>
 * Copyright (C) 2009-2013 by Marcel Wiesweg <marcel dot wiesweg at gmx dot de>
 * Copyright (C) 2009-2011 by Andi Clemens <andi dot clemens at gmail dot com>
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

#ifndef DIGIKAM_HAAR_IFACE_H
#define DIGIKAM_HAAR_IFACE_H

// Qt includes

#include <QSet>
#include <QString>
#include <QMap>
#include <QList>

// Local includes

#include "haar.h"
#include "digikam_export.h"

class QImage;

namespace Digikam
{

class DImg;
class ItemInfo;

class HaarProgressObserver
{
public:

    HaarProgressObserver()                                       = default;
    virtual ~HaarProgressObserver()                              = default;

    virtual void imageProcessed()                                = 0;
    virtual bool isCanceled()
    {
        return false;
    };

private:

    Q_DISABLE_COPY(HaarProgressObserver)
};

// --------------------------------------------------------------------------

class DIGIKAM_DATABASE_EXPORT HaarIface
{

public:

    enum SketchType
    {
        ScannedSketch   = 0,
        HanddrawnSketch = 1
    };

    enum DuplicatesSearchRestrictions
    {
        None            = 0,
        SameAlbum       = 1,
        DifferentAlbum  = 2
    };

    enum AlbumTagRelation
    {
        NoMix           = 0,
        Union           = 1,
        Intersection    = 2,
        AlbumExclusive  = 3,
        TagExclusive    = 4
    };

    using DuplicatesResultsMap = QMap<qlonglong, QPair<double, QList<qlonglong> > >;

public:

    explicit HaarIface();
    explicit HaarIface(const QSet<qlonglong>& images2Scan);
    ~HaarIface();

    static int preferredSize();

    /**
     * Adds an image to the index in the database.
     */
    bool indexImage(const QString& filename);
    bool indexImage(const QString& filename, const QImage& image);
    bool indexImage(const QString& filename, const DImg& image);
    bool indexImage(qlonglong imageid, const QImage& image);
    bool indexImage(qlonglong imageid, const DImg& image);

    QMap<qlonglong, double> bestMatchesForSignature(const QString& signature,
                                                    const QList<int>& targetAlbums,
                                                    int numberOfResults = 20,
                                                    SketchType type = ScannedSketch);

    /**
     * Searches the database for the best matches for the specified query image.
     * All matches with a similarity in a given threshold interval are returned.
     * The threshold is in the range requiredPercentage..maximumPercentage.
     */
    QPair<double, QMap<qlonglong, double> > bestMatchesForImageWithThreshold(
        qlonglong imageid,
        double requiredPercentage,
        double maximumPercentage,
        const QList<int>& targetAlbums,
        DuplicatesSearchRestrictions searchResultRestriction = DuplicatesSearchRestrictions::None,
        SketchType type = ScannedSketch
    );

    /**
     * Searches the database for the best matches for the specified query image.
     * All matches with a similarity in a given threshold interval are returned.
     * The threshold is in the range requiredPercentage..maximumPercentage.
     */
    QPair<double, QMap<qlonglong, double> > bestMatchesForImageWithThreshold(
        const QString& imagePath,
        double requiredPercentage,
        double maximumPercentage,
        const QList<int>& targetAlbums,
        DuplicatesSearchRestrictions searchResultRestriction = DuplicatesSearchRestrictions::None,
        SketchType type = ScannedSketch
    );

    /**
     * Calculates the Haar signature, bring it in a form as stored in the DB,
     * and encode it to Ascii data. Can be used for bestMatchesForSignature.
     */
    QString signatureAsText(const QImage& image);

    /**
     * Checks whether the image with the given imageId fulfills all restrictions given in
     * targetAlbums and in respect to searchResultRestriction.
     */
    bool fulfillsRestrictions(qlonglong imageId,
                              int albumId,
                              qlonglong originalImageId,
                              int originalAlbumId,
                              const QList<int>& targetAlbums,
                              DuplicatesSearchRestrictions searchResultRestriction);

    /**
     * For a given signature, find out the highest and lowest possible score
     * that any other signature could reach, compared to the given signature.
     */
    void getBestAndWorstPossibleScore(Haar::SignatureData* const querySig,
                                      SketchType type,
                                      double* const lowestAndBestScore,
                                      double* const highestAndWorstScore);

    /**
     * Fill a map of duplicates images found over a list of images to scan.
     * For each map item, the result values is list of candidate images which are duplicates of the key image.
     * All images are referenced by id from database.
     * The threshold is in the range 0..1, with 1 meaning identical signature.
     */
    DuplicatesResultsMap findDuplicates(
        const QSet<qlonglong>& images2Scan,
        const QSet<qlonglong>::const_iterator& rangeBegin,
        const QSet<qlonglong>::const_iterator& rangeEnd,
        double requiredPercentage,
        double maximumPercentage,
        DuplicatesSearchRestrictions searchResultRestriction = DuplicatesSearchRestrictions::None,
        HaarProgressObserver* const observer = nullptr
    );

    /**
     * Collects all images from the given album and tag ids according to their relation.
     */
    static QSet<qlonglong> imagesFromAlbumsAndTags(const QList<int>& albums2Scan,
                                                   const QList<int>& tags2Scan,
                                                   AlbumTagRelation relation);

    /**
     * This method rebuilds the given SAlbums using the given results.
     * @param results Map of duplicates images found over a list of images.
     */
    static void rebuildDuplicatesAlbums(const DuplicatesResultsMap& results, bool isAlbumUpdate);

    /**
     * Retrieve the Haar signature from database using image id.
     * Return true if item signature exist else false.
     */
    bool retrieveSignatureFromDB(qlonglong imageid, Haar::SignatureData& sig);

    /**
     * Give a list of albumRoots to which the search shall be limited.
     * Calling with an empty list will disable filtering.
     */
    void setAlbumRootsToSearch(const QList<int>& albumRootIds);
    void setAlbumRootsToSearch(const QSet<int>& albumRootIds);

    /**
     * This method loads a QImage from the given filename.
     * @param filename the name of the file (path)
     * @return A QImage, non-null on success.
     */
    QImage loadQImage(const QString& filename);

private:

    bool   indexImage(qlonglong imageid);

    /**
     * This method writes the search results to the SearchXml structure.
     * @param searchResults The results to write as XML.
     */
    static QMap<QString, QString> writeSAlbumQueries(const DuplicatesResultsMap& searchResults);

    QMultiMap<double, qlonglong> bestMatches(Haar::SignatureData* const data,
                                             int numberOfResults,
                                             const QList<int>& targetAlbums,
                                             SketchType type);

    QPair<double, QMap<qlonglong, double> > bestMatchesWithThreshold(qlonglong imageid,
                                                                     Haar::SignatureData* const querySig,
                                                                     double requiredPercentage,
                                                                     double maximumPercentage,
                                                                     const QList<int>& targetAlbums,
                                                                     DuplicatesSearchRestrictions searchResultRestriction,
                                                                     SketchType type);

    /**
     * This function generates the scores for all images in database.
     * @param data The signature of the original image for score calculation.
     * @param type The type of the sketch, e.g. scanned.
     * @param searchResultRestriction restrictions to apply to the generated map, i.e. None (default), same album or different album.
     * @param originalImageId the id of the original image to compare to other images. -1 is only used for sketch search.
     * @param albumId The album which images must or must not belong to (depending on searchResultRestriction).
     * @return The map of image ids and scores which fulfill the restrictions, if any.
     */
    QMap<qlonglong, double> searchDatabase(Haar::SignatureData* const data,
                                           SketchType type,
                                           const QList<int>& targetAlbums,
                                           DuplicatesSearchRestrictions searchResultRestriction = None,
                                           qlonglong originalImageId = -1,
                                           int albumId = -1);

    double calculateScore(const Haar::SignatureData& querySig,
                          const Haar::SignatureData& targetSig,
                          Haar::Weights& weights,
                          std::reference_wrapper<Haar::SignatureMap>* const queryMaps);

private:

    // Disable
    HaarIface(const HaarIface&)            = delete;
    HaarIface& operator=(const HaarIface&) = delete;

private:

    class Private;
    Private* const d;
};

} // namespace Digikam

#endif // DIGIKAM_HAAR_IFACE_H
