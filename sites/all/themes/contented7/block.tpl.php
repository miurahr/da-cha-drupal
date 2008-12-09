<?php
// $Id: block.tpl.php,v 1.8.2.2 2008/04/27 08:39:57 hswong3i Exp $
?>
<div id="block-<?php print $block->module .'-'. $block->delta ?>" class="block block-<?php print $block->module ?> block-<?php print $block_id ?>">
  <?php if ($block->subject): ?><h2><?php print $block->subject ?></h2><?php endif; ?>
  <div class="content"><?php print $block->content ?></div>
</div>
