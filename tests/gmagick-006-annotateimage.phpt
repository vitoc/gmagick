--TEST--
Test annotate image
--SKIPIF--
<?php
/* $Id: gmagick-006-annotateimage.phpt 294865 2010-02-10 23:50:11Z mkoppanen $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new GMagick();
$gd = new GMagickDraw();
$gm->read("magick:rose");

$fonts = $gm->queryFonts();

if (!empty($fonts))
    $gd->setFont($fonts[0]);
else
    $gd->setFont(dirname(__FILE__) .'/Vera.ttf');

$gm->annotateImage($gd, 5, 15, 0, 'Test Text');
echo "ok";
?>
--EXPECT--
ok
