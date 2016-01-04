--TEST--
Test filling thumbnail with color
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc');

$v = Gmagick::getVersion();
if ($v['versionNumber'] < 0x632)
	die ('skip too old ImageMagick');

if ($v ['versionNumber'] >= 0x660 && $v ['versionNumber'] < 0x670)
	die ('skip seems to be broken in this version of ImageMagick');
?>
--FILE--
<?php

$gmagick = new Gmagick("magick:logo");
$gmagick->setImageBackgroundColor("pink");
$gmagick->thumbnailImage(200, 200, true);


echo "ok"
?>
--EXPECT--

ok