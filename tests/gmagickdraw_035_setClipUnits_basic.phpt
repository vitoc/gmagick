--TEST--
Test GmagickDraw, setClipUnits
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$backgroundColor = 'rgb(225, 225, 225)';
$strokeColor = 'rgb(0, 0, 0)';
$fillColor = 'DodgerBlue2';

function setClipUnits($strokeColor, $fillColor, $backgroundColor) {

    $draw = new \GmagickDraw();

    $draw->setStrokeColor($strokeColor);
    $draw->setFillColor($fillColor);
    $draw->setStrokeOpacity(1);
    $draw->setStrokeWidth(2);
    $clipPathName = 'testClipPath';
    $draw->setClipUnits(\Gmagick::RESOLUTION_PIXELSPERINCH);
    $draw->pushClipPath($clipPathName);
    $draw->rectangle(0, 0, 250, 250);
    $draw->popClipPath();
    $draw->setClipPath($clipPathName);
    $clipUnits = $draw->getClipUnits();
    if ($clipUnits !== \Gmagick::RESOLUTION_PIXELSPERINCH) {
        echo "Failed to get correct clipUnits $clipRule != \Gmagick::RESOLUTION_PIXELSPERINCH \n";
    }

    //RESOLUTION_PIXELSPERINCH
    //RESOLUTION_PIXELSPERCENTIMETER

    $draw->rectangle(200, 200, 300, 300);
    $imagick = new \Gmagick();
    $imagick->newImage(500, 500, $backgroundColor);
    $imagick->setImageFormat("png");

    $imagick->drawImage($draw);

    $bytes = $imagick->getImageBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
}

setClipUnits($strokeColor, $fillColor, $backgroundColor) ;
echo "Ok";
?>
--EXPECTF--
Ok