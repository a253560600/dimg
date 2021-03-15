<?xml version="1.0" encoding="UTF-8" ?>

<!--
 * ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2009-02-01
 * Description : A rounded corner theme for the digiKam html gallery tool.
 *
 * Copyright (C) 2009 by Franz Dietrich <enaut dot w at googlemail dot com>
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
 * ============================================================
 -->

<!-- Documentatione of the parameters:

titlebar - The String that will appear in the titlebar.
thumbnailsPerPage - The maximum number of thumbnails per page.
homepage - The name of the Homepage you want to go back to.
homepageUrl - The Url to the Homepage.

Colors:
background - The Background of the page.
thumbBorderColor - The border of the thumbnails.
navigationColor - The background of the navigation box.
urlColor - The color ofactive urls.
content-bgc - The color of the contentbox.
listBackground - The Color of the Thumb list.
-->
 
<!DOCTYPE stylesheet [
<!ENTITY raquo "&#187;">
<!ENTITY auml "&#x00e4;">
<!ENTITY Uuml "&#220;">
<!ENTITY uuml "&#252;">
<!ENTITY nbsp "&#160;">
<!ENTITY middot "&#183;">
]>


<xsl:transform version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:exsl="http://exslt.org/common"
	extension-element-prefixes="exsl">
	<xsl:output
			method="xml"
			doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN"
			doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"
			version="1.0"
			media-type="text/html"
			encoding="UTF-8"
			indent="yes" />
			
	<!-- Setting some variables to keep the theme flexible.-->
	<xsl:variable name="cssname" select='"layout.css"' /><!-- caution! that file will be overwritten! -->
	<xsl:variable name="styledir" select='"simplerounded/"' /><!-- This can usually be any directory available. It has to contain: the css specified above, the niftyCube.js and the niftyCorners.css -->
	<xsl:variable name="keywords" select='"generated gallery images"' />
	<xsl:variable name="description" select='"a gallery generated by digiKam"' />
			
	<!-- Setting some variables to keep the code more readable. -->
	<xsl:variable name="numberOfCollections" select="count(collections/collection)" />
	<xsl:variable name="numberOfListPages" select="number(ceiling($numberOfCollections div $thumbnailsPerPage))" />
	
	<!-- Generation of the Headder. -->
	<xsl:template name="head">
		<xsl:param name="relPath" /><!-- the path to the root of the generated galery -->
		<head>
			<meta
				http-equiv="Content-Type"
				content="text/html; charset=UTF-8" />
			<meta
				http-equiv="Content-Script-Type"
				content="text/javascript" />
			<meta
				http-equiv="Content-Style-Type"
				content="text/css" />
			<meta
				name="description">
				<xsl:attribute name="content"> <xsl:value-of select="$description" /></xsl:attribute>
			</meta>
			<meta
				name="keywords">
				<xsl:attribute name="content"> <xsl:value-of select="$keywords" /></xsl:attribute>
			</meta>
			<link rel="stylesheet" type="text/css" href="{$relPath}{$styledir}layout.css" />
			<link rel="stylesheet" type="text/css" href="{$relPath}{$styledir}niftyCorners.css" />
			<title>
				<xsl:value-of select="$titlebar"/>
				&nbsp;
				<xsl:value-of select="fileName" />
				<xsl:value-of select="substring(title, 0, string-length(title) - 3)"/>
			</title>
			<script
				type="text/javascript"
				src="{$relPath}{$styledir}niftycube.js"></script>
			<script
				type="text/javascript">
					window.onload = function()
					{
						Nifty("div.header", "big transparent");
						Nifty("ul.menu a", "same-height transparent");
						Nifty("ul.menu", "big transparent");
						Nifty("div.round", "big transparent");
						Nifty("div.thumb li", "same-height big transparent");
						Nifty("div.thumb", "big fixed-height transparent");
					}
			</script>
		</head>
	</xsl:template>
	
	
