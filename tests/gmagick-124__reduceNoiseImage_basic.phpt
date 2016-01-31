--TEST--
Test Gmagick, reduceNoiseImage
--SKIPIF--
<?php
$imageMagickRequiredVersion=0x675;
require_once(dirname(__FILE__) . '/skipif.inc');
checkClassMethods('Gmagick', array('reduceNoiseImage'));
?>
--FILE--
<?php

$reduceNoise = 5;

function reduceNoiseImage($reduceNoise) {
    $gmagick = new \Gmagick("magick:logo");
    @$gmagick->reduceNoiseImage($reduceNoise);
    $bytes = $gmagick->getImageBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
}

reduceNoiseImage($reduceNoise) ;
echo "Ok";
?>
--EXPECTF--
Ok