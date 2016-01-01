--TEST--
Test GmagickDraw, setFontStretch
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

function setFontStretch($fillColor, $strokeColor, $backgroundColor) {

    $draw = new \GmagickDraw();

    $draw->setStrokeColor($strokeColor);
    $draw->setFillColor($fillColor);
    $draw->setStrokeWidth(2);
    $draw->setFontSize(36);

    $fontStretchTypes = array(
        \Gmagick::STRETCH_ULTRACONDENSED,
        \Gmagick::STRETCH_CONDENSED,
        \Gmagick::STRETCH_SEMICONDENSED,
        \Gmagick::STRETCH_SEMIEXPANDED,
        \Gmagick::STRETCH_EXPANDED,
        \Gmagick::STRETCH_EXTRAEXPANDED,
        \Gmagick::STRETCH_ULTRAEXPANDED,
        \Gmagick::STRETCH_ANY
    );

    $offset = 0;
    foreach ($fontStretchTypes as $fontStretch) {
        $draw->setFontStretch($fontStretch);
        $draw->annotate(50, 75 + $offset, "Lorem Ipsum!");
        $offset += 50;
        
        $currentFontStretch = $draw->setFontStretch($fontStretch);
        
        if ($currentFontStretch != $fontStretch) {
            echo "Failed to get correct fontStretch $currentFontStretch != $fontStretch \n";
        }
    }

    $gmagick = new \Gmagick();
    $gmagick->newImage(500, 500, $backgroundColor);
    $gmagick->setImageFormat("png");
    $gmagick->drawImage($draw);

    $bytes = $gmagick->getImageBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
}

setFontStretch($fillColor, $strokeColor, $backgroundColor) ;
echo "Ok";
?>
--EXPECTF--
Ok