<!-- Decide, wether there are more than one collections or not. -->			
	<xsl:template match="/">
		<xsl:choose>
			<xsl:when test="$numberOfCollections = 1">
				<!-- DEBUG <xsl:value-of select="$numberOfCollections" /> -->
				<xsl:for-each select="collections/collection[number(1)]">
					<xsl:call-template name="collectionOverviewPage">
						<xsl:with-param name="workingDir" select="concat(//collection[1]/fileName, '/')"/>
						<xsl:with-param name="currentPage" select="0" />
						<xsl:with-param name="relPath" select="''" />
						<xsl:with-param name="collectionPageCount" select="ceiling(count(//image) div $thumbnailsPerPage)" />
					</xsl:call-template>
				</xsl:for-each>
			</xsl:when>
			<xsl:otherwise>
				<xsl:call-template name="collectionListPage">
					<xsl:with-param name="currentPage" select="number(0)" />
				</xsl:call-template>
			</xsl:otherwise>
		</xsl:choose>
		<exsl:document
			href="{$styledir}{$cssname}"
			method="text"
			version="1.0"
			encoding="UTF-8"
			media-type="text/css"
			indent="yes">
			<xsl:call-template name="cssstyle" />
		</exsl:document>
	</xsl:template>
	
<!-- This template generates in an recursive fashion the overviewpages for each collection. If one page is full it calls itself again to create a new page. -->
	<xsl:template name="collectionOverviewPage">
		<xsl:param name="workingDir" /> <!-- The directory where the images are stored relative to the working directory. -->
		<xsl:param name="relPath" /> <!-- The directions to the root of the gallery. -->
		<xsl:param name="currentPage" /> <!-- The current Page -->
		<xsl:param name="collectionPageCount" /> <!-- The total count of pages -->
		<html>
			<!-- Include the headder -->
			<xsl:call-template name="head">
				<xsl:with-param name="relPath" select="$relPath" />
			</xsl:call-template>
			
			<body id="collectionPage">
				<div class="round" id="content">
					<h1><xsl:value-of select="name" /></h1>
					<div class="thumb" id="mainpage">
						<ul>
							<!-- Call the single thumbnail generation template. -->
							<xsl:call-template name="collectionOverviewListItem">
								<xsl:with-param name="iterator" select="1" />
								<xsl:with-param name="workingDir" select='$workingDir' />
								<xsl:with-param name="offset" select="number($thumbnailsPerPage * $currentPage)" />
							</xsl:call-template>
						</ul>
						<div class="clear">&nbsp;</div>
					</div>
					<!-- Generate the Navigation below the thumblist. -->
					<div class="round" id="imageNavigationBox">
						<div id="block"> <!-- A workaround for the IE boxmodell. -->
							<p>
								<xsl:if test="$homepage != ''">
									<a href="{$homepageUrl}"><xsl:value-of select="$homepage" /></a>
									&raquo;
								</xsl:if>
								<xsl:if test="$numberOfCollections != 1">
									<a href="../index.html"><xsl:value-of select="$i18nCollectionList" /></a>
								&raquo;
								</xsl:if>
								<a class="inactive" href="#"><xsl:value-of select="name" /></a>
							</p>
							<xsl:if test="$collectionPageCount != 1">
								<p>
									<!-- The "Previous" link -->
									<xsl:choose>
										<xsl:when test="$currentPage = 0">
											<a class="inactive" href="#"><xsl:value-of select="$i18nPrevious" /></a>
										</xsl:when>
										<xsl:when test="$currentPage = 1">
											<a href="index.html"><xsl:value-of select="$i18nPrevious" /></a>
										</xsl:when>
										<xsl:otherwise>
											<a href="{fileName}Page{$currentPage}.html"><xsl:value-of select="$i18nPrevious" /></a>
										</xsl:otherwise>
									</xsl:choose>
									&middot;
									<!-- The pagenumber links. -->
									<xsl:call-template name="pageLink">
										<xsl:with-param name="currentPosition" select="number(1)" />
										<xsl:with-param name="collectionPageCount" select="$collectionPageCount" />
										<xsl:with-param name="baseName" select="fileName" />
										<xsl:with-param name="currentPage" select="$currentPage" />
									</xsl:call-template>
									<!-- The "Next" link.-->
									<xsl:choose>
										<xsl:when test="$currentPage = ($collectionPageCount - 1)">
											<a class="inactive" href="#"><xsl:value-of select="$i18nNext" /></a>
										</xsl:when>
										<xsl:otherwise>
											<a href="{fileName}Page{$currentPage + 2}.html"><xsl:value-of select="$i18nNext" /></a>
										</xsl:otherwise>
									</xsl:choose>
								</p>
							</xsl:if>
						</div> <!-- End of IE borderworkaround -->
					</div><!-- End of imageNavigationBox -->
				</div><!-- End of content. -->
			</body>
		</html>
		<!-- recursive call for the next page. -->
		<xsl:if test="$currentPage &lt; ($collectionPageCount - 1)">
			<exsl:document
				href="{fileName}Page{$currentPage + 2}.html"
				method="xml"
				version="1.0"
				encoding="UTF-8"
				doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN"
				doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"
				media-type="text/html" 
				indent="yes">
				<xsl:call-template name="collectionOverviewPage">
						<xsl:with-param name="workingDir" select="$workingDir"/>
						<xsl:with-param name="relPath" select="$relPath"/>
						<xsl:with-param name="currentPage" select="number($currentPage + 1)" />
						<xsl:with-param name="collectionPageCount" select="$collectionPageCount" />
				</xsl:call-template>
			</exsl:document>
		</xsl:if>
	</xsl:template>

