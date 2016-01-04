--TEST--
Test Gmagick, colorizeImage
--SKIPIF--
<?php
$imageMagickRequiredVersion=0x675;
require_once(dirname(__FILE__) . '/skipif.inc');
?>
--FILE--
<?php

$color = 'rgb(127, 127, 127)';
$opacity = 100;

function colorizeImage($color, $opacity) {
    $gmagick = new \Gmagick("magick:logo");
    $opacity = $opacity / 255.0;
    $opacityColor = new \GmagickPixel("rgba(0, 0, 0, $opacity)");
    $gmagick->colorizeImage($color, $opacityColor);
    $bytes = $gmagick->getImageBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
}

colorizeImage($color, $opacity) ;
echo "Ok";
?>
--EXPECTF--
Ok