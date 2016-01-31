--TEST--
Test Gmagick, radialBlurImage
--SKIPIF--
<?php

die("skip - not implemented by GraphicsMagick");

//checkClassMethods('Gmagick', array('radialBlurImage'));
?>
--FILE--
<?php


function radialBlurImage() {
    $gmagick = new \Gmagick("magick:logo");
    $gmagick->radialBlurImage(3);
    $gmagick->radialBlurImage(5);
    $gmagick->radialBlurImage(7);
    $bytes = $gmagick->getImageBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
}

radialBlurImage() ;
echo "Ok";
?>
--EXPECTF--
Ok