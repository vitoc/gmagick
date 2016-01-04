--TEST--
Test Gmagick, haldClutImage
--SKIPIF--
<?php
$imageMagickRequiredVersion=0x675;
require_once(dirname(__FILE__) . '/skipif.inc');
?>
--FILE--
<?php


function haldClutImage() {
    $gmagick = new \Gmagick("magick:logo");
    $gmagickPalette = new \Gmagick(__DIR__."/hald_8.png");

    //$gmagickPalette->sepiatoneImage(55);
    $gmagick->haldClutImage($gmagickPalette);
    $bytes = $gmagick->getImageBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
}

haldClutImage() ;
echo "Ok";
?>
--EXPECTF--
Ok