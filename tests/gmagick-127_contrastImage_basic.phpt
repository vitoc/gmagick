--TEST--
Test Gmagick, contrastImage
--SKIPIF--
<?php
$imageMagickRequiredVersion=0x675;
require_once(dirname(__FILE__) . '/skipif.inc');
?>
--FILE--
<?php

$contrastType = 1;

function contrastImage($contrastType) {
    $gmagick = new \Gmagick("magick:logo");
    if ($contrastType != 2) {
        $gmagick->contrastImage($contrastType);
    }

    $bytes = $gmagick->getImageBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
}

contrastImage($contrastType) ;
echo "Ok";
?>
--EXPECTF--
Ok