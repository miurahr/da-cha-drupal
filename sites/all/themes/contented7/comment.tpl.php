<?php
// $Id: comment.tpl.php,v 1.8.2.5 2008/06/12 03:16:57 hswong3i Exp $
?>
<div class="comment<?php print ($comment->new) ? ' comment-new' : ''; print ' '. $status ?> clear-block">
  <h3 class="title"><?php print $title ?></h3>
  <div class="meta meta-header">
    <?php if ($picture): print $picture; endif; ?>
    <?php if ($submitted): ?><div class="submitted"><?php print $submitted ?></div><?php endif; ?>
  </div>
  <div class="content">
    <?php print $content ?>
    <?php if ($signature): ?><div class="user-signature clear-block"><?php print $signature ?></div><?php endif; ?>
    <div class="meta meta-footer">
      <?php if ($links): ?><?php print $links ?><?php endif; ?>
    </div>
  </div>
</div>