<!-- Generate the thumbnail lists by adding one item and call itself recursively. -->
	<xsl:template name="collectionOverviewListItem">
		<xsl:param name="iterator" />
		<xsl:param name="workingDir" /><!-- The location of the files -->
		<xsl:param name="offset" /><!-- The number of thumbnails that has already been worked on. -->
		
		<xsl:if test="number($iterator) &lt; number($thumbnailsPerPage + 1)">
			<xsl:for-each select="image[number($iterator + $offset)]">
				<li>
					<a href='{$workingDir}{full/@fileName}.html'>
						<img src="{$workingDir}{thumbnail/@fileName}" width="{thumbnail/@width}" height="{thumbnail/@height}" alt="{full/description}"/>
					</a>
				</li>
				<exsl:document
					href='{$workingDir}{full/@fileName}.html'
					method="xml"
					version="1.0"
					encoding="UTF-8"
					doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN"
					doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"
					media-type="text/html"
					indent="yes">
					<xsl:call-template name="imagePage">
						<xsl:with-param name="iterator" select="number($iterator + $offset)" />
					</xsl:call-template>
				</exsl:document>
			</xsl:for-each>
			<!-- The recursion -->
			<xsl:call-template name="collectionOverviewListItem">
				<xsl:with-param name="iterator" select="$iterator + 1" />
					<xsl:with-param name="workingDir" select="$workingDir" />
					<xsl:with-param name="offset" select="$offset" />
			</xsl:call-template>
		</xsl:if>
	</xsl:template>

<!-- Generation of the pagenumbers for each Page. -->
	<xsl:template name="pageLink">
		<xsl:param name="currentPosition" /><!-- The current position iterator. -->
		<xsl:param name="collectionPageCount" /><!-- The total num of pages -->
		<xsl:param name="currentPage" /><!-- The current page. -->
		<xsl:param name="baseName" /> <!-- The basic name for the pages. -->
		<xsl:choose>
			<xsl:when test="$currentPosition = ($currentPage + 1)">
				<a class="inactive" href="#"><xsl:value-of select="$currentPosition"/></a>
				&middot;
			</xsl:when>
			<xsl:when test="$currentPosition = 1">
				<a href="index.html"><xsl:value-of select="$currentPosition"/></a>
				&middot;
			</xsl:when>
			<xsl:otherwise>
				<a href="{$baseName}Page{$currentPosition}.html"><xsl:value-of select="$currentPosition"/></a>
				&middot;
			</xsl:otherwise>
		</xsl:choose>
		<xsl:if test="$currentPosition &lt; $collectionPageCount">
			<xsl:call-template name="pageLink">
				<xsl:with-param name="currentPosition" select="number($currentPosition + 1)" />
				<xsl:with-param name="collectionPageCount" select="$collectionPageCount" />
				<xsl:with-param name="currentPage" select="$currentPage" />
				<xsl:with-param name="baseName" select="$baseName" />
			</xsl:call-template>
		</xsl:if>
	</xsl:template>
	

