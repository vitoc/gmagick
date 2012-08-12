--TEST--
Set, get filename
--SKIPIF--
<?php
/* $Id: gmagick-035-set_getfilename.phpt 295011 2010-02-13 17:06:23Z mkoppanen $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
echo $gm->setFilename("magickrose.png")->getFilename();
?>
--EXPECTF--
magickrose.png