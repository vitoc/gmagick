--TEST--
Test Gmagick, adaptiveThresholdImage
--SKIPIF--
<?php
$imageMagickRequiredVersion=0x675;
require_once(dirname(__FILE__) . '/skipif.inc'); 
?>
--FILE--
<?php

$width = 50;
$height = 20;
$adaptiveOffset = 0.125;

function adaptiveThresholdImage($width, $height, $adaptiveOffset) {
    $gmagick = new \Gmagick('magick:rose');
    $adaptiveOffsetQuantum = intval($adaptiveOffset * \Gmagick::QUANTUM);
    $gmagick->adaptiveThresholdImage($width, $height, $adaptiveOffsetQuantum);
    $bytes = $gmagick->getImageBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
}

adaptiveThresholdImage($width, $height, $adaptiveOffset) ;
echo "Ok";
?>
--EXPECTF--
Ok