--TEST--
Test GmagickDraw, setTextAntialias
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

function setTextAntialias($fillColor, $backgroundColor) {

    $draw = new \GmagickDraw();
    $draw->setStrokeColor('none');
    $draw->setFillColor($fillColor);
    $draw->setStrokeWidth(1);
    $draw->setFontSize(32);
    $draw->setTextAntialias(false);
    $draw->annotate(5, 30, "Lorem Ipsum!");
    $draw->setTextAntialias(true);
    $draw->annotate(5, 65, "Lorem Ipsum!");

    $currentValue = $draw->getTextAntialias();

    if ($currentValue !== true) {
        echo "Failed to get textAntiAlias setting, which should be true\n";
        var_dump($currentValue);
    }

    $gmagick = new \Gmagick();
    $gmagick->newImage(220, 80, $backgroundColor);
    $gmagick->setImageFormat("png");
    $gmagick->drawImage($draw);

    //Scale the image so that people can see the aliasing.
    $gmagick->scaleImage(220 * 6, 80 * 6);
    $gmagick->cropImage(640, 480, 0, 0);

    $bytes = $gmagick->getImageBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
}

setTextAntialias($fillColor, $backgroundColor);
echo "Ok";
?>
--EXPECTF--
Ok