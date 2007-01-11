<!-- Text container -->
<div class="content<?php echo $layoutcode ?>-container line-box">
  <div class="content<?php echo $layoutcode ?>-container-1col">
   <p class="content-title-shade-size3 bg-blue07 box-on">&nbsp;</p>
   <p class="content-title-shade-size3 bg-blue03 txt-white"><a href="<?php print $node_url ?> " title="<?php print $title ?>"><?php print $title ?></a></p>
   <?php
      // If you need a subtitle, try this:
      //  echo'<p class="content-subtitle-noshade-size1">a subtitle here</p>' 
      ?>
   <div class="content-txtbox-shade">
     
     <span class="taxonomy"><?php print $terms?></span>
     <?php print ($content) ?>
     <?php if ($links): ?>
     <p class="readmore align-right"><?php print $links ?></p>    
     <?php endif ; ?>
   </div>
  </div>
</div>
