--TEST--
Test Gmagick, blackThresholdImage
--SKIPIF--
<?php
$imageMagickRequiredVersion=0x675;
require_once(dirname(__FILE__) . '/skipif.inc');
?>
--FILE--
<?php

$thresholdColor = 'rgb(127, 127, 127)';

function blackThresholdImage($thresholdColor) {
    $gmagick = new \Gmagick("magick:logo");
    $gmagick->blackthresholdimage($thresholdColor);
    $bytes = $gmagick->getImageBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
}

blackThresholdImage($thresholdColor) ;
echo "Ok";
?>
--EXPECTF--
Ok