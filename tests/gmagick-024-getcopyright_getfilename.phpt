--TEST--
Test getCopyright, getFileName
--SKIPIF--
<?php
/* $Id: gmagick-024-getcopyright_getfilename.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$gm->getCopyright();
$gm->getFilename();
echo "ok";
?>
--EXPECTF--
ok