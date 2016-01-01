--TEST--
Test GmagickDraw, setFontFamily
--SKIPIF--
<?php
$imageMagickRequiredVersion=0x675;
require_once(dirname(__FILE__) . '/skipif.inc');
?>
--FILE--
<?php

$backgroundColor = 'rgb(225, 225, 225)';
$strokeColor = 'rgb(0, 0, 0)';
$fillColor = 'DodgerBlue2';

function setFontFamily($fillColor, $strokeColor, $backgroundColor) {

    $draw = new \GmagickDraw();

    $strokeColor = new \GmagickPixel($strokeColor);
    $fillColor = new \GmagickPixel($fillColor);

    $draw->setStrokeColor($strokeColor);
    $draw->setFillColor($fillColor);
    //TODO - actually use setFontFamily
    $draw->setStrokeWidth(2);

    $draw->setFontSize(24);
    $draw->annotate(50, 50, "Lorem Ipsum!");

    $draw->setFontSize(36);
    $draw->annotate(50, 100, "Lorem Ipsum!");

    $draw->setFontSize(48);
    $draw->annotate(50, 150, "Lorem Ipsum!");

    $draw->setFontSize(60);
    $draw->annotate(50, 200, "Lorem Ipsum!");

    $draw->setFontSize(72);
    $draw->annotate(50, 250, "Lorem Ipsum!");

    $gmagick = new \Gmagick();
    $gmagick->newImage(500, 500, $backgroundColor);
    $gmagick->setImageFormat("png");
    $gmagick->drawImage($draw);

    $bytes = $gmagick->getImageBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
}

setFontFamily($fillColor, $strokeColor, $backgroundColor) ;
echo "Ok";
?>
--EXPECTF--
Ok