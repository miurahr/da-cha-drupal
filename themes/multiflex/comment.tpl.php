<div class="content<?php echo $layoutcode ?>-container line-box"> 
  <div class="content<?php echo $layoutcode ?>-container-1col"> 
    <div class="comment<?php if ($comment->status == COMMENT_NOT_PUBLISHED) print ' comment-unpublished'; ?>">
      <?php if ($picture) {
	    print $picture;
	    } ?>
      <div class="content-title-noshade-size2"><?php print $title; ?></div><?php if ($new != '') { ?><span class="new"><?php print $new; ?></span><?php } ?>
      <div class="content-subtitle-noshade-size1"><?php print $submitted; ?></div>
      <div class="content"><?php print $content; ?></div>
      <div class="links">&raquo; <?php print $links; ?></div>
    </div>
  </div>
</div>
