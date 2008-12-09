  <div class="node<?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
    <?php if ($picture) {
      print $picture;
    }?>
    <?php if ($page == 0) { ?><span class="taxonomy"><?php print $terms?></span>
    <br>
    <h1 class="title"><a href="<?php print $node_url?>"><?php print $title?></a></h1><?php }; ?>
    <?php if ($submitted): ?>
    <span class="date-node"><?php print t('!date — !username', array('!username' => theme('username', $node), '!date' => format_date($node->created))); ?></span>
  <?php endif; ?>
    <div class="content"><?php print $content?></div>
    <?php if ($links) { ?><div class="links"><?php print $links?></div><?php }; ?>
	<hr>
  </div>
