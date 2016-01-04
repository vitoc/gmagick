--TEST--
Test Gmagick, sharpenImage
--SKIPIF--
<?php
$imageMagickRequiredVersion=0x675;
require_once(dirname(__FILE__) . '/skipif.inc');
?>
--FILE--
<?php

$radius = 5;
$sigma = 1;
$channel = Gmagick::CHANNEL_DEFAULT;

function sharpenImage($radius, $sigma, $channel) {
    $gmagick = new \Gmagick("magick:logo");
    $gmagick->sharpenimage($radius, $sigma, $channel);
    $bytes = $gmagick->getImageBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
}

sharpenImage($radius, $sigma, $channel) ;
echo "Ok";
?>
--EXPECTF--
Ok