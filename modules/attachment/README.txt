Description
-----------
This module is an alternative to Drupal's included upload module. It uses the
filemanager module to allow a unique namespace per node and support large
number of files. In addition this module allows you to give each attachment a
title and description.

Features
--------
* Unique namespace per node - This allows each node to have it's own file list
  completely separate from other nodes. This prevents your users from getting
  confusing file renames when someone else has already uploaded a file with the
  same name.

* Thread safe - This module prevents users from accidentally seeing other users
  uploads upload issue

* Disk space control - Prevents users from filling up your disk during node
  creation. Standard upload module relies on session timeouts to clear out
  unused files. Attachment does clean up before each upload attempt.
