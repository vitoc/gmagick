--TEST--
Test Gmagick, shaveImage
--SKIPIF--
<?php
$imageMagickRequiredVersion=0x675;
require_once(dirname(__FILE__) . '/skipif.inc');
?>
--FILE--
<?php


function shaveImage() {
    $gmagick = new \Gmagick("magick:logo");
    $gmagick->shaveImage(100, 50);
    $bytes = $gmagick->getImageBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
}

shaveImage() ;
echo "Ok";
?>
--EXPECTF--
Ok