<?php
/* $Id */

/**
 * @ingroup hooks
 * @{
 */

/**
 * @name Filemanager Hooks
 *
 * These hooks are defined by the file api, modules that use the file api will
 * use these hooks.
 */

/**
 * Define file areas this module uses.
 *
 * This hook allows file API using modules to define new file areas which
 * will have their own size limits.
 *
 * This hook should return an array of associative arrays containing area
 * information
 *
 * The following fields must be defined in the area information array
 *
 * -area - This is the name of the area used programtically in the module.
 * -name - This is the display name of the area for site admins.
 * -description - This is a description for site admins of what this area holds.
 *
 */
function hook_filemanager_areas() {
  return array(
    array(
      'area' => 'general',
      'name' => t('General'),
      'description' => t('All files not specifically stored in another area.')
    )
  );
}

/**
 * Determine whether this private download is accessible by the user.
 *
 * When a private file is requested the file api will call all modules
 * passing them the file.  The first module to respond will be authoritative
 * and no further modules will be queried.
 *
 * The file api will default access to FALSE, except for general where it will
 * be TRUE, if no modules return a value.
 *
 * This hook should not return anything or one of three values:
 *
 * - No Return - indicates this module does not know about this file
 * - FALSE - Indicates this user should be denied access.
 * - TRUE - Indicates this user should be given access.
 * - Array - This array contains headers that will given to the client
 */
function hook_filemanager_download($file) {
  if ($file->area == 'myarea') {
    return TRUE;
  }
}