<!-- ############################ The Template to gererate every single image page. ############################ -->
	<xsl:template name="imagePage">
		<xsl:param name="iterator" /><!-- The psitoin to generate the navigation. -->
		<html>
			<!-- Include the headder information -->
			<xsl:call-template name="head">
				<xsl:with-param name="relPath" select="'../'" />
			</xsl:call-template>
			
			<body id="imagePage">
				<div class="round" id="content">
					<div class="round" id="image">
						<!-- Include the Image. -->
						<img src="{full/@fileName}" width="{full/@width}" height="{full/@height}" alt="{full/description}"/>
						<xsl:if test="description != ''"><!-- Check for original file -->
							<p><!-- Add the comment. -->
								<xsl:value-of select="description"/>
							</p>
						</xsl:if>
						<xsl:if test="original/@fileName != ''"><!-- Check for original file -->
							<p>
								<a href="{original/@fileName}"><xsl:value-of select="$i18nOriginalImage"/></a>
								(<xsl:value-of select="original/@width"/>x<xsl:value-of select="original/@height"/>)
							</p>
						</xsl:if>
					</div>
					<div class="round" id="imageNavigationBox"><!-- Create the navigation -->
						<div id="block"> <!-- A workaround for the IE boxmodell. -->
							<p><!-- Create the path -->
								<xsl:if test="$homepage != ''">
									<a href="{$homepageUrl}"><xsl:value-of select="$homepage" /></a>
									&raquo;
								</xsl:if>
								<xsl:choose>
									<xsl:when test="$numberOfCollections &gt; 1">
											<a href="../index.html">
												<xsl:value-of select="$i18nCollectionList"/>
											</a>
											&raquo;
											<a href="index.html">
												<xsl:value-of select="../name" />
											</a>
									</xsl:when>
									<xsl:otherwise>
											<a	href="../index.html">
											<xsl:value-of select="../name"/>
											</a>
									</xsl:otherwise>
								</xsl:choose>
								&raquo;
								<a href="#" class="inactive"><xsl:value-of select="substring(title, 0, string-length(title) - 3)"/></a>
							</p>
							<!-- create the navigation bar -->
							<p>
								<xsl:choose>
									<xsl:when test="$iterator &gt; 1">
											<a href="{preceding-sibling::image[position()=1]/full/@fileName}.html">
												<xsl:value-of select="$i18nPrevious" />
											</a>
									</xsl:when>
									<xsl:otherwise>
											<a href="#" class="inactive">
												<xsl:value-of select="$i18nPrevious" />
											</a>
									</xsl:otherwise>
								</xsl:choose>
								&nbsp;
								<a href="#" class="inactive">(<xsl:value-of select="$iterator"/>/<xsl:value-of select="count(../image)"/>)</a>
								&nbsp;
								<xsl:choose>
									<xsl:when test="$iterator &lt; count(../image)">
											<a href="{following-sibling::image[position()=1]/full/@fileName}.html">
												<xsl:value-of select="$i18nNext"/>
											</a>
									</xsl:when>
									<xsl:otherwise>
											<a href="#" class="inactive">
												<xsl:value-of select="$i18nNext"/>
											</a>
									</xsl:otherwise>
								</xsl:choose>
							</p>
						</div>
					</div>
				</div>
			</body>
		</html>
	</xsl:template>

