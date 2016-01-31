--TEST--
Test Gmagick, whiteThresholdImage
--SKIPIF--
<?php
$imageMagickRequiredVersion=0x675;
require_once(dirname(__FILE__) . '/skipif.inc');
?>
--FILE--
<?php

$color = 'rgb(127, 127, 127)';

function whiteThresholdImage($color) {
    $gmagick = new \Gmagick("magick:logo");
    $gmagick->whiteThresholdImage($color);
    $bytes = $gmagick->getImageBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
}

whiteThresholdImage($color) ;
echo "Ok";
?>
--EXPECTF--
Ok