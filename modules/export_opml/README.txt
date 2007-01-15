export_opml module
==================

Description:
------------
        
This module allows the export of outlines of Drupal books, in OPML
format.  This format allows outlines to be edited in an external OPML
aware Outline editor.


Version:
________

This version of export_opml depends on book.module v1.334 or later.
(CVS HEAD Nov 30, 2005)


Bugs:
_____

The way in which the generated XML is supplied to the user is
unfriendly.  Perhaps a better approach would be to take the user to a
page with a generated link to download the requested XML.

This exports a pretty bare-bones OPML; I'm sure this could be improved
considerably with little effort.  Suggestions, offers of help, or
offers of funding gladly accepted.

There may be other bugs; please report issues via Drupal's issue
tracker: http://drupal.org/project/issues


History
-------

This module packages functionality which was originally part of Drupal
book.module (a core module).

2005-11-27: First (alpha) release.


Author
-------

Djun Kim (puregin [at] puregin [dot] org)
