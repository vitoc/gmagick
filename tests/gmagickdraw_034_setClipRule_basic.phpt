--TEST--
Test GmagickDraw, setClipRule
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$backgroundColor = 'rgb(225, 225, 225)';
$strokeColor = 'rgb(0, 0, 0)';
$fillColor = 'DodgerBlue2';

function setClipRule($strokeColor, $fillColor, $backgroundColor) {

    $draw = new \GmagickDraw();

    $draw->setStrokeColor($strokeColor);
    $draw->setFillColor($fillColor);
    $draw->setStrokeOpacity(1);
    $draw->setStrokeWidth(2);
    //\Gmagick::FILLRULE_EVENODD
    //\Gmagick::FILLRULE_NONZERO

    $clipPathName = 'testClipPath';
    $draw->pushClipPath($clipPathName);
    $draw->setClipRule(\Gmagick::FILLRULE_EVENODD);

    $draw->rectangle(0, 0, 300, 500);
    $draw->rectangle(200, 0, 500, 500);
    $draw->popClipPath();
    $draw->setClipPath($clipPathName);
    $draw->rectangle(200, 200, 300, 300);
    
    $clipRule = $draw->getClipRule();
    if ($clipRule !== \Gmagick::FILLRULE_EVENODD) {
        echo "Failed to get correct clipRule $clipRule != \Gmagick::FILLRULE_EVENODD \n";
    }

    $gmagick = new \Gmagick();
    $gmagick->newImage(500, 500, $backgroundColor);
    $gmagick->setImageFormat("png");

    $gmagick->drawImage($draw);

    $bytes = $gmagick->getImageBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
}

setClipRule($strokeColor, $fillColor, $backgroundColor) ;
echo "Ok";
?>
--EXPECTF--
Ok