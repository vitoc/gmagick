--TEST--
Test Gmagick, waveImage
--SKIPIF--
<?php
$imageMagickRequiredVersion=0x675;
require_once(dirname(__FILE__) . '/skipif.inc');
?>
--FILE--
<?php

$amplitude = 5;
$length = 20;

function waveImage($amplitude, $length) {
    $gmagick = new \Gmagick("magick:logo");
    $gmagick->waveImage($amplitude, $length);
    $bytes = $gmagick->getImageBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
}

waveImage($amplitude, $length) ;
echo "Ok";
?>
--EXPECTF--
Ok