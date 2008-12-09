<?php
// $Id: search-theme-form.tpl.php,v 1.3.2.6 2008/06/16 04:23:46 hswong3i Exp $

  global $user;

  if (!$user->uid) {
    $message .= '<div>'. t('Please <a href="@login">Login</a> or <a href="@register">Register</a>', array('@login' => url('user/login'), '@register' => url('user/register'))) .'</div>';
    $message .= '<div>'. t('<a href="@password">Request New Password</a>', array('@password' => url('user/password'))) .'</div>';
  }
  else {
    $message .= '<div>'. t('Welcome @user', array('@user' => $user->name)) .'</div>';
    $message .= '<div>'. t('<a href="@view">View</a> | <a href="@edit">Edit</a> | <a href="@logout">Logout</a>', array('@view' => url('user/' . $user->uid), '@edit' => url('user/' . $user->uid . '/edit'), '@logout' => url('logout'))) .'</div>';
  }
?>

<div class="welcome"><?php print $message ?></div>
<div class="search-form"><div class="top left"><div class="top right"><div class="bottom left"><div class="bottom right">
  <?php print $search_form ?>
  <div class="advanced"><a href="<?php print url('search') ?>"><?php print t('Advanced search') ?></a></div>
</div></div></div></div></div>