<!-- ############################ Collections list - the collection thumbnailpage ############################ -->
	<xsl:template name="collectionListPage">
		<xsl:param name="currentPage" /><!-- The position to generate the navigation. -->
		
		<xsl:variable name="offset" select="number($thumbnailsPerPage  * $currentPage)"/> <!-- The offset of the current page. -->
		
				<html>
					<!-- Include the headder information -->
					<xsl:call-template name="head">
						<xsl:with-param name="relPath" select="''" />
					</xsl:call-template>
					
					<body id="collectionPage">
						<div class="round" id="content">
							<h1><xsl:value-of select="$i18nCollectionList" /></h1>
							<div class="thumb" id="mainpage">
								<ul>
									<!-- Call the single thumbnail generation template. -->
									<xsl:call-template name="collectionListItem">
										<xsl:with-param name="iterator" select="1" />
										<xsl:with-param name="offset" select="$offset" />
									</xsl:call-template>
								</ul>
								<div class="clear">&nbsp;</div>
							</div>
							<xsl:if test="$numberOfListPages != 1">
								<!-- The navigation. -->
								<div class="round" id="imageNavigationBox">
									<div id="block"> <!-- A workaround for the IE boxmodell. -->
										<xsl:if test="$homepageUrl != ''">
											<p><!-- Create the path -->
												<a href="{$homepageUrl}"><xsl:value-of select="$homepage" /></a>
												&raquo;
												<a class="inactive" href="#"><xsl:value-of select="$i18nCollectionList" /></a>
											</p>
										</xsl:if>
										<p>
											<!-- The "Previous" link -->
											<xsl:choose>
												<xsl:when test="$currentPage = 0">
													<a class="inactive" href="#"><xsl:value-of select="$i18nPrevious" /></a>
												</xsl:when>
												<xsl:when test="$currentPage = 1">
													<a href="index.html"><xsl:value-of select="$i18nPrevious" /></a>
												</xsl:when>
												<xsl:otherwise>
													<a href="{$i18nCollectionList}Page{$currentPage}.html"><xsl:value-of select="$i18nPrevious" /></a>
												</xsl:otherwise>
											</xsl:choose>
											&middot;
											<!-- The pagenumber links. -->
											<xsl:call-template name="pageLink">
												<xsl:with-param name="currentPosition" select="number(1)" />
												<xsl:with-param name="collectionPageCount" select="$numberOfListPages" />
												<xsl:with-param name="baseName" select="$i18nCollectionList" />
												<xsl:with-param name="currentPage" select="$currentPage" />
											</xsl:call-template>
											<!-- The "Next" link.-->
											<xsl:choose>
												<xsl:when test="$currentPage = ($numberOfListPages - 1)">
													<a class="inactive" href="#"><xsl:value-of select="$i18nNext" /></a>
												</xsl:when>
												<xsl:otherwise>
													<a href="{$i18nCollectionList}Page{$currentPage + 2}.html"><xsl:value-of select="$i18nNext" /></a>
												</xsl:otherwise>
											</xsl:choose>
										</p>
									</div>
								</div>
							</xsl:if>
						</div>
					</body>
				</html>
			<!-- Recursion call of this template. -->
			<xsl:if test="($currentPage + 1) &lt; $numberOfListPages">
				<exsl:document
					href='{$i18nCollectionList}Page{number($currentPage + 2)}.html'
					method="xml"
					version="1.0"
					encoding="UTF-8"
					doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN"
					doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"
					media-type="text/html"
					indent="yes">
					<xsl:call-template name="collectionListPage">
						<xsl:with-param name="currentPage" select="number($currentPage + 1)" />
					</xsl:call-template>
				</exsl:document>
			</xsl:if>
	</xsl:template>
	
	<!-- The thumnails for each single collection. -->
	<xsl:template name="collectionListItem">
		<xsl:param name="iterator" />
		<xsl:param name="offset" /><!-- The number of thumbnails that has already been worked on. -->

			<xsl:for-each select="/collections/collection[$iterator + $offset]">
				<li>
					<a href='{fileName}/index.html'>
						<img src="{fileName}/{image[1]/thumbnail/@fileName}" width="{image[1]/thumbnail/@width}" height="{image[1]/thumbnail/@height}" alt="{image[1]/full/description}"/>
						<br />
						<xsl:value-of select="name" />
					</a>
				</li>
				<exsl:document
					href='{fileName}/index.html'
					method="xml"
					version="1.0"
					encoding="UTF-8"
					doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN"
					doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"
					media-type="text/html"
					indent="yes">
					<xsl:call-template name="collectionOverviewPage">
						<xsl:with-param name="workingDir" select="''" />
						<xsl:with-param name="relPath" select="'../'" />
						<xsl:with-param name="currentPage" select="0" />
						<xsl:with-param name="collectionPageCount" select="ceiling(count(image) div $thumbnailsPerPage)" />
					</xsl:call-template>
				</exsl:document>
			</xsl:for-each>

		<!-- The recursion -->
		<xsl:if test="($iterator &lt; $thumbnailsPerPage) and ($iterator &lt;= $numberOfCollections)">
			<xsl:call-template name="collectionListItem">
				<xsl:with-param name="iterator" select="$iterator + 1" />
				<xsl:with-param name="offset" select="$offset" />
			</xsl:call-template>
		</xsl:if>
	</xsl:template>
	
	<!-- Generate the stylesheet -->
	<xsl:template name="cssstyle">@CHARSET "UTF-8";
	
	* {
	    margin:0;
	    padding:0;
	}
	
	body {
		padding: 20px;
		background-color: <xsl:value-of select="$background" />;
	}
	
	div.clear {
		clear: both;
		height: 0;
		width: 0;
	}
	
	
	/**
	 * Headdings
	 */
	h1,h2,h3,h4,h5,h6 {
		font-variant: small-caps;
		text-decoration: underline;
		font-weight: bold;
	}
	
	h1 {
		font-size: 28px;
		padding: 0 0 15px 0;
	}
	
	#imageNavigationBox {
		font-size: 20px;
		margin: 7px 0 0 0;
		padding: 10px;
		text-align: center;
		font-variant: small-caps;
		font-weight: bold;
		background-color: <xsl:value-of select="$navigationColor" />;
	}
	
	#block{
		display: block;
		width: 100%;
	}
	
	#imageNavigationBox a{
		color: <xsl:value-of select="$urlColor" />;
	}
	
	#imageNavigationBox a.inactive{
		color: #000;
	}
	
	/**
	 * Texts
	 */
	p {
		padding: 5px 0;
	}
	
	p:first-letter {
		font-size: 1.3em;
	}
	
	/**
	 * Divboxes
	 */
	div.round, #content {
		margin: 7px 0;
		padding: 25px 25px 10px 25px;
		font-size: 18px;
		text-align: center;
		background-color: <xsl:value-of select="$content-bgc" />;
	}
	
	/**
	 * Images
	 */
	img {
		border: none;
	}
	
	div.thumb {
		background-color: <xsl:value-of select="$listBackground" />;
		margin: 7px 0;
		padding: 10px;
	}
	
	div.thumb li {
		display: block;
		background-color:<xsl:value-of select="$thumbBorderColor" />;
		padding: 12px;
		margin: 4px;
		width: <xsl:value-of select="//image[1]/thumbnail/@width" />px;
		_width:<xsl:value-of select="((//image[1]/thumbnail/@width) + 28)" />px;
		list-style: none;
	}
	
	div#mainpage {
		text-align: center;
	}
	
	div#mainpage li {
		float: left;
		display: block;
		font-size: 15px;
	}
	
	div.thumb a:link {
		color: <xsl:value-of select="$urlColor" />;
		text-decoration: none;
	}
	
	div.thumb a:visited {
		color: <xsl:value-of select="$urlColor" />;
		text-decoration: none;
	}
	</xsl:template>
			
</xsl:transform